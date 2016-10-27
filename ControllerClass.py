class ControllerClass(object):
    """description of class"""

    def __init__(self, kP, kI, kD):
        self._kp = kP
        self._ki = kI
        self._kd = kD
        self._i = 0.0
        self._d = 0.0
        self._error = 0.0

    def update(self, dt, error):
        if (dt <= 0.0): return
        self._i += error*dt
        self._d = (error - self._error)/dt
        self._error = error
        return

    def set_wind_up(self):
        pass

    def reset(self):
        self._i = 0.0
        self._d = 0.0
        self._error = 0.0

    @property
    def error(self):
        return self.error_p + self.error_i + self.error_d

    @property
    def error_p(self):
        return self._error * self._kp

    @property
    def error_i(self):
        return self._i * self._ki

    @property
    def error_d(self):
        return self._d * self._kd
