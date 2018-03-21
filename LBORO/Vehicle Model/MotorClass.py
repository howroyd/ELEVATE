#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import math
from RotatingThingClass import RotatingCylinderClass, rpm_to_rads
from ElectricalDeviceClass import ElectricalDeviceClass

class MotorClass(ElectricalDeviceClass, RotatingCylinderClass):
    '''Motor for an electric vehicle'''
    # Tq = P*w (mech)
    # Pe = Vs * I (elec)
    # Pm = Tq * w
    # Vemf = kme * w (w=rad/s, ki=const)
    # I = (Vs - Vemf) / R = (Vs - kme*w) / R (R=motor resistance)
    # Tq = kem * I
    # kt = kme (for 100% eff) therefor Pe=Pm

    # Ideally at stall speed there is no back emf, and at no the no-load speed the back emf is equal to the driving source voltage.

    _ctrl_sig                = None
    _efficiency_elec_to_mech = 0.9
    _efficiency_mech_to_elec = 0.9
    _winding_resistance      = 1.0
    _is_generating           = False
    _torque_motor            = 0.0
    _torque_max              = None
    _v_min                   = None
    _v_max                   = None
    _i_max                   = None
    _p_max                   = None
    _w_motor                 = 0.0
    _w_motor_max             = None
    _reduction_ratio         = None
    _v_in                    = None
    _i_in                    = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):

        _kwargs = dict(diameter=kwargs['motor_rotor_diameter'],
                mass=kwargs['motor_rotor_mass']
                )
        super(RotatingCylinderClass, self).__init__(_kwargs)

        super(ElectricalDeviceClass, self).__init__()

        self._torque_max  = kwargs['motor_max_torque']
        self._v_min = kwargs['motor_v_min']
        self._v_max = kwargs['motor_v_max']
        self._i_max = kwargs['motor_i_max']
        self._p_max = kwargs['motor_p_max']
        self._w_motor_max = rpm_to_rads(kwargs['motor_max_rpm'])
        self._reduction_ratio = kwargs['motor_reduction_ratio']
        
        return


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        # Dumb system.  May over current battery on regen.  Must handle this higher up and ramp off ctrl sig
        # Note; low voltages/currents are handled by PWM

        # Update shaft speed
        # Calculate torque demand
        # Account for inertia, new torque demand
        # Calculate current
        # Calculate torque
        # Calculate voltage

        ## Calculate torque demand from control signal
        # Update for intertia
        super(RotatingCylinderClass, self).update(dt) 
        self._w_motor = self.speed * self._reduction_ratio

        # If motor overspeed, only allow negative current (regen)
        if (self._w_motor > self._w_motor_max):
            self.current = min(self.current, 0.0)

        motor_torque_out = self.calculate_torque_from_current(self.current)

        if self.is_generating:
            # Calculate supply voltage produced
            Vemf = self._efficiency_mech_to_elec * self._w_motor
            Vs = (self.current * self._winding_resistance) + Vemf

            if ( Vs > self._v_max ):    
                # If over-voltage, constrain and recalculate
                Vs = self._v_max
                self.current = (Vs - Vemf) / self._winding_resistance
                motor_torque_out = self.calculate_torque_from_current(self.current)

            self.voltage = Vs
            print("regen: ", self.voltage, self.current)

        self._torque_motor = motor_torque_out
        self.torque = motor_torque_out * self._reduction_ratio
        super(ElectricalDeviceClass, self).update(dt)

        dissipated_power = abs(super(ElectricalDeviceClass, self).power - super(RotatingCylinderClass, self).power)


    ###############################
    ###     OLD UPDATE LOOP     ###
    ###############################
    def old_update(self, dt):
        # Dumb system.  May over current battery on regen.  Must handle this higher up and ramp off ctrl sig
        # Note; low voltages/currents are handled by PWM

        # Update shaft speed
        # Calculate torque demand
        # Account for inertia, new torque demand
        # Calculate current
        # Calculate torque
        # Calculate voltage

        ## Calculate torque demand from control signal
        # Update for intertia
        RotatingThingClass.RotatingCylinderClass.update(dt) 
        self._w_motor = self.speed * self._reduction_ratio

        motor_torque_out = self.calculate_torque_from_current(self._i_in)

        # Calculate supply voltage required
        Vemf = self._efficiency_mech_to_elec * self._w_motor
        Vs = (self._i_in * self._winding_resistance) + Vemf

        if ( Vs > self._v_max ):    
            # If over-voltage, constrain and recalculate
            Vs = self._v_max
            self._i_in = (Vs - Vemf) / self._winding_resistance
            motor_torque_out = self.calculate_torque_from_current(self._i_in)

        self._v = Vs
        self._i = self._i_in
        self._torque_motor = motor_torque_out
        self.torque = motor_torque_out * self._reduction_ratio
        ElectricalDevice.update(dt)

        dissipated_power = abs(ElectricalDevice.get_p() - RotatingThingClass.RotatingCylinderClass.power)


    ###############################
    ###       ELECTRICITY       ###
    ###############################
    def set_electricity(self, voltage, current):
        self.voltage            = voltage
        self.current            = current    

    ###############################
    ###         CURRENT         ###
    ###############################
    def calculate_current_from_torque(self, tq):
        return tq / self._efficiency_elec_to_mech


    ###############################
    ###         TORQUE          ###
    ###############################
    def calculate_torque_from_current(self, i):
        return i * self._efficiency_elec_to_mech


    ###############################
    ###  SYMMETRIC CONSTRAINT   ###
    ###############################
    @staticmethod
    def constrain_plus_minus(var, constraint):
        return constraint * (var/abs(var)) if (abs(var) > constraint) else var


    ###############################
    ###        GETTERS          ###
    ###############################

    # Binary logic for if in regen mode
    @property
    def is_generating(self):
        return bool(self._i < 0)


###############################
###############################
######       END         ######
###############################
###############################