import WheelClass
import MotorClass
import BrakesClass
import ControllerClass
import enum

PowertrainState = { 'initialising',
                    'stopped',
                    'accelerating',
                    'cruising',
                    'coasting',
                    'deccelerating',
                    'braking',
                    'error'}
PowertrainState = dict( zip( PowertrainState, range(len(PowertrainState)) ) )

ControlState = { 'off',
                    'too_fast',
                    'too_slow',
                    'ok',
                    'error'}
ControlState = dict( zip( ControlState, range(len(ControlState)) ) )
    

class SpeedControlClass(ControllerClass.ControllerClass):
    """Takes in the current and target speeds and outputs a control signal"""
    
    def __init__(self, battery_array, motor_array, wheel_array, kwargs):
        self._state = PowertrainState['initialising']
        self._control_state = ControlState['off']
        self._battery_array = battery_array
        self._motor_array = motor_array
        self._wheel_array = wheel_array
        self._brake_array = kwargs['brake_model_array']
        self._i = 0.0
        self._d = 0.0
        #self._kp = 10#0.8
        #self._ki = 0.001#0.005
        #self._kd = 20#3.0
        #self._kp = 60.0
        #self._ki = 0.05
        #self._kd = 5.0
        self._dv = 0.0
        self._dv_last = 0.0
        self._dv_next = None
        self._target = 0.0
        self._current = 0.0
        self._feed_forward = None
        self._k_feed_forward = 5
        self._state = PowertrainState['stopped']
        self._hysteresis = 10
        return super().__init__(150, 50, -7.5)  # 128, 16, 0
        #return super().__init__(15, 0.05, 1)
        #self._speed_controller = ControllerClass.ControllerClass(10, 0.001, 20)

    @property
    def state(self):
        return self._state

    def update(self, dt, model_update=True):
        state_last = self._state
        super().update(dt, self.dv)
        #if (state_last != self._state):
        #    super().reset()

        if (self._target == 0.0 and self._current == 0.0):
            # We are stationary and want to stay that way!
            self._state = PowertrainState['stopped']
            self._control_state = ControlState['off']
            self.set_brakes(absolute=0.0) # Brakes off
            self.set_motor(absolute=0.0) # Motor off
            super().reset()

        elif (super().error == 0.00 and self.target == 0.00):
            # Stationary
            self._state = PowertrainState['stopped']
            for ptr in self._motor_array:
                ptr.motor_value = 0.00
            for ptr in self._wheel_array:
                ptr.brake_value = 0.00
            super().reset()

        elif (super().error > self._hysteresis):
            # Too slow
            self._control_state = ControlState['too_slow']
            if sum(ptr.brake_torque for ptr in self._wheel_array) > 0.00:
                # Brakes are on, so release
                self._state = PowertrainState['deccelerating']
                #print('Brakes are on, so release')
                self.set_brakes(relative=-super().error)
            else:
                # Brakes not on, increase motor power
                self._state = PowertrainState['accelerating']
                #print('Brakes not on, increase motor power')
                self.set_motor(relative=super().error)

        elif (super().error < -self._hysteresis):
            # Too fast
            self._control_state = ControlState['too_fast']
            if sum(ptr.motor_value for ptr in self._motor_array) > 0.00:
                # Motors are on, reduce power
                self._state = PowertrainState['accelerating']
                #print('Motors are on, reduce power')
                self.set_motor(relative=super().error)
            else:
                # Motors not on, apply brakes
                self._state = PowertrainState['deccelerating']
                #print('Motors not on, apply brakes')
                self.set_brakes(relative=-super().error)

        else:
            # Within hysteresis bracket
            if (self._control_state is ControlState['too_slow']):
                # Too slow
                if sum(ptr.brake_torque for ptr in self._wheel_array) > 0.00:
                    # Brakes are on, so release
                    self._state = PowertrainState['deccelerating']
                    #print('Brakes are on, so release')
                    self.set_brakes(relative=-super().error)
                else:
                    # Brakes not on, increase motor power
                    self._state = PowertrainState['accelerating']
                    #print('Brakes not on, increase motor power')
                    self.set_motor(relative=super().error)

            elif (self._control_state is ControlState['too_fast']):
                # Too fast
                if sum(ptr.motor_value for ptr in self._motor_array) > 0.00:
                    # Motors are on, reduce power
                    self._state = PowertrainState['accelerating']
                    #print('Motors are on, reduce power')
                    self.set_motor(relative=super().error)
                else:
                    # Motors not on, apply brakes
                    self._state = PowertrainState['deccelerating']
                    #print('Motors not on, apply brakes')
                    self.set_brakes(relative=-super().error)

        if model_update: self._update_models(dt)

        #if (self._state == PowertrainState['stopped']):
        #    super().reset()

        return

    def _update_models(self, dt):
        # Update models
        for ptr in self._battery_array:
            ptr.update(dt)
        for ptr in self._motor_array:
            ptr.update(dt)
        for ptr in self._wheel_array:
            ptr.update(dt)

    def set_brakes(self, absolute=None, relative=None):
        if (absolute != None):
            for ptr in self._wheel_array:
                ptr.brake_value = absolute
        elif (relative != None):
            for ptr in self._wheel_array:
                ptr.brake_value = ptr.brake_value + relative/len(self._brake_array)
        else:
            pass # This shouldn't happen

    def set_motor(self, absolute=None, relative=None):
        if (absolute != None):
            for ptr in self._motor_array:
                ptr.motor_value = absolute
        elif (relative != None):
            for ptr in self._motor_array:
                ptr.motor_value = ptr.motor_value + relative/len(self._motor_array)
        else:
            pass # This shouldn't happen

    @property
    def target(self):
        return self._target
    @target.setter
    def target(self, value):
        self._target = max(0, value) # Positive numbers only

    @property
    def feed_forward(self):
        return self._feed_forward
    @feed_forward.setter
    def feed_forward(self, value):
        self._feed_forward = max(0, value) # Positive numbers only

    @property
    def current(self):
        return self._current
    @current.setter
    def current(self, value):
        self._current = max(0, value) # Positive numbers only
        for ptr in self._wheel_array:
            ptr.set_wheel_speed(self._current)
            
    @property
    def dv(self):
        if self._feed_forward is not None:
            return self._target + self._k_feed_forward*(self._feed_forward - self._target) - self._current
        else:
            return self._target - self._current

    @property
    def error(self):
        return super().error


class TractionControlClass(SpeedControlClass):
    """Takes a control signal and drives the brakes/motors"""
    
    def __init__(self, battery_array, motor_array, wheel_array, kwargs):
        self._brake_controller = ControllerClass.ControllerClass(0.9, 0.1, -0.05, 0, 255)
        self._motor_controller = ControllerClass.ControllerClass(1.5, 0.1, -0.025, -95, 255)
        #self._brake_controller = ControllerClass.ControllerClass(10, 0.6, -0.2, -255, 255)
        #self._motor_controller = ControllerClass.ControllerClass(5, 0.5, -2.0, -255, 255)
        #self._brake_controller.set_i_limits(0,255)
        self._brake_controller.set_i_limits(-50,50)
        self._motor_controller.set_i_limits(-50,50)
        self._error_brake = 0.0
        self._error_motor = 0.0 
        return super().__init__(battery_array, motor_array, wheel_array, kwargs)

    def update(self, dt):
        state_last = self._state
        super().update(dt, model_update=False)
        self._brake_controller.update(dt, self._error_brake)
        self._motor_controller.update(dt, self._error_motor)

        if ( super().state is PowertrainState['accelerating'] or super().state is PowertrainState['stopped']):
            self._brake_controller.anti_wind_up()
        if ( super().state is PowertrainState['deccelerating'] or super().state is PowertrainState['stopped'] ):
            self._motor_controller.anti_wind_up()

        #if (state_last != self._state):# or self._state==PowertrainState.stopped):
        #    self._brake_controller.reset()
        #    self._motor_controller.reset()
        for ptr in self._wheel_array:
                ptr.brake_value = self._brake_controller.error
        for ptr in self._motor_array:
                ptr.motor_value = self._motor_controller.error/len(self._motor_array)
        super()._update_models(dt)


    def set_brakes(self, absolute=None, relative=None):
        if (absolute == 0.0):
            for ptr in self._wheel_array:
                ptr.brake_value = absolute
            self._brake_controller.reset()
            self._error_brake = 0.0
        else:
            self._error_brake = (absolute if absolute!=None else relative if relative!=None else 0.0)

    def set_motor(self, absolute=None, relative=None):
        if (absolute == 0.0):
            for ptr in self._motor_array:
                ptr.motor_value = absolute
            self._motor_controller.reset()
            self._error_motor = 0.0
        else:
            self._error_motor = (absolute if absolute!=None else relative if relative!=None else 0.0)

    def control_brakes(self, absolute=None, relative=None):
        if (absolute != None):
            for ptr in self._wheel_array:
                ptr.brake_value = absolute
        elif (relative != None):
            for ptr in self._wheel_array:
                ptr.brake_value = ptr.brake_value + relative/len(self._brake_array)
        else:
            pass # This shouldn't happen

    def control_motor(self, absolute=None, relative=None):
        if (absolute != None):
            for ptr in self._motor_array:
                ptr.motor_value = absolute
        elif (relative != None):
            for ptr in self._motor_array:
                ptr.motor_value = ptr.motor_value + relative/len(self._motor_array)
        else:
            pass # This shouldn't happen

    