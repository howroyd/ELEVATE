#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
from RotatingThingClass import RotatingCylinderClass, RotatingThingData

class AxleClass(RotatingCylinderClass):
    """Axle class for an electric vehicle"""
    _wheels = [ None, None ]
    _shaft  = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self):

        _data = { 'length' : 1.5,
                    'diameter' : 0.03,
                    'mass' : 5.0 }

        self._wheels = [ RotatingThingData(),
                            RotatingThingData() ]

        self._shaft = RotatingThingData()

        return super(RotatingCylinderClass, self).__init__(_data)


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        super().update(dt)


    ###############################
    ###        GETTERS          ###
    ###############################

    # Wheel rotational data
    @property
    def wheel_data(self):
        return self._wheels

    @property
    def rotation_left(self):
        return self._wheels[0].rotational_data
   
    @property
    def rotation_right(self):
        return self._wheels[1].rotational_data


    # Shaft rotational data
    @property
    def shaft_data(self):
        return self._shaft


    ###############################
    ###        SETTERS          ###
    ###############################
 
    # Wheel rotational data   
    @wheel_data.setter
    def wheel_data(self, new_data):
        if len(new_data) is not len(self._wheels):
            raise IndexError("Unable to set axle wheel data, length mismatch")

        total_torque = 0.0
        total_speed = 0.0
        counter = 0
        for x in range(len(self._wheels)):
            self._wheels[x].speed  = new_data[x].get('speed')
            self._wheels[x].torque = new_data[x].get('torque')
            total_torque          += self._wheels[x].speed
            total_speed           += self._wheels[x].torque
        self._shaft.torque = total_torque # This isn't true, may not be 5050, think stuck in mud
        self._shaft.speed  = total_speed / len(self._wheels)

    # Shaft rotational data
    @shaft_data.setter
    def shaft_data(self, new_data):
        for x in range(len(self._wheels)):
            self._wheels[x].speed  = new_data.get('speed')
            self._wheels[x].torque = new_data.get('torque') / len(self._wheels)


###############################
###############################
######       END         ######
###############################
###############################