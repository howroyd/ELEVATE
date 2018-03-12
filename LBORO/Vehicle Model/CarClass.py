import time
import PowertrainClass2
import AerodynamicsClass

class CarClass(object):
    '''DESCRIPTION'''

    # Instance constructor
    def __init__(self, kwargs=None):
        if (kwargs is None):
            raise Exception("Must define car data!")
        else:
            self._powertrain = PowertrainClass2.PowertrainControllerClass(kwargs)
            self._aero_model = AerodynamicsClass.AerodynamicsClass(kwargs)
            self._vehicle_mass = kwargs.get('car_mass')

    def update(self, dt):
        self._powertrain.update(dt)

        self._aero_model.update(self._speed)

        total_force = self._powertrain.force - self._aero_model.force

        accn = total_force / self._vehicle_mass
        self.speed = self.speed + accn*dt
        return

    @property
    def target_speed(self,):
        return self._powertrain.set_speed
    @target_speed.setter
    def target_speed(self, speed):
        self._powertrain.set_speed = speed

    @property
    def speed(self):
        return self._speed
    @speed.setter
    def speed(self, value):
        if (value <= 0.0): value = 0.0
        self._speed = value

    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)