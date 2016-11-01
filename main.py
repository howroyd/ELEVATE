#!/usr/bin/python3

VERSION = 1.0

import telnetlib, time, sys, os, datetime
import matlab.engine
import matplotlib.pyplot as plt
import numpy as np
from TdiLoadbankClass import TdiLoadbank
from battery_sw import Battery_Model
from CarClass import CarClass
from DataInputClass import DataInputClass
from ControllerClass import ControllerClass
from Cars import Nissan_Leaf
import threading
import colorama
from colorama import Fore, Back, Style

many = False
graph = True

# Main run function
if __name__ == "__main__":
    time_start = time.time()

    colorama.init()

    print(Fore.GREEN, Style.BRIGHT)
    print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")
    print("Hardware Simulation Model Version", VERSION)
    print("Simon Howroyd", datetime.date.today().year)
    print("Loughborough University\n")
    print(Style.RESET_ALL)

    filename = "nedc2_short"

    #eng = matlab.engine.start_matlab('-nojvm')
    #print(eng.sqrt(4.0))
    #eng.quit()

    print(sys.version)
    
    d = DataInputClass(filename+".tsv")
#    e = ControllerClass(d)

    leaf_data = Nissan_Leaf()

    mycar = list()
    
    # Spawn vehicle(s)
    if many:
        for x in range(1000):
            mycar.append(CarClass(leaf_data.data))
    leaf = CarClass(leaf_data.data)

    d.set_line(['Time','NEDC','Speed'])

    print(d.get_num_lines(), 'lines in input file')

    while (d.update()):
        if many:
            for x in mycar:
                x.target_speed = d.get_line()[1]/2.23694 # mph to m/s
                x.update(d.dt)

        leaf.target_speed = d.get_line()[1]/2.23694 # mph to m/s
        leaf.update(d.dt)

        d.set_line([d.get_line()[0], leaf.target_speed*2.23694, leaf.speed*2.23694, leaf._powertrain_model_array[0]._speed_control._dv*2.23694, leaf._powertrain_model_array[0].error])
        #print([d.get_line()[0], leaf.target_speed, leaf.speed])

        for ptr in leaf._powertrain_model_array[0]._motor_array:
            d.set_line([ptr.motor_value])
        for ptr in leaf._powertrain_model_array[0]._wheel_array:
            d.set_line([ptr.brake_value])
        
        d.set_line([leaf._powertrain_model_array[0]._speed_control.error])
        d.set_line([leaf._powertrain_model_array[0]._speed_control._motor_controller.error_p])
        d.set_line([leaf._powertrain_model_array[0]._speed_control._motor_controller.error_i])
        d.set_line([leaf._powertrain_model_array[0]._speed_control._motor_controller.error_d])

    if graph:
        data_out = np.genfromtxt(filename+"_out.csv", delimiter=',', skip_header=1, skip_footer=1, names = ['x', 'v_set', 'v_true', 'dv', 'error', 'motor', 'brake0', 'brake1', 'brake2', 'brake3', 'error', 'errorP', 'errorI', 'errorD'])

        fig = plt.figure()
        ax1 = fig.add_subplot(211)

        ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
        ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
        ax1.set_ylabel('Speed')
        leg1 = ax1.legend(loc='upper right', shadow=True)

        ## Ax2
        ax2 = fig.add_subplot(212)
        # Motor & Brakes
        ax2.plot(data_out['x'], data_out['motor'], label='motor')
        ax2.plot(data_out['x'], data_out['brake0'], label='brake0')
        #ax2.plot(data_out['x'], data_out['brake1'], label='brake1')
        #ax2.plot(data_out['x'], data_out['brake2'], label='brake2')
        ##ax2.plot(data_out['x'], data_out['brake3'], label='brake3')
        ax2.set_ylabel('0-255')

        # Controller
#        ax2.plot(data_out['x'], data_out['error'], label='error')
        ax2.plot(data_out['x'], data_out['errorP'], label='errorP')
        ax2.plot(data_out['x'], data_out['errorI'], label='errorI')
        ax2.plot(data_out['x'], data_out['errorD'], label='errorD')

        leg2 = ax2.legend(loc='upper right', shadow=True)
        ax2.set_xlabel('Time /s')

    print(Fore.YELLOW, Style.BRIGHT)
    print("Speed Cost:", round(leaf._powertrain_model_array[0]._speed_control.cost, 1))
    print("Motor Cost:", round(leaf._powertrain_model_array[0]._speed_control._motor_controller.cost, 1))
    print("Brake Cost:", round(leaf._powertrain_model_array[0]._speed_control._brake_controller.cost, 1))    

    print(Fore.RED, Style.BRIGHT)
    print("\n", round((time.time()-time_start),1), "seconds to run")
    print(Fore.RED, Style.DIM)
    print("\n***end***\n\n")
    print(Style.RESET_ALL)

    if graph:
        plt.show()

d.__del__()
