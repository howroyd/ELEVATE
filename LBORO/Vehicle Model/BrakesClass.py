from Filters import LowPassFilter

class BrakesClass(object):
    """description of class"""


    # Instance constructor
    def __init__(self, diameter, max_torque, kwargs):
        self._temperature = 16.0 # TODO
        self._max_torque = max_torque
        self._current_torque = 0.0
        self._value = 0 # 0-255
        self._diameter = diameter
        self._lpf = LowPassFilter(1)
        return

    def update(self, dt):
        if self._value > 0:
            # Calculate force & temperature (1-255)
            self._current_torque = max(0.0, (self._value/255)*self._max_torque)
        else:
            self._current_torque = 0.0
        return

    @property
    def value(self):
        return self._value
    @value.setter
    def value(self, value):
        if value is None:
            self._value = self._lpf.reset()
        else:
            self._value = self._lpf.get(max(min(-value/10, 255), 0) )
        
        

    @property
    def torque(self):
        return self._current_torque

    @property
    def temperature(self):
        return self._temperature