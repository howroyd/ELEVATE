import math
import ElectricalDeviceClass
import ElectricalManagementClass

class MotorClass(ElectricalDeviceClass.ElectricalDevice):
    """description of class"""
    # Tq = P*90549/rpm (mech)
    # Pe = Vs * I (elec)
    # Pm = Tq * w
    # Vemf = ki * w (w=rad/s, ki=const)
    # I = (Vs - Vemf) / R = (Vs - ki*w) / R (R=motor resistance)
    # Tq = kt * I
    # kt = ki (for 100% eff) therefor Pe=Pm

    # Ideally at stall speed there is no back emf, and at no the no-load speed the back emf is equal to the driving source voltage.

    # Instance constructor
    def __init__(self, connected_wheels, kwargs):
        self._connected_wheels = connected_wheels
        self._torque_shaft = 0.0 # post reduction gear
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
        self._torque_shaft = ((self._value/255)*self._max_torque) # TODO fudge
        self._torque_motor = self._torque_shaft / self._reduction_ratio
        wheel_speed = []
        for ptr in self._connected_wheels:
            ptr.motor_torque = self._torque_shaft / len(self._connected_wheels)
            wheel_speed.append(ptr.wheel_speed)
        self._w_shaft = sum(wheel_speed) / len(wheel_speed)
        self._w_motor = self._w_shaft * self._reduction_ratio
        if (self._w_motor > self._w_motor_max):
            print("Motor overspeed", self._w_motor, self._w_motor_max)
        return

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
