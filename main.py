import telnetlib, time, sys, os
import matlab.engine
import matplotlib.pyplot as plt
import numpy as np
from TdiLoadbankClass import TdiLoadbank
from battery_sw import Battery_Model
from CarClass import CarClass
from DataInputClass import DataInputClass
from ControllerClass import ControllerClass
from Cars import Nissan_Leaf

many = False

# Main run function
if __name__ == "__main__":
    print("Hello world!")

    filename = "nedc2"

    #eng = matlab.engine.start_matlab('-nojvm')
    #print(eng.sqrt(4.0))
    #eng.quit()

    time_start = time.time()

    print(time_start)
    print(sys.version)
    
    d = DataInputClass(filename+".tsv")
    e = ControllerClass(d)

    dt = d.get_dt()

    print('Input dt =', dt)

    leaf_data = Nissan_Leaf()

    mycar = list()
    
    if many:
        for x in range(1000):
            mycar.append(CarClass(dt, leaf_data.data))
    leaf = CarClass(dt, leaf_data.data)

    d.set_line(['Time','NEDC','Speed'])

    print(d.get_num_lines(), 'lines in input file')

    while (d.update()):
        if many:
            for x in mycar:
                x.target_speed = d.get_line()[1]/2.23694 # mph to m/s
                x.update()

        leaf.target_speed = d.get_line()[1]/2.23694 # mph to m/s
        leaf.update()

        d.set_line([d.get_line()[0], leaf.target_speed*2.23694, leaf.speed*2.23694, leaf._powertrain_model_array[0]._dv*2.23694, leaf._powertrain_model_array[0]._error])
        #print([d.get_line()[0], leaf.target_speed, leaf.speed])

        for ptr in leaf._powertrain_model_array[0]._motor_array:
            d.set_line([ptr.motor_value])
        for ptr in leaf._powertrain_model_array[0]._wheel_array:
            d.set_line([ptr.brake_value])

d.__del__()

data_out = np.genfromtxt(filename+"_out.csv", delimiter=',', skip_header=1, skip_footer=1, names = ['x', 'v_set', 'v_true', 'dv', 'error', 'motor', 'brake0', 'brake1', 'brake2', 'brake3'])

fig = plt.figure()
ax1 = fig.add_subplot(211)

ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
ax1.plot(data_out['x'], data_out['dv'], label='dv')
ax1.set_ylabel('Speed')
leg1 = ax1.legend(loc='upper right', shadow=True)

ax2 = fig.add_subplot(212)
ax2.plot(data_out['x'], data_out['motor'], label='motor')
ax2.plot(data_out['x'], data_out['brake0'], label='brake0')
ax2.plot(data_out['x'], data_out['brake1'], label='brake1')
ax2.plot(data_out['x'], data_out['brake2'], label='brake2')
ax2.plot(data_out['x'], data_out['brake3'], label='brake3')
ax2.set_ylabel('0-255')
leg2 = ax2.legend(loc='upper right', shadow=True)
ax2.set_xlabel('Time /s')

print("Complete in", int(time.time()-time_start),"seconds")

plt.show()

