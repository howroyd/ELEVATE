#!/usr/bin/python3
from elevate_includes import *
from BrakesClass import BrakesClass
from WheelClass import WheelClass
from battery_sw import Battery_Model
from MotorClass import MotorClass
from PowertrainClass import PowertrainClass

VERSION = 0.0

outpath= "Results"

def display_init():
    colorama.init()
    print(Fore.GREEN, Style.BRIGHT, end='')
    print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")
    print("Hardware Simulation Model Version", VERSION)
    print("Simon Howroyd", datetime.date.today().year)
    print("Loughborough University")
    print(Style.RESET_ALL)
    print(sys.version, '\n')

def get(ptr, item):
    if item in ptr.data:
        return ptr.data[item] if ptr.data[item] is not None else 0.0
    else:
        #print(item + ' not found')
        return None

def get_motor_wheel(_car, _val):
    return (_val / 255) * _car._data.get('motor_max_torque') * _car._data.get('motor_reduction_ratio') / 2

def check_units(fname):
    if 'kph' in fname:
        _conversion_factor = 1.0/3.6
        _units = 'kph'
    elif 'mph' in fname:
        _conversion_factor = 0.44704
        _units = 'mph'
    elif 'ms' in fname:
        _conversion_factor = 1.0
        _units = 'ms'
    else:
        sys.exit("No defined speed units in drive cycle filename")
    return _conversion_factor, _units

# Check the units of the input data file; mph, kph, m/s
conversion_factor, units = check_units("mph")




# Main run function
if __name__ == "__main__":
    # Make a note of the start time
    time_start = time.time()

    # Initialise the terminal display
    display_init()





    car = Nissan_Leaf()

    battery = Battery_Model(car.data)
    
    brake = BrakesClass(car._data.get('wheel_diameter'), car._data.get('brake_max_torque')[0], kwargs=dict())
    wheel = [WheelClass(brake, kwargs={'wheel_diameter':car._data.get('wheel_diameter') , 'car_mass':car._data.get('car_mass')})] * 2

    motor   = MotorClass(wheel, car.data)
    motor.regen_activated = False

    powertrain = PowertrainClass([battery], [motor], wheel, car.data)



    
    # Construct the output data buffers
    d_wheel      = DataOutputClass(outpath+"/"+"wheel")

    

    speed = 0.0

    for ptr in wheel:
        ptr.vehicle_speed = speed
        ptr.brake_parking = False
    powertrain.force = 0.0
    powertrain.current_speed = speed
    powertrain.update(0)

    dt = 0.01
    # RUN SIMULATION
    for x in np.arange(0.0, 130.0, dt):

        if x < 1:
            powertrain.target_speed = 0
        elif x < 15:
            powertrain.target_speed = conversion_factor * 60
        elif x < 70:
            powertrain.target_speed = conversion_factor * 50
        elif x < 100:
            powertrain.target_speed = conversion_factor * 30
        else:
            powertrain.target_speed = 0.0










        powertrain.current_speed = speed
        
        


        #wheel.update(x)

        drag_dynamic = 0.5*1.225*speed*speed*car._data.get('car_area')*car._data.get('car_cd')

        force = wheel[0].force*2.0 - drag_dynamic

        accn = force / (car._data.get('car_mass'))

        speed = max(speed + accn*dt, 0.0)

        for ptr in wheel:
            ptr.vehicle_speed = speed

        powertrain.force = force

        powertrain.update(x)



        # Output data to save file
        d_wheel.line = [x,
            get(powertrain, 'brake_value'),
            get(powertrain, 'brake_torque'),
            get(powertrain, 'wheel_force_motor'), #dN
            get(powertrain, 'wheel_force_brake'), #N E10
            get(powertrain, 'wheel_force'), #N E10
            speed/conversion_factor,
            ]
        d_wheel.update()

    # Print to screen the percentage of number of lines completed from the input data file
    print(Fore.GREEN, Style.BRIGHT, end='')
    print('100 % -', end='')
    print(Fore.RED, Style.BRIGHT, end='')
    print(round((time.time()-time_start),1), 'sec', end='\r\n')
    print(Style.RESET_ALL, end='')
    
    print(end='\r\n')

    d_wheel.__del__()

    # Plot data to screen
    if True:
        data_out = np.genfromtxt(outpath+"/"+"wheel_out"+".csv", delimiter=',', skip_header=1, skip_footer=1,
                    names = ['x', 'brake_value', 'brake_torque', 'force_motor', 'force_brake', 'force', 'speed'])

        plt.style.use('grayscale')

        line_width = 2.0



        ## Figure 2
        fig_pres = plt.figure(1)        
        fig_pres.suptitle("Powertrain")

        ax7 = fig_pres.add_subplot(211)#add_subplot(211)
        #ax7.plot(data_out['x'], data_out['brake_value'], label='brake_value')
        #ax7.plot(data_out['x'], data_out['brake_torque'], label='brake_torque')
        #ax7.plot(data_out['x'], data_out['force_motor'], label='force_motor')
        #ax7.plot(data_out['x'], data_out['force_brake'], ':', label='force_brake')
        #ax7.plot(data_out['x'], data_out['force'], '--', label='force')
        ax7.plot(data_out['x'], data_out['speed'], '--', label='speed')
        ax7.set_ylabel('Vehicle Speed /mph')
        leg7 = ax7.legend(loc='upper right', shadow=True)
        plt.grid()
        ax7.set_xlabel('Something something complete')

        ax8 = fig_pres.add_subplot(212)#add_subplot(211)
        #ax8.plot(data_out['x'], data_out['brake_value'], label='brake_value')
        #ax8.plot(data_out['x'], data_out['brake_torque'], label='brake_torque')
        ax8.plot(data_out['x'], data_out['force_motor']/1000, label='force_motor')
        ax8.plot(data_out['x'], data_out['force_brake']/1000, ':', label='force_brake')
        #ax8.plot(data_out['x'], data_out['force'], '--', label='force')
        #ax8.plot(data_out['x'], data_out['speed'], '--', label='speed')
        ax8.set_ylabel('Horizontal Force /kN')
        leg8 = ax8.legend(loc='upper right', shadow=True)
        plt.grid()
        ax8.set_xlabel('Time /s')




    print(Fore.RED, Style.BRIGHT)
    print("\n", round((time.time()-time_start),1), "seconds to run")
    print(Fore.RED, Style.DIM)
    print("\n***end***\n\n")
    print(Style.RESET_ALL)

    plt.show()