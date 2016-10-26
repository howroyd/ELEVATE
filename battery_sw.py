import time
import ElectricalDeviceClass

class Battery_Model(ElectricalDeviceClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, kwargs):
        self._v_set_max = kwargs['e']     if 'e'     in kwargs else 0.0
        self._v_set_max = self.kwh_to_joules(kwargs['kwh'])   if 'kwh' in kwargs else 0.0
        
        return super().__init__(kwargs)


    def charge_to(self, soc):
        self._soc = soc
        self.update(dt)

    @staticmethod
    def kwh_to_joules(kwh) -> float:
        return kwh * 3.6e+6
    @staticmethod
    def joules_to_kwh(joules) -> float:
        return joules / 3.6e+6

    @staticmethod
    def battery_model(v, i, soc) -> float:
        return v*1 - i*0.1

    def update(self, dt):
        return self.battery_model(self._v, self._i, 100)



