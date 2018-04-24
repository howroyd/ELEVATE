<<<<<<< HEAD
import BrakesClass
import sys

# Ref: https://theses.lib.vt.edu/theses/available/etd-5440202339731121/unrestricted/CHAP3_DOC.pdf
=======
#!/usr/bin/python3
>>>>>>> linking_overhaul

###############################
###    IMPORT LIBRARIES     ###
###############################
from RotatingThingClass import RotatingCylinderShellClass, RotatingThingData
from BrakesClass import BrakesClass


<<<<<<< HEAD
# Instance constructor
    def __init__(self, brake, kwargs, name='wheel'):
        self._brake = brake
        self._force = 0.0
        self._motor_torque_in = 0.0
        self._wheel_diameter = kwargs['wheel_diameter']
        self._mass_on_wheel = kwargs['car_mass'] / 4.0 # TODO assumed 4 wheels equally balanced
        self._mu_road = 0.9 # Dry asphalt
        self._slip_peak = 0.15 # Approx from graph 4.2 in ref
        self._powertrain_model_array = None
        self._inertia_moment = 0.5#3.3e-3 # TODO get this number  ; wheel mass 21lbs, 9.5kg
        self._omega = 0.0
        self._omega_veh = 0.0
        self._omega_wheel = 0.0
        self._adhesion_coeff = 1.0
        self._adhesion_coeff2 = 1.0
        self._slip = 0.0
        self._slip2= 0.0
        self._brake_parking = True
        self._vehicle_speed = 0.0

        self._F_motor = 0.0
        self._F_brake = 0.0

        self._name = name
        self._data = dict()
        return

    @property
    def data(self):
        return self._data

    def update(self, dt):
        if self._brake_parking:
            self.reset()
            self._force += 0.2*(((self._mass_on_wheel * -self.vehicle_speed/dt) if dt > 0.0 else 0.0) - self._force) # TODO F=ma brute force
        else:

            self._brake.update(dt)

            self._F_motor = self._motor_torque_in / (self._wheel_diameter / 2.0)
            self._F_brake = self.brake_torque / (self._wheel_diameter / 2.0)

            self._force = self._F_motor + self._F_brake

        self._data.update(self._brake.data)
        self._data.update({(self._name+'_force_motor') : self._F_motor,
                            (self._name+'_force_brake') : self._F_brake,
                            (self._name+'_force') : self._force
        })

        return

    def reset(self):
        self._omega = 0.0
        self._omega_veh = 0.0
        self._omega_wheel = 0.0
        self._slip = 0.0
        self._slip2= 0.0

=======
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
>>>>>>> linking_overhaul
    @property 
    def force(self):
        # The main output of this class.  The total forward force provided by this wheel.
        return self._force
    @force.setter
    def force(self, veh_force):
        self._force = veh_force

    @property 
    def slip(self):
        return self._slip

    @property 
    def slip_peak(self):
        return self._slip_peak

    @property
    def brake_parking(self):
        return self._brake_parking
    @brake_parking.setter
    def brake_parking(self, state):
        if ((state is True) and (self._brake_parking is False)): self._force = 0.0
        self._brake_parking = state


    # Odometer
    @property 
    def odometer(self):
        return self._odometer


    # Axle torque
    @property
<<<<<<< HEAD
    def brake_value(self):
        return self._brake.value
    @brake_value.setter
    def brake_value(self, value):
        self._brake.value = value
=======
    def axle_data(self):
        return self.self._axle


    # Brake Rotational
    @property
    def brake_rotational(self):
        return self._brake.rotational_data
>>>>>>> linking_overhaul

    # Brake torque
    @property
    def brake_torque(self):
        return -self._brake.torque

    # Brake control signal
    @property
    def brake_control_sig(self):
        return self._brake.value

<<<<<<< HEAD
    @property
    def mu(self):
        return self._mu_road
    @mu.setter
    def mu(self, fric_coeff):
        self._mu_road = fric_coeff if fric_coeff > 0.0 else sys.exit("Invalid road friction coefficient (mu)")

    @property
    def vehicle_speed(self):
        return self._vehicle_speed
    @vehicle_speed.setter
    def vehicle_speed(self, speed):
        self._vehicle_speed = max(0.0, speed)

    def _calc_angular_acceleration(self): # LOOK AT THIS: http://www.thecartech.com/subjects/auto_eng/car_performance_formulas.htm
        #print(self._inertia_moment)
        #print(self.motor_torque, self._brake.torque)
        temp = (max(0.0, self.motor_torque) - self._brake.torque - (self._wheel_diameter/2.0) * ( self._force if False else 0.0 - self._calc_force_friction())) / self._inertia_moment # TODO 
        #print(temp/100)
        return temp

    def _calc_force_tractive(self): # Braking
        return self._adhesion_coeff * self._mass_on_wheel * 9.81

    def _calc_force_friction(self):
        return self._mass_on_wheel * 9.81 * 0.010 / (self._wheel_diameter/2.0) # Ref: https://en.wikipedia.org/wiki/Rolling_resistance
=======

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
>>>>>>> linking_overhaul
