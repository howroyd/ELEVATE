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

class ElectricalDevice(object):
    '''DESCRIPTION'''
    # Instance Constructor
    def __init__(self, kwargs=[]):
        self._v       = kwargs['v'] if 'v' in kwargs else 0.0
        self._i       = kwargs['i'] if 'i' in kwargs else 0.0
        self._p       = kwargs['p'] if 'p' in kwargs else 0.0
        self._e_in    = 0.0
        self._e_out   = 0.0
        self._e_total = 0.0
        self._e_max   = kwargs['e_max'] if 'e_max' in kwargs else 0.0
        self._e_min   = kwargs['e_min'] if 'e_min' in kwargs else 0.0
        self._e_start = kwargs['e_start'] if 'e_start' in kwargs else self._e_max
        self.error    = error_t.none
        return None


    def update(self, dt):
        e = self.p * dt
        if ( e >= 0 ):
            self._e_out += e
        else:
            self._e_in += e
        self._e_total -= e

    @property
    def e_to_empty(self):
        return self._e_total - self._e_min

    @property
    def e_to_full(self):
        return self._e_total - self._e_max

    @property
    def v(self):
        return self._v

    @property
    def i(self):
        return self._i

    @property
    def p(self):
        return self._v * self._i

    @property
    def e_max(self):
        return self._e_max

    @property
    def e_now(self):
        return self._e_total