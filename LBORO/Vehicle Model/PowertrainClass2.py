#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
from AxleClass import AxleClass
from BatteryClass import BatteryClass
from BatteryManagementClass import BatteryManagementClass
from ControllerClass import ControllerClass
from EscClass import ESC
from MotorClass import MotorClass
from WheelClass import WheelClass
from statistics import mean


class PowertrainControllerClass(object):
    '''Electric vehicle powertrain class'''
    _axle  = None
    _bms   = None
    _esc   = None
    _motor = None
    _wheel = [ None, None, None, None ]
    _ctrl_speed = None
    _ctrl_motor = None
    _ctrl_brake = None
    _speed_set  = None
    _speed_now  = None
    _mode       = None
    _car_mass   = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):

        kwargs.update(dict(i_max_charge=(kwargs.get('batt_p_max')*0.5/kwargs.get('batt_v_min')),
                                                    i_max_discharge=kwargs.get('batt_i_max'),
                                                    p_max=kwargs.get('batt_p_max'),
                                                    batt_kwh=kwargs.get('batt_kwh'),
                                                    v_min=kwargs.get('batt_v_min'),
                                                    v_max=kwargs.get('batt_v_max'),
                                                    ))


        self._axle    = AxleClass()
        self._battery = BatteryClass(kwargs)
        self._bms     = BatteryManagementClass(kwargs)
        self._esc     = ESC(kwargs)
        self._motor   = MotorClass(kwargs)
        self._wheel   = [ WheelClass(kwargs),   # FL
                          WheelClass(kwargs),   # FR
                          WheelClass(kwargs),   # RL
                          WheelClass(kwargs) ]  # RR
        self._ctrl_speed = ControllerClass(50, 5, -0.8, "signed")
        self._ctrl_motor = ControllerClass(2, 0, -0.075, "unsigned")
        self._ctrl_brake = ControllerClass(1, 0, -0.075, "unsigned")
        self._speed_target = 0.0
        self._speed        = 0.0
        self._car_mass     = kwargs.get('car_mass')

        self._bms.set_battery_data(self._battery.battery_data)
        self._esc.set_input_power(self._bms.availability)


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):

        # Get wheel speeds and torques, pass to axle then motor
        #self._axle.wheel_data       = [ self._wheel[0].rotational_data, self._wheel[1].rotational_data ]
        #self._motor.rotational_data = self._axle.shaft_data.rotational_data

        # Get battery availability, pass to BMS & ESC
        self._bms.set_battery_data(self._battery.battery_data)
        
        # Parse control signal from speed controller
        self._parse_control_signal(dt)
    
        # Send motor control signal to ESC
        self._esc.control_signal    = self._ctrl_motor.value
        self._esc.set_input_power(self._bms.availability)

        # Send brake control signal to wheels
        for ptr in self._wheel:
            ptr.brake_control_sig   = self._ctrl_brake.value

        # Give (or receive) electricity to (or from) motor
        self._motor.set_electricity(self._esc.voltage, self._esc.current)

        # Calculate voltage boost in ESC to charge battery if in regen
        self._bms.current           = self._esc.current
        self._battery.current       = self._bms.current

        # Update axle torque and speed, pass to drive wheels
        self._motor.update(dt)
        self._axle.shaft_data       = self._motor.rotational_data
        self._axle.update(dt)
        self._wheel[0].axle_data    = self._axle.wheel_data[0].rotational_data
        self._wheel[1].axle_data    = self._axle.wheel_data[1].rotational_data
        for ptr in self._wheel:
            ptr.update(dt)

        # Update time dependancies (energy calcs)
        self._battery.update(dt)
        self._bms.update(dt)
        self._esc.update(dt)




    ###############################
    ###     CONTROL DECODER     ###
    ###############################        
    def _parse_control_signal(self, dt):
        dv = self.target_speed - self.vehicle_speed
        self._ctrl_speed.update(dt, dv)

        mode = 0.0

        if self._ctrl_speed.value <= 0.0:
            # Trying to decelerate
            self._ctrl_motor.update(dt, self._ctrl_speed.value)

            if self._ctrl_motor.at_minimum:
                # Motor fully off or in full regen, apply brakes
                self._ctrl_brake.update(dt, -1.0*self._ctrl_speed.value)
                mode = 1.0
            else:
                # In regen or coasting, no brakes applied
                self._ctrl_brake.reset()
                self._ctrl_brake.update(dt)
                mode = 2.0
        else:
            # Trying to accelerate
            self._ctrl_brake.update(dt, -1.0*self._ctrl_speed.value)

            if self._ctrl_brake.at_minimum:
                # Brake fully off, power motor
                self._ctrl_motor.update(dt, self._ctrl_speed.value)
                mode = 3.0
            else:
                # Brake on but trying to speed up
                self._ctrl_motor.update(dt)
                mode = 4.0

        self._mode = mode

        if self.target_speed <=0.01 and self.vehicle_speed <=0.01:
            self._ctrl_speed.anti_wind_up()
            self._ctrl_motor.anti_wind_up()
            self._ctrl_brake.anti_wind_up()


    ###############################
    ###        GETTERS          ###
    ###############################

    # Actual vehicle speed
    @property
    def vehicle_speed(self):
        return self._speed

    # Target speed
    @property
    def target_speed(self):
        return self._speed_target


    # Road Friction Drag
    @property
    def road_drag(self):
        return sum(ptr.road_drag for ptr in self._wheel)

    # Powertrain Force
    @property
    def force(self):
        return sum(ptr.force for ptr in self._wheel)


    # Speed Controller PID
    @property
    def speed_ctrl_error(self):
        return self._ctrl_speed.value
    @property
    def speed_ctrl_pid(self):
        return self._ctrl_speed.pid_data

    # Motor Controller PID
    @property
    def motor_ctrl_error(self):
        return self._ctrl_motor.value
    @property
    def motor_ctrl_pid(self):
        return self._ctrl_motor.pid_data

    # Brake Controller PID
    @property
    def brake_ctrl_error(self):
        return self._ctrl_brake.value
    @property
    def brake_ctrl_pid(self):
        return self._ctrl_brake.pid_data


    # Motor Rotational
    @property
    def motor_rotation(self):
        return self._motor.rotational_data

    # Axle Rotation
    @property
    def axle_rotation(self):
        return self._axle.shaft_data.rotational_data

    # Wheel Rotational
    @property
    def wheel_rotation(self):
        return [ self._wheel[0].rotational_data,
                    self._wheel[1].rotational_data,
                    self._wheel[2].rotational_data,
                    self._wheel[3].rotational_data ]
    # Odometer
    @property
    def odometer(self):
        return  mean([ self._wheel[0].odometer,
                    self._wheel[1].odometer,
                    self._wheel[2].odometer,
                    self._wheel[3].odometer ])


    # Brake Rotational
    @property
    def brake_rotation(self):
        return [ self._wheel[0].brake_rotational,
                    self._wheel[1].brake_rotational,
                    self._wheel[2].brake_rotational,
                    self._wheel[3].brake_rotational ]


    # Battery Electricity
    @property
    def battery_electricity(self):
        return self._battery.battery_data

    # ESC Electricity
    @property
    def esc_electricity(self):
        return self._esc.electricity_data

    # Motor Electricity
    @property
    def motor_electricity(self):
        return self._motor.electricity_data


    # Controller Mode
    @property
    def controller_mode(self):
        return self._mode


    ###############################
    ###        SETTERS          ###
    ###############################

    # Actual vehicle speed
    @vehicle_speed.setter
    def vehicle_speed(self, speed):
        self._speed = speed
        for ptr in self._wheel:
            ptr.vehicle_speed_feedback(speed)
        self._axle.wheel_speed_feedback(self._wheel[0].speed, self._wheel[1].speed) 
        self._motor.shaft_speed_feedback(self._axle.shaft_data.speed)

    # Target speed
    @target_speed.setter
    def target_speed(self, speed):
        self._speed_target = speed
    

###############################
###############################
######       END         ######
###############################
###############################