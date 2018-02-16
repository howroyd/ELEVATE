import ElectricalDeviceClass
import BatteryClass

class BatteryManagementClass(ElectricalDeviceClass.ElectricalDeviceClass):
    def __init__(self, **kwargs):
        self._i_max_charge = kwargs.get('i_max_charge')
        self._i_max_discharge = kwargs.get('i_max_discharge')
        self._p_max = kwargs.get('p_max')

        batt_e_max = self.kwh_to_joules(kwargs.get('batt_kwh'))

        self._battery_data = ElectricalDeviceClass.ElectricalDeviceClass(e_min=0.0, e_max=batt_e_max, e_start=batt_e_max)

        self._dt_last = 0.1 # Todo, realistic? Maybe use None?

    def update(dt):
        self._dt_last = dt

    @property
    def i_max_discharge(self):  
        if self._i_max_out is not None: return self._i_max_out
        max_remainder = (self.e_to_empty / self._dt_last) / self._v
        return min(max_remainder, self._i_max_discharge, self._p_max / self._battery_data._v)

    @property
    def i_max_charge(self):
        if self._i_max_in is not None: return self._i_max_in
        max_remainder = (self.e_to_full / self._dt_last) / self._v
        return min(max_remainder, self._i_max_charge, self._p_max / self._battery_data._v)

    @property
    def availability(self):
        return {self._key_voltage : self._v, 'max_charge' : self.i_max_charge, 'max_discharge' : self.i_max_discharge}

    def set_battery_data(self, battery_dict):
        self._battery_data._v     = battery_dict.get('voltage')
        self._battery_data.energy = battery_dict.get('energy')