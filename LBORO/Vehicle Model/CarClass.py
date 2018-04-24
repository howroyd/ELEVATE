#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import time
<<<<<<< HEAD
import Cars
from Filters import LowPassFilter
=======
from AerodynamicsClass import AerodynamicsClass
from PowertrainClass2 import PowertrainControllerClass
>>>>>>> linking_overhaul


class CarClass(object):
    '''Class for an electric vehicle'''
    _powertrain   = None
    _aero_model   = None
    _vehicle_mass = None
    _speed        = 0.0
    _odometer     = 0.0

<<<<<<< HEAD
    # Instance constructor
    def __init__(self, kwargs=None, name="car"):
        if (kwargs is not None):
            self._aero_model = kwargs['aero_model']
            self._powertrain_model_array = kwargs['powertrain_model_array']
            self._vehicle_mass = kwargs['car_mass']
            self._speed = 0.0
            self._target_speed = 0.0
            self._feed_forward_speed = 0.0
            self._total_force = 0.0 
        self._lpf    = LowPassFilter(1)
        self._lpf_ff = LowPassFilter(1)
        self._data = dict()
        self._name = name
        return
=======
    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs=None):
        if (kwargs is None):
            raise Exception("Must define car data!")
        else:
            self._powertrain   = PowertrainControllerClass(kwargs)
            self._aero_model   = AerodynamicsClass(kwargs)
            self._vehicle_mass = kwargs.get('car_mass')
>>>>>>> linking_overhaul

    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
<<<<<<< HEAD
        for ptr in self._powertrain_model_array:
                ptr.current_speed = self.speed
                ptr.target_speed = self._target_speed
                ptr.force = self._total_force / len(self._powertrain_model_array)
                if self._feed_forward_speed is not None:
                    ptr.feed_forward_speed = self._feed_forward_speed
                ptr.update(dt)
=======
        self._powertrain.update(dt)
>>>>>>> linking_overhaul

        self._aero_model.update(self._speed)
        
        self._total_force = sum(ptr.force for ptr in self._powertrain_model_array) - self._aero_model.force

        #print(str(self._powertrain_model_array[0].force), '\t', str(sum(ptr.force for ptr in self._powertrain_model_array)))

        accn = self._total_force / self._vehicle_mass

<<<<<<< HEAD
        #print("accn=", accn, 'dt=', dt)

        self.speed = self.speed + accn*dt
        #print(accn*dt, dt)
        #print("speed=", self.speed, 'dt=', dt)

        self._data.update(self._powertrain_model_array[0].data)
        self._data.update(self._aero_model.data)
        self._data.update({(self._name+'_speed') : self.speed,
                            (self._name+'_accel') : accn,
                            (self._name+'_target_speed') : self.target_speed,
                            (self._name+'_dv') : self.dv,
                            (self._name+'_total_force') : self._total_force
        })

        return

    @property
    def data(self):
        return self._data

    @property
    def dv(self):
        return self.target_speed - self.speed

    @property
    def target_speed(self,):
        return self._target_speed
    @target_speed.setter
    def target_speed(self, speed):
        self._target_speed = self._lpf.get(speed)

    @property
    def feed_forward_speed(self,):
        return self._feed_forward_speed
    @feed_forward_speed.setter
    def feed_forward_speed(self, speed):
        self._feed_forward_speed = self._lpf_ff.get(speed)
=======
        #print(self._powertrain.force, self._aero_model.force)

        total_force = self._powertrain.force - self._aero_model.force

        accn = total_force / self._vehicle_mass
        self.speed += accn*dt
        self._powertrain.vehicle_speed = self.speed

        self._odometer += self.speed*dt
        return

>>>>>>> linking_overhaul

    ###############################
    ###     BATTERY CHARGER     ###
    ###############################
    def charge_battery(self, target_soc):
        self._battery.charge_to(target_soc)


    ###############################
    ###        GETTERS          ###
    ###############################

    # Actual vehicle speed
    @property
    def speed(self):
        return self._speed

    # Target speed
    @property
    def target_speed(self,):
        return self._powertrain.target_speed

    @property
    def odometer(self):
        return self._odometer


    # Aerodynamic Load
    @property
    def aero_force(self):
        return self._aero_model.force

    # Road Friction Drag
    @property
    def road_drag(self):
        return self._powertrain.road_drag

    # Powertrain Force
    @property
    def powertrain_force(self):
        return self._powertrain.force


    # Speed Controller PID
    @property
    def speed_ctrl_error(self):
        return self._powertrain.speed_ctrl_error
    @property
    def speed_ctrl_pid(self):
        return self._powertrain.speed_ctrl_pid

    # Motor Controller PID
    @property
    def motor_ctrl_error(self):
        return self._powertrain.motor_ctrl_error
    @property
    def motor_ctrl_pid(self):
        return self._powertrain.motor_ctrl_pid

    # Brake Controller PID
    @property
    def brake_ctrl_error(self):
        return self._powertrain.brake_ctrl_error
    @property
    def brake_ctrl_pid(self):
        return self._powertrain.brake_ctrl_pid


    # Motor Rotational
    @property
    def motor_rotation(self):
        return self._powertrain.motor_rotation

    # Axle Rotation
    @property
    def axle_rotation(self):
        return self._powertrain.axle_rotation

    # Wheel Rotational
    @property
    def wheel_rotation(self):
        return self._powertrain.wheel_rotation
    @property
    def odometer_wheels(self):
        return self._powertrain.odometer


    # Brake Rotational
    @property
    def brake_rotation(self):
        return self._powertrain.brake_rotation


    # Battery Electricity
    @property
    def battery_electricity(self):
        return self._powertrain.battery_electricity

    # ESC Electricity
    @property
    def esc_electricity(self):
        return self._powertrain.esc_electricity

    # Motor Electricity
    @property
    def motor_electricity(self):
        return self._powertrain.motor_electricity


    # Powertrain Controller Mode
    @property
    def powertrain_mode(self):
        return self._powertrain.controller_mode


    ###############################
    ###        SETTERS          ###
    ###############################

    # Actual vehicle speed
    @speed.setter
    def speed(self, value):
<<<<<<< HEAD
        self._speed = max(0.0, value)
=======
        if (value <= 0.0): value = 0.0
        self._speed = value
        self._powertrain.speed = value
>>>>>>> linking_overhaul

    # Target speed
    @target_speed.setter
    def target_speed(self, speed):
        self._powertrain.target_speed = speed


###############################
###############################
######       END         ######
###############################
###############################