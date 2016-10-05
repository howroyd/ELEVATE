class PowertrainClass(object):
    """description of class"""

    def __init__(self, battery_array, motor_array, wheel_array, kwargs):
        self._battery_array = battery_array
        self._motor_array = motor_array
        self._wheel_array = wheel_array
        self._current_speed = 0.0
        self._target_speed  = 0.0
        self._dv = 0.0
        self._aero_model = kwargs['aero_model']
        self._total_force = 0.0
        self._dt = 1.0
        self._p = 0.0
        self._i = 0.0
        self._error = 0.0

    def update(self):      
        self._dv = self._target_speed - self._current_speed # Positive if too slow

        self._p = self._dv * 1
        self._i = self._i + 0.1*self._dv*self._dt

        self._error = self._p# + self._i


        if (self._error >= 0.0):
            # Too slow
            if sum(ptr.brake_torque for ptr in self._wheel_array) > 0.0:
                # Brakes are on, so release
                #print('Brakes are on, so release')
                for ptr in self._wheel_array:
                    ptr.brake_value = ptr.brake_value - self._error
            else:
                # Brakes not on, increase motor power
                #print('Brakes not on, increase motor power')
                for ptr in self._motor_array:
                    ptr.motor_value = ptr.motor_value + self._error
        else:
            # Too fast
            if sum(ptr.motor_value for ptr in self._motor_array) > 0.0:
                # Motors are on, reduce power
                #print('Motors are on, reduce power')
                for ptr in self._motor_array:
                    ptr.motor_value = ptr.motor_value + self._error
            else:
                # Motors not on, apply brakes
                #print('Motors not on, apply brakes')
                for ptr in self._wheel_array:
                    ptr.brake_value = ptr.brake_value - self._error

#        if (self._dv > 4.0):
#            # Much too slow
#            print("Much too slow")
#            for ptr in self._motor_array:
#                ptr.motor_value = ptr.motor_value + 100.0 # Give it the beans!!!! Vroooooommmmmm...............
#            for ptr in self._wheel_array:
#                ptr.brake_value = 0.0

#        elif (self._dv > 2.0):
#            # Too slow
#            print("Too slow")
#            if sum(ptr.brake_value for ptr in self._wheel_array) > 0.0:
#                for ptr in self._wheel_array:
#                    ptr.brake_value = ptr.brake_value - 5.0 # Reduce brake
#            else:
#                for ptr in self._motor_array:
#                    ptr.motor_value = ptr.motor_value + 5.0 # Increase accel

#        elif (self._dv > 0.5):
#            # Too slow
#            print("Slow")
#            if sum(ptr.brake_value for ptr in self._wheel_array) > 0.0:
#                for ptr in self._wheel_array:
#                    ptr.brake_value = ptr.brake_value - 1.0 # Reduce brake
#            else:
#                for ptr in self._motor_array:
#                    ptr.motor_value = ptr.motor_value + 1.0 # Increase accel

#        elif (self._dv > -0.5):
#            print("OK")
#            # Within 5mph, OK
#            pass

#        elif (self._dv > -2.0):
#            # Too fast
#            print("Fast")
#            if sum(ptr.motor_value for ptr in self._motor_array) > 0.0:
#                for ptr in self._motor_array:
#                    ptr.motor_value = ptr.motor_value - 1.0 # Reduce accel
#            else:
#                for ptr in self._wheel_array:
#                    ptr.brake_value = ptr.brake_value + 1.0 # Increase brake

#        elif (self._dv > -4.0):
#            # Too fast
#            print("Too fast")
#            if sum(ptr.motor_value for ptr in self._motor_array) > 0.0:
#                for ptr in self._motor_array:
#                    ptr.motor_value = ptr.motor_value - 5.0 # Reduce accel
#            else:
#                for ptr in self._wheel_array:
#                    ptr.brake_value = ptr.brake_value + 5.0 # Increase brake

#        else:
#            # Much too fast
#            print("Much too fast")
#            for ptr in self._motor_array:
#                ptr.motor_value = 0.0
#            for ptr in self._wheel_array:
#                ptr.brake_value = ptr.brake_value + 100.0 # Hit the anchors!!!!

        # Update models
        for ptr in self._battery_array:
            ptr.update()
        for ptr in self._motor_array:
            ptr.update()
        for ptr in self._wheel_array:
            ptr.update()

        self._total_force = sum(ptr.force for ptr in self._wheel_array) # minus road drag
        return

    @property
    def target_speed(self):
        return self._target_speed   # Could just input dv???
    @target_speed.setter
    def target_speed(self, speed):
        self._target_speed = max(0.0, speed)

    @property
    def dt(self):
        return self._dt
    @dt.setter
    def dt(self, dt):
        self._dt = dt
    
    @property
    def current_speed(self):
        return self._current_speed
    @current_speed.setter
    def current_speed(self, speed):
        self._current_speed = speed

    @property
    def force(self):
        return self._total_force