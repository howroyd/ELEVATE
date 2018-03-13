#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import RotatingThingClass
import WheelClass
import MotorClass
import GeartrainClass


class AxleClass(RotatingThingClass.RotatingCylinderClass):
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

        self._wheels = [ RotatingThingClass.RotatingThingData(),
                            RotatingThingClass.RotatingThingData() ]

        self._shaft = RotatingThingClass.RotatingThingData()

        return super(RotatingThingClass.RotatingCylinderClass, self).__init__(_data)


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
        return self._wheels[0].data
   
    @property
    def rotation_right(self):
        return self._wheels[1].data


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
        self._wheels = new_data # Todo error checking here
        total_torque = 0.0
        total_speed = 0.0
        counter = 0
        for ptr in self._wheels:
            total_torque += ptr.get('torque')
            total_speed += ptr.get('speed')
            counter += 1
        self._shaft.torque = total_torque # This isn't true, may not be 5050, think stuck in mud
        self._shaft.speed  = total_speed / counter

    # Shaft rotational data
    @shaft_data.setter
    def shaft_data(self, new_data):
        self._shaft = new_data # Todo error checking here
        for ptr in self._wheels:
            ptr.torque = self._shaft.torque / len(self._wheels)
            ptr.speed  = self._shaft.speed # As above comment about mud


###############################
###############################
######       END         ######
###############################
###############################