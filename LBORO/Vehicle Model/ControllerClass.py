#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import ControlBusClass

class ControllerClass(ControlBusClass.ControlBusClass):
    '''PID controller'''
    _key_p = 'p'
    _key_i = 'i'
    _key_d = 'd'
    _kp = None
    _ki = None
    _kd = None
    _i = 0.0
    _d = 0.0
    _error = 0.0
    _dont_update_flag = True
    _cost = 0.0
    _min_i = None
    _max_i = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kP, kI, kD, type):
        self._kp = kP
        self._ki = kI
        self._kd = kD
        super().__init__(type)
        self._min_i = self.min_val
        self._max_i = self.max_val


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt, error=None):
        if (self._dont_update_flag or dt<=0.0 or error==None):
            self._dont_update_flag = False
            return
        if self._ki is not 0:
            self._i += error*dt
            self._i = self.constrain(self._i*self._ki, self._min_i, self._max_i) / self._ki
        if self._kd is not 0:
            self._d = (error - self._error)/dt
        self._error = error
        #self._cost += abs(error)*dt # TODO machine learning on cost function

        self.value = self.error_p + self.error_i + self.error_d

        return


    ###############################
    ###     INTEGRAL LIMITS     ###
    ###############################
    def set_i_limits(self, min_i, max_i):
        self._min_i = min_i
        self._max_i = max_i

    ###############################
    ###         WIND UP         ###
    ###############################
    def anti_wind_up(self):
        self._i = 0.0

    ###############################
    ###          RESET          ###
    ###############################
    def reset(self):
        self._i = 0.0
        self._d = 0.0
        self._error = 0.0
        self._dont_update_flag = True


    ###############################
    ###        GETTERS          ###
    ###############################

    # PID Data
    @property
    def pid_data(self):
        return {self._key_p : self._error_p, self._key_i : self._error_i, self._key_d : self.error_d}

    # Cost Function Data
    @property
    def cost(self):
        return self._cost

    # Proportional Error
    @property
    def error_p(self):
        return self._error * self._kp

    # Integral Error
    @property
    def error_i(self):
        return self._i * self._ki

    # Derivative Error
    @property
    def error_d(self):
        return self._d * self._kd


###############################
###############################
######       END         ######
###############################
###############################