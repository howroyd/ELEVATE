import time
import ElectricalDeviceClass

class my_class(ElectricalDeviceClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, **kwargs):
        self._v_set_max = kwargs['e']     if 'e'     in kwargs
        self._v_set_max = self.kwh_to_joules(kwargs['kwh'])   if 'kwh' in kwargs
        
        return super().__init__(**kwargs)

    @staticmethod
    def kwh_to_joules(kwh):
        return kwh * 3.6e+6
    @staticmethod
    def joules_to_kwh(joules):
        return joules / 3.6e+6




