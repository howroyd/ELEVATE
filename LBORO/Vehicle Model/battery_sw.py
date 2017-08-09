import time
import ElectricityClass

class Battery_Model(ElectricityClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, kwargs, name='battery'):
        self._v_set_max = kwargs['e'] if 'e' in kwargs else 0.0
        self._v_set_max = self.kwh_to_joules(kwargs['kwh'])   if 'kwh' in kwargs else 0.0
        #self._output = ElectricityClass.Electricity()
        self._power_good = True 
        self._max_power = False
        self._name = name
        return super().__init__(kwargs, name=self._name)

    def update(self):
        # check power good
        # check max power
        pass

    @property
    def power_good(self):
        return self._power_good
    @property
    def max_power(self):
        return self._max_power

    def power_good_reset(self):
        self._power_good = True

    def set_max_power(self):
        pass

    def charge_to(self, soc):
        self._soc = soc
        self.update(dt)

    def get_electricity(self):
        return self._output

    def give_electricity(self, input):
        pass



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



