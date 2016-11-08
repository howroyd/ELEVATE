import time
import Cars

class CarClass(object):
    '''DESCRIPTION'''

    # Instance constructor
    def __init__(self, kwargs=None):
        if (kwargs is not None):
            self._aero_model = kwargs['aero_model']
            self._powertrain_model_array = kwargs['powertrain_model_array']
            self._vehicle_mass = kwargs['car_mass']
            self._speed = 0.0
            self._target_speed = 0.0
            super().__init__()
        return

    def update(self, dt):
        for ptr in self._powertrain_model_array:
                ptr.current_speed = self.speed
                ptr.target_speed = self._target_speed
                ptr.update(dt)

        self._aero_model.update(self._speed)

        total_force = sum(ptr.force for ptr in self._powertrain_model_array) - self._aero_model.force

        accn = total_force / self._vehicle_mass
        self.speed = self.speed + accn*dt
        return

    @property
    def target_speed(self,):
        return self._target_speed
    @target_speed.setter
    def target_speed(self, speed):
        self._target_speed = speed

    @property
    def speed(self):
        return self._speed
    @speed.setter
    def speed(self, value):
        if (value <= 0.0): value = 0.0
        self._speed = value

    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)