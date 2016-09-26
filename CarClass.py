import time
import PowertrainClass
import AerodynamicsClass
import battery_sw

class CarClass(object):
    '''DESCRIPTION'''

    # Instance constructor
    def __init__(self, kwargs):
        self._v_set     = kwargs['v']     if 'v'     in kwargs else 10.0
        self._v_set_min = kwargs['v_min'] if 'v_min' in kwargs else 0.0
        self._v_set_max = kwargs['v_max'] if 'v_max' in kwargs else 10.0
        self._i_set_max = kwargs['i_max'] if 'i_max' in kwargs else 10.0
        self._p_set_max = kwargs['p_max'] if 'p_max' in kwargs else 10.0

        self._aero = AerodynamicsClass.AerodynamicsClass(kwargs)

        self._battery = battery_sw.Battery_Model(kwargs)

        kwargs.update(battery = self._battery) # TODO: is this necessary?

        self._powertrain = PowertrainClass.PowertrainClass(kwargs)

        return

    def update(self):
        self._aero.update(self.get_speed())
        self._battery.update()
        self._powertrain.update(self._aero.get_drag())
        return

    def set_speed(self, speed):
        self._powertrain.set_speed(speed)

    def get_speed(self):
        return self._powertrain.get_speed()

    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)