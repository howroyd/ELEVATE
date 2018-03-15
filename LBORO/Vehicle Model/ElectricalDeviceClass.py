#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
from ElectricityClass import ElectricityClass

class ElectricalDeviceClass(ElectricityClass):
    '''Base class describing an electrial device'''
    _i_max_in = None
    _i_max_out = None
    _e_in    = 0.0
    _e_out   = 0.0
    _e_total = kwargs.get('e_start')
    _e_max   = kwargs.get('e_max')
    _e_min   = kwargs.get('e_min')

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs=dict()):
        return super().__init__()


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        if self._e_total is not None:
            e = self.power * dt

            if ( e >= 0 ):
                self._e_out += e
            else:
                self._e_in += e

            self._e_total -= e

            self._e_total = min(self._e_total, self._e_max)

            if self._e_total < self._e_min:
                self._v = 0.0
                self._i = 0.0
                print('Electrical device out of energy!')


    ###############################
    ###        GETTERS          ###
    ###############################

    # Energy output (cumulative)
    @property
    def energy(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_total

    # Energy left to minimum setpoint
    @property
    def e_to_empty(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_total - self._e_min

    # Energy left to maximum setpoint
    @property
    def e_to_full(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_total - self._e_max

    # Maximum energy in device
    @property
    def e_max(self):
        if self._e_total is None:
            raise NotImplementedError
        return self._e_max


    ###############################
    ###        SETTERS          ###
    ###############################

    # Force set energy stored in device
    @energy.setter
    def energy(self, e):
        self._e_total = e


###############################
###############################
######       END         ######
###############################
###############################