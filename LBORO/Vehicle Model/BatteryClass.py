import ElectricalDeviceClass

class Battery_Model(ElectricalDeviceClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, kwargs):
        self._v_min = kwargs['batt_v_min']
        self._v_max = kwargs['batt_v_max']
        self._i_max = kwargs['batt_i_max']
        self._p_max = kwargs['batt_p_max']

        kwargs.update(dict(e_max=self.kwh_to_joules(kwargs['batt_kwh'])))
        return super().__init__(kwargs)

    @staticmethod
    def kwh_to_joules(kwh):
        return kwh * 3.6e+6
    @staticmethod
    def joules_to_kwh(joules):
        return joules / 3.6e+6


    def calculate_v(self):
        return self.e_total * ((self._v_max - self._v_min) / self.e_max) + self._v_min

    def update(self, dt):
        super().update(dt)
        self._v = self.calculate_v()

        
    @property
    def soc(self):
        return self.e_now / self.e_max



    @property
    def v_min(self):
        return self._v_min

    @property
    def v_max(self):
        return self._v_max

    @property
    def i_max(self):
        return self._i_max

    @property
    def p_max(self):
        return self._p_max