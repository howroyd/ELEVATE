#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import RotatingThingClass
import BrakesClass

class WheelClass(RotatingThingClass.RotatingCylinderShellClass):
    '''Wheel class for an electric vehicle'''
    _brake = None
    _force = None
    _axle_torque_in = None
    _road_drag      = None
    _vehicle_speed  = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        self._brake = BrakesClass.BrakesClass(kwargs)

        _kwargs = dict(diameter=kwargs['wheel_diameter'],
                mass=kwargs['wheel_mass']
                )
        RotatingThingClass.RotatingCylinderShellClass.__init__(self, _kwargs)

        self._force = 0.0

        self._axle_torque_in = 0.0

        self._road_drag = 0.0
        self._vehicle_speed = 0.0

        return


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        self._brake.speed = self.speed

        super().update(dt)
        self._brake.update(dt)

        brake_torque = self._brake.torque
        if self._brake.speed >= 0.0: brake_torque *= -1.0

        self.torque = self._axle_torque_in + brake_torque - self._road_drag # todo road drag

        self._force = self.torque / self.radius

        # todo wheel slip
        return


    ###############################
    ###        FEEDBACK         ###
    ###############################
    def set_wheel_speed(self, vehicle_speed):
        self.w = 2.0 * vehicle_speed / self.diameter
        return None


    ###############################
    ###        GETTERS          ###
    ###############################

    # Net lateral force
    @property 
    def force(self):
        return self._force


    # Axle torque
    @property
    def axle_torque(self):
        return self._axle_torque_in


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
    @axle_torque.setter
    def axle_torque(self, torque):
        self._axle_torque_in = torque


    # Brake control signal
    @brake_control_sig.setter
    def brake_control_sig(self, value):
        self._brake.value = value


###############################
###############################
######       END         ######
###############################
###############################