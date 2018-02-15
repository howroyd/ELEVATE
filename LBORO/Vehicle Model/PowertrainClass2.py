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
        self._battery = BatteryClass.Battery_Model()
        self._bms     = BatteryManagementClass.BatteryManagementClass()
        self._esc     = EscClass.ESC()
        self._motor   = MotorClass.MotorClass()
        self._wheel   = [ WheelClass.WheelClass(),   # FL
                          WheelClass.WheelClass(),   # FR
                          WheelClass.WheelClass(),   # RL
                          WheelClass.WheelClass() ]  # RR
        self._ctrl_speed = ControlBusClass.ControlBusClass()
        self._ctrl_motor = ControllerClass.ControllerClass()
        self._ctrl_brake = ControllerClass.ControllerClass()

    def update(self, dt):
        # Get wheel speeds and torques, pass to axle then motor
        self._axle.wheel_data = [self._wheel[0].data, self._wheel[1].data]
        self._motor.data = self._axle.shaft_data

        # Get battery availability, pass to BMS & ESC
        self._bms.set_battery_available(self._battery.battery_data)
        self._esc.set_battery_available(self._bms.available)
        
        # Parse control signal from speed controller
        ctrl_sig_motor, ctrl_sig_brake = self._parse_control_signal()

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
        self._axle.rotation = self._motor.rotation
        self._wheel[2].rotation = self._axle.rotation_left
        self._wheel[3].rotation = self._axle.rotation_right

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
        
    def parse_control_signal(self):
        pass

    