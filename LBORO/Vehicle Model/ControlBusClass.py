#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import math


###############################
###    UTILITY FUNCTIONS    ###
###############################

# Constrain
def constrain(val, _min, _max):
    return min(_max, max(_min, val))


class ControlBusClass(object):
    '''Data handler for a PID controller'''
    _data_type = None
    _val       = 0.0
    _val_last  = 0.0
    _min       = 0
    _max       = 255

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, type):
        if (type is "signed"):
            self._data_type = type
        elif (type is "unsigned"):
            self._data_type = type
        else:
            print("Please specify constraint method")
            raise NotImplementedError

        self._min = 0   if (type is "unsigned") else -127
        self._max = 255 if (type is "unsigned") else 128


    ###############################
    ###        OVERFLOW         ###
    ###############################
    def check_overflow(self, val):
        new_val = self._val + val
        return new_val - constrain(new_val, self._min, self._max)


    ###############################
    ###        GETTERS          ###
    ###############################

    # Control signal (raw)
    @property
    def value(self):
        return self._val

    # Control signal (decimal)
    @property
    def decimal(self):
        return self._val / self._max


    # Delta of the control signal
    @property
    def d_value(self):
        return self._val_last - self._val


    # Maximum value limit
    @property
    def max_val(self):
        return self._max

    # Minimum value limit
    @property
    def min_val(self):
        return self._min


    # Binary logic for bound at upper limit
    @property
    def at_maximum(self):
        return True if self._val >= self._max else False

    # Binary logic for bound al lower limit
    @property
    def at_minimum(self):
        return True if self._val <= self._min else False


    ###############################
    ###        SETTERS          ###
    ###############################
 
    # Control signal (raw)
    @value.setter
    def value(self, val):
        last = self._val
        next = constrain(val, self._min, self._max)
        if next is not None:
            self._val_last = last
            self._val = next

    # Maximum value limit
    @max_val.setter
    def max_val(self, _max):
        self._max = _max

    # Minimum value limit
    @min_val.setter
    def min_val(self, _min):
        self._min = _min


###############################
###############################
######       END         ######
###############################
###############################