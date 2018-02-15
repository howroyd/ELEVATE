class ElectricityClass(object):
    def __init__(self):
        self._key_voltage = 'voltage'
        self._key_current = 'current'
        self._key_power   = 'power'
        self._v = 0.0
        self._i = 0.0

    @property
    def data(self):
        return {self._key_voltage : self._v, self._key_current : self._i, self._key_power : self.power}

    @property
    def voltage(self):
        return self._v

    @property
    def current(self):
        return self._i

    @property
    def power(self):
        return self._v * self._i

class ElectricalDeviceClass(ElectricityClass):
    '''DESCRIPTION'''
    # Instance Constructor
    def __init__(self, **kwargs):
        self._e_in    = 0.0
        self._e_out   = 0.0
        self._e_total = kwargs.get('e_start')
        self._e_max   = kwargs.get('e_max')
        self._e_min   = kwargs.get('e_min')
        return super().__init__()

    def update(self, dt):
        if self._e_total is not None:
            e = self.power * dt

            if ( e >= 0 ):
                self._e_out += e
            else:
                self._e_in += e

            self._e_total -= e

            self._e_total = min(self._e_total, self._e_max)

            if self._e_total < self._e_min:
                self._v = 0.0
                self._i = 0.0
                print('Electrical device out of energy!')

    @property
    def energy(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_total

    @property
    def e_to_empty(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_total - self._e_min

    @property
    def e_to_full(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_total - self._e_max

    @property
    def e_max(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_max

    @staticmethod
    def kwh_to_joules(kwh):
        return kwh * 3.6e+6
    @staticmethod
    def joules_to_kwh(joules):
        return joules / 3.6e+6