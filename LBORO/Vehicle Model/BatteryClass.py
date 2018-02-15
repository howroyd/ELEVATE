import ElectricalDeviceClass

class BatteryClass(ElectricalDeviceClass.ElectricalDeviceClass):
    '''DESCRIPTION'''
    # Instance constructor
    def __init__(self, **kwargs):
        self._v_min = kwargs.get('v_min')
        self._v_max = kwargs.get('v_max')
        self._i_max_charge = kwargs.get('i_max_charge')
        self._i_max_discharge = kwargs.get('i_max_discharge')
        self._p_max = kwargs.get('p_max')

        batt_e_max = self.kwh_to_joules(kwargs.get('batt_kwh'))

        return super().__init__(e_min=0.0, e_max=batt_e_max, e_start=batt_e_max)

    def calculate_v(self):
        return self._e_total * ((self._v_max - self._v_min) / self._e_max) + self._v_min

    def update(self, dt):
        super().update(dt)
        self._v = self.calculate_v()
        
    @property
    def soc(self):
        return self.energy / self._e_max

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

    @property
    def battery_data(self):
        _battery_data = { 'soc' : self.soc, 'total_energy_in' : self._e_in, 'total_energy_out' : self._e_out,
                            'energy' : self._e_total, 'energy_to_empty' : self.e_to_empty, 'energy_to_full' : self.e_to_full }
        _battery_data.update(self.data)
        return _battery_data