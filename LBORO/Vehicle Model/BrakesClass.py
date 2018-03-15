#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import math
from RotatingThingClass import RotatingDiscClass
from ControlBusClass import ControlBusClass


class BrakesClass(RotatingDiscClass):
    '''Brake for an electric vehicle wheel'''
    _shc_carbon_steel                 = 502.416
    _density_carbon_steel             = 7850.0
    _conductivity_to_air_carbon_steel = 36.0
    _temperature_ambient = None
    _temperature         = None
    _thickness           = None
    _torque_max          = None
    _ctrl_sig            = None
    _K_J                 = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        self._temperature_ambient   = 16.0
        self._thickness   = 0.015

        _diameter    = kwargs['brake_diameter']
        _area        = math.pi * (_diameter / 2.0)**2
        _mass        = _area * self._thickness * self._density_carbon_steel

        _kwargs = dict(diameter=kwargs['brake_diameter'],
                        area=_area,
                        mass=_mass
                        )

        RotatingDiscClass.__init__(self, _kwargs)

        self._torque_max  = kwargs['brake_max_torque']

        self._ctrl_sig    = ControlBusClass('unsigned')

        self._K_J         = 1.0 / ( self._shc_carbon_steel * _mass)

        return


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        super().update(dt)

        self.torque = self._ctrl_sig.decimal * self.torque_max

        power_gained = self.torque * self.w
        energy_gained = power_gained * dt

        power_lost = self._conductivity_to_air_carbon_steel * ( 2.0 * self.area ) * ( self._temperature_ambient - self._temperature ) * -1.0
        energy_lost = power_lost * dt
        
        self._temperature += (self._K_J * (energy_gained-energy_lost))

        return


    ###############################
    ###        GETTERS          ###
    ###############################

    # Control signal
    @property
    def value(self):
        return self._ctrl_sig.value


    # Maximum torque limit
    @property
    def torque_max(self):
        return self._torque_max


    # Brake temperature approximation
    @property
    def temperature(self):
        return self._temperature


    ###############################
    ###        SETTERS          ###
    ###############################

    # Control signal
    @value.setter
    def value(self, val):
        self._ctrl_sig.value = val

    # Maximum torque limit
    @torque_max.setter
    def torque_max(self, tq):
        if (tq < 0.0):
            print("Torque max cannot be negative")
            raise ValueError
            return None
        self._torque_max = tq


###############################
###############################
######       END         ######
###############################
###############################