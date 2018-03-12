import math
import RotatingThingClass
import ControlBusClass
import ElectricalDeviceClass
import ElectricalManagementClass

class MotorClass(ElectricalDeviceClass.ElectricalDeviceClass, RotatingThingClass.RotatingCylinderClass):
    """description of class"""
    # Tq = P*w (mech)
    # Pe = Vs * I (elec)
    # Pm = Tq * w
    # Vemf = kme * w (w=rad/s, ki=const)
    # I = (Vs - Vemf) / R = (Vs - kme*w) / R (R=motor resistance)
    # Tq = kem * I
    # kt = kme (for 100% eff) therefor Pe=Pm

    # Ideally at stall speed there is no back emf, and at no the no-load speed the back emf is equal to the driving source voltage.

    # Instance constructor
    def __init__(self, kwargs):

        _kwargs = dict(diameter=kwargs['motor_rotor_diameter'],
                mass=kwargs['motor_rotor_mass']
                )
        super(RotatingThingClass.RotatingCylinderClass, self).__init__(_kwargs)

        super(ElectricalDeviceClass.ElectricalDeviceClass, self).__init__()

        self._ctrl_sig    = ControlBusClass.ControlBusClass('signed')

        self._efficiency_elec_to_mech = 0.9
        self._efficiency_mech_to_elec = 0.9

        self._winding_resistance = 1.0

        self._is_generating = False

        self._torque_motor = 0.0
        self._torque_max  = kwargs['motor_max_torque']
        self._v_min = kwargs['motor_v_min']
        self._v_max = kwargs['motor_v_max']
        self._i_max = kwargs['motor_i_max']
        self._p_max = kwargs['motor_p_max']
        self._w_motor = 0.0
        self._w_motor_max = self.rpm_to_rads(kwargs['motor_max_rpm'])
        self._reduction_ratio = kwargs['motor_reduction_ratio']
        return

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
        RotatingThingClass.RotatingCylinderClass.update(dt) 
        self._w_motor = self.speed * self._reduction_ratio

        # Calculate how much torque we need to generate
        shaft_torque_demand = (self._ctrl_sig.decimal * self.torque_max*self._reduction_ratio) + self.inertia_torque_x
        motor_torque_demand = shaft_torque_demand / self._reduction_ratio
        motor_torque_demand = self.constrain_plus_minus(motor_torque_demand, self._torque_max)

        # First guess at current
        i = self.calculate_current_from_torque(motor_torque_demand)
        i = self.constrain_plus_minus(i, self._i_max)
        
        if (self._w_motor > self._w_motor_max):
            # If motor overspeed, only allow negative current (regen)
            i = min(i, 0.0)

        motor_torque_out = self.calculate_torque_from_current(i)

        # Calculate supply voltage required
        Vemf = self._efficiency_mech_to_elec * self._w_motor
        Vs = (i * self._winding_resistance) + Vemf

        if ( Vs > self._v_max ):    
            # If over-voltage, constrain and recalculate
            Vs = self._v_max
            i = (Vs - Vemf) / self._winding_resistance
            motor_torque_out = self.calculate_torque_from_current(i)

        self._v = Vs
        self._i = i
        self._torque_motor = motor_torque_out
        self.torque = motor_torque_out * self._reduction_ratio
        ElectricalDeviceClass.ElectricalDevice.update(dt)

        dissipated_power = abs(ElectricalDeviceClass.ElectricalDevice.get_p() - RotatingThingClass.RotatingCylinderClass.power)


    def calculate_current_from_torque(self, tq):
        return tq / self._efficiency_elec_to_mech

    def calculate_torque_from_current(self, i):
        return i * self._efficiency_elec_to_mech

    @staticmethod
    def constrain_plus_minus(var, constraint):
        return constraint * (var/abs(var)) if (abs(var) > constraint) else var

    @property
    def value(self):
        return self._value
    @value.setter
    def value(self, value):
        self._ctrl_sig.value = value

    @property
    def is_generating(self):
        return bool(self._i < 0)