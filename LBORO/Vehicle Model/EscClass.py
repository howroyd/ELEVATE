import ControlBusClass
from Filters import LowPassFilter
import ElectricalDeviceClass

class ESC(ElectricalDeviceClass.ElectricalDeviceClass):
    """description of class"""

    # Takes in electrical power from battery and converts it to elec power for motor
    # Does not work in reverse to charge battery

    # Instance constructor
    def __init__(self, **kwargs):
        self._ctrl_sig = ControlBusClass.ControlBusClass('signed')
        self.i_max_to_motor   = kwargs.get('i_max_to_motor')
        self.i_max_from_motor = kwargs.get('i_max_from_motor')
        self._p_max = kwargs.get('p_max')
        self._lpf = LowPassFilter(1)
        self._electrical_efficiency = kwargs.get('efficiency', 0.85)
        self._input_data = ElectricalDeviceClass.ElectricalDeviceClass()
        self._motor_data = ElectricalDeviceClass.ElectricalDeviceClass()
        return super().__init__(kwargs)

    def update(self, dt):
        current = 0.0
        if self._ctrl_sig.decimal >= 0.0:
            current = self._ctrl_sig.decimal * self.i_max_to_motor
        else:
            current = self._ctrl_sig.decimal * self.i_max_from_motor

        # This current value need constraining to battery and motor realtime limits




    def set_input_power(self, availability_dict):
        self._input_data._v = availability_dict.get('voltage')
        self._input_data._i_max_in = availability_dict.get('max_charge')
        self._input_data._i_max_out = availability_dict.get('max_discharge')

    def set_output_power(self, availability_dict):
        self._motor_data._v = availability_dict.get('voltage')
        self._motor_data._i_max_in = availability_dict.get('max_current')
        self._motor_data._i_max_out = availability_dict.get('max_regen')

    @property
    def control_signal(self):
        return self._ctrl_sig.value
    @control_signal.setter
    def control_signal(self, value):
        self._ctrl_sig.value = value
        