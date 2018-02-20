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
        super().update(dt)

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

    @property
    def rotation_left(self):
        return self._wheels[0].data
    

    @property
    def rotation_right(self):
        return self._wheels[1].data
