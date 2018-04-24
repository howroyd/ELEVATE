#!/usr/bin/python3

class LowPassFilter(object):
    '''Basic low pass filter'''
    _last = 0.0

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, gain):
        self._k = gain


    ###############################
    ###          RESET          ###
    ###############################
    def reset(self):
        self._last = 0
        return self._last


    ###############################
    ###         GETTER          ###
    ###############################
    def get(self, new_val):
        self._last = self._last + self._k*(new_val - self._last)
        return self._last


###############################
###############################
######       END         ######
###############################
###############################
