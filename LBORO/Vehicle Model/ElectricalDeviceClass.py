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

class ElectricalDevice():
    '''DESCRIPTION'''
    # Instance Constructor
    def __init__(self, kwargs):
        self._v       = kwargs['v'] if 'v' in kwargs else 0.0
        self._i       = kwargs['i'] if 'i' in kwargs else 0.0
        self._p       = kwargs['p'] if 'p' in kwargs else 0.0
        self._e_in    = 0.0
        self._e_out   = 0.0
        self._e_total = 0.0
        self._e_start = kwargs['e_start'] if 'e_start' in kwargs else 0.0
        self._e_max   = kwargs['e_max'] if 'e_max' in kwargs else 0.0
        self._e_min   = kwargs['e_min'] if 'e_min' in kwargs else 0.0
        self.error    = error_t.none
        return None

    # Interactive methods
    def add_v(self, v):
        self._v += v
    def add_i(self, i):
        self._i += i
    def add_p(self, p):
        self._p += p
    def add_e(self, e):
        _e_left = self._e_max - self._e_total
        e_in_accepted = min(e, _e_left)
        self.e_in += e_in_accepted
        return e_in_accepted
    def sub_v(self, v):
        self._v -= v
    def sub_i(self, i):
        self._i -= i
    def sub_p(self, p):
        self._p -= p
    def sub_e(self, e):
        _e_left = self._e_total - self._e_min
        e_out_accepted = min(e, _e_left)
        self.e_in -= e_out_accepted
        return e_out_accepted
    def get_v(self) -> float:
        return self._v
    def get_i(self) -> float:
        return self._i
    def get_p(self) -> float:
        return self._p
    def get_e_in(self) -> float:
        return self._e_in
    def get_e_out(self) -> float:
        return self._e_out
    def get_e_total(self) -> float:
        return self._e_total
    def set_v(self, v):
        self._v = v
        return self._v
    def set_i(self, i):
        self._i = i
        return self._i
    def set_p(self, p):
        self._p = p
        return self._p