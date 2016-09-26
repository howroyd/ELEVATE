import BrakesClass
import TractionControlClass

class WheelClass(object):
    """description of class"""


# Instance constructor
    def __init__(self, kwargs):
        self._v_set     = kwargs['v']     if 'v'     in kwargs else 10.0
        self._v_set_min = kwargs['v_min'] if 'v_min' in kwargs else 0.0
        self._v_set_max = kwargs['v_max'] if 'v_max' in kwargs else 10.0
        self._i_set_max = kwargs['i_max'] if 'i_max' in kwargs else 10.0
        self._p_set_max = kwargs['p_max'] if 'p_max' in kwargs else 10.0

        self._brake = BrakesClass.BrakesClass(kwargs)

        self._wheel_speed = 0.0

        self._force = 0.0

        self._mass = 1521.0

        return

    def update(self, shaft_torque=0, brakes=False):
        self._brake.apply(brakes)
        brake_torque = self._brake.get_torque()
        self._force = (shaft_torque-brake_torque)/0.2159
        return

    def get_force(self):
        return self._force

    def brake(self, error):
        return self._brake.update(error)

    def set_speed(self, speed):
        self._wheel_speed = speed
        return

    def get_speed(self):
        return self._wheel_speed