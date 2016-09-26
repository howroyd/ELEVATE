import ElectricalDeviceClass
import ElectricalManagementClass

class MotorClass(ElectricalDeviceClass.ElectricalDevice):
    """description of class"""

    # Instance constructor
    def __init__(self, kwargs):
        self._max_torque = kwargs['max_torque']     if 'max_torque'     in kwargs else 280.0 # Nissan leaf Nm
        self._v_set_min = kwargs['v_min'] if 'v_min' in kwargs else 0.0
        self._v_set_max = kwargs['v_max'] if 'v_max' in kwargs else 10.0
        self._i_set_max = kwargs['i_max'] if 'i_max' in kwargs else 10.0
        self._p_set_max = kwargs['p_max'] if 'p_max' in kwargs else 10.0

        self._shaft_torque = 0.0

        kwargs.update(shaft_torque = self._shaft_torque)

        return super().__init__(kwargs)

    def update(self, error):
        self._shaft_torque = max(min(self._max_torque, self._shaft_torque + 100.0*error), 0.0)
        return

    def get_torque(self):
        return self._shaft_torque