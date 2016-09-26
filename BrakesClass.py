class BrakesClass(object):
    """description of class"""


    # Instance constructor
    def __init__(self, kwargs):
        self._v_set     = kwargs['v']     if 'v'     in kwargs else 10.0
        self._v_set_min = kwargs['v_min'] if 'v_min' in kwargs else 0.0
        self._v_set_max = kwargs['v_max'] if 'v_max' in kwargs else 10.0
        self._i_set_max = kwargs['i_max'] if 'i_max' in kwargs else 10.0
        self._p_set_max = kwargs['p_max'] if 'p_max' in kwargs else 10.0

        self._temperature = 16.0

        self._max_torque = 500.0

        self._current_torque = 0.0

        return

    def apply(self, switch):
        if switch:
            self._current_torque = self._max_torque
        else:
            self._current_torque = 0.0
        return

    def get_torque(self):
        return self._current_torque