from enum import Enum, unique

@unique
class electricity_t(Enum):
    '''DESCRIPTION'''
    AC  = 0
    DC  = 1


class Electricity(object):
    def __init__(self):
        self._type = electricity_t.DC
        self._v = 0.0
        self._i = 0.0
        self._f = None
        self._noise_f = 50
        self._noise_rms = 0.0

    @property
    def v(self):
        return self._v
    @v.setter
    def v(self, voltage):
        self._v = voltage

    @property
    def i(self):
        return self._i
    @i.setter
    def i(self, current):
        self._i = current

    @property
    def type(self):
        if self._type is electricity_t.AC: return 'AC'
        elif self._type is electricity_t.DC: return 'DC'
        else:
            print('Invalid electricity type in memory')
            return None
    @type.setter
    def type(self, type):
        if 'AC' in type: self._type = electricity_t.AC
        elif 'DC' in type: self._type = electricity_t.DC
        else:
            print('Invalid electricity type setting')
            pass

    @property
    def f(self):
        if self._type is electricity_t.AC: return self._f
        else:
            print('Requested DC frequency!')
            return None
    @f.setter
    def f(self, frequency):
        if self._type is electricity_t.AC: self._f = frequency
        else:
            print('Tried to set DC frequency!')
            pass

    @property
    def noise_f(self):
        return self._noise_f

    @noise_f.setter
    def noise_f(self, frequency):
        self._noise_f = frequency

    @property
    def noise_rms(self):
        return self._noise_rms

    @noise_rms.setter
    def noise_rms(self, rms):
        self._noise_rms = rms

