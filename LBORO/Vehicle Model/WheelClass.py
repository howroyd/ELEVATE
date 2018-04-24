#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
from RotatingThingClass import RotatingCylinderShellClass, RotatingThingData
from BrakesClass import BrakesClass


class WheelClass(RotatingCylinderShellClass):
    '''Wheel class for an electric vehicle'''
    _brake = None
    _force = None
    _axle_torque_in = None
    _road_drag      = None
    _vehicle_speed  = None
    _odometer = 0.0

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        self._brake = BrakesClass(kwargs)

        _kwargs = dict(diameter=kwargs['wheel_diameter'],
                mass=kwargs['wheel_mass'],
                length=kwargs['wheel_width']
                )
        RotatingCylinderShellClass.__init__(self, _kwargs)

        self._force = 0.0

        self._axle = RotatingThingData()

        self._road_drag = 0.0
        self._vehicle_speed = 0.0

        return


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        super().update(dt)

        self._brake.temperature = self._brake.temperature_amb

        self._brake.update(dt)

        #if self._brake.speed >= 0.0: brake_torque *= -1.0

        self.torque = self._axle.torque + self._brake.torque - self._road_drag # todo road drag

        self._force = self.torque / self.radius

        self._odometer += self.speed * self.radius * dt

        # todo wheel slip
        return


    ###############################
    ###        FEEDBACK         ###
    ###############################
    def vehicle_speed_feedback(self, vehicle_speed):
        self.speed = 2.0 * vehicle_speed / self.diameter
        self.speed = self.speed # HACK TO FORCE w_last
        self._brake.speed = self.speed
        self._brake.speed = self.speed
        return self.speed


    ###############################
    ###        GETTERS          ###
    ###############################

    # Net lateral force
    @property 
    def force(self):
        return self._force


    # Odometer
    @property 
    def odometer(self):
        return self._odometer


    # Axle torque
    @property
    def axle_data(self):
        return self.self._axle


    # Brake Rotational
    @property
    def brake_rotational(self):
        return self._brake.rotational_data

    # Brake torque
    @property
    def brake_torque(self):
        return self._brake.torque

    # Brake control signal
    @property
    def brake_control_sig(self):
        return self._brake.value


    ###############################
    ###        SETTERS          ###
    ###############################

    # Axle torque
    @axle_data.setter
    def axle_data(self, data_dict):
        self._axle.rotational_data = data_dict


    # Brake control signal
    @brake_control_sig.setter
    def brake_control_sig(self, value):
        self._brake.value = value


###############################
###############################
######       END         ######
###############################
###############################