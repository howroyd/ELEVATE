import WheelClass
import MotorClass
import BrakesClass
import ControllerClass
import enum

PowertrainState = { 'initialising',
                    'stopped',
                    'accelerating',
                    'cruising',
                    'deccelerating',
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

    @property
    def state(self):
        if   self._state is PowertrainState['initialising']:    return  0
        elif self._state is PowertrainState['stopped']:         return  1
        elif self._state is PowertrainState['accelerating']:    return  2
        elif self._state is PowertrainState['cruising']:        return  3
        elif self._state is PowertrainState['deccelerating']:   return  4
        elif self._state is PowertrainState['error']:           return -1

    def __init__(self, battery_array, motor_array, wheel_array, kwargs):
        self._state = PowertrainState['initialising']
        self._control_state = ControlState['off']
        self._battery_array = battery_array
        self._motor_array = motor_array
        self._wheel_array = wheel_array
        self._brake_array = kwargs['brake_model_array']
        self._dt_last = 0.0
        self._dv = 0.0
        self._dv_filtered = 0.0
        self._dv_last = 0.0
        self._dv_next = None
        self._target = 0.0
        self._current = 0.0
        self._feed_forward = None
        self._state = PowertrainState['stopped']
        self._regen = False # Set to None to disable

        self._hysteresis_speed = 0.25*1 # 0.45=1mph

        p = 100 # 100
        i = 100 # 100
        d = 0 # 3.5

        self._k_feed_forward = 2 # 15

        self._hysteresis = self._hysteresis_speed * p/10 # PID error

        return super(SpeedControlClass, self).__init__(p, i, d, min_i=-50, max_i=50)

    def update(self, dt):
        if ((self._target <= self._hysteresis_speed/10.0) and (self._current <= self._hysteresis_speed/10.0) and ((self._feed_forward <= self._hysteresis_speed/10.0) if self._feed_forward is not None else True)):
            if (self._state is not PowertrainState['stopped']):
                self._state = PowertrainState['stopped']
            super(SpeedControlClass, self).reset()

        super(SpeedControlClass, self).update(dt, self.dv)

        (motor, brake, parking) = self._control(super(SpeedControlClass, self).error, self.dv, self._hysteresis, self._hysteresis_speed,
                                                        True if (ptr.brake_parking for ptr in self._wheel_array) else False, verbose=False)

        if (brake is not None and parking is not True):
            if (brake > -255/4):
                motor = brake   
                brake = 0
            else:
                motor = -255/4
                brake = (brake + 255/4) * 4

        if parking:
            motor = 0

        self._set_motor(motor)
        self._set_brakes(brake, parking)

        self._update_models(dt)

    def _update_models(self, dt):
        #if (self._dt_last > dt):
            # Update models
            for ptr in self._battery_array:
                ptr.update(dt)
            for ptr in self._motor_array:
                ptr.update(dt)
            for ptr in self._wheel_array:
                ptr.update(dt)

            self._dt_last = dt

    def _set_motor(self, val, verbose=False):
        if verbose: print("Motor: ", end=' ')
        for ptr in self._motor_array:
            ptr.motor_value = val
            if verbose: print(str(int(ptr.motor_value)), end=' ')
        if verbose: print()

    def _set_brakes(self, val, parking=False, verbose=False):
        if verbose: print("Brake: ", end=' ')

        for ptr in self._wheel_array:
            ptr.brake_parking = parking
            ptr.brake_value = val
               
        if verbose: 
            if parking: print("parking brake on", end=' ')
            print(str(int(ptr.brake_value)), end=' ')   

        if verbose: print()

    def _control(self, pid_error, dv, hysteresis, v_hysteresis, parking, verbose=False):     
    ###################
    ## STATE MACHINE ##
    ###################
        motor_sig = None
        brake_sig = None
        state_last = self._state
        ###################
        ##    STOPPED    ##
        ###################
        if self._state is PowertrainState['stopped']:
            if (pid_error <= hysteresis):
                # Remain stopped
                self._control_state = ControlState['ok']
                motor_sig = None
                brake_sig = None
                parking   = True
            else:
                # Accelerate
                self._state         = PowertrainState['accelerating']
                self._control_state = ControlState['too_slow']   
                motor_sig = pid_error
                brake_sig = None
                parking   = False
        
        ###################
        ##   ACCELERATE  ##
        ###################
        elif self._state is PowertrainState['accelerating']:
            # Remain accelerating, cruise (not straight to coast or decelerate)
            if (pid_error > -hysteresis):
                # Continue accelerating
                self._control_state =  ControlState['ok'] if (pid_error <= hysteresis) else ControlState['too_slow']
                motor_sig = pid_error
                brake_sig = None
                parking   = False
            else:
                # Cruise
                self._state         = PowertrainState['cruising']
                self._control_state = ControlState['too_fast']   
                motor_sig = pid_error
                brake_sig = None
                parking   = False

        ###################
        ##     CRUISE    ##
        ###################
        elif self._state is PowertrainState['cruising']:
            # Remain cruising, accelerate or coast
            if (abs(dv) <= v_hysteresis):
                # Continue cruising
                self._control_state = ControlState['ok']   
                motor_sig = pid_error
                brake_sig = None
                parking   = False
            elif (dv > 0.0):
                # Accelerate
                self._state = PowertrainState['accelerating']
                self._control_state = ControlState['too_slow']   
                motor_sig = pid_error
                brake_sig = None
                parking   = False
            elif (dv < 0.0):
                # Deccel
                #self._state = PowertrainState['regen'] if (regen is not None) else PowertrainState['deccelerating']
                self._state = PowertrainState['deccelerating']
                self._control_state = ControlState['too_fast']   
                motor_sig = None
                brake_sig = pid_error
                parking   = False

        ###################
        ##     REGEN     ##
        ###################
        #elif self._state is PowertrainState['regen']:
        #    if (regen is None):
        #        print("Regen error - in regen mode with regen turned off")
        #        self._state = PowertrainState['error']

        #    # Remain in regen, cruise or decelerate
        #    if (pid_error < (-255/4)):
        #        # Decelerate, can't regen enough
        #        self._state = PowertrainState['deccelerating']
        #        self._control_state = ControlState['too_fast']   
        #        motor_sig = pid_error
        #        brake_sig = None
        #        parking   = False
        #        regen     = True if (regen is not None) else None
        #    elif (pid_error > 0.0):
        #        # Cruise
        #        self._state = PowertrainState['cruising']
        #        self._control_state = ControlState['too_slow']   
        #        motor_sig = pid_error
        #        brake_sig = None
        #        parking   = False
        #        regen     = False ## REGEN OFF
        #    else:
        #        # Continue regen
        #        self._control_state = ControlState['ok']   
        #        motor_sig = pid_error
        #        brake_sig = None
        #        parking   = False
        #        regen     = True if (regen is not None) else None               

        ###################
        ##     DECCEL    ##
        ###################
        elif self._state is PowertrainState['deccelerating']:
            # Remain decelerating
            if (pid_error <= hysteresis):
                self._control_state = ControlState['ok']
                parking   = False
                motor_sig = 0
                brake_sig = pid_error
            elif (pid_error > 0.0):
                # Cruise
                self._state         = PowertrainState['cruising']
                self._control_state = ControlState['too_slow']
                motor_sig = pid_error
                brake_sig = None
                parking   = False


        ###################
        ##     ERROR     ##
        ###################
        elif (self._state is PowertrainState['error'] or self._control_state is ControlState['error']):
            # Test to see if stationary. If so apply parking and relieve the error
            print("Speed controller in error state")
            self._control_state = ControlState['error']
            motor_sig = None
            brake_sig = None
            parking   = True
            regen     = False if (regen is not None) else None
        else:
            # WTF
            print("Speed controller in WTF state, it's completely broken mate, Alt+F4")
            self._control_state = ControlState['ok']
            motor_sig = None
            brake_sig = None
            parking   = True
            regen     = False if (regen is not None) else None

    ###################
    ##      END      ##
    ###################

        if (verbose and self._state is not state_last):
            print("State changed to " + str(self.state))
        if verbose:
            print("Motor: " + str(motor_sig) + "\tBrake: " + str(brake_sig))

        return (motor_sig, brake_sig, parking)


        
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
        


    @property
    def dv(self):
        if self._feed_forward is not None:
            return self._target + self._k_feed_forward*(self._feed_forward - self._target) - self._current
        else:
            return self._target - self._current

    @property
    def error(self):
        return super(SpeedControlClass, self).error


class TractionControlClass(SpeedControlClass):
    """Takes a control signal and drives the brakes/motors"""
    
    def __init__(self, battery_array, motor_array, wheel_array, kwargs):
        self._motor_controller = ControllerClass.ControllerClass(1, 0, 0, min_val=0, max_val=255)
        self._brake_controller = ControllerClass.ControllerClass(0, 0, 0, min_val=0, max_val=255)
        
        self._motor_controller.set_i_limits(-150,150)
        self._brake_controller.set_i_limits(-100,100)

        self._error_motor = 0.0 
        self._error_brake = 0.0
        return super(TractionControlClass, self).__init__(battery_array, motor_array, wheel_array, kwargs)

    def update(self, dt):
        state_last = self._state
        super(TractionControlClass, self).update(dt, model_update=False)
        self._brake_controller.update(dt, self._error_brake)
        self._motor_controller.update(dt, self._error_motor)

        if ( super(TractionControlClass, self).state is PowertrainState['accelerating'] ):
            self._brake_controller.anti_wind_up()
        if ( super(TractionControlClass, self).state is PowertrainState['deccelerating'] ):
            self._motor_controller.anti_wind_up()

        if ( super(TractionControlClass, self).state is PowertrainState['stopped'] ):
            for ptr in self._wheel_array:
                ptr.reset()
            self._brake_controller.reset()
            self._motor_controller.reset()

        # Anti slip
        trac_ctrl = False
        for ptr in self._wheel_array:
                if ptr.slip > ptr.slip_peak: trac_ctrl = True

#        if trac_ctrl:
#            for ptr in self._wheel_array:
#                    ptr.brake_value = self._brake_controller.error                        /2
#            for ptr in self._motor_array:
#                    ptr.motor_value = self._motor_controller.error/len(self._motor_array) /2
#        else:
        #for ptr in self._wheel_array:
        #        ptr.brake_value = self._brake_controller.error
        #for ptr in self._motor_array:
        #        ptr.motor_value = self._motor_controller.error/len(self._motor_array)

        #self.control_motor(relative=(self._motor_controller.error/len(self._motor_array)))
        #self.control_brakes(relative=self._brake_controller.error, parking=False)

        super(TractionControlClass, self)._update_models(dt)


    def set_brakes(self, absolute=None, relative=None, parking=False):
        #if parking: pass#print("Parking true")
        #else: print("Parking false")

        for ptr in self._wheel_array:
                ptr.brake_parking = parking

        if (absolute == 0.0):
            if absolute is not None:
                for ptr in self._wheel_array:
                    ptr.brake_value = absolute
                    
            self._brake_controller.reset()
            self._error_brake = 0.0
        else:                   
            self._error_brake = (absolute if absolute!=None else relative if relative!=None else 0.0)
            
            self._motor_controller.reset()
            self._error_motor = 0.0
            for ptr in self._wheel_array:
                ptr.brake_value = ptr.brake_value + self._error_brake/len(self._brake_array)

    def set_motor(self, absolute=None, relative=None):
        #print("Set motor; abs:", absolute, "rel:", relative)

        if (absolute == 0.0):
            for ptr in self._motor_array:
                ptr.motor_value = absolute
            self._motor_controller.reset()
            self._error_motor = 0.0
        else:
            self._error_motor = (absolute if absolute!=None else relative if relative!=None else 0.0)
            self._brake_controller.reset()
            self._error_brake = 0.0
            for ptr in self._motor_array:
                ptr.motor_value = ptr.motor_value + self._error_motor/len(self._motor_array)

        

    def control_brakes(self, absolute=None, relative=None, parking=False):
        for ptr in self._wheel_array:
                ptr.brake_parking = parking

        if (absolute != None):
            for ptr in self._wheel_array:
                ptr.brake_value = absolute
        elif (parking is True):
                for ptr in self._wheel_array:
                    ptr.brake_value = 0.0
        elif (relative != None):
            for ptr in self._wheel_array:
                ptr.brake_value = ptr.brake_value + relative/len(self._brake_array)
        else:
            pass # This shouldn't happen    
        #print("Brake val=", self._brake_array[0].value)

    def control_motor(self, absolute=None, relative=None):
        if (absolute != None):
            for ptr in self._motor_array:
                ptr.motor_value = absolute
        elif (relative != None):
            for ptr in self._motor_array:
                ptr.motor_value = ptr.motor_value + relative/len(self._motor_array)
        else:
            pass # This shouldn't happen
        #print("Motor val=", self._motor_array[0].motor_value)

    