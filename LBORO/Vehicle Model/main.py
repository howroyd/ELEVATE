#!/usr/bin/python3

VERSION = 2.1

###############################
###    IMPORT LIBRARIES     ###
###############################
import telnetlib, time, sys, os, datetime, copy
import matlab.engine
import matplotlib.pyplot as plt
import numpy as np
from CarClass import CarClass
from DataInputClass import DataInputClass
from DataInputClass import Continuous_dt
from Cars import Nissan_Leaf
import colorama
from colorama import Fore, Back, Style
from elevate_includes import Display as Display, mph_to_ms


###############################
###     LOCAL VARIABLES     ###
###############################
disp = Display(VERSION)
graph = True
feed_forward = False


###############################
###   TEST DATAFILE NAME    ###
###############################
filename = "nedc2_short"


###############################
###    PRINT SETUP DATA     ###
###############################
disp.disp_testfile(filename)
disp.disp_feed_forward(feed_forward)


if __name__ == "__main__":  

    ###############################
    ###     INITIALISATION      ###
    ###############################

    # Note starting epoch time for reference
    time_start = time.time()

    #eng = matlab.engine.start_matlab('-nojvm')
    #print(eng.sqrt(4.0))
    #eng.quit()
    
    datafile = DataInputClass(filename+".tsv")
    timer    = Continuous_dt(datafile.dt, 50)

    # Spawn vehicle(s)
    mycar = CarClass(Nissan_Leaf().data)
    
    disp.disp((datafile.num_lines, 'lines in input file\n'))


    ###############################
    ###    BEGIN SIMULATION     ###
    ###############################
    while not datafile.finished:


        ###############################
        ###      UPDATE TIMERS      ###
        ###############################
        timer.update()
        datafile.update(timer.sim_time)
        if datafile.new_data:
            disp.disp((round(datafile.percent_complete,1),'%'),end='\r')

        ###############################
        ###    SET VEHICLE SPEED    ###
        ###############################
        if datafile.new_data:
            mycar.target_speed = mph_to_ms(datafile.line[1])


        ###############################
        ###      UPDATE MODEL       ###
        ###############################
        mycar.update(timer.dt)


        ###############################
        ###      UPDATE SAVE        ###
        ###############################
        datafile.line = [timer.sim_time]
        datafile.line = [mycar.target_speed * 2.23694]
        datafile.line = [mycar.speed * 2.23694]
        datafile.line = [mycar._powertrain._speed_control.error]
        datafile.line = [mycar._powertrain._speed_control.error_p]
        datafile.line = [mycar._powertrain._speed_control.error_i]
        datafile.line = [mycar._powertrain._speed_control.error_d]
        datafile.line = [mycar._powertrain._speed_control._motor_controller.error]
        datafile.line = [mycar._powertrain._speed_control._motor_controller.error_p]
        datafile.line = [mycar._powertrain._speed_control._motor_controller.error_i]
        datafile.line = [mycar._powertrain._speed_control._motor_controller.error_d]
        datafile.line = [mycar._powertrain._speed_control._brake_controller.error]
        datafile.line = [mycar._powertrain._speed_control._brake_controller.error_p]
        datafile.line = [mycar._powertrain._speed_control._brake_controller.error_i]
        datafile.line = [mycar._powertrain._speed_control._brake_controller.error_d]

    disp.disp(None, end='\r\n')


    ###############################
    ###     COMPILE GRAPHS      ###
    ###############################
    if graph:

        # Get data from saved datafile
        data_out = np.genfromtxt(filename+"_out.csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'v_set', 'v_true', 'speedE', 'speedP', 'speedI', 'speedD', 'motorE', 'motorP', 'motorI', 'motorD', 'brakeE', 'brakeP', 'brakeI', 'brakeD'])

        ###############################
        ###        FIGURE 1         ###
        ###############################
        fig = plt.figure()

        ###############################
        ###    FIG 1, SUBPLOT 1     ###
        ###############################
        ax1 = fig.add_subplot(411)
        ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
        ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
        ax1.set_ylabel('Mph')
        ax1.set_ylim([0, 60])
        leg1 = ax1.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 1, SUBPLOT 2     ###
        ###############################
        ax2 = fig.add_subplot(412)
        ax2.plot(data_out['x'], data_out['speedE'], label='speedE')
        ax2.plot(data_out['x'], data_out['speedP'], label='speedP')
        ax2.plot(data_out['x'], data_out['speedI'], label='speedI')
        ax2.plot(data_out['x'], data_out['speedD'], label='speedD')
        ax2.set_ylabel('Speed Ctrl \n 0-255')
        ax2.set_ylim([-260, 260])
        leg2 = ax2.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 1, SUBPLOT 3     ###
        ###############################
        ax3 = fig.add_subplot(413)
        ax3.plot(data_out['x'], data_out['motorE'], label='motorE')
        ax3.plot(data_out['x'], data_out['motorP'], label='motorP')
        ax3.plot(data_out['x'], data_out['motorI'], label='motorI')
        ax3.plot(data_out['x'], data_out['motorD'], label='motorD')
        ax3.set_ylabel('Motor Ctrl \n 0-255')
        ax3.set_ylim([-260, 260])
        leg3 = ax3.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 1, SUBPLOT 4     ###
        ###############################
        ax4 = fig.add_subplot(414)
        ax4.plot(data_out['x'], data_out['brakeE'], label='brakeE')
        ax4.plot(data_out['x'], data_out['brakeE'], label='brakeE')
        ax4.plot(data_out['x'], data_out['brakeI'], label='brakeI')
        ax4.plot(data_out['x'], data_out['brakeD'], label='brakeD')
        ax4.set_ylabel('Brake Ctrl \n 0-255')
        ax4.set_ylim([-260, 260])
        leg4 = ax4.legend(loc='upper right', shadow=True)
        
        # Fig 1 x-Axis Label
        ax4.set_xlabel('Time /s')

    ###############################
    ###       SHOW COSTS        ###
    ###############################
    print(Fore.YELLOW, Style.BRIGHT)
    print("Speed Cost:", round(leaf1._powertrain_model_array[0]._speed_control.cost, 1))
    print("Motor Cost:", round(leaf1._powertrain_model_array[0]._speed_control._motor_controller.cost, 1))
    print("Brake Cost:", round(leaf1._powertrain_model_array[0]._speed_control._brake_controller.cost, 1))    

    ###############################
    ###       SHOW TIME         ###
    ###############################
    print(Fore.RED, Style.BRIGHT)
    print("\n", round((time.time()-time_start),1), "seconds to run")
    print(Fore.RED, Style.DIM)
    print("\n***end***\n\n")
    print(Style.RESET_ALL)

    ###############################
    ###       SHOW GRAPH        ###
    ###############################
    if graph:
        plt.show()

###############################
###############################
######       END         ######
###############################
###############################