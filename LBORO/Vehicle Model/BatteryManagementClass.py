import ElectricalDeviceClass
import BatteryClass

class BatteryManagementClass(ElectricalDeviceClass.ElectricalDevice):
    def __init__(self, kwargs):
        self._battery = BatteryClass.Battery_Model(kwargs)
        self._i_max_charge = 0.0
        self._i_max_discharge = 0.0
        self._i_max = 0.0, 0.0

    def update(dt):
        self._battery.update(dt)

        max_in  = min(self._battery.e_to_full  * dt / self._battery.v, self._battery.i_max)
        max_out = min(self._battery.e_to_empty * dt / self._battery.v, self._battery.i_max)

        self._i_max = min(max_out, self._i_max_discharge), -1.0*(min(max_out, self._i_max_charge))

    @property
    def i_max(self):
        return self._i_max # Tuple; max out of mattery, max recharge into battery

    @property
    def i_max_charge(self):
        return self._i_max_charge

    @property
    def i_max_discharge(self):
        return self._i_max_discharge
