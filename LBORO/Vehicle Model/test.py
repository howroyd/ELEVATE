#!/usr/bin/python3

VERSION = 1.0

import telnetlib, time, sys, os, datetime, copy
import matlab.engine
import matplotlib.pyplot as plt
import numpy as np
from TdiLoadbankClass import TdiLoadbank
from battery_sw import Battery_Model
from CarClass import CarClass
from DataInputClass import DataInputClass
from DataInputClass import Continuous_dt
from ControllerClass import ControllerClass
from Cars import Nissan_Leaf
import threading
import colorama
from colorama import Fore, Back, Style

from WheelClass import WheelClass
from BrakesClass import BrakesClass
from MotorClass import MotorClass

num_cars = 1
graph = True
feed_forward = False

inpath = "DriveCycles"
outpath= "Results"
#filename = "FTP_mph"
filename = "nedc2_short_kph"

def display_init():
    colorama.init()
    print(Fore.GREEN, Style.BRIGHT)
    print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")
    print("Hardware Simulation Model Version", VERSION)
    print("DEBUGGING VERSION")
    print("Simon Howroyd", datetime.date.today().year)
    print("Loughborough University")
    print(Style.RESET_ALL)
    print(sys.version, '\n')

# Main run function
if __name__ == "__main__":
    time_start = time.time()

    display_init()

    #matlab_init()
    
    #datafile = DataInputClass(inpath+"/"+filename+".tsv", outpath+"/"+filename+".csv")
    #timer    = Continuous_dt(datafile.dt, 50)

    if 'kph' in filename:
        conversion_factor = 1.0/3.6
        units = 'kph'
    elif 'mph' in filename:
        conversion_factor = 0.44704
        units = 'mph'
    elif 'ms' in filename:
        conversion_factor = 1.0
        units = 'ms'
    else:
        sys.exit("No defined speed units in drive cycle filename")
    
    #print(datafile.num_lines, 'lines in input file\n')

    brake = BrakesClass(diameter=0.1, max_torque=500.0, kwargs=None)
    wheel = WheelClass(brake, kwargs=dict(wheel_diameter=0.2159, car_mass=1521.0))
    motor = MotorClass(wheel, kwargs=dict(motor_max_torque=280, motor_v_min = 400.0, motor_v_max=300.0, motor_i_max=266.0, motor_p_max=80000.0))

    wheel.brake_parking = False

    speed = 0.0

    finished = False

    i = 0
    dt = 1
    
    results = list()
    for x in range(3): results.append(list())

    # RUN SIMULATION
    while not finished:

        # Update the timer and input data file
        #timer.update()

        if i <= 1:
            speed = 0.0
        elif i < 49:
            motor.motor_value = i
        elif i < 99:
            motor.motor_value = 99-i
            if i > 75:
                wheel.brake_value += 1
        elif i is 99:
            finished = True

        motor.update(dt)
        wheel.motor_torque = motor.shaft_torque/4.0
        speed = max(0.0, speed-i)

        wheel.vehicle_speed = speed
        wheel.update(dt)

        if wheel._slip > 0.2:
            motor.motor_value -= motor.motor_value/2
            motor.update(dt)
            wheel.motor_torque = motor.shaft_torque/4.0
            wheel.update(dt)

        # Output data to save file
        results[0].append(i)
        results[1].append(speed)
        results[2].append(wheel._slip)

        i += dt

    print(end='\r\n')

    # Plot data to screen
    if graph:
        fig = plt.figure(1)
        ylim = max(max(results[1]), max(results[2]))+1
        ax1 = fig.add_subplot(111)
        ax1.plot(results[0], results[1], label='speed')
        ax1.plot(results[0], results[2], '--', label='force')
        leg1 = ax1.legend(loc='upper right', shadow=True)
        ax1.set_ylim([0, ylim])
        ax1.set_xlabel('Time')  

    print(Fore.RED, Style.BRIGHT)
    print("\n", round((time.time()-time_start),1), "seconds to run")
    print(Fore.RED, Style.DIM)
    print("\n***end***\n\n")
    print(Style.RESET_ALL)

    if graph:
        plt.show()


