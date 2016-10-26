import time
#import PowertrainClass
#import AerodynamicsClass
#import battery_sw
import Cars

class CarClass(object):
    '''DESCRIPTION'''

    # Instance constructor
    def __init__(self, kwargs):
        self._aero_model = kwargs['aero_model']
        self._powertrain_model_array = kwargs['powertrain_model_array']
        self._vehicle_mass = kwargs['car_mass']
        self._speed = 0.0
        self._target_speed = 0.0
        return

    def update(self, dt):
        for ptr in self._powertrain_model_array:
                ptr.current_speed = self._speed
                ptr.target_speed = self._target_speed
                ptr.update(dt)

        self._aero_model.update(self._speed)

        total_force = sum(ptr.force for ptr in self._powertrain_model_array) - self._aero_model.force

        accn = total_force / self._vehicle_mass
        self._speed = self._speed + accn*dt
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

    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)