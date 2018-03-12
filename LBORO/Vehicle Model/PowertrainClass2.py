import AxleClass
import BatteryClass
import BatteryManagementClass
import ControlBusClass
import ControllerClass
import ElectricityClass
import EscClass
import MotorClass
import WheelClass

# Powertrain controller

class PowertrainControllerClass(object):
    def __init__(self, kwargs):
        self._axle    = AxleClass.AxleClass()
        self._battery = BatteryClass.BatteryClass(dict(i_max_charge=(kwargs.get('batt_p_max')*0.5/kwargs.get('batt_v_min')),
                                                    i_max_discharge=kwargs.get('batt_i_max'),
                                                    p_max=kwargs.get('batt_p_max'),
                                                    batt_kwh=kwargs.get('batt_kwh')))
        self._bms     = BatteryManagementClass.BatteryManagementClass(kwargs)
        self._esc     = EscClass.ESC(kwargs)
        self._motor   = MotorClass.MotorClass(kwargs)
        self._wheel   = [ WheelClass.WheelClass(kwargs),   # FL
                          WheelClass.WheelClass(kwargs),   # FR
                          WheelClass.WheelClass(kwargs),   # RL
                          WheelClass.WheelClass(kwargs) ]  # RR
        self._ctrl_speed = ControllerClass.ControllerClass(1, 0.01, 0.002, 'signed')
        self._ctrl_motor = ControllerClass.ControllerClass(1, 0.01, 0.002, 'unsigned')
        self._ctrl_brake = ControllerClass.ControllerClass(1, 0.01, 0.002, 'unsigned')
        self._speed_set = 0.0
        self._speed_now = 0.0

    def update(self, dt):
        # Get wheel speeds and torques, pass to axle then motor
        self._axle.wheel_data = [self._wheel[0].rotational_data, self._wheel[1].rotational_data]
        self._motor.rotational_data = self._axle.rotational_data

        # Get battery availability, pass to BMS & ESC
        self._bms.set_battery_data(self._battery.battery_data)
        self._esc.set_input_power(self._bms.availability)
        
        # Parse control signal from speed controller
        self._parse_control_signal(dt)
    
        # Send motor control signal to ESC
        self._esc.control_signal = self._ctrl_motor.value

        # Send brake control signal to wheels
        for ptr in self._wheel:
            ptr.brake_control_sig = self._ctrl_brake.value

        # Give (or receive) electricity to (or from) motor
        self._motor.exchange_electricity(self._esc.output)

        # Update axle torque and speed, pass to drive wheels
        self._axle.data = self._motor.data
        self._wheel[2].axle_torque = self._axle.wheel_data[0]
        self._wheel[3].axle_torque = self._axle.wheel_data[1]

        # Update time dependancies (energy calcs)
        self._axle.update(dt)
        self._battery.update(dt)
        self._bms.update(dt)
        self._ctrl_brake.update(dt)
        self._ctrl_motor.update(dt)
        self._esc.update(dt)
        self._motor.update(dt)
        for ptr in self._wheel:
            ptr.update(dt)
        
    def _parse_control_signal(self, dt):
        dv = self._speed_set - self._speed_now
        self._ctrl_speed.update(dt, dv)

        if self._ctrl_speed.value <= 0.0:
            # Trying to decellerate
            self._ctrl_motor.update(dt, self._ctrl_speed.value)

            if self._ctrl_motor.at_minimum:
                # Motor fully off or in full regen, apply brakes
                self._ctrl_brake.update(dt, -1.0 * self._ctrl_speed.value)
            else:
                # In regen or coasting, no brakes applied
                self._ctrl_brake.reset()
                self._ctrl_brake.update(dt)
        else:
            # Trying to accelerate
            self._ctrl_brake.update(dt, -1.0 * self._ctrl_speed.value)

            if self._ctrl_brake.at_minimum:
                # Brake fully off, power motor
                self._ctrl_motor.update(dt, self._ctrl_speed.value)
            else:
                # Brake on but trying to speed up
                self._ctrl_motor.update(dt)


    @property
    def set_speed(self):
        return self._speed_set
    @set_speed.setter
    def set_speed(self, speed):
        self._speed_set = speed

    @property
    def vehicle_speed(self):
        return self._speed_now
    @vehicle_speed.setter
    def vehicle_speed(self, speed):
        self._speed_now = speed
        for ptr in self._wheel:
            ptr._wheel.set_wheel_speed = speed
    
    @property
    def force(self):
        return sum(ptr.force for ptr in self._wheel)  # TODO minus road drag