import ElectricalDeviceClass
import ElectricalManagementClass

class MotorClass(ElectricalDeviceClass.ElectricalDevice):
    """description of class"""

    # Instance constructor
    def __init__(self, connected_wheels, kwargs):
        self._connected_wheels = connected_wheels
        self._shaft_torque = 0.0
        self._value = 0 # 0-255
        self._max_torque = kwargs['motor_max_torque']
        self._v_min = kwargs['motor_v_min']
        self._v_max = kwargs['motor_v_max']
        self._i_max = kwargs['motor_i_max']
        self._p_max = kwargs['motor_p_max']
        return super().__init__(kwargs)

    def update(self, dt):
        self._shaft_torque = (self._value/255)*self._max_torque
        for ptr in self._connected_wheels:
            ptr.motor_torque = self._shaft_torque / len(self._connected_wheels)
        return

    @property
    def shaft_torque(self):
        return self._shaft_torque

    @property
    def motor_value(self):
        return self._value
    @motor_value.setter
    def motor_value(self, value):
        #value = self._value + 1*(value - self._value)
        self._value = max(min(value, 255), 0)
