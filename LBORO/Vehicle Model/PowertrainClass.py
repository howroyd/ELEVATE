import TractionControlClass


class PowertrainClass(object):
    """description of class"""

    def __init__(self, battery_array, motor_array, wheel_array, kwargs, name="powertrain"):
        self._battery_array = battery_array
        self._motor_array = motor_array
        self._wheel_array = wheel_array
        self._aero_model = kwargs['aero_model']
        self._total_force = 0.0
        self._speed_control = TractionControlClass.SpeedControlClass(battery_array, motor_array, wheel_array, kwargs, name="speedController")
        #self._speed_control = TractionControlClass.TractionControlClass(battery_array, motor_array, wheel_array, kwargs)
        self._data = dict()
        self._name = name

    def update(self, dt):
        self._speed_control.update(dt)
        self._total_force = sum(ptr.force for ptr in self._wheel_array)
        self._data.update(self._speed_control.data)
        self._data.update(self._motor_array[0].data)
        self._data.update({(self._name+'_force') : self._total_force})
        return

    @property
    def data(self):
        return self._data

    @property
    def target_speed(self):
        return self._speed_control.target
    @target_speed.setter
    def target_speed(self, speed):
        self._speed_control.target = max(0.0, speed)

    @property
    def feed_forward_speed(self):
        return self._speed_control.feed_forward
    @feed_forward_speed.setter
    def feed_forward_speed(self, speed):
        self._speed_control.feed_forward = max(0.0, speed)

    @property
    def dt(self):
        return self._dt
    @dt.setter
    def dt(self, dt):
        self._dt = dt
    
    @property
    def current_speed(self):
        return self._speed_control.current
    @current_speed.setter
    def current_speed(self, speed):
        self._speed_control.current = speed
        for ptr in self._wheel_array:
            ptr.vehicle_speed = speed

    @property
    def force(self):
        return self._total_force
    @force.setter
    def force(self, force_new):
        for ptr in self._wheel_array:
            ptr.force = force_new / len(self._wheel_array)
        return

    @property
    def error(self):
        return self._speed_control.error