from enum import Enum, unique

@unique
class electricity_t(Enum):
    '''DESCRIPTION'''
    AC  = 0
    DC  = 1

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

class Electricity(object):
    def __init__(self, kwargs, name="electricity"):
        self._type = electricity_t.DC
        self._v       = kwargs['v'] if 'v' in kwargs else 0.0
        self._i       = kwargs['i'] if 'i' in kwargs else 0.0
        self._f = None
        self._noise_f = 50
        self._noise_rms = 0.0
        self._name = name
        self._data = dict()

    def _update(self):
        self._data.update({(self._name+'_v') : self.v,
                            (self._name+'_i') : self.i,
                            (self._name+'_f') : self.f,
                            (self._name+'_noise_f') : self.noise_f,
                            (self._name+'_noise_rms') : self.noise_rms
        })



    @property
    def data(self):
        return self._data

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
            #print('Requested DC frequency!')
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



class ElectricalDevice(Electricity):
    '''DESCRIPTION'''
    # Instance Constructor
    def __init__(self, kwargs, name="electricalDevice"):
        super().__init__(kwargs, name=name)
        self._p       = kwargs['p'] if 'p' in kwargs else 0.0
        self._e_in    = 0.0
        self._e_out   = 0.0
        self._e_total = 0.0
        self._e_start = kwargs['e_start'] if 'e_start' in kwargs else 0.0
        self._e_max   = kwargs['e_max'] if 'e_max' in kwargs else None
        self._e_min   = kwargs['e_min'] if 'e_min' in kwargs else 0.0
        self._error    = error_t.none
        self._name = name
        self._data = dict()
        return 

    def update(self, dt):
        super(ElectricalDevice, self)._update()
        self._data.update(super(ElectricalDevice, self).data)
        self._data.update({(self._name+'_v') : super(ElectricalDevice, self).v,
                            (self._name+'_i') : super(ElectricalDevice, self).i,
                            (self._name+'_p') : self._p,
                            (self._name+'_e_in') : self._e_in,
                            (self._name+'_e_out') : self._e_out,
                            (self._name+'_e_total') : self._e_total,
                            (self._name+'_e_start') : self._e_start,
                            (self._name+'_e_max') : self._e_max,
                            (self._name+'_e_min') : self._e_min,
                            (self._name+'_error') : self._error,
                            })

    #def elec_update(self, kwargs):
    #    self._v       = kwargs['v'] if 'v' in kwargs else self._v
    #    self._i       = kwargs['i'] if 'i' in kwargs else self._i
    #    self._p       = kwargs['p'] if 'p' in kwargs else self._p
    #    self._e_in    = kwargs['e_in'] if 'e_in' in kwargs else self._e_in
    #    self._e_out   = kwargs['e_out'] if 'e_out' in kwargs else self._e_out
    #    self._e_total = kwargs['e'] if 'e' in kwargs else self._e_total
    #    self._e_start = kwargs['e_start'] if 'e_start' in kwargs else self._e_start
    #    self._e_max   = kwargs['e_max'] if 'e_max' in kwargs else self._e_max
    #    self._e_min   = kwargs['e_min'] if 'e_min' in kwargs else self._e_min
    #    self.error    = kwargs['error'] if 'error' in kwargs else self.error

    #def export(self):
    #    return dict(    v       = self._v,
    #                    i       = self._i,
    #                    p       = self._p,
    #                    e_in    = self._e_in,
    #                    e_out   = self._e_out,
    #                    e       = self._e_total,
    #                    e_start = self._e_start,
    #                    e_max   = self._e_max,
    #                    e_min   = self._e_min,
    #                    error   = self.error
    #                )

    @property
    def data(self):
        return self._data

    # Interactive methods
    #def add_v(self, v):
    #    self._v += v
    #def add_i(self, i):
    #    self._i += i
    #def add_p(self, p):
    #    self._p += p
    #def add_e(self, e):
    #    _e_left = self._e_max - self._e_total
    #    e_in_accepted = min(e, _e_left)
    #    self.e_in += e_in_accepted
    #    return e_in_accepted
    #def sub_v(self, v):
    #    self._v -= v
    #def sub_i(self, i):
    #    self._i -= i
    #def sub_p(self, p):
    #    self._p -= p
    #def sub_e(self, e):
    #    _e_left = self._e_total - self._e_min
    #    e_out_accepted = min(e, _e_left)
    #    self.e_in -= e_out_accepted
    #    return e_out_accepted
    #def get_v(self) -> float:
    #    return self._v
    #def get_i(self) -> float:
    #    return self._i
    #def get_p(self) -> float:
    #    return self._p
    #def get_e_in(self) -> float:
    #    return self._e_in
    #def get_e_out(self) -> float:
    #    return self._e_out
    #def get_e_total(self) -> float:
    #    return self._e_total
    #def set_v(self, v):
    #    self._v = v
    #    return self._v
    #def set_i(self, i):
    #    self._i = i
    #    return self._i
    #def set_p(self, p):
    #    self._p = p
    #    return self._p