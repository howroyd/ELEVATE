import math
import RotatingThingClass
import ControlBusClass
import ElectricalDeviceClass
import ElectricalManagementClass

class MotorClass(ElectricalDeviceClass.ElectricalDevice, RotatingThingClass.RotatingCylinderClass):
    """description of class"""
    # Tq = P*(rad/s) (mech)
    # Pe = Vs * I (elec)
    # Pm = Tq * w
    # Vemf = ki * w (w=rad/s, ki=const)
    # I = (Vs - Vemf) / R = (Vs - ki*w) / R (R=motor resistance)
    # Tq = kt * I
    # kt = ki (for 100% eff) therefor Pe=Pm

    # Ideally at stall speed there is no back emf, and at no the no-load speed the back emf is equal to the driving source voltage.

    # Instance constructor
    def __init__(self, **kwargs):

        RotatingThingClass.RotatingCylinderClass.__init__(self,
                                                            diameter=kwargs['motor_rotor_diameter'],
                                                            mass=kwargs['motor_rotor_mass'] )

        ElectricalDeviceClass.ElectricalDevice.__init__(self)

        self._torque_max  = kwargs['motor_max_torque']

        self._ctrl_sig    = ControlBusClass.ControlBusClass('signed')

        self._efficiency_elec_to_mech = 0.9
        self._efficiency_mech_to_elec = 0.9

        self._requested_power = 0.0 # TODO power demand or current demand??? Includes inefficiencies
        self._received_v      = 0.0 # Voltage actually arrived at point of use
        self._received_i      = 0.0 # Current actually arrived at point of use

        self._winding_resistance = 1.0

        self._is_generating = False

        self._value = 0 # 0-255
        self._torque_motor = 0.0
        self._max_torque = kwargs['motor_max_torque']
        self._v_min = kwargs['motor_v_min']
        self._v_max = kwargs['motor_v_max']
        self._i_max = kwargs['motor_i_max']
        self._p_max = kwargs['motor_p_max']
        self._w_motor_max = kwargs['motor_max_rpm'] / 60.0 / 2.0 / math.pi
        self._w_motor = 0.0
        self._w_shaft = 0.0
        self._reduction_ratio = kwargs['motor_reduction_ratio']
        return super().__init__(kwargs)

    def update(self, dt):
        dissipated_power = 0.0

        # Dumb system.  May over current battery on regen.  Must handle this higher up and ramp off ctrl sig

        # Note; low voltages/currents are handled by PWM

        torque_demand = self._ctrl_sig.decimal * self.torque_max

        if (torque_demand >= 0.0):
            self._is_generating = False
        else:
            self._is_generating = True
            max_torque = -1.0 * self._efficiency_elec_to_mech * self._i # i must be the highest current that can be accepted by battery
            torque_demand = max(max_torque, torque_demand) # Override with max current that can be sunk

        # Find supply voltage to satisfy torque requirement
        vs = self._efficiency_elec_to_mech * ( (self._efficiency_elec_to_mech * self._efficiency_mech_to_elec * self.speed) + (torque_demand * self._winding_resistance) )
        i = ( (vs / ( self._efficiency_elec_to_mech**2 ) ) - self._efficiency_mech_to_elec * self.speed ) / self._winding_resistance
        tq = self._efficiency_elec_to_mech * i
        # Above works for motor under power, e.g. accelerating

        self.torque = ( self._efficiency_elec_to_mech * ( vs - ( self._efficiency_mech_to_elec * self.speed ) ) ) / self._winding_resistance

        self._i = self.torque / self._efficiency_elec_to_mech # Need a while loop to iterate if over current or voltage
        self._p = self.torque * self.speed

        if (torque_demand >= 0.0):
            self._p *= self._efficiency_elec_to_mech
        else:
            self._p *= self._efficiency_mech_to_elec

        self._v = self._p / self._i

    def calculate_torque(self, i=None, tq=None):
        if i is None and tq is None:
            print("Cannot calculate, no values entered!")
            raise AttributeError
        elif i is not None:
            # i is the max current we can sink, therefore generate
            pass

    @property
    def shaft_torque(self):
        return self._torque_shaft

    @property
    def motor_value(self):
        return self._value
    @motor_value.setter
    def motor_value(self, value):
        #value = self._value + 1*(value - self._value)
        self._value = max(min(value, 255), 0)

    @property
    def is_generating(self):
        return self._is_generating