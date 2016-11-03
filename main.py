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
from DataInputClass import Continuous_dt
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
    print("Loughborough University")
    print(Style.RESET_ALL)

    filename = "nedc2_short"

    #eng = matlab.engine.start_matlab('-nojvm')
    #print(eng.sqrt(4.0))
    #eng.quit()

    print(sys.version, '\n')
    
    d = DataInputClass(filename+".tsv")
    timer = Continuous_dt(d.dt, 50)
#    e = ControllerClass(d)

    leaf_data = Nissan_Leaf()

    mycar = list()
    
    # Spawn vehicle(s)
    if many:
        for x in range(1000):
            mycar.append(CarClass(leaf_data.data))
    leaf = CarClass(leaf_data.data)

    d.line = ['Time','NEDC','Speed']

    print(d.num_lines, 'lines in input file\n')

    while not d.finished:
        timer.update()
        d.update(timer.sim_time)

        if many:
            for x in mycar:
                if d.new_data: d.target_speed = d.line[1]/2.23694 # mph to m/s
                x.update(timer.dt)
        else:
            if d.new_data: leaf.target_speed = d.line[1]/2.23694 # mph to m/s
            leaf.update(timer.dt)


        if d.new_data: print(round(d.percent_complete,1),'%',end='\r')


        d.line = [timer.sim_time]

        d.line = [leaf.target_speed * 2.23694]
        d.line = [leaf.speed * 2.23694]
       
        d.line = [leaf._powertrain_model_array[0]._speed_control.error]
        d.line = [leaf._powertrain_model_array[0]._speed_control.error_p]
        d.line = [leaf._powertrain_model_array[0]._speed_control.error_i]
        d.line = [leaf._powertrain_model_array[0]._speed_control.error_d]

        d.line = [leaf._powertrain_model_array[0]._speed_control._motor_controller.error]
        d.line = [leaf._powertrain_model_array[0]._speed_control._motor_controller.error_p]
        d.line = [leaf._powertrain_model_array[0]._speed_control._motor_controller.error_i]
        d.line = [leaf._powertrain_model_array[0]._speed_control._motor_controller.error_d]

        d.line = [leaf._powertrain_model_array[0]._speed_control._brake_controller.error]
        d.line = [leaf._powertrain_model_array[0]._speed_control._brake_controller.error_p]
        d.line = [leaf._powertrain_model_array[0]._speed_control._brake_controller.error_i]
        d.line = [leaf._powertrain_model_array[0]._speed_control._brake_controller.error_d]


    if graph:
        data_out = np.genfromtxt(filename+"_out.csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'v_set', 'v_true', 'speedE', 'speedP', 'speedI', 'speedD', 'motorE', 'motorP', 'motorI', 'motorD', 'brakeE', 'brakeP', 'brakeI', 'brakeD'])

        fig = plt.figure()

        ax1 = fig.add_subplot(411)
        ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
        ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
        ax1.set_ylabel('Mph')
        ax1.set_ylim([0, 60])
        leg1 = ax1.legend(loc='upper right', shadow=True)

        ax2 = fig.add_subplot(412)
        ax2.plot(data_out['x'], data_out['speedE'], label='speedE')
        ax2.plot(data_out['x'], data_out['speedP'], label='speedP')
        ax2.plot(data_out['x'], data_out['speedI'], label='speedI')
        ax2.plot(data_out['x'], data_out['speedD'], label='speedD')
        ax2.set_ylabel('Speed Ctrl \n 0-255')
        ax2.set_ylim([-260, 260])
        leg2 = ax2.legend(loc='upper right', shadow=True)

        ax3 = fig.add_subplot(413)
        ax3.plot(data_out['x'], data_out['motorE'], label='motorE')
        ax3.plot(data_out['x'], data_out['motorP'], label='motorP')
        ax3.plot(data_out['x'], data_out['motorI'], label='motorI')
        ax3.plot(data_out['x'], data_out['motorD'], label='motorD')
        ax3.set_ylabel('Motor Ctrl \n 0-255')
        ax3.set_ylim([-260, 260])
        leg3 = ax3.legend(loc='upper right', shadow=True)

        # Controller
        ax4 = fig.add_subplot(414)
        ax4.plot(data_out['x'], data_out['brakeE'], label='brakeE')
        ax4.plot(data_out['x'], data_out['brakeE'], label='brakeE')
        ax4.plot(data_out['x'], data_out['brakeI'], label='brakeI')
        ax4.plot(data_out['x'], data_out['brakeD'], label='brakeD')
        ax4.set_ylabel('Brake Ctrl \n 0-255')
        ax4.set_ylim([-260, 260])
        leg4 = ax4.legend(loc='upper right', shadow=True)
         
        ax4.set_xlabel('Time /s')

    print(Fore.YELLOW, Style.BRIGHT)
    print("\nSpeed Cost:", round(leaf._powertrain_model_array[0]._speed_control.cost, 1))
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
