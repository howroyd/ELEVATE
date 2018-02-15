import RotatingThingClass
import WheelClass
import MotorClass
import GeartrainClass


class AxleClass(RotatingThingClass.RotatingCylinderClass):
    """description of class"""

    # Instance constructor
    def __init__(self):

        _data = { 'length' : 1.5,
                    'diameter' : 0.03,
                    'mass' : 5.0 }

        self._wheels = [ RotatingThingClass.RotatingThingData(),
                            RotatingThingClass.RotatingThingData() ]

        self._shaft = RotatingThingClass.RotatingThingData()

        return super(RotatingThingClass.RotatingCylinderClass, self).__init__(**_data)

    def update(self, dt):
        for ptr in self._connected_wheels:
            ptr.speed = self.speed
        for ptr in self._connected_motors:
            ptr.speed = self.speed

        super().update(dt)

        self.torque = 0.0

        if self.num_motors is not None:
            torque_in = 0.0
            for ptr in self._connected_motors:  
                ptr.torque = self._reduction_gear.convert_backward(torque=(self.torque / self.num_motors)) # TODO assumes even loading
                ptr.update(dt)
                torque_in += self._reduction_gear.convert_forward(ptr.torque)
            self.torque = torque_in

        wheel_torque = 0.0
        for ptr in self._connected_wheels:
            # ptr.w = veh speed ## TODO
            ptr.axle_torque = self.torque / self.num_wheels
            ptr.update(dt)

            wheel_torque += ptr.torque
            
        self.torque = wheel_torque

    @property
    def wheel_data(self):
        return self._wheels
    @wheel_data.setter
    def wheel_data(self, new_data):
        self._wheels = new_data # Todo error checking here
        total_torque = 0.0
        total_speed = 0.0
        counter = 0
        for ptr in self._wheel:
            total_torque += ptr.torque
            total_speed += ptr.speed
            counter += 1
        self._shaft.torque = total_torque # This isn't true, may not be 5050, think stuck in mud
        self._shaft.speed  = total_speed / counter

    @property
    def shaft_data(self):
        return self._shaft
    @shaft_data.setter
    def shaft_data(self, new_data):
        self._shaft = new_data # Todo error checking here
        for ptr in self._wheel:
            ptr.torque = self._shaft.torque / len(self._wheels)
            ptr.speed  = self._shaft.speed # As above comment about mud
