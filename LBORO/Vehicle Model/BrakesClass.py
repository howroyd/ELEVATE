from Filters import LowPassFilter

class BrakesClass(object):
    """description of class"""


    # Instance constructor
    def __init__(self, diameter, max_torque, kwargs, name='brake'):
        self._temperature = 16.0 # TODO
        self._max_torque = max_torque
        self._current_torque = 0.0
        self._value = 0 # 0-255
        self._diameter = diameter
        self._lpf = LowPassFilter(0.01)
        self._name = name
        self._data = dict()
        return

    def update(self, dt):
        if self._value is None: self._value = 0.0
        if self._value > 0.0:
            # Calculate force & temperature (1-255)
            self._current_torque = self._lpf.get(max(0.0, (self._value/255)*self._max_torque))
        else:
            self._current_torque = 0.0

        self._data.update({(self._name+'_value') : self._value,
                    (self._name+'_torque') : self._current_torque,
        })

        return

    @property
    def data(self):
        return self._data

    @property
    def value(self):
        return self._value
    @value.setter
    def value(self, value):
        self._value = max(min(-value/10, 255), 0) if value is not None else 0.0
        #self._value = value
        #if value is None:
        #    self._value = self._lpf.reset()
        #else:
        #    self._value = self._lpf.get(max(min(-value/10, 255), 0) )
        
        

    @property
    def torque(self):
        return self._current_torque

    @property
    def temperature(self):
        return self._temperature