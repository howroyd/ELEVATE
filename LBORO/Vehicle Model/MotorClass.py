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
        self._v_min = kwargs['motor_v_min']
        self._v_max = kwargs['motor_v_max']
        self._i_max = kwargs['motor_i_max']
        self._p_max = kwargs['motor_p_max']
        self._reduction_ratio = kwargs['motor_reduction_ratio']
        self._wheel_diameter = kwargs['wheel_diameter']
        self._lpf = LowPassFilter(0.05)
        self._mechanical_efficiency = 0.96
        self._electrical_efficiency = 0.92
        self._max_rpm = kwargs['motor_max_rpm']
        #self._electricity = ElectricityClass.Electricity()
        self._name = name
        self._data = dict()
        return super().__init__(kwargs, name=self._name)

    #@property
    #def electricity(self):
    #    return self._output
    #@electricity.setter
    #def electricity(self, elec):
    #    pass

    def update(self, dt):
        self._shaft_torque = self._lpf.get((self._value/255)*self._max_torque)

        rotation = 0.0

        for ptr in self._connected_wheels:
            rotation += ptr.vehicle_speed

        rotation /= (len(self._connected_wheels) * pi * self._wheel_diameter)

        rotation *= self._reduction_ratio

        if (rotation > 0.0):
            mechanical_power = rotation * self._shaft_torque * (1.0/self._mechanical_efficiency)  # Supplied by motor # TODO 1.5 bodge

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
            ptr.motor_torque = self._shaft_torque / len(self._connected_wheels)

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

    @property
    def motor_value(self):
        return self._value
    @motor_value.setter
    def motor_value(self, value):
        self._value = max(min(value, 255), -255/4) if value is not None else 0.0
        #value = self._value + 1*(value - self._value)
        #self._value = max(min(value, 255), -255/4)
        #self._value = self._lpf.get(max(min(value, 255), -255/4))
        #print("value: ", self._value)
