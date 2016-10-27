import BrakesClass

class WheelClass(object):
    """description of class"""


# Instance constructor
    def __init__(self, brake, kwargs):
        self._brake = brake
        self._wheel_speed = 0.0
        self._force = 0.0
        self._motor_torque_in = 0.0
        self._wheel_diameter = kwargs['wheel_diameter']
        self._road_drag = 0.0
        return

    def update(self, dt):
        self._brake.update(dt)
        self._force = (self._motor_torque_in-self._brake.torque-self._road_drag)/self._wheel_diameter
        # TODO wheel speed, road drag??
        return

    @property 
    def force(self):
        return self._force

    @property
    def brake_value(self):
        return self._brake.value
    @brake_value.setter
    def brake_value(self, value):
        self._brake.value = max(min(value, 255), 0) # 0-255

    @property
    def brake_torque(self):
        return self._brake.torque

    @property
    def motor_torque(self):
        return self._motor_torque_in
    @motor_torque.setter
    def motor_torque(self, torque):
        self._motor_torque_in = torque

    @property
    def speed(self):
        return self._wheel_speed