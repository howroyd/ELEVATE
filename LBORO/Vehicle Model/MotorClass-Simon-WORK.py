import ElectricityClass
from Filters import LowPassFilter
from math import pi

class MotorClass(ElectricityClass.ElectricalDevice):
    """description of class"""

    # Instance constructor
    def __init__(self, connected_wheels, kwargs, name="motor"):
        self._connected_wheels      = connected_wheels
        self._shaft_torque          = 0.0
        self._motor_torque          = 0.0
        self._rolling_resistance    = 0.0
        self._value                 = 0 # 0-255
        self._max_torque            = kwargs['motor_max_torque']
        self._v_min                 = kwargs['motor_v_min']
        self._v_max                 = kwargs['motor_v_max']
        self._i_max                 = kwargs['motor_i_max']
        self._p_max                 = kwargs['motor_p_max']
        self._reduction_ratio       = kwargs['motor_reduction_ratio']
        self._wheel_diameter        = kwargs['wheel_diameter']
        self._lpf                   = LowPassFilter(0.05)
        self._mechanical_efficiency = 0.96
        self._electrical_efficiency = 0.92
        self._max_rpm               = kwargs['motor_max_rpm']
        #self._electricity = ElectricityClass.Electricity()
        self._name                  = name
        self._regen_activated       = False
        self._time_last             = 0.0
        self._dt                    = 0.01
        self._data                  = dict()
        self._rotation              = 0.0
        self._last_torque           = 0.0
        return super().__init__(kwargs, name=self._name)

    #@property
    #def electricity(self):
    #    return self._output
    #@electricity.setter
    #def electricity(self, elec):
    #    pass

    def update(self, dt):
        self._dt        = dt# - self._time_last
        self._time_last = dt

        ## Shaft rotation
        omega_at_motor = 0.0

        # Calculate average rotational velocity of wheel.  Assumptions about differential here!
        for ptr in self._connected_wheels:
            omega_at_motor += ptr.vehicle_speed
        omega_at_motor /= (len(self._connected_wheels) * pi * self._wheel_diameter)

        omega_at_motor *= self._reduction_ratio

        max_torque_available = -self._max_torque/(self._max_rpm*pi*2.0/60.0) * omega_at_motor + self._max_torque
        
        torque_demand = (self._value/255) * max_torque_available

        mechanical_power = torque_demand*omega_at_motor * (2.0-self._mechanical_efficiency)
        electrical_power = mechanical_power * (2.0-self._electrical_efficiency) # Required

        current = electrical_power / self._v

        if current > self._i_max:
            current = self._i_max
            electrical_power = self._v * current
        if electrical_power > self._p_max:
            electrical_power = self._p_max
            current = electrical_power / self._v
        if current > self._i_max:
            current = self._i_max
            electrical_power = self._v * current

        self._i = current
        self._p = electrical_power
            
        for ptr in self._connected_wheels:
            ptr.motor_torque = self._motor_torque*self._reduction_ratio / len(self._connected_wheels)

        #self._error = None
        super().update(dt)

        self._data.update(super().data)
        self._data.update({(self._name+'_shaftTorque') : torque_demand,
                            (self._name+'_rotation') : omega_at_motor,
                            (self._name+'_value') : self.motor_value,
                            (self._name+'_v') : self.v,
                            (self._name+'_i') : self.i,
                            (self._name+'_p') : self.p,
                            })
        return

    @property
    def data(self):
        return self._data

    @property
    def shaft_torque(self):
        return self._shaft_torque

    @property
    def rotation(self):
        return self._rotation

    @property
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

        value = self._value + 0.85*self._dt*(value - self._value) # TODO this is Tract control

        if self._regen_activated:
            self._value = max(min(value, 255), -255/4) if value is not None else 0.0
        else:
            self._value = max(min(value, 255), 0) if value is not None else 0.0
