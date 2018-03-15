#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import ElectricalDeviceClass
from Filters import LowPassFilter
import ControlBusClass

class ESC(ElectricalDeviceClass.ElectricalDeviceClass):
    '''Electronic speed controller for an induction motor'''
    # Takes in electrical power from battery and converts it to elec power for motor
    # Does not work in reverse to charge battery
    _ctrl_sig              = ControlBusClass.ControlBusClass('signed')
    i_max_to_motor         = None
    i_max_from_motor       = None
    _p_max                 = None
    _lpf                   = LowPassFilter(1)
    _electrical_efficiency = None
    _input_data            = ElectricalDeviceClass.ElectricalDeviceClass()
    _motor_data            = ElectricalDeviceClass.ElectricalDeviceClass()


    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        self.i_max_to_motor   = kwargs.get('i_max_to_motor')
        self.i_max_from_motor = kwargs.get('i_max_from_motor')
        self._p_max = kwargs.get('p_max')
        self._electrical_efficiency = kwargs.get('efficiency', 0.85)
        return super().__init__(kwargs)


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        current = 0.0
        if self._ctrl_sig.decimal >= 0.0:
            current = self._ctrl_sig.decimal * self.i_max_to_motor
        else:
            current = self._ctrl_sig.decimal * self.i_max_from_motor

        # This current value needs constraining to battery and motor realtime limits


    ###############################
    ###        GETTERS          ###
    ###############################

    # Control signal
    @property
    def control_signal(self):
        return self._ctrl_sig.value


    ###############################
    ###        SETTERS          ###
    ###############################

    # Control signal
    @control_signal.setter
    def control_signal(self, value):
        self._ctrl_sig.value = value

    # Input power
    def set_input_power(self, availability_dict):
        self._input_data._v = availability_dict.get('voltage')
        self._input_data._i_max_in = availability_dict.get('max_charge')
        self._input_data._i_max_out = availability_dict.get('max_discharge')

    # Output power
    def set_output_power(self, availability_dict):
        self._motor_data._v = availability_dict.get('voltage')
        self._motor_data._i_max_in = availability_dict.get('max_current')
        self._motor_data._i_max_out = availability_dict.get('max_regen')


###############################
###############################
######       END         ######
###############################
###############################