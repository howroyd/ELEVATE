import time
import Cars
from Filters import LowPassFilter


class CarClass(object):
    '''DESCRIPTION'''

    # Instance constructor
    def __init__(self, kwargs=None, name="car"):
        if (kwargs is not None):
            self._aero_model = kwargs['aero_model']
            self._powertrain_model_array = kwargs['powertrain_model_array']
            self._vehicle_mass = kwargs['car_mass']
            self._speed = 0.0
            self._target_speed = 0.0
            self._feed_forward_speed = None
            self._total_force = 0.0 
        self._lpf    = LowPassFilter(0.5)
        self._lpf_ff = LowPassFilter(0.25)
        self._data = dict()
        self._name = name
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

        self._data.update(self._powertrain_model_array[0].data)
        self._data.update(self._aero_model.data)
        self._data.update({(self._name+'_speed') : self.speed,
                            (self._name+'_accel') : accn,
                            (self._name+'_target_speed') : self.target_speed,
                            (self._name+'_dv') : self.dv,
                            (self._name+'_total_force') : self._total_force
        })

        return

    @property
    def data(self):
        return self._data

    @property
    def dv(self):
        return self._powertrain_model_array[0]._speed_control.dv

    @property
    def target_speed(self,):
        return self._target_speed
    @target_speed.setter
    def target_speed(self, speed):
        self._target_speed = self._lpf.get(speed)

    @property
    def feed_forward_speed(self,):
        return self._feed_forward_speed
    @feed_forward_speed.setter
    def feed_forward_speed(self, speed):
        self._feed_forward_speed = self._lpf_ff.get(speed)

    @property
    def speed(self):
        return self._speed
    @speed.setter
    def speed(self, value):
        self._speed = max(0.0, value)

    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)