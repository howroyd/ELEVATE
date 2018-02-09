import math
import RotatingThingClass
import ControlBusClass

class BrakesClass(RotatingThingClass.RotatingDiscClass):
    """description of class"""

    # Instance constructor
    def __init__(self, **kwargs):
        self._shc_carbon_steel = 502.416
        self._density_carbon_steel = 7850.0
        self._conductivity_to_air_carbon_steel = 36.0

        self._temperature_ambient   = 16.0
        self._temperature           = self._temperature_ambient

        self._thickness   = 0.015

        _diameter    = kwargs['brake_diameter']
        _area        = math.pi * (_diameter / 2.0)**2
        _mass        = self._area * self._thickness * self._density_carbon_steel

        super().__init__(self, diameter=kwargs['brake_diameter'], mass=_mass)

        self._torque_max  = kwargs['brake_max_torque']

        self._ctrl_sig    = ControlBusClass.ControlBusClass('unsigned')

        self._K_J         = 1.0 / ( self._shc_carbon_steel * self.mass)

        return

    def update(self, dt):
        super().update(dt)

        self.torque = self._ctrl_sig.decimal * self.torque_max

        power_gained = self.torque * self.w
        energy_gained = power_gained * dt

        power_lost = self._conductivity_to_air_carbon_steel * ( 2.0 * self.area ) * ( self._temperature_ambient - self._temperature ) * -1.0
        energy_lost = power_lost * dt
        
        self._temperature += (self._K_J * (energy_gained-energy_lost))

        return

    @property
    def value(self):
        return self._ctrl_sig.value
    @value.setter
    def value(self, val):
        self._ctrl_sig.value = val

    @property
    def torque_max(self):
        return self._torque_max
    @torque_max.setter
    def torque_max(self, tq):
        if (tq < 0.0):
            print("Torque max cannot be negative")
            raise ValueError
            return None
        self._torque_max = tq

    @property
    def temperature(self):
        return self._temperature