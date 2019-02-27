#!/usr/bin/python3

# Electric Vehicle, Object Oriented Model

# ELEVATE (ELEctric Vehicles and Advanced TEchnologies)
# Simon Howroyd, Loughborough University 2018

VERSION = 2.1

###############################
###    IMPORT LIBRARIES     ###
###############################
from elevate_includes import *
from SupercapacitorClass import SupercapacitorClass
from Cars import Supercapacitor
from ElectricityClass import joules_to_kwh

from mpl_toolkits import mplot3d
#%matplotlib notebook
import numpy as np
import matplotlib.pyplot as plt

###############################
###     LOCAL VARIABLES     ###
###############################
disp         = Display(VERSION)
graph        = False
feed_forward = False
distribution = None

###############################
###   TEST DATAFILE NAME    ###
###############################
filename     = "sc_test"
#filename     = "realcycle_kph"


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
    
    datafile = DataIoClass(filename+".tsv")
    #timer    = Continuous_dt(datafile.dt, 50)
    timer    = Discrete_dt(10.0, 1)

    # Spawn supercapacitor(s)
    mysupercap = SupercapacitorClass(Supercapacitor().data)
    
    disp.disp(datafile.num_lines, " lines in input file")

    disp.disp("SoC at start ",     round( mysupercap.soc, 1 ), '%\n')

    progress = progressbar.ProgressBar().start()

    ###############################
    ###    BEGIN SIMULATION     ###
    ###############################
    while not datafile.finished:# and timer.sim_time<(10*60):


        ###############################
        ###      UPDATE TIMERS      ###
        ###############################
        timer.update()

        datafile.update(timer.sim_time)

        if datafile.new_data:
            progress.update(round(datafile.percent_complete,1))

            #if datafile.finished:
            #    disp.disp("100%", end="\n\n")
            #else:
            #    disp.disp(round(datafile.percent_complete,1),"%",end="\r")

        ###############################
        ###    SET VEHICLE SPEED    ###
        ###############################
        if datafile.new_data:
            #print('Datafile=', datafile.line, end='\n')
            mysupercap.current = datafile.line[1] * 1.0 / 1.0 # TODO


        ###############################
        ###      UPDATE MODEL       ###
        ###############################
            mysupercap.update(timer.dt)
            #mysupercap.update(10)
        
            if distribution is None:
                distribution = mysupercap.distribution
            else:
                distribution = np.append( distribution, mysupercap._distribution, axis=0 )

        ###############################
        ###      UPDATE SAVE        ###
        ###############################
        datafile.line = [ timer.sim_time ]

        datafile.line = [ mysupercap.voltage ]
        datafile.line = [ mysupercap.current ]
        datafile.line = [ mysupercap.soc ]


    progress.finish()
    disp.disp("", end='\r\n')

    X    = np.arange(mysupercap.num_rungs)
    Y    = np.arange(distribution.shape[0])
    Z    = distribution
    X, Y = np.meshgrid(X, Y)

    fig = plt.figure()
    ax = plt.axes(projection='3d')
    #ax.plot_surface(X, Y, Z, cmap='Greens')
    #ax.plot_surface(X, Y, Z, cmap='jet_r')
    ax.plot_surface(X, Y, Z, cmap='summer_r')
    ax.view_init(elev=25, azim=-130)
    z_low, z_high = ax.get_zlim()
    ax.set_zlim(0, z_high)
    ax.set_xlabel('Pascal Rungs of Series Stack')
    ax.set_ylabel('Time /s')
    ax.set_zlabel('Voltage /V')

    soc      = mysupercap.sc_data.get('soc')*100.0
    kwh_out  = joules_to_kwh(mysupercap.sc_data.get('total_energy_out'))
    kwh_in   = joules_to_kwh(mysupercap.sc_data.get('total_energy_in'))

    disp.disp("Soc at end ",       round(soc,1), "%")
    disp.disp("Total energy out ", round(kwh_out, 1), "kWh")
    disp.disp("Total energy in ",  round(kwh_in, 1),  "kWh")

    disp.disp("\n\nFinished!\n\n")
    plt.show()

    ###############################
    ###     COMPILE GRAPHS      ###
    ###############################
    if graph:

        # Get data from saved datafile
        data_out = np.genfromtxt(filename+"_out.csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = [   'x',
                                'v_set', 'v_true',  'mode', 'regen',
                                'dragAero',
                                'speedE', 'speedP', 'speedI', 'speedD',
                                'motorE', 'motorP', 'motorI', 'motorD',
                                'brakeE', 'brakeP', 'brakeI', 'brakeD',
                                'batt_v', 'esc_v',  'motor_v',
                                'batt_i', 'esc_i',  'motor_i',
                                'tq_m',   'tq_ax',  'tq_w0',   'tq_w2', 'tq_b0', 'tq_b2',
                                'w_m',    'w_ax',   'w_w0',    'w_w2',  'w_b0',  'w_b2'
                            ])

        timestamp = data_out['x']
        timestamp /= 60 # Convert seconds to minutes

        xlim = False
        #xlim = [1.9, 2.0]
        

        ###############################
        ###        FIGURE 1         ###
        ###############################
        fig = plt.figure()

        ###############################
        ###    FIG 1, SUBPLOT 1     ###
        ###############################
        ax1 = fig.add_subplot(411)
        ax1.plot(timestamp, data_out['v_set'],  label='v_set')
        ax1.plot(timestamp, data_out['v_true'], label='v_true')
        ax1.plot(timestamp, data_out['dragAero']/10, label='dragAero')
        ax1.set_ylabel('Mph, N/10')
        #ax1.set_ylim([0, 80])
        if xlim is not False:
            ax1.set_xlim(xlim)
            ax1.relim()
            ax1.autoscale_view(scalex=False, scaley=True)
        ax1.grid(True)
        leg1 = ax1.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 1, SUBPLOT 2     ###
        ###############################
        ax2 = fig.add_subplot(412)
        ax2.plot(timestamp, data_out['speedE'], label='speedE')
        ax2.plot(timestamp, data_out['speedP'], label='speedP', linestyle=':')
        ax2.plot(timestamp, data_out['speedI'], label='speedI', linestyle=':')
        ax2.plot(timestamp, data_out['speedD'], label='speedD', linestyle=':')
        ax2.set_ylabel('Speed Ctrl \n 0-255')
        #ax2.set_ylim([-260, 260])
        if xlim is not False:
            ax2.set_xlim(xlim)
            ax2.relim()
            ax2.autoscale_view(scalex=False, scaley=True)
        ax2.grid(True)
        leg2 = ax2.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 1, SUBPLOT 3     ###
        ###############################
        ax3 = fig.add_subplot(413)
        ax3.plot(timestamp, data_out['motorE'], label='motorE')
        ax3.plot(timestamp, data_out['motorP'], label='motorP', linestyle=':')
        ax3.plot(timestamp, data_out['motorI'], label='motorI', linestyle=':')
        ax3.plot(timestamp, data_out['motorD'], label='motorD', linestyle=':')
        ax3.set_ylabel('Motor Ctrl \n 0-255')
        #ax3.set_ylim([-260, 260]
        if xlim is not False:
            ax3.set_xlim(xlim)
            ax3.relim()
            ax3.autoscale_view(scalex=False, scaley=True)
        ax3.grid(True)
        leg3 = ax3.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 1, SUBPLOT 4     ###
        ###############################
        ax4 = fig.add_subplot(414)
        ax4.plot(timestamp, data_out['brakeE'], label='brakeE')
        ax4.plot(timestamp, data_out['brakeP'], label='brakeP', linestyle=':')
        ax4.plot(timestamp, data_out['brakeI'], label='brakeI', linestyle=':')
        ax4.plot(timestamp, data_out['brakeD'], label='brakeD', linestyle=':')
        ax4.set_ylabel('Brake Ctrl \n 0-255')
        #ax4.set_ylim([-260, 260])
        if xlim is not False:
            ax4.set_xlim(xlim)
            ax4.relim()
            ax4.autoscale_view(scalex=False, scaley=True)
        leg4 = ax4.legend(loc='upper right', shadow=True)
        ax4.grid(True)
        # Fig 1 x-Axis Label
        ax4.set_xlabel('Time /mins')


        ###############################
        ###        FIGURE 2         ###
        ###############################
        fig2 = plt.figure()

        ###############################
        ###    FIG 2, SUBPLOT 1     ###
        ###############################
        ax1 = fig2.add_subplot(411)
        #ax1.plot(timestamp, data_out['batt_v'],  label='batt_v')
        #ax1.plot(timestamp, data_out['esc_v'],   label='esc_v')
        #ax1.plot(timestamp, data_out['motor_v'], label='motor_v')
        #ax1.plot(timestamp, data_out['batt_i'],    label='batt_i')
        #ax1.plot(timestamp, data_out['esc_i'],     label='esc_i')
        #ax1.plot(timestamp, data_out['motor_i'],   label='motor_i')
        #ax1.plot(timestamp, data_out['motor_v']*data_out['motor_i']/1000.0,   label='motor_p', linestyle=':')
        ax1.plot(timestamp, data_out['speedE'], label='speedE')
        ax1.plot(timestamp, data_out['motorE'], label='motorE', linestyle=':')
        ax1.plot(timestamp, data_out['brakeE'], label='brakeE', linestyle=':')
        ax1.set_ylabel('Speed Ctrl \n 0-255')
        #ax1.set_ylabel('Voltage/4V, Current/I, Power/kW')
        #ax1.set_ylim([300, 400])
        if xlim is not False:
            ax1.set_xlim(xlim)
            ax1.relim()
            ax1.autoscale_view(scalex=False, scaley=True)
        ax1.grid(True)
        leg1 = ax1.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 2, SUBPLOT 2     ###
        ###############################
        ax2 = fig2.add_subplot(412)
        #ax2.plot(timestamp, data_out['mode'],  label='mode')
        #ax2.plot(timestamp, data_out['regen'], label='regen', linestyle=':')
        #ax2.set_ylabel('Mode')
        #ax2.set_ylim([0, 5])
        ax2.plot(timestamp, data_out['batt_i'],  label='batt_i')
        ax2.plot(timestamp, data_out['esc_i'],   label='esc_i')
        ax2.plot(timestamp, data_out['motor_i'], label='motor_i')
        ax2.plot([0,max(timestamp)], [267,267],  linestyle='--', color='k')
        ax2.set_ylabel('Current')
        ax2.set_ylim([0, 300])
        if xlim is not False:
            ax2.set_xlim(xlim)
            ax2.relim()
            ax2.autoscale_view(scalex=False, scaley=True)
        ax2.grid(True)
        leg2 = ax2.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 2, SUBPLOT 3     ###
        ###############################
        ax3 = fig2.add_subplot(413)
        ax3.plot(timestamp, data_out['tq_m'],    label='tq_m' , linestyle='-')
        ax3.plot(timestamp, data_out['tq_ax'],   label='tq_ax', linestyle=':')
        ax3.plot(timestamp, data_out['tq_w0'],   label='tq_w0', linestyle='-')
        ax3.plot(timestamp, data_out['tq_b0'],   label='tq_b0', linestyle=':')
        ax3.set_ylabel('Torque')
        #ax3.set_ylim([0, 300])
        if xlim is not False:
            ax3.set_xlim(xlim)
            ax3.relim()
            ax3.autoscale_view(scalex=False, scaley=True)
        ax3.grid(True)
        leg3 = ax3.legend(loc='upper right', shadow=True)

        ###############################
        ###    FIG 2, SUBPLOT 4     ###
        ###############################
        ax4 = fig2.add_subplot(414)
        ax4.plot(timestamp, data_out['w_m'],      label='w_m' , linestyle='-')
        ax4.plot(timestamp, data_out['w_ax'],     label='w_ax', linestyle=':')
        ax4.plot(timestamp, data_out['w_w0'],     label='w_w0', linestyle='-')
        ax4.plot(timestamp, data_out['w_b0'],     label='w_b0', linestyle=':')
        ax4.set_ylabel('RPM')
        #ax4.set_ylim([-260, 260])
        if xlim is not False:
            ax4.set_xlim(xlim)
            ax4.relim()
            ax4.autoscale_view(scalex=False, scaley=True)
        leg4 = ax4.legend(loc='upper right', shadow=True)
        ax4.grid(True)
        # Fig 1 x-Axis Label
        ax4.set_xlabel('Time /mins')


    ###############################
    ###       SHOW COSTS        ###
    ###############################
    #disp.disp_cost("Speed Cost:", round(leaf1._powertrain_model_array[0]._speed_control.cost, 1))
    #disp.disp_cost("Motor Cost:", round(leaf1._powertrain_model_array[0]._speed_control._motor_controller.cost, 1))
    #disp.disp_cost("Brake Cost:", round(leaf1._powertrain_model_array[0]._speed_control._brake_controller.cost, 1))    

    ###############################
    ###       SHOW TIME         ###
    ###############################
    disp.disp_time(("\n", round((time.time()-time_start),1), "seconds to run"))

    ###############################
    ###       SHOW GRAPH        ###
    ###############################
    if graph:
        plt.show()

###############################
###############################
######       END         ######
###############################
###############################matl