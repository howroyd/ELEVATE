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
            self._feed_forward_speed = None
            self._total_force = 0.0
            super().__init__()
        return

    def update(self, dt):
        for ptr in self._powertrain_model_array:
                ptr.current_speed = self.speed
                ptr.target_speed = self._target_speed
                ptr.force = self._total_force / len(self._powertrain_model_array)
                if self._feed_forward_speed is not None:
                    ptr.feed_forward_speed = self._feed_forward_speed
                ptr.update(dt)

        self._aero_model.update(self._speed)
        
        self._total_force = sum(ptr.force for ptr in self._powertrain_model_array) - self._aero_model.force

        #print(str(self._powertrain_model_array[0].force), '\t', str(sum(ptr.force for ptr in self._powertrain_model_array)))

        accn = self._total_force / self._vehicle_mass

        #print("accn=", accn, 'dt=', dt)

        self.speed = self.speed + accn*dt
        #print(accn*dt, dt)
        #print("speed=", self.speed, 'dt=', dt)

        return

    @property
    def dv(self):
        return self._powertrain_model_array[0]._speed_control.dv

    @property
    def target_speed(self,):
        return self._target_speed
    @target_speed.setter
    def target_speed(self, speed):
        self._target_speed = speed

    @property
    def feed_forward_speed(self,):
        return self._feed_forward_speed
    @feed_forward_speed.setter
    def feed_forward_speed(self, speed):
        self._feed_forward_speed = speed

    @property
    def speed(self):
        return self._speed
    @speed.setter
    def speed(self, value):
        self._speed = max(0.0, value)

    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)