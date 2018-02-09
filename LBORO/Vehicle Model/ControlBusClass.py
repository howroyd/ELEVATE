import math

class ControlBusClass(object):
    def __init__(self, **kwargs):
        if ('signed' in kwargs):
            self._data_type = 'signed'
        elif ('unsigned' in kwargs):
            self._data_type = 'unsigned'
        else:
            print("Please specify constraint method")
            raise NotImplementedError
            return None

        self._val = 0
        self._val_last = 0
        self._min_unsigned = 0
        self._max_unsigned = 255
        self._min_signed = -127
        self._max_signed = 128

    def constrain(val):
        if ('signed' in self._data_type):
            return min(self._max_signed, max(self._min_signed, val))
        elif ('unsigned' in self._data_type):
            return min(self._max_unsigned, max(self._min_unsigned, val))
        else:
            print("Please specify constraint method")
            raise AttributeError
            return None

    @property
    def d_value(self):
        return self._val_last - self._val

    @property
    def value(self):
        return self._val
    @value.setter
    def value(self, val):
        last = self._val
        next = self.constrain(val)
        if Next is not None:
            self._val_last = last
            self._val = next
        
    @property
    def decimal(self):
        if ('signed' in self._data_type):
            return self._value / 128
        elif ('unsigned' in self._data_type):
            return self._value / 255
        else:
            print("Please specify constraint method")
            raise AttributeError
            return None