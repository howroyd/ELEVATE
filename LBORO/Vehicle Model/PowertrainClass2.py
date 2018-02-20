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
    def __init__(self):
        self._axle    = AxleClass.AxleClass()
        self._battery = BatteryClass.BatteryClass()
        self._bms     = BatteryManagementClass.BatteryManagementClass()
        self._esc     = EscClass.ESC()
        self._motor   = MotorClass.MotorClass()
        self._wheel   = [ WheelClass.WheelClass(),   # FL
                          WheelClass.WheelClass(),   # FR
                          WheelClass.WheelClass(),   # RL
                          WheelClass.WheelClass() ]  # RR
        self._ctrl_speed = ControllerClass.ControllerClass(1, 0.01, 0.002, 'signed')
        self._ctrl_motor = ControllerClass.ControllerClass(1, 0.01, 0.002, 'unsigned')
        self._ctrl_brake = ControllerClass.ControllerClass(1, 0.01, 0.002, 'unsigned')
        self._speed_set = 0.0
        self._speed_now = 0.0

    def update(self, dt):
        # Get wheel speeds and torques, pass to axle then motor
        self._axle.wheel_data = [self._wheel[0].data, self._wheel[1].data]
        self._motor.data = self._axle.shaft_data

        # Get battery availability, pass to BMS & ESC
        self._bms.set_battery_data(self._battery.battery_data)
        self._esc.set_input_power(self._bms.availability)
        
        # Parse control signal from speed controller
        ctrl_sig_motor, ctrl_sig_brake = self._parse_control_signal(dt)

        # Update independent motor and brake controllers
        self._ctrl_motor.update(dt, ctrl_sig_motor)
        self._ctrl_brake.update(dt, ctrl_sig_brake)
    
        # Send motor control signal to ESC
        self._esc.control_signal = self._ctrl_motor.error

        # Send brake control signal to wheels
        for ptr in self._wheel:
            ptr.brake_control_sig = self._ctrl_brake.error

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
        
    def parse_control_signal(self, dt):
        dv = self._speed_set - self._speed_now
        self._ctrl_speed.update(dt, dv)

        if self._ctrl_motor.value <= 0.0:
            # Motor is off
            if self._ctrl_brake.value > 0.0:
                # Brake is on
                self._ctrl_motor.reset()
                self._ctrl_motor.update(dt, None)
                self._ctrl_brake.update(dt, abs(self._ctrl_speed.value))
            else:
                # Brake is off
                if self._ctrl_speed.value >= 0.0:
                    # Apply motor
                    self._ctrl_motor.update(dt, self._ctrl_speed.value) # Apply motor
                    self._ctrl_brake.update(dt, abs(self._ctrl_speed.value)) # Apply brake (if 
                else:
                    # Apply brake
                    self._ctrl_motor.update(dt, self._ctrl_speed.value) # Apply motor
                    self._ctrl_brake.update(dt, abs(self._ctrl_speed.value)) # Apply brake (if 
        else:
            self._ctrl_motor.update(dt, self._ctrl_speed.value)
            self._ctrl_brake.reset()
            self._ctrl_brake.update(dt, None)

        self._ctrl_motor.value = self._ctrl_speed.error # TODO
        self._ctrl_brake.value = self._ctrl_speed.error # TODO
        sig_motor = self._ctrl_motor.error
        sig_brake = self._ctrl_brake.error
        return sig_motor, sig_brake

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
    