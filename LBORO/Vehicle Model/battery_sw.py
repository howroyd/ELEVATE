import time
import ElectricityClass
from enum import Enum, unique

@unique
class error_t(Enum):
    '''DESCRIPTION'''
    none    = 0
    v_high  = 1
    v_low   = 2
    i_high  = 3
    i_low   = 4
    p_high  = 5
    p_low   = 6
    e_full  = 7
    e_empty = 8

class Battery_Model(ElectricityClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, kwargs, name='battery'):
        self._v_max = kwargs['batt_v_max'] if 'batt_v_max' in kwargs else None
        self._v_min = kwargs['batt_v_min'] if 'batt_v_min' in kwargs else 0.0
        self._i_max = kwargs['batt_i_max'] if 'batt_i_max' in kwargs else None
        self._p_max = kwargs['batt_p_max'] if 'batt_p_max' in kwargs else None
        self._joules_max = self.kwh_to_joules(kwargs['batt_kwh_max']) if 'batt_kwh_max' in kwargs else None
        self._joules = self.kwh_to_joules(kwargs['batt_kwh']) if 'batt_kwh' in kwargs else self._joules_max

        #self._output = ElectricityClass.Electricity()
        self._power_good = True 
        self._max_power = False
        self._name = name
        self._error    = error_t.none
        return super().__init__(kwargs, name=self._name)

    #@staticmethod
    #def battery_model(v, i, soc) -> float:
    #    return v*1 - i*0.1

    def update(self, dt):
        error = self._check_errors()
        
        if error is error_t.none:
            joules_transferred = self.i * self.v * dt # Joule is a watt-second
            self._joules -= joules_transferred
        elif error is error_t.e_full:
            if self.i >= 0.0:
                joules_transferred = self.i * self.v * dt # Joule is a watt-second
                self._joules -= joules_transferred
            else:
                self.i = 0.0
                self.p = 0.0 
        else:
            self.i = 0.0
            self.p = 0.0 

        self.v = (self._joules / self._joules_max * 100.0) + self._v_min

        return

    def _check_errors(self):
        if self.v > self._v_max:
            self._error = error_t.v_high
        elif self.v < self._v_min:
            self._error = error_t.v_low

        elif self.i > self._i_max:
            self._error = error_t.i_high

        elif self.p > self._p_max:
            self._error = error_t.p_high

        elif self._joules > self._joules_max:
            self._error = error_t.e_full
        elif self._joules <= 0.0:
            self._error = error_t.e_empty

        else:
            self._error = error_t.none

        return self.error




    @property
    def power_good(self):
        return self._power_good
    @property
    def max_power(self):
        return self._max_power
    
    @property
    def error(self):
        return self._error

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





