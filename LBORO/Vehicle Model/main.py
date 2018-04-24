#!/usr/bin/python3
from elevate_includes import *

VERSION = 2.2

<<<<<<< HEAD
graph = True
feed_forward = 1 # Zero/None for off, integer for for forcast distance
matlab = False
display = True

inpath = "DriveCycles"
outpath= "Results"

#filename = "nedc_kph"
filename = "WLTP_kph"


#filename = "FTP75_mph"
#filename = "HWFET_mph"
#filename = "SFTP_US06_mph"
#filename = "bham_lboro_int_mph"
#filename = "step_irl_mph"


#filename = "parabola_kph"
#filename = "impulse_kph"
#filename = "step_kph"
#filename = "sine_kph"

break_at_pc = 10

def display_init():
    colorama.init()
    print(Fore.GREEN, Style.BRIGHT, end='')
    print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")
    print("Hardware Simulation Model Version", VERSION)
    print("Simon Howroyd", datetime.date.today().year)
    print("Loughborough University")
    print(Style.RESET_ALL)
    print(sys.version, '\n')
=======
# Electric Vehicle, Object Oriented Model

# ELEVATE (ELEctric Vehicles and Advanced TEchnologies)
# Simon Howroyd, Loughborough University 2018

VERSION = 2.1

###############################
###    IMPORT LIBRARIES     ###
###############################
from elevate_includes import *
from Cars import Nissan_Leaf
from ElectricityClass import joules_to_kwh

###############################
###     LOCAL VARIABLES     ###
###############################
disp         = Display(VERSION)
graph        = True
feed_forward = False


###############################
###   TEST DATAFILE NAME    ###
###############################
filename     = "nedc2_short"
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
>>>>>>> linking_overhaul

def matlab_init():
    eng = matlab.engine.start_matlab('-nojvm')
    print(eng.sqrt(4.0))
    eng.quit()
    return eng

def check_units(fname):
    if 'kph' in filename:
        _conversion_factor = 1.0/3.6
        _units = 'kph'
    elif 'mph' in filename:
        _conversion_factor = 0.44704
        _units = 'mph'
    elif 'ms' in filename:
        _conversion_factor = 1.0
        _units = 'ms'
    else:
        sys.exit("No defined speed units in drive cycle filename")
    return _conversion_factor, _units

# Check the units of the input data file; mph, kph, m/s
conversion_factor, units = check_units(filename)

time_start = 0.0
time_init  = 0.0
time_calc  = 0.0
time_disp  = 0.0

def get(ptr, item):
    if item in ptr.data:
        return ptr.data[item]
    else:
        #print(item + ' not found')
        return None

mytime = 0
dt = 0.01

# Main run function
if __name__ == "__main__":
    # Make a note of the start time
    time_start = time.time()

    # Initialise the terminal display
    if display: display_init()

    # Initialise the Matlab engine
    if matlab: matlab_init()
    
<<<<<<< HEAD
    # Construct the input data gatherer and timer
    datafile     = DataInputClass(inpath+"/"+filename+".tsv", outpath+"/"+filename+".csv")
    #timer        = Continuous_dt(datafile.dt, 50)

    # Construct the output data buffers
    d_force      = DataOutputClass(outpath+"/"+"force")
    d_gen        = DataOutputClass(outpath+"/"+"general")
    d_ctrl       = DataOutputClass(outpath+"/"+"ctrl")
    d_ctrl_spd   = DataOutputClass(outpath+"/"+"ctrl_spd")
    d_ctrl_motor = DataOutputClass(outpath+"/"+"ctrl_motor")
    d_ctrl_brake = DataOutputClass(outpath+"/"+"ctrl_brake")
    d_elec_motor = DataOutputClass(outpath+"/"+"elec_motor")

    # Define low pass filters TODO
    lpf1 = LowPassFilter(1.0)
    lpf2 = LowPassFilter(1.0) # Feed forward
    
    # Spawn vehicle(s)
    mycar = list()
    mycar.append(CarClass(Nissan_Leaf().data))
    
    print(datafile.num_lines, 'lines in input file\n')
    _new_data = False
    # RUN SIMULATION
    while (not datafile.finished) and (datafile.percent_complete <= break_at_pc):

        # Update the timer and input data file
        #timer.update()
        mytime += dt
        _new_data = datafile.update(mytime)#timer.sim_time)

        # Calculate dynamics (main updater)
        for _car in mycar:
            # Update target speed if required
            if _new_data:
                #_car.target_speed = lpf1.get((datafile.line[1] if datafile.line[1] is not 'NaN' else 0) *conversion_factor)
                #print(datafile.line)
                _car.target_speed = ((datafile.line[1] if datafile.line[1] is not 'NaN' else 0) *conversion_factor)

                if feed_forward:
                    #_car.feed_forward_speed = lpf2.get((datafile.line[1] if datafile.line[1] is not 'NaN' else 0) *conversion_factor)
                    #print(datafile.read_ahead(10))
                    _car.feed_forward_speed = ((datafile.read_ahead(feed_forward)[1] if datafile.read_ahead(feed_forward)[1] is not 'NaN' else 0) *conversion_factor)

            _car.update(dt)#timer.dt)

        # Output data to save file
        d_gen.line = [mytime,
            (datafile.line[1] if datafile.line[1] is not 'NaN' else 0),
            get(mycar[0], 'car_target_speed') / conversion_factor,
            get(mycar[0], 'car_speed') / conversion_factor,
            get(mycar[0], 'car_dv') / conversion_factor,
            get(mycar[0], 'speedController_error'),
            get(mycar[0], 'speedController_p'),
            get(mycar[0], 'speedController_i'),
            get(mycar[0], 'speedController_d'),
            get(mycar[0], 'speedController_powertrain_state'),
            ]
        d_gen.update()

        d_force.line = [mytime,
            get(mycar[0], 'car_total_force'),
            get(mycar[0], 'front_left_force_motor'),
            get(mycar[0], 'front_left_force_brake'),
            get(mycar[0], 'aero_dynamic'),
            ]
        d_force.update()

        d_ctrl.line = [mytime,
            mycar[0]._powertrain_model_array[0].error,
            get(mycar[0], 'motor_value'),
            get(mycar[0], 'brake_value'),
            get(mycar[0], 'speedController_p'),
            get(mycar[0], 'speedController_i'),
            get(mycar[0], 'speedController_d'),
            ] 
        d_ctrl.update()

        d_elec_motor.line = [mytime,
            get(mycar[0], 'motor_v'),
            get(mycar[0], 'motor_i'),
            get(mycar[0], 'motor_p'),
            ]
        d_elec_motor.update()

        #d_ctrl_motor.update()

        #d_ctrl_spd.update()
        #d_ctrl_brake.update()
        #

        # Print to screen the percentage of number of lines completed from the input data file
        if datafile.new_data: print(round(datafile.percent_complete,1),'%',end='\r')

    # Print to screen the percentage of number of lines completed from the input data file
    print(Fore.GREEN, Style.BRIGHT, end='')
    print('100 % -', end='')
    print(Fore.RED, Style.BRIGHT, end='')
    print(round((time.time()-time_start),1), 'sec', end='\r\n')
    print(Style.RESET_ALL, end='')
    
    print(end='\r\n')

    #time.sleep(2)

    # Plot data to screen
    if graph:
        data_out = np.genfromtxt(outpath+"/"+"general_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'data', 'v_tgt', 'v_car', 'dv', 'speedE', 'speedP', 'speedI', 'speedD', 'state'])#, 'motorE',
                                #'motorP', 'motorI', 'motorD', 'brakeE', 'brakeP', 'brakeI', 'brakeD', 'parking',
                                #'state', 'slip', 'force', 'force_car', 'force_aero', 'force_powertrain',
                                #'w_veh', 'w_wheel', 'Tm', 'Tb', 'F', 'w', 'adhesion','adhesion2', 'v', 'dt', 'F_motor', 'F_brake'])

        
        data_force = np.genfromtxt(outpath+"/"+"force_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'force', 'F_motor', 'F_brake', 'F_aero_d'])

        data_ctrl = np.genfromtxt(outpath+"/"+"ctrl_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'error', 'motor', 'brake', 'p', 'i', 'd'])

        data_elec_motor = np.genfromtxt(outpath+"/"+"elec_motor_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'v', 'i', 'p'])




        # Figure 1
        fig = plt.figure(1)
        fig.suptitle(filename)

        ax1 = fig.add_subplot(511)
        ax1.plot(data_out['x'], data_out['v_tgt'], ':', label='v_tgt')
        ax1.plot(data_out['x'], data_out['v_car'], label='v_car')
        ax1.plot(data_out['x'], data_out['dv'], '--', label='dv')
        ax1.set_ylabel('Velocity\n'+units)
        #if time_lim is not None: ax1.set_xlim(time_lim)
=======
    datafile = DataIoClass(filename+".tsv")
    timer    = Continuous_dt(datafile.dt, 50)

    # Spawn vehicle(s)
    mycar = CarClass(Nissan_Leaf().data)
    
    disp.disp(datafile.num_lines, " lines in input file")

    disp.disp("SoC at start ",     round(mycar.battery_electricity.get('soc')*100.0,1), '%\n')

    progress = progressbar.ProgressBar().start()

    ###############################
    ###    BEGIN SIMULATION     ###
    ###############################
    while not datafile.finished and timer.sim_time<(10*60):


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
            mycar.target_speed = mph_to_ms(datafile.line[1])


        ###############################
        ###      UPDATE MODEL       ###
        ###############################
        mycar.update(timer.dt)


        ###############################
        ###      UPDATE SAVE        ###
        ###############################
        datafile.line = [ timer.sim_time ]

        datafile.line = [ ms_to_mph(mycar.target_speed) ]
        datafile.line = [ ms_to_mph(mycar.speed) ]
        datafile.line = [ mycar.powertrain_mode ]
        datafile.line = [ int(mycar._powertrain._motor.is_generating) ]

        datafile.line = [ mycar.aero_force ]

        datafile.line = [ mycar.speed_ctrl_error ]
        datafile.line = [ mycar.speed_ctrl_pid.get('p') ]
        datafile.line = [ mycar.speed_ctrl_pid.get('i') ]
        datafile.line = [ mycar.speed_ctrl_pid.get('d') ]

        datafile.line = [ mycar.motor_ctrl_error ]
        datafile.line = [ mycar.motor_ctrl_pid.get('p') ]
        datafile.line = [ mycar.motor_ctrl_pid.get('i') ]
        datafile.line = [ mycar.motor_ctrl_pid.get('d') ]

        datafile.line = [ mycar.brake_ctrl_error ]
        datafile.line = [ mycar.brake_ctrl_pid.get('p') ]
        datafile.line = [ mycar.brake_ctrl_pid.get('i') ]
        datafile.line = [ mycar.brake_ctrl_pid.get('d') ]

        datafile.line = [ mycar.battery_electricity.get('voltage') ]
        datafile.line = [ mycar.esc_electricity.get('voltage') ]
        datafile.line = [ mycar.motor_electricity.get('voltage') ]

        datafile.line = [ mycar.battery_electricity.get('current') ]
        #datafile.line = [ mycar.esc_electricity.get('current') ]
        datafile.line = [ mycar._powertrain._esc.current ]
        datafile.line = [ mycar.motor_electricity.get('current') ]

        datafile.line = [ mycar.motor_rotation.get('torque') ]
        datafile.line = [ mycar.axle_rotation.get('torque') ]
        datafile.line = [ mycar.wheel_rotation[0].get('torque') ]
        datafile.line = [ mycar.wheel_rotation[2].get('torque') ]
        datafile.line = [ mycar.brake_rotation[0].get('torque') ]
        datafile.line = [ mycar.brake_rotation[2].get('torque') ]

        datafile.line = [ rads_to_rpm(mycar.motor_rotation.get('speed')) ]
        datafile.line = [ rads_to_rpm(mycar.axle_rotation.get('speed')) ]
        datafile.line = [ rads_to_rpm(mycar.wheel_rotation[0].get('speed')) ]
        datafile.line = [ rads_to_rpm(mycar.wheel_rotation[2].get('speed')) ]
        datafile.line = [ rads_to_rpm(mycar.brake_rotation[0].get('speed')) ]
        datafile.line = [ rads_to_rpm(mycar.brake_rotation[2].get('speed')) ]

    progress.finish()
    disp.disp("", end='\r\n')


    odometer = mycar.odometer/1000.0
    odometerW= mycar.odometer_wheels/1000.0
    soc      = mycar.battery_electricity.get('soc')*100.0
    kwh_out  = joules_to_kwh(mycar.battery_electricity.get('total_energy_out'))
    kwh_in   = joules_to_kwh(mycar.battery_electricity.get('total_energy_in'))

    disp.disp("Odometer ",         round(odometer,1), "km")
    disp.disp("Odometer (wheels)", round(odometerW,1), "km")
    disp.disp("Soc at end ",       round(soc,1), "%")
    disp.disp("Total energy out ", round(kwh_out, 1), "kWh")
    disp.disp("Total energy in ",  round(kwh_in, 1),  "kWh")
    disp.disp("Efficiency ",       round(100.0*kwh_out/odometer,1), "kWh/100km")

    disp.disp("\n\nFinished!\n\n")


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
>>>>>>> linking_overhaul
        leg1 = ax1.legend(loc='upper right', shadow=True)
        plt.grid()

<<<<<<< HEAD
        ax2 = fig.add_subplot(512)
        ax2.plot(data_force['x'], data_force['force'], label='Total')
        ax2.plot(data_force['x'], data_force['F_motor'], label='Fmotor')
        ax2.plot(data_force['x'], data_force['F_brake'], label='Fbrake')
        ax2.plot(data_force['x'], data_force['F_aero_d'], label='Faero')
        ax2.set_ylabel('Force\nNewtons')
        #if time_lim is not None: ax2.set_xlim(time_lim)
=======
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
>>>>>>> linking_overhaul
        leg2 = ax2.legend(loc='upper right', shadow=True)
        plt.grid()

<<<<<<< HEAD
        ax3 = fig.add_subplot(513)
        ax3.plot(data_ctrl['x'], data_ctrl['motor'], label='motor')
        ax3.plot(data_ctrl['x'], data_ctrl['brake'], label='brake')
        ax3.set_ylabel('Ctrl Sig\n-255 to 255')
        ax3.set_ylim([-300, 300])
        #if time_lim is not None: ax3.set_xlim(time_lim)
=======
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
>>>>>>> linking_overhaul
        leg3 = ax3.legend(loc='upper right', shadow=True)
        plt.grid()

<<<<<<< HEAD
        ax5 = fig.add_subplot(514)
        ax5.plot(data_ctrl['x'], data_ctrl['error'], '--', label='error')
        ax5.plot(data_ctrl['x'], data_ctrl['p'], label='p')
        ax5.plot(data_ctrl['x'], data_ctrl['i'], label='i')
        ax5.plot(data_ctrl['x'], data_ctrl['d'], label='d')
        ax5.set_ylabel('Ctrl Sig PID\n-255 to 255')
        #if time_lim is not None: ax5.set_xlim(time_lim)
        leg5 = ax5.legend(loc='upper right', shadow=True)
        plt.grid()
         
        ax6 = fig.add_subplot(515)
        ax6.plot(data_elec_motor['x'], data_elec_motor['v'], label='v')
        ax6.plot(data_elec_motor['x'], data_elec_motor['i'], label='i')
        ax6.set_ylabel('Voltage,\ncurrent,\npower')
        #if time_lim is not None: ax6.set_xlim(time_lim)
        leg6 = ax6.legend(loc='upper right', shadow=True)
        plt.grid()



        ### Figure 2
        #fig_pres = plt.figure(2)        
        ##fig_pres.suptitle(filename)

        #plt.style.use('presentation')
        

        #ax7 = fig_pres.add_subplot(111)
        #ax7.plot(data_out['x'], data_out['v_car'], label='Actual Velocity')
        #ax7.plot(data_out['x'], data_out['v_tgt'], '--', label='Target Velocity')
        ##ax7.plot(data_out['x'], data_out['dv'], '--', label='dv')
        #ax7.set_ylabel('Vehicle Velocity /'+units)
        #ax7.set_xlabel('Time /s')
        ##if time_lim is not None: ax7.set_xlim(time_lim)
        #leg7 = ax7.legend(loc='upper left', shadow=True)
        #plt.grid()

        ##ax8 = fig_pres.add_subplot(212)
        ##ax8.plot(data_force['x'], data_force['force'], label='Total')
        ##ax8.plot(data_force['x'], 2*data_force['F_motor']/1000, '--.', label='force_motor')
        ##ax8.plot(data_force['x'], 4*data_force['F_brake']/-1000, ':', label='force_brake')
        ##ax8.set_ylabel('Horizontal Force /kN')
        ##if time_lim is not None: ax8.set_xlim(time_lim)
        ##leg8 = ax8.legend(loc='upper left', shadow=True)
        ##plt.grid()

        #fig_pres.tight_layout()

        rmse = np.sqrt(((data_out['v_car'] - data_out['v_tgt']) ** 2).mean())

        print("RMSE: ", rmse)


    print(Fore.YELLOW, Style.BRIGHT)
    print("Speed Cost:", round(mycar[0]._powertrain_model_array[0]._speed_control.cost, 1))
    #print("Motor Cost:", round(leaf1._powertrain_model_array[0]._speed_control._motor_controller.cost, 1))
    #print("Brake Cost:", round(leaf1._powertrain_model_array[0]._speed_control._brake_controller.cost, 1))    
=======
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
>>>>>>> linking_overhaul

    ###############################
    ###       SHOW TIME         ###
    ###############################
    disp.disp_time(("\n", round((time.time()-time_start),1), "seconds to run"))

    ###############################
    ###       SHOW GRAPH        ###
    ###############################
    if graph:
        plt.show()

<<<<<<< HEAD

=======
###############################
###############################
######       END         ######
###############################
###############################
>>>>>>> linking_overhaul
