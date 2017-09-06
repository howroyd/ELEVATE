#!/usr/bin/python3
from elevate_includes import *

VERSION = 2.2

graph = True
feed_forward = 1 # Zero/None for off, integer for for forcast distance
matlab = False
display = True

inpath = "DriveCycles"
outpath= "Results"

#filename = "nedc_kph"
#filename = "WLTP_kph"


#filename = "FTP75_mph"
#filename = "HWFET_mph"
#filename = "SFTP_US06_mph"



filename = "bham_lboro_int_mph"

#filename = "parabola_kph"
#filename = "impulse_kph"
#filename = "step_kph"
#filename = "sine_kph"

time_lim = None
#time_lim = [920, 940]

def display_init():
    colorama.init()
    print(Fore.GREEN, Style.BRIGHT, end='')
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

time_lim = None
#time_lim = [920, 940]

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
    while not datafile.finished:

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
            get(mycar[0], 'battery_v'),
            get(mycar[0], 'battery_i'),
            get(mycar[0], 'battery_v')*get(mycar[0], 'battery_i')/1000,
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
        if time_lim is not None: ax1.set_xlim(time_lim)
        leg1 = ax1.legend(loc='upper right', shadow=True)
        plt.grid()

        ax2 = fig.add_subplot(512)
        ax2.plot(data_force['x'], data_force['force'], label='Total')
        ax2.plot(data_force['x'], data_force['F_motor'], label='Fmotor')
        ax2.plot(data_force['x'], data_force['F_brake'], label='Fbrake')
        ax2.plot(data_force['x'], data_force['F_aero_d'], label='Faero')
        ax2.set_ylabel('Force\nNewtons')
        if time_lim is not None: ax2.set_xlim(time_lim)
        leg2 = ax2.legend(loc='upper right', shadow=True)
        plt.grid()

        ax3 = fig.add_subplot(513)
        ax3.plot(data_ctrl['x'], data_ctrl['motor'], label='motor')
        ax3.plot(data_ctrl['x'], data_ctrl['brake'], label='brake')
        ax3.set_ylabel('Ctrl Sig\n-255 to 255')
        ax3.set_ylim([-300, 300])
        ax3.set_xlim(time_lim)
        leg3 = ax3.legend(loc='upper right', shadow=True)
        plt.grid()

        ax5 = fig.add_subplot(514)
        ax5.plot(data_ctrl['x'], data_ctrl['error'], '--', label='error')
        ax5.plot(data_ctrl['x'], data_ctrl['p'], label='p')
        ax5.plot(data_ctrl['x'], data_ctrl['i'], label='i')
        ax5.plot(data_ctrl['x'], data_ctrl['d'], label='d')
        ax5.set_ylabel('Ctrl Sig PID\n-255 to 255')
        if time_lim is not None: ax5.set_xlim(time_lim)
        leg5 = ax5.legend(loc='upper right', shadow=True)
        plt.grid()
         
        ax6 = fig.add_subplot(515)
        ax6.plot(data_elec_motor['x'], data_elec_motor['v'], label='v')
        ax6.plot(data_elec_motor['x'], data_elec_motor['i'], label='i')
        ax6.set_ylabel('Voltage,\ncurrent,\npower')
        if time_lim is not None: ax6.set_xlim(time_lim)
        leg6 = ax6.legend(loc='upper right', shadow=True)
        plt.grid()



        ## Figure 2
        fig_pres = plt.figure(2)        
        fig_pres.suptitle(filename)

        plt.style.use('grayscale')
        

        ax7 = fig_pres.add_subplot(111)
        ax7.plot(data_out['x'], data_out['v_tgt'], ':', label='v_tgt')
        ax7.plot(data_out['x'], data_out['v_car'], label='v_car')
        ax7.plot(data_out['x'], data_out['dv'], '--', label='dv')
        ax7.set_ylabel('Speed /'+units)
        ax7.set_xlabel('Time /s')
        if time_lim is not None: ax7.set_xlim(time_lim)
        leg7 = ax7.legend(loc='upper center', shadow=True)
        plt.grid()

        #ax8 = fig_pres.add_subplot(212)
        #ax8.plot(data_force['x'], data_force['force'], label='Total')
        #ax8.plot(data_force['x'], data_force['F_motor'], label='Fmotor')
        #ax8.plot(data_force['x'], data_force['F_brake'], label='Fbrake')
        #ax8.set_ylabel('Force\nNewtons')
        #if time_lim is not None: ax8.set_xlim(time_lim)
        #leg8 = ax8.legend(loc='upper right', shadow=True)
        #plt.grid()


    print(Fore.YELLOW, Style.BRIGHT)
    print("Speed Cost:", round(mycar[0]._powertrain_model_array[0]._speed_control.cost, 1))
    #print("Motor Cost:", round(leaf1._powertrain_model_array[0]._speed_control._motor_controller.cost, 1))
    #print("Brake Cost:", round(leaf1._powertrain_model_array[0]._speed_control._brake_controller.cost, 1))    

    print(Fore.RED, Style.BRIGHT)
    print("\n", round((time.time()-time_start),1), "seconds to run")
    print(Fore.RED, Style.DIM)
    print("\n***end***\n\n")
    print(Style.RESET_ALL)

    if graph:
        plt.show()


