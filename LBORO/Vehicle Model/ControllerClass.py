class ControllerClass(object):
    """description of class"""

    def __init__(self, kP, kI, kD, min_val=-255, max_val=255):
        self._kp = kP
        self._ki = kI
        self._kd = kD
        self._i = 0.0
        self._d = 0.0
        self._error = 0.0
        self._dont_update_flag = True
        self._cost = 0.0
        self._min_val = min_val
        self._max_val = max_val
        self._min_i = min_val
        self._max_i = max_val

    def update(self, dt, error):
        if (self._dont_update_flag or dt<=0.0):
            self._dont_update_flag = False
            return
        if self._ki is not 0:
            self._i += error*dt
            self._i = self.constrain(self._i*self._ki, self._min_i, self._max_i) / self._ki
        if self._kd is not 0:
            self._d = (error - self._error)/dt
        self._error = error
        self._cost += abs(error)*dt # TODO machine learning on cost function
        return

    def set_i_limits(self, min_i, max_i):
        self._min_i = min_i
        self._max_i = max_i

    def anti_wind_up(self):
        self._i = 0.0

    def reset(self):
        self._i = 0.0
        self._d = 0.0
        self._error = 0.0
        self._dont_update_flag = True

    @property
    def cost(self):
        return self._cost

    @staticmethod
    def constrain(val, min_val, max_val):
        return max(min(val, max_val), min_val)

    @property
    def error(self):
        return self.constrain(self.error_p + self.error_i + self.error_d, self._min_val, self._max_val)

    @property
    def error_p(self):
        return self.constrain(self._error * self._kp, self._min_val, self._max_val)

    @property
    def error_i(self):
        return self.constrain(self._i * self._ki, self._min_i, self._max_i)

    @property
    def error_d(self):
        return self._d * self._kd
