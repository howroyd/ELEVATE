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

# Main run function
if __name__ == "__main__":
    print("Hello world!")

    filename = "nedc2"

    #eng = matlab.engine.start_matlab('-nojvm')
    #print(eng.sqrt(4.0))
    #eng.quit()

    print(time.time())
    print(sys.version)
    
    d = DataInputClass(filename+".tsv")
    e = ControllerClass(d)

    dt = d.get_dt()

    print('Input dt =', dt)

    leaf_data = Nissan_Leaf()

    leaf = CarClass(leaf_data.data)

    d.set_line(['Time','NEDC','Speed'])

    print(d.get_num_lines(), 'lines in input file')

    counter = 0
    error_cumulative = 0

    while (d.update()):
        leaf.target_speed = d.get_line()[1]/2.23694 # mph to m/s
        leaf.update(dt)

        d.set_line([d.get_line()[0], leaf.target_speed*2.23694, leaf.speed*2.23694, leaf._powertrain_model_array[0]._dv*2.23694, leaf._powertrain_model_array[0]._error])
        #print([d.get_line()[0], leaf.target_speed, leaf.speed])

        for ptr in leaf._powertrain_model_array[0]._motor_array:
            d.set_line([ptr.motor_value])
        for ptr in leaf._powertrain_model_array[0]._wheel_array:
            d.set_line([ptr.brake_value])

        #for ptr in leaf._powertrain_model_array[0]:
        d.set_line([leaf._powertrain_model_array[0]._p])
        d.set_line([leaf._powertrain_model_array[0]._i])
        d.set_line([leaf._powertrain_model_array[0]._d])
        d.set_line([leaf._powertrain_model_array[0]._error])

        error_cumulative += leaf._powertrain_model_array[0]._error
        counter += 1

    print("Average error: ", abs(round(error_cumulative/counter, 5)))

d.__del__()

#while True:
#    pass

data_out = np.genfromtxt(filename+"_out.csv", delimiter=',', skip_header=1, skip_footer=1, names = ['x', 'v_set', 'v_true', 'dv', 'error', 'motor', 'brake0', 'brake1', 'brake2', 'brake3', 'p', 'i', 'd', 'error'])

fig = plt.figure()
ax1 = fig.add_subplot(211)

ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
ax1.plot(data_out['x'], data_out['dv'], label='dv')
ax1.set_ylabel('Speed')
leg1 = ax1.legend(loc='upper right', shadow=True)

ax2 = fig.add_subplot(212)
#ax2.plot(data_out['x'], data_out['p'], label='p')
#ax2.plot(data_out['x'], data_out['i'], label='i')
#ax2.plot(data_out['x'], data_out['d'], label='d')
#ax2.plot(data_out['x'], data_out['error'], label='error')
ax2.plot(data_out['x'], data_out['motor'], label='motor')
ax2.plot(data_out['x'], data_out['brake0'], label='brake0')
ax2.plot(data_out['x'], data_out['brake1'], label='brake1')
ax2.plot(data_out['x'], data_out['brake2'], label='brake2')
ax2.plot(data_out['x'], data_out['brake3'], label='brake3')
ax2.set_ylabel('0-255')
leg2 = ax2.legend(loc='upper right', shadow=True)
ax2.set_xlabel('Time /s')

plt.show()

