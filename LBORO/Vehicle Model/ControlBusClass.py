import math

class ControlBusClass(object):
    def __init__(self, type):
        if ('signed' in type):
            self._data_type = "signed"
        elif ('unsigned' in type):
            self._data_type = "unsigned"
        else:
            print("Please specify constraint method")
            raise NotImplementedError

        self._val = 0
        self._val_last = 0

        self._min = -127 if ('signed' in type) else 0
        self._max = 128 if ('signed' in type) else 255

    @staticmethod
    def constrain(val, _min, _max):
        return min(_max, max(_min, val))

    @property
    def d_value(self):
        return self._val_last - self._val

    @property
    def value(self):
        return self._val
    @value.setter
    def value(self, val):
        last = self._val
        next = self.constrain(val, self._min, self._max)
        if Next is not None:
            self._val_last = last
            self._val = next
        
    @property
    def decimal(self):
        return self._value / self._max

    @property
    def min_val(self):
        return self._min
    @min_val.setter
    def min_val(self, _min):
        self._min = _min

    @property
    def max_val(self):
        return self._max
    @max_val.setter
    def max_val(self, _max):
        self._max = _max