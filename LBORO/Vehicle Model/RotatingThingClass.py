import math
from abc import ABCMeta, ABC, abstractmethod

class RotatingThingData(object):
    def __init__(self):
        self._key_torque = 'torque'
        self._key_speed  = 'speed'
        self._torque = 0.0
        self._speed  = 0.0

    @property
    def rotational_data(self):
        return {self._key_torque : self._torque, self._key_speed : self._speed}
    @rotational_data.setter
    def rotational_data(self, data_dict):
        print('Setting data', data_dict)
        self._torque = data_dict.get(self._key_torque)
        self._speed  = data_dict.get(self._key_speed)

    @property
    def torque(self):
        return self._torque
    @torque.setter
    def torque(self, tq):
        self._torque = tq

    @property
    def speed(self):
        return self._speed
    @speed.setter
    def speed(self, rad_sec):
        self._speed = rad_sec

    @property
    def key_torque(self):
        return self._key_torque

    @property
    def key_speed(self):
        return self._key_speed

class RotatingThingClass(ABC, RotatingThingData):
    """description of class"""

    def __init__(self, kwargs):
        self._w_last      = 0.0
        self._p           = 0.0
        self._dt          = 0.0
        self._diameter    = kwargs.get('diameter')
        self._area        = kwargs.get('area', (math.pi * (self._diameter / 2.0)**2) if self._diameter is not None else None)
        self._mass        = kwargs.get('mass')
        self._circumference = math.pi * self._diameter if self._diameter is not None else None
        super(ABC, self).__init__()
        return super(RotatingThingData, self).__init__()

    def update(self, dt):
        self._dt = dt
        return None

    @staticmethod
    def rpm_to_rads(rpm):
        return rpm / 60.0 / 2.0 / math.pi

    @staticmethod 
    def rads_to_rpm(rads):
        return rads * 60.0 * 2.0 * math.pi

    @property
    def diameter(self):
        return self._diameter

    @property
    def radius(self):
        return self._diameter / 2.0

    @property
    def area(self):
        return self._area

    @property
    def mass(self):
        return self._mass

    @property
    def power(self):
        return self._torque * self._speed

    @property
    def torque(self):
        return super().torque
    @torque.setter
    def torque(self, tq):
        super(RotatingThingData, self).torque.__set__(tq - self.inertia_torque_x)

    @property
    def force(self):
        return self._torque * self.radius

    @property
    def speed(self):
        return super()._speed
    @speed.setter
    def speed(self, rad_sec):
        if (rad_sec < 0.0):
            print("Rotational speed cannot be negative")
            raise ValueError
            return None
        self._w_last = self._speed
        super(RotatingThingData, self).speed.__set__(rad_sec)

    @property
    @abstractmethod
    def inertia_x(self):
        ...



    @property
    def inertia_torque_x(self):
        return self.inertia_x * ( self._speed - self._w_last ) / self._dt



class RotatingDiscClass(RotatingThingClass):
    """description of class"""

    def __init__(self, kwargs):
        RotatingThingClass.__init__(self, kwargs)
        return

    @property
    def inertia_x(self):
        return (self.mass * self.radius**2) / 2.0

class RotatingCylinderClass(RotatingThingClass):
    """description of class"""

    def __init__(self, kwargs):
        RotatingThingClass.__init__(self, kwargs)
        self._length = kwargs.get('length')
        return

    @property
    def inertia_x(self):
        return (self.mass * self.radius**2) / 2.0

    @ property
    def length(self):
        return self._length

class RotatingCylinderShellClass(RotatingThingClass):
    """description of class"""

    def __init__(self, kwargs):
        RotatingThingClass.__init__(self, kwargs)
        self._length = kwargs['length'] if 'length' in kwargs else None
        return

    @property
    def inertia_x(self):
        return self.mass * self.length**2

    @ property
    def length(self):
        return self._length