import WheelClass
import MotorClass
import BrakesClass
import ControllerClass
import enum
import EscClass

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

    def __init__(self, battery_array, motor_array, wheel_array, kwargs, name="speedController"):
        self._state = PowertrainState['initialising']
        self._control_state = ControlState['off']
        self._battery_array = battery_array
        self._motor_array = motor_array
        self._wheel_array = wheel_array
<<<<<<< HEAD
        self._brake_array = kwargs['brake_model_array']
        self._esc = kwargs['esc']
        self._dt_last = 0.0
=======
        #self._brake_array = kwargs['brake_model_array']
        self._i = 0.0
        self._d = 0.0
        #self._kp = 10#0.8
        #self._ki = 0.001#0.005
        #self._kd = 20#3.0
        #self._kp = 60.0
        #self._ki = 0.05
        #self._kd = 5.0
>>>>>>> linking_overhaul
        self._dv = 0.0
        self._dv_filtered = 0.0
        self._dv_last = 0.0
        self._dv_next = None
        self._target = 0.0
        self._current = 0.0
        self._feed_forward = None
        self._k_feed_forward = 5
        self._state = PowertrainState['stopped']
<<<<<<< HEAD
        self._regen = False # Set to None to disable
        self._name = name
        self._data = dict()
        self._hysteresis_speed = 0#0.44704/4#0.25*1 # 0.45=1mph
        self._target_forward = 0

        p = 100
        i = 1/20
        d = 0

        self._feed_forward = None#ControllerClass.ControllerClass(p, i, d, min_i=-50, max_i=50, name=(self._name+"_ff"))

        self._hysteresis = 0#self._hysteresis_speed * p/10 # PID error
        super(SpeedControlClass, self).__init__(p, i, d, min_i=-50, max_i=50, name=self._name)

        return 

    @property
    def data(self):
        return self._data

    def update(self, dt):
        #if ((self._target <= self._hysteresis_speed/10.0) and (self._current <= self._hysteresis_speed/10.0) and ((self._feed_forward.error <= self._hysteresis_speed/10.0) if self._feed_forward is not None else True)):
        #    if (self._state is not PowertrainState['stopped']):
        #        self._state = PowertrainState['stopped']
        #    super(SpeedControlClass, self).reset()
        #    self._feed_forward.reset() if self._feed_forward is not None else None

        super(SpeedControlClass, self).update(dt, (self._target+self._target_forward)/2 - self._current)#self.dv)
=======
        self._hysteresis = 10
        return super().__init__(150, 50, -7.5, type='signed')  # 128, 16, 0
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
>>>>>>> linking_overhaul

        if self._feed_forward is not None:
            self._feed_forward.update(dt, self._target_forward - self._current)
            #print(self._feed_forward.error)
            self._error = (super(SpeedControlClass, self).error + self._feed_forward.error) 
        else:
            self._error = super(SpeedControlClass, self).error  

        #print(self.error)

        (motor, brake, parking) = self._control(self._error, self.dv, self._hysteresis, self._hysteresis_speed,
                                                        True if (ptr.brake_parking for ptr in self._wheel_array) else False, verbose=False)

<<<<<<< HEAD

        #if self._feed_forward is not None:
        #    return self._target - self._current + self._k_feed_forward*(self._feed_forward)
        #else:


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

        self._esc.update(dt)
=======
    def _update_models(self, dt):
        # Update models
        #for ptr in self._battery_array:
        #    ptr.update(dt)
>>>>>>> linking_overhaul
        for ptr in self._motor_array:
            ptr.update(dt)
        for ptr in self._wheel_array:
            ptr.update(dt)


        for ptr in self._battery_array:
            ptr.i = self._motor_array[0].i
            ptr.p = self._motor_array[0].p

        for ptr in self._motor_array:
            ptr.v = self._battery_array[0].v

        for ptr in self._battery_array:
            ptr.update(dt)


        #self._update_models(dt)

        self._data.update(super(SpeedControlClass, self).data)
        self._data.update({(self._name+'_motor') : motor,
                            (self._name+'_brake') : brake,
                            (self._name+'_parking') : parking,
                            (self._name+'_powertrain_state') : self._state,
                            (self._name+'_control_state') : self._control_state,
        })

        return

    def _update_models(self, dt):
        #if (self._dt_last > dt):
            # Update models
            for ptr in self._battery_array:
                ptr.update(dt)
            self._esc.update(dt)
            for ptr in self._motor_array:
                ptr.update(dt)
            for ptr in self._wheel_array:
                ptr.update(dt)

            self._dt_last = dt

    def _set_motor(self, val, verbose=False):
        if verbose: print("Motor: ", end=' ')
        for ptr in self._motor_array:
            if self._regen is None: ptr.regen_activated = False
            else: ptr.regen_activated = True
            ptr.motor_value = val
            if verbose: print(str(int(ptr.motor_value)), end=' ')
        if verbose: print()

    def _set_brakes(self, val, parking=False, verbose=False):
        if verbose: print("Brake: ", end=' ')

        for ptr in self._wheel_array:
            ptr.brake_parking = parking
            ptr.brake_value = -val if val is not None else None
               
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
<<<<<<< HEAD
    def target_forward(self):
        return self._feed_forward
    @target_forward.setter
    def target_forward(self, value):
        self._target_forward = max(0, value) # Positive numbers only
=======
    def feed_forward(self):
        return self._feed_forward
    @feed_forward.setter
    def feed_forward(self, value):
        self._feed_forward = max(0, value) # Positive numbers only
>>>>>>> linking_overhaul

    @property
    def current(self):
        return self._current
    @current.setter
    def current(self, value):
        self._current = max(0, value) # Positive numbers only
<<<<<<< HEAD
        


    @property
    def dv(self):
        #if self._feed_forward is not None:
            return self._target - self._current
        #else:
        #    return self._target - self._current
=======
        for ptr in self._wheel_array:
            ptr.set_wheel_speed(self._current)
            
    @property
    def dv(self):
        if self._feed_forward is not None:
            return self._target + self._k_feed_forward*(self._feed_forward - self._target) - self._current
        else:
            return self._target - self._current
>>>>>>> linking_overhaul

    @property
    def error(self):
        return self._error


class TractionControlClass(SpeedControlClass):
    """Takes a control signal and drives the brakes/motors"""
    
    def __init__(self, battery_array, motor_array, wheel_array, kwargs):
<<<<<<< HEAD
        self._motor_controller = ControllerClass.ControllerClass(1, 0, 0, min_val=0, max_val=255)
        self._brake_controller = ControllerClass.ControllerClass(1, 0, 0, min_val=0, max_val=255)
        
        self._motor_controller.set_i_limits(-150,150)
        self._brake_controller.set_i_limits(-100,100)

=======
        self._brake_controller = ControllerClass.ControllerClass(0.9, 0.1, -0.05, type='unsigned')
        self._motor_controller = ControllerClass.ControllerClass(1.5, 0.1, -0.025, type='signed')
        self._motor_controller.min_val = -95
        #self._brake_controller = ControllerClass.ControllerClass(10, 0.6, -0.2, -255, 255)
        #self._motor_controller = ControllerClass.ControllerClass(5, 0.5, -2.0, -255, 255)
        #self._brake_controller.set_i_limits(0,255)
        self._brake_controller.set_i_limits(-50,50)
        self._motor_controller.set_i_limits(-50,50)
        self._error_brake = 0.0
>>>>>>> linking_overhaul
        self._error_motor = 0.0 
        self._error_brake = 0.0
        return super(TractionControlClass, self).__init__(battery_array, motor_array, wheel_array, kwargs)

    def update(self, dt):
        state_last = self._state
        super(TractionControlClass, self).update(dt, model_update=False)
        self._brake_controller.update(dt, self._error_brake)
        self._motor_controller.update(dt, self._error_motor)

<<<<<<< HEAD
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
=======
        if ( super().state is PowertrainState['accelerating'] or super().state is PowertrainState['stopped']):
            self._brake_controller.anti_wind_up()
        if ( super().state is PowertrainState['deccelerating'] or super().state is PowertrainState['stopped'] ):
            self._motor_controller.anti_wind_up()

        #if (state_last != self._state):# or self._state==PowertrainState.stopped):
        #    self._brake_controller.reset()
        #    self._motor_controller.reset()
>>>>>>> linking_overhaul
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

    