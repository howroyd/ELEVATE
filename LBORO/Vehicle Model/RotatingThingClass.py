import math
from abc import ABCMeta, ABC, abstractmethod

class RotatingThingClass(ABC):
    """description of class"""

    def __init__(self, kwargs):
        self._torque      = 0.0
        self._w           = 0.0
        self._w_last      = 0.0
        self._p           = 0.0
        self._dt          = 0.0
        self._diameter    = kwargs['diameter'] if 'diameter' in kwargs else None
        self._area        = kwargs['area'] if 'area' in kwargs else ((math.pi * (self._diameter / 2.0)**2) if self._diameter is not None else None)
        self._mass        = kwargs['mass'] if 'mass' in kwargs else None
        self._circumference = math.pi * self._diameter if self._diameter is not None else None
        return

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
        return self._torque * self._w

    @property
    def torque(self):
        return self._torque
    @torque.setter
    def torque(self, tq):
        self._torque = tq - self.inertia_torque_x

    @property
    def force(self):
        return self._torque * self.radius

    @property
    def speed(self):
        return self._w
    def speed(self, rad_sec):
        if (rad_sec < 0.0):
            print("Rotational speed cannot be negative")
            raise ValueError
            return None
        self._w_last = self._w
        self._w = rad_sec

    @property
    @abstractmethod
    def inertia_x(self):
        ...



    @property
    def inertia_torque_x(self):
        return self.inertia_x * ( self._w - self._w_last ) / self._dt



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
        self._length = kwargs['length'] if 'length' in kwargs else None
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