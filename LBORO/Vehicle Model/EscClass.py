import ElectricalDeviceClass
from Filters import LowPassFilter
from ElectricityClass import Electricity

class ESC(ElectricalDeviceClass.ElectricalDevice):
    """description of class"""

    # Takes in electrical power from battery and converts it to elec power for motor
    # Does not work in reverse to charge battery

    # Instance constructor
    def __init__(self, kwargs):
        self._value = 0 # 0-255
        self._v_min = kwargs['esc_v_min'] if 'esc_v_min' in kwargs else kwargs['motor_v_min']
        self._v_max = kwargs['esc_v_max'] if 'esc_v_max' in kwargs else kwargs['motor_v_max']
        self._i_max = kwargs['esc_i_max'] if 'esc_i_max' in kwargs else kwargs['motor_i_max']
        self._p_max = kwargs['esc_p_max'] if 'esc_p_max' in kwargs else kwargs['motor_p_max']
        self._lpf = LowPassFilter(1)
        self._electrical_efficiency = 0.85

        self._first_iteration = True
        self._output = Electricity()
        return super().__init__(kwargs)

    def update(self, dt):
        if self._first_iteration: self._first_iteration = False
        else:
            # Do the magic
            
            pass

    def _generate_electricity_class(self):
        pass

    @property
    def electricity(self):
        return self._output
    @electricity.setter
    def electricity(self, elec):
        pass

    @property
    def electricity_array(self):
        return None
    @electricity_array.setter
    def electricity_array(self, elec):
        pass

    # def elec_update(kwargs):

