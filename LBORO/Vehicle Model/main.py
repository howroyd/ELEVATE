#!/usr/bin/python3

VERSION = 1.0

import telnetlib, time, sys, os, datetime, copy
import matlab.engine
import matplotlib.pyplot as plt
import numpy as np
from TdiLoadbankClass import TdiLoadbank
from battery_sw import Battery_Model
from CarClass import CarClass
from DataInputClass import DataInputClass, DataOutputClass
from DataInputClass import Continuous_dt
from ControllerClass import ControllerClass
from Cars import Nissan_Leaf
import threading
import colorama
from colorama import Fore, Back, Style
import random
from Filters import LowPassFilter


num_cars = 1
graph = True
feed_forward = True
k_lpf1 = 1
k_lpf2 = 1

inpath = "DriveCycles"
outpath= "Results"
#filename = "FTP_mph"
filename = "nedc_int_kph"
#filename = "bham_lboro_int_kph"
#filename = "WLTP_kph" # ****
#filename = "parabola_kph"
#filename = "impulse_kph"
#filename = "step_kph"

time_lim = None
#time_lim = [920, 940]

def display_init():
    colorama.init()
    print(Fore.GREEN, Style.BRIGHT)
    print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")
    print("Hardware Simulation Model Version", VERSION)
    print("Simon Howroyd", datetime.date.today().year)
    print("Loughborough University")
    print(Style.RESET_ALL)
    print(sys.version, '\n')

def matlab_init():
    eng = matlab.engine.start_matlab('-nojvm')
    print(eng.sqrt(4.0))
    eng.quit()
    return eng

# Main run function
if __name__ == "__main__":
    time_start = time.time()

    display_init()

    #matlab_init()
    
    datafile = DataInputClass(inpath+"/"+filename+".tsv", outpath+"/"+filename+".csv")
    d_force = DataOutputClass(outpath+"/"+"force")
    d_ctrl = DataOutputClass(outpath+"/"+"ctrl")
    d_ctrl_spd = DataOutputClass(outpath+"/"+"ctrl_spd")
    d_ctrl_motor = DataOutputClass(outpath+"/"+"ctrl_motor")
    d_ctrl_brake = DataOutputClass(outpath+"/"+"ctrl_brake")
    d_elec_motor = DataOutputClass(outpath+"/"+"elec_motor")
    timer    = Continuous_dt(datafile.dt, 50)

    lpf1 = LowPassFilter(k_lpf1)
    lpf2 = LowPassFilter(k_lpf2) # Feed forward

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
    
    # Spawn vehicle(s)
    mycar = list()
    for x in range(num_cars):
        mycar.append(CarClass(Nissan_Leaf().data))

    # Create "pointer" to car 0
    leaf1 = mycar[0]
    
    print(datafile.num_lines, 'lines in input file\n')

    # RUN SIMULATION
    while not datafile.finished:

        # Update the timer and input data file
        timer.update()

        #if (timer.sim_time > 200.0): break

        datafile.update(timer.sim_time)

        # Update cars
        for x in mycar:
            # Update target speed if required
            if datafile.new_data:
                x.target_speed = lpf1.get((datafile.line[1] if datafile.line[1] is not 'NaN' else 0) *conversion_factor)
                #print(datafile.line[1]*conversion_factor)
                if feed_forward:
                    x.feed_forward_speed = lpf2.get((datafile.line[1] if datafile.line[1] is not 'NaN' else 0) *conversion_factor)
            # Calculate dynamics
            x.update(timer.dt)

        # Print to screen the percentage of number of lines completed from the input data file
        if datafile.new_data: print(round(datafile.percent_complete,1),'%',end='\r')

        # Output data to save file
        datafile.line = [timer.sim_time]
        datafile.line = [(datafile.line[1] if datafile.line[1] is not 'NaN' else 0)]
        datafile.line = [leaf1.target_speed / conversion_factor]
        datafile.line = [leaf1.speed / conversion_factor]
        datafile.line = [leaf1.dv / conversion_factor]
        datafile.line = [leaf1._powertrain_model_array[0]._speed_control.error]
        datafile.line = [leaf1._powertrain_model_array[0]._speed_control.error_p]
        datafile.line = [leaf1._powertrain_model_array[0]._speed_control.error_i]
        datafile.line = [leaf1._powertrain_model_array[0]._speed_control.error_d]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error_p]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error_i]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error_d]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._brake_controller.error]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._brake_controller.error_p]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._brake_controller.error_i]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._brake_controller.error_d]
        #datafile.line = [int(leaf1._powertrain_model_array[0]._speed_control._wheel_array[0].brake_parking)*-100]
        datafile.line = [leaf1._powertrain_model_array[0]._speed_control.state]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._adhesion_coeff]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0].force]

        #datafile.line = [leaf1._total_force]
        #datafile.line = [leaf1._aero_model.force]
        #datafile.line = [leaf1._powertrain_model_array[0].force]

        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._omega_veh]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._omega_wheel]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0].motor_torque]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0].brake_torque]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._force]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._omega]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._adhesion_coeff]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._adhesion_coeff2]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._vehicle_speed]
        #datafile.line = [timer.dt]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._F_motor]
        #datafile.line = [leaf1._powertrain_model_array[0]._speed_control._wheel_array[0]._F_brake]

        d_force.line = [timer.sim_time]
        d_force.line = [leaf1._total_force]
        d_force.line = [leaf1._powertrain_model_array[0]._wheel_array[0]._F_motor]
        d_force.line = [leaf1._powertrain_model_array[0]._wheel_array[0]._F_brake]
        #d_ctrl_spd.line   = [timer.sim_time]
        #d_ctrl_spd.line   = [leaf1._powertrain_model_array[0]._speed_control.error] 
        #d_ctrl_spd.line   = [leaf1._powertrain_model_array[0]._speed_control.error_p] 
        #d_ctrl_spd.line   = [leaf1._powertrain_model_array[0]._speed_control.error_i] 
        #d_ctrl_spd.line   = [leaf1._powertrain_model_array[0]._speed_control.error_d]
        #d_ctrl_motor.line = [timer.sim_time] 
        #d_ctrl_motor.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error] 
        #d_ctrl_motor.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error_p] 
        #d_ctrl_motor.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error_i] 
        #d_ctrl_motor.line = [leaf1._powertrain_model_array[0]._speed_control._motor_controller.error_d]
        d_ctrl.line = [timer.sim_time] 
        d_ctrl.line = [leaf1._powertrain_model_array[0].error] 
        d_ctrl.line = [leaf1._powertrain_model_array[0]._motor_array[0].motor_value] 
        d_ctrl.line = [leaf1._powertrain_model_array[0]._wheel_array[0]._brake.value] 
        d_ctrl.line = [leaf1._powertrain_model_array[0]._speed_control.error_p] 
        d_ctrl.line = [leaf1._powertrain_model_array[0]._speed_control.error_i] 
        d_ctrl.line = [leaf1._powertrain_model_array[0]._speed_control.error_d] 

        d_elec_motor.line = [timer.sim_time] 
        d_elec_motor.line = [leaf1._powertrain_model_array[0]._motor_array[0]._v]
        d_elec_motor.line = [leaf1._powertrain_model_array[0]._motor_array[0]._i]
        d_elec_motor.line = [leaf1._powertrain_model_array[0]._motor_array[0]._p]


        d_force.update()
        d_ctrl.update()
        #d_ctrl_spd.update()
        d_ctrl_motor.update()
        d_ctrl_brake.update()
        d_elec_motor.update()

    print(end='\r\n')

    #time.sleep(2)

    # Plot data to screen
    if graph:
        data_out = np.genfromtxt(outpath+"/"+filename+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'v_real', 'v_set', 'v_true', 'dv', 'speedE', 'speedP', 'speedI', 'speedD', 'state'])#, 'motorE',
                                #'motorP', 'motorI', 'motorD', 'brakeE', 'brakeP', 'brakeI', 'brakeD', 'parking',
                                #'state', 'slip', 'force', 'force_car', 'force_aero', 'force_powertrain',
                                #'w_veh', 'w_wheel', 'Tm', 'Tb', 'F', 'w', 'adhesion','adhesion2', 'v', 'dt', 'F_motor', 'F_brake'])

        
        data_force = np.genfromtxt(outpath+"/"+"force_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x','force', 'F_motor', 'F_brake'])

        data_ctrl = np.genfromtxt(outpath+"/"+"ctrl_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x','error', 'motor', 'brake', 'p', 'i', 'd'])

        data_elec_motor = np.genfromtxt(outpath+"/"+"elec_motor_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x','v', 'i', 'p'])

        #data_ctrl_spd = np.genfromtxt(outpath+"/"+"ctrl_spd_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
        #            names = ['x','speedE', 'speedP', 'speedI', 'speedD'])

        #data_ctrl_motor = np.genfromtxt(outpath+"/"+"ctrl_motor_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
        #            names = ['x','motorE', 'motorP', 'motorI', 'motorD'])

        #data_ctrl_brake = np.genfromtxt(outpath+"/"+"ctrl_brake_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
        #            names = ['x','brakeE', 'brakeP', 'brakeI', 'brakeD'])



        fig = plt.figure(1)

#        ax1 = fig.add_subplot(511)
#        ax1.plot(data_out['x'], data_out['w'], label='w')
#        ax1.plot(data_out['x'], data_out['w_veh'], label='w_veh')
#        ax1.plot(data_out['x'], data_out['w_wheel'], ':', label='w_wheel')
#        ax1.set_ylabel(units)
##        ax1.set_ylim([0, 60])
#        leg1 = ax1.legend(loc='upper right', shadow=True)

#        ax2 = fig.add_subplot(512)
#        ax2.plot(data_out['x'], data_out['F']/10, ':', label='F')
#        ax2.plot(data_out['x'], data_out['Tm'], label='Tm')
#        ax2.plot(data_out['x'], data_out['Tb'], label='Tb')
#        ax2.set_ylabel(units)
##        ax2.set_ylim([0, 60])
#        leg2 = ax2.legend(loc='upper right', shadow=True)

#        ax3 = fig.add_subplot(513)
#        ax3.plot(data_out['x'], data_out['slip'], label='slip')
#        ax3.plot([0,data_out['x'][-1]], [0.15,0.15], ':', label='peak')
#        ax3.set_ylabel('-1 to 1')
#        #ax3.set_ylim([-300, 300])
#        leg3 = ax3.legend(loc='upper right', shadow=True)

#        ax4 = fig.add_subplot(514)
#        ax4.plot(data_out['x'], data_out['adhesion'], label='adhesion')
#        ax4.plot(data_out['x'], data_out['adhesion2'], label='adhesion2')
#        ax4.set_ylabel('-1 to 1')
#        #ax4.set_ylim([-300, 300])
#        leg4 = ax4.legend(loc='upper right', shadow=True)

#        # Controller
#        ax5 = fig.add_subplot(515)
#        ax5.plot(data_out['x'], data_out['v'], label='v')
#        ax5.plot(data_out['x'], data_out['dt'], label='dt')
#        ax5.set_ylabel(units)
#        #ax5.set_ylim([-300, 300])
#        leg5 = ax5.legend(loc='upper right', shadow=True)
         
#        ax5.set_xlabel('Time /s')

        fig = plt.figure(1)

        fig.suptitle(filename)

        ax1 = fig.add_subplot(611)
        ax1.plot(data_out['x'], data_out['v_real'], ':', label='v_real')
        ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
        ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
        ax1.plot(data_out['x'], data_out['dv'], '--', label='dv')
        ax1.set_ylabel('Velocity\n'+units)
#        ax1.set_ylim([0, 60])
        if time_lim is not None: ax1.set_xlim(time_lim)
        leg1 = ax1.legend(loc='upper right', shadow=True)
        plt.grid()

#        ax2 = fig.add_subplot(512)
#        ax2.plot(data_out['x'], data_out['state'], label='state')
#        ax2.plot(data_out['x'], data_out['slip'], label='slip')
#        ax2.plot(data_out['x'], (data_out['force']/1000) -10, ':', label='force')
#        #ax2.set_ylabel(units)
##        ax2.set_ylim([0, 60])
#        leg2 = ax2.text(1,0.1,"initialising=0\nstopped=1\naccelerating=2\ncruising=3\ncoasting=4\ndeccelerating=5\nbraking=6\nerror=-1",
#                    horizontalalignment='right', transform = ax2.transAxes)

        ax2 = fig.add_subplot(612)
        ax2.plot(data_force['x'], data_force['force'], label='Total')
        ax2.plot(data_force['x'], data_force['F_motor'], label='Fmotor')
        ax2.plot(data_force['x'], data_force['F_brake'], label='Fbrake')
        ax2.set_ylabel('Force\nNewtons')
#        ax2.set_ylim([0, 60])
        if time_lim is not None: ax2.set_xlim(time_lim)
        leg2 = ax2.legend(loc='upper right', shadow=True)
        plt.grid()

        ax3 = fig.add_subplot(613)
        ax3.plot(data_ctrl['x'], data_ctrl['motor'], label='motor')
        ax3.plot(data_ctrl['x'], data_ctrl['brake'], label='brake')
        ax3.set_ylabel('Ctrl Sig\n-255 to 255')
        ax3.set_ylim([-300, 300])
        ax3.set_xlim(time_lim)
        leg3 = ax3.legend(loc='upper right', shadow=True)
        plt.grid()

        ax4 = fig.add_subplot(614)
        ax4.plot(data_out['x'], data_out['state'], label='state')
        if time_lim is not None: ax4.set_xlim(time_lim)
        ax4.set_ylabel('Ctrl State\n-1 to 4')
        ax4.set_ylim([-1, 5])
        leg4 = ax4.legend(loc='upper right', shadow=True)
        plt.grid()

        #ax4 = fig.add_subplot(514)
        #ax4.plot(data_ctrl_motor['x'], data_ctrl_motor['motorE'], '--', label='motorE')
        #ax4.plot(data_ctrl_motor['x'], data_ctrl_motor['motorP'], label='motorP')
        #ax4.plot(data_ctrl_motor['x'], data_ctrl_motor['motorI'], label='motorI')
        #ax4.plot(data_ctrl_motor['x'], data_ctrl_motor['motorD'], label='motorD')
        #ax4.set_ylabel('Motor Ctrl \n 0-255')
        #ax4.set_ylim([-300, 300])
        #leg4 = ax4.legend(loc='upper right', shadow=True)
        #plt.grid()

        ## Controller
        ax5 = fig.add_subplot(615)
        ax5.plot(data_ctrl['x'], data_ctrl['error'], '--', label='error')
        ax5.plot(data_ctrl['x'], data_ctrl['p'], label='p')
        ax5.plot(data_ctrl['x'], data_ctrl['i'], label='i')
        ax5.plot(data_ctrl['x'], data_ctrl['d'], label='d')
        ax5.set_ylabel('Ctrl Sig PID\n-255 to 255')
        #ax5.set_ylim([-300, 300])
        if time_lim is not None: ax5.set_xlim(time_lim)
        leg5 = ax5.legend(loc='upper right', shadow=True)
        plt.grid()
         
        #ax5.set_xlabel('Time /s')

        ## Controller
        ax6 = fig.add_subplot(616)
        ax6.plot(data_elec_motor['x'], data_elec_motor['v'], label='v')
        ax6.plot(data_elec_motor['x'], data_elec_motor['i'], label='i')
        ax6.plot(data_elec_motor['x'], data_elec_motor['p'], label='p')
        ax6.set_ylabel('Voltage, current, power')
        if time_lim is not None: ax6.set_xlim(time_lim)
        leg6 = ax6.legend(loc='upper right', shadow=True)
        plt.grid()

#        fig2 = plt.figure(2)
#        a2x1 = fig2.add_subplot(111)
#        a2x1.plot(data_out['x'], data_out['force_car'], '--', label='force_car')
#        a2x1.plot(data_out['x'], data_out['force_aero'], label='force_aero')
#        a2x1.plot(data_out['x'], data_out['force_powertrain'], ':', label='force_powertrain')
#        a2x1.set_ylabel('Force /N')
#        a2x1.set_xlabel('Time /s')
#        l2eg1 = a2x1.legend(loc='upper right', shadow=True)


    print(Fore.YELLOW, Style.BRIGHT)
    print("Speed Cost:", round(leaf1._powertrain_model_array[0]._speed_control.cost, 1))
    #print("Motor Cost:", round(leaf1._powertrain_model_array[0]._speed_control._motor_controller.cost, 1))
    #print("Brake Cost:", round(leaf1._powertrain_model_array[0]._speed_control._brake_controller.cost, 1))    

    print(Fore.RED, Style.BRIGHT)
    print("\n", round((time.time()-time_start),1), "seconds to run")
    print(Fore.RED, Style.DIM)
    print("\n***end***\n\n")
    print(Style.RESET_ALL)

    if graph:
        plt.show()


