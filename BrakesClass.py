class BrakesClass(object):
    """description of class"""


    # Instance constructor
    def __init__(self, diameter, max_torque, kwargs):
        self._temperature = 16.0 # TODO
        self._max_torque = max_torque
        self._current_torque = 0.0
        self._value = 0 # 0-255
        self._diameter = diameter
        return

    def update(self, dt):
        if self._value > 0:
            # Calculate force & temperature (1-255)
            self._current_torque = (self._value/255)*self._max_torque
        else:
            self._current_torque = 0.0
        return

    @property
    def value(self):
        return self._value
    @value.setter
    def value(self, value):
        #value = self._value + 1*(value - self._value)
        self._value = max(min(value, 255), 0)

    @property
    def torque(self):
        return self._current_torque

    @property
    def temperature(self):
        return self._temperature