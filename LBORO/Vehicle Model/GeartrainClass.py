import RotatingThingClass

class GeartrainClass(RotatingThingClass.RotatingDiscClass):
    """description of class"""

# Instance constructor
    def __init__(self, forward_turn_ratio):
        super().__init__(self)
        self._forward_turn_ratio = forward_turn_ratio
        self._backward_turn_ratio = 1.0/ self._forward_turn_ratio
        return

    def convert_forward(self, torque=None, speed=None):
        torque_out = torque * self._forward_turn_ratio if torque is not None else None
        speed_out  = speed * self._backward_turn_ratio if speed is not None else None

        if torque is None: return speed_out
        elif speed is None: return torque_out
        else: return (torque, speed)

    def convert_backward(self, torque=None, speed=None):
        torque_out = torque * self._backward_turn_ratio if torque is not None else None
        speed_out  = speed * self._forward_turn_ratio if speed is not None else None

        if torque is None: return speed_out
        elif speed is None: return torque_out
        else: return (torque, speed)