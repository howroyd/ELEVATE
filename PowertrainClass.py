import MotorClass
import WheelClass
import ElectricalManagementClass
import battery_sw

class PowertrainClass(object):
    """description of class"""

    def __init__(self, kwargs):
        self._battery   = kwargs['battery'] if 'battery' in kwargs else battery_sw.Battery_Model(**kwargs) 
        
        self._motor = MotorClass.MotorClass(kwargs)

        kwargs.update(battery = self._battery)
        kwargs.update(motor = self._motor)

        self._wheel_front_left = WheelClass.WheelClass(kwargs)
        self._wheel_front_right = WheelClass.WheelClass(kwargs)
        self._wheel_rear_left = WheelClass.WheelClass(kwargs)
        self._wheel_rear_right = WheelClass.WheelClass(kwargs)

        kwargs.update(wheel_front_left = self._wheel_front_left,
                        wheel_front_right = self._wheel_front_right,
                        wheel_rear_left = self._wheel_rear_left,
                        wheel_rear_right = self._wheel_rear_right)

        self._wheel_front_right._brake._temperature = 20.0

        self._current_speed = 0.0
        self._target_speed  = 0.0
        self._mass = 1521.0
        self._dv = 0.0

    def update(self, drag):
        self._battery.update()

        self._dv = self._target_speed - self._current_speed

        self._motor.update(self._dv)

        if self._motor.get_torque() <= 0.0 and self._dv <= -10.0:
            # Apply brakes
            self._wheel_front_left.update(brakes=True)
            self._wheel_front_right.update(brakes=True)
            self._wheel_rear_left.update(brakes=True)
            self._wheel_rear_right.update(brakes=True)
        else:
            # Accelerate, cruise or decelerate
            self._wheel_front_left.update(shaft_torque=self._motor.get_torque()/2)
            self._wheel_front_right.update(shaft_torque=self._motor.get_torque()/2)
            self._wheel_rear_left.update()
            self._wheel_rear_right.update()

        total_force = self._wheel_front_left.get_force() + self._wheel_front_right.get_force() + self._wheel_rear_left.get_force() + self._wheel_rear_right.get_force()

        accn = total_force / self._mass

        self._wheel_front_left.set_speed(self._wheel_front_left.get_speed() + accn*1.0)    

        self._current_speed = self._wheel_front_left.get_speed()
        

    def set_speed(self, speed):
        self._target_speed = speed
        

    def get_speed(self) -> float:
        return self._current_speed