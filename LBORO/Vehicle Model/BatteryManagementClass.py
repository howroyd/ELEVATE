import ElectricalDeviceClass
import BatteryClass

class BatteryManagementClass(ElectricalDeviceClass.ElectricalDeviceClass):
    def __init__(self, **kwargs):
        self._v_min = kwargs.get('v_min')
        self._v_max = kwargs.get('v_max')
        self._i_max_charge = kwargs.get('i_max_charge')
        self._i_max_discharge = kwargs.get('i_max_discharge')
        self._p_max = kwargs.get('p_max')

        batt_e_max = self.kwh_to_joules(kwargs.get('batt_kwh'))

        self._battery_data = ElectricalDeviceClass.ElectricalDeviceClass(e_min=0.0, e_max=batt_e_max, e_start=batt_e_max)

        self._dt_last = 0.1 # Todo, realistic? Maybe use None?

    def update(dt):
        self._battery.update(dt)

        max_in  = min(self._battery.e_to_full  * dt / self._battery.v, self._battery.i_max)
        max_out = min(self._battery.e_to_empty * dt / self._battery.v, self._battery.i_max)

        self._i_max = min(max_out, self._i_max_discharge), -1.0*(min(max_out, self._i_max_charge))

    @property
    def i_max_discharge(self):
        max_remainder = (self.e_to_empty / self._dt_last) / self._v
        return min(max_remainder, self._i_max_discharge, self._p_max / self._v)

    @property
    def i_max_charge(self):
        max_remainder = (self.e_to_full / self._dt_last) / self._v
        return min(max_remainder, self._i_max_charge, self._p_max / self._v)

    @property
    def availability(self):
        return {self._key_voltage : self._v, 'max_charge' : self.i_max_charge, 'max_discharge' : self.i_max_discharge}

    @property
    def battery_data(self):
        _battery_data = { 'soc' : self.soc, 'total_energy_in' : self._e_in, 'total_energy_out' : self._e_out,
                            'energy' : self._e_total, 'energy_to_empty' : self.e_to_empty, 'energy_to_full' : self.e_to_full }
        _battery_data.update(self.data)
        return _battery_data

    def set_battery_data(self, battery_dict):
        self._battery_data._v = battery_dict.get('voltage')
        self._battery_data.