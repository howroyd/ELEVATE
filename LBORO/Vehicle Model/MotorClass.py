<<<<<<< HEAD
import ElectricityClass
from Filters import LowPassFilter
from math import pi

class MotorClass(ElectricityClass.ElectricalDevice):
    """description of class"""

    # Instance constructor
    def __init__(self, connected_wheels, kwargs, name="motor"):
        self._connected_wheels = connected_wheels
        self._shaft_torque = 0.0
        self._value = 0 # 0-255
        self._max_torque = kwargs['motor_max_torque']
=======
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
    _efficiency_elec_to_mech = 0.85
    _efficiency_mech_to_elec = 0.7
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
>>>>>>> linking_overhaul
        self._v_min = kwargs['motor_v_min']
        self._v_max = kwargs['motor_v_max']
        self._i_max = kwargs['motor_i_max']
        self._p_max = kwargs['motor_p_max']
<<<<<<< HEAD
        self._reduction_ratio = kwargs['motor_reduction_ratio']
        self._wheel_diameter = kwargs['wheel_diameter']
        self._lpf = LowPassFilter(0.05)
        self._mechanical_efficiency = 0.96
        self._electrical_efficiency = 0.92
        self._max_rpm = kwargs['motor_max_rpm']
        #self._electricity = ElectricityClass.Electricity()
        self._name = name
        self._regen_activated = False
        self._time_last = 0.0
        self._dt = 0.01
        self._data = dict()
        return super().__init__(kwargs, name=self._name)

    #@property
    #def electricity(self):
    #    return self._output
    #@electricity.setter
    #def electricity(self, elec):
    #    pass
=======
        self._w_motor_max = rpm_to_rads(kwargs['motor_max_rpm'])
        self._reduction_ratio = kwargs['motor_reduction_ratio']
        
        return
>>>>>>> linking_overhaul


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
<<<<<<< HEAD
        self._dt = dt# - self._time_last
        self._time_last = dt

        self._shaft_torque = (self._value/255)*self._max_torque

        rotation = 0.0

        for ptr in self._connected_wheels:
            rotation += ptr.vehicle_speed

        rotation /= (len(self._connected_wheels) * pi * self._wheel_diameter)

        rotation /= self._reduction_ratio

        if (rotation > 0.0):
            mechanical_power = rotation * self._shaft_torque * (1.0/self._mechanical_efficiency)  # Supplied by motor

            self.p = min(self._p_max, mechanical_power * (1.0/self._electrical_efficiency)) # Required by motor
            # https://www.precisionmicrodrives.com/tech-blog/2015/08/03/dc-motor-speed-voltage-and-torque-relationships

            #print(self.p)

            #y=mx+c
            m = self._i_max / self._max_rpm # motor model

            self.i = m*rotation

            self.v = self.p / self.i

            if (self.v > self._v_max) or (self.v < self._v_min):
                self.v = max(self._v_min, min(self.v, self._v_max))
                #print("Overcurrent")
                self.i = self.p / self.v # Overcurrent for rotational speed

                if (self.i > self._i_max):
                    self.i = self._i_max
                    self.p = self.v * self.i

                if (self.p > self._p_max):
                    self.i = self._i_max
                    self.v = self.p / self.i       

                self._shaft_torque = self.p * self._electrical_efficiency * self._mechanical_efficiency / rotation

            if (self.i > self._i_max):
                self.i = self._i_max
                #print("Overvoltage")

                self.v = self.p / self.i # Overvoltage for rotational speed

                if (self.v > self._v_max):
                    self.v = self._v_max
                    self.p = self.v * self.i

                if (self.p > self._p_max):
                    self.v = self._v_max
                    self.i = self.p / self.v       

                self._shaft_torque = self.p * self._electrical_efficiency * self._mechanical_efficiency / rotation

        for ptr in self._connected_wheels:
            ptr.motor_torque = self._shaft_torque*self._reduction_ratio / len(self._connected_wheels)

        #self._error = None
        super().update(dt)

        self._data.update(super().data)
        self._data.update({(self._name+'_shaftTorque') : self.shaft_torque,
                            (self._name+'_value') : self.motor_value
                            })
        return

    @property
    def data(self):
        return self._data

    @property
    def shaft_torque(self):
        return self._shaft_torque
=======
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
        self._w_motor = self.speed * self._reduction_ratio
        super(RotatingCylinderClass, self).update(dt)

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
>>>>>>> linking_overhaul

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
        self._w_motor           = self.speed * self._reduction_ratio

        # If motor overspeed, only allow negative current (regen)
        if (self._w_motor > self._w_motor_max):
            pass
            #print("Motor overspeed! w=", round(self._w_motor_max), round(self._w_motor))
            #self.current = min(self.current, 0.0)

        motor_torque_out        = self.calculate_torque_from_current(self.current)

        if self.is_generating:
            # Calculate supply voltage produced
            Vemf = self._efficiency_mech_to_elec * self._w_motor
            Vs   = (self.current * self._winding_resistance) + Vemf

            if ( Vs > self._v_max ):    
                # If over-voltage, constrain and recalculate
                Vs = self._v_max
                self.current     = (Vs - Vemf) / self._winding_resistance
                motor_torque_out = self.calculate_torque_from_current(self.current)

            self.voltage = Vs
            print("regen: ", self.voltage, self.current)

        self._torque_motor       = motor_torque_out
        self.torque              = motor_torque_out * self._reduction_ratio


    ###############################
    ###         CURRENT         ###
    ###############################
    def calculate_current_from_torque(self, tq):
        return tq * self._efficiency_mech_to_elec


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
    ###        FEEDBACK         ###
    ###############################
    def shaft_speed_feedback(self, shaft_speed):
        self.speed    = shaft_speed
        self.speed    = shaft_speed # HACK TO FORCE w_last
        self._w_motor = self.speed * self._reduction_ratio
        return self.speed


    ###############################
    ###        GETTERS          ###
    ###############################

    # Binary logic for if in regen mode
    @property
<<<<<<< HEAD
    def regen_activated(self):
        return self._regen_activated
    @regen_activated.setter
    def regen_activated(self, value):
        self._regen_activated = bool(value)

    @property
    def motor_value(self):
        return self._value
    @motor_value.setter
    def motor_value(self, value):
        #if value > self._value and value > 0:
        value = self._value + 0.85*self._dt*(value - self._value) # TODO this is Tract control
        if self._regen_activated:
            self._value = max(min(value, 255), -255/4) if value is not None else 0.0
        else:
            self._value = max(min(value, 255), 0) if value is not None else 0.0
        #value = self._value + 1*(value - self._value)
        #self._value = max(min(value, 255), -255/4)
        #self._value = self._lpf.get(max(min(value, 255), -255/4))
        #print("value: ", self._value)
=======
    def is_generating(self):
        return bool(self._i < 0)


###############################
###############################
######       END         ######
###############################
###############################
>>>>>>> linking_overhaul
