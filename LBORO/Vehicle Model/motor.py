import time
import ElectricalDeviceClass

class motor(ElectricalDeviceClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, **kwargs):
        self._v_min = kwargs['v_min'] if 'v_min' in kwargs else 0.0
        self._v_max = kwargs['v_max'] if 'v_max' in kwargs else 0.0
        self._i_max = kwargs['i_max'] if 'i_max' in kwargs else 0.0
        self._p_max = kwargs['p'] if 'p' in kwargs else 0.0

        self._dt = time.time()


