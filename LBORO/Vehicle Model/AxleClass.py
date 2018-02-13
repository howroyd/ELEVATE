import RotatingThingClass
import WheelClass
import MotorClass
import GeartrainClass


class AxleClass(RotatingThingClass.RotatingCylinderClass):
    """description of class"""

    # Instance constructor
    def __init__(self, num_wheels, num_motors=None, kwargs):
        if (num_wheels <= 0) or (int(num_wheels) is not num_wheels):
            print("Axle must have a positive integer number of wheels connected")
            raise ValueError
            return None

        self._connected_wheels = [WheelClass.WheelClass(kwargs)] * num_wheels

        self._connected_motors = [MotorClass.MotorClass(kwargs)] * num_motors if num_motors is not None else None

        self._reduction_gear   = GeartrainClass.GeartrainClass( (1.0 / kwargs['motor_reduction_ratio']) )

        super().__init__(self)

        return

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
    def num_wheels(self):
        return len(self._connected_wheels)

    @property
    def num_motors(self):
        return len(self._connected_motors) if self._connected_motors else None

    @property
    def brake_control_sig(self):
        arr = []
        for ptr in self._connected_wheels:
            arr.append(ptr.brake_control_sig)
        return arr
    @brake_control_sig.setter
    def brake_control_sig(self, value):
        for ptr in self._connected_wheels:
            ptr.brake_control_sig = value

    @property
    def motor_control_sig(self):
        if self.num_motors is None: return None
        arr = []
        for ptr in self._connected_motors:
            arr.append(ptr.motor_control_sig)
        return arr
    @motor_control_sig.setter
    def motor_control_sig(self, value):
        for ptr in self._connected_motors:
            ptr.motor_control_sig = value