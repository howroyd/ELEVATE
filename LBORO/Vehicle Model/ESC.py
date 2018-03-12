import ElectricalDeviceClass
from Filters import LowPassFilter

class ESC(ElectricalDeviceClass.ElectricalDeviceClass):
    """description of class"""

    # Instance constructor
    def __init__(self, kwargs):
        self._value = 0 # 0-255
        self._v_min = kwargs.get('motor_v_min')
        self._v_max = kwargs.get('motor_v_max')
        self._i_max = kwargs.get('motor_i_max')
        self._p_max = kwargs.get('motor_p_max')
        self._lpf = LowPassFilter(1)
        self._electrical_efficiency = 0.85

        self._first_iteration = True

        return super().__init__(kwargs)

    def update(self, val, dt):
        if self._first_iteration: self._first_iteration = False
        else:
            
            pass

