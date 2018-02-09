import RotatingThingClass
import BrakesClass

class WheelClass(RotatingThingClass.RotatingCylinderShellClass):
    """description of class"""

# Instance constructor
    def __init__(self, **kwargs):
        self._brake = BrakesClass.BrakesClass(kwargs)

        super().__init__(self, diameter=kwargs['wheel_diameter'], mass=kwargs['wheel_mass'])

        self._force = 0.0

        self._axle_torque_in = 0.0

        self._road_drag = 0.0
        self._vehicle_speed = 0.0

        return

    def update(self, dt):
        self._brake.speed = self.speed

        super().update(dt)
        self._brake.update(dt)

        brake_torque = self._brake.torque
        if elf._brake.speed >= 0.0: brake_torque *= -1.0

        self.torque = self._axle_torque_in + brake_torque - self._road_drag # todo road drag

        self._force = self.torque / self.radius

        # todo wheel slip
        return

    @property 
    def force(self):
        return self._force

    @property
    def brake_control_sig(self):
        return self._brake.value
    @brake_control_sig.setter
    def brake_control_sig(self, value):
        self._brake.value = value

    @property
    def brake_torque(self):
        return self._brake.torque

    @property
    def axle_torque(self):
        return self._axle_torque_in
    @axle_torque.setter
    def axle_torque(self, torque):
        self._axle_torque_in = torque

    def set_wheel_speed(self, vehicle_speed):
        self.w = 2.0 * vehicle_speed / self.diameter
        return None