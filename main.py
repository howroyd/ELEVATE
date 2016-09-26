import telnetlib, time, sys, os
import matlab.engine
import matplotlib.pyplot as plt
import numpy as np
from TdiLoadbankClass import TdiLoadbank
from battery_sw import Battery_Model
from CarClass import CarClass
from DataInputClass import DataInputClass
from ControllerClass import ControllerClass

# Main run function
if __name__ == "__main__":
    print("Hello world!")

    eng = matlab.engine.start_matlab('-nojvm')

    print(eng.sqrt(4.0))

    print(time.time())
    print(sys.version)

    eng.quit()

    data = dict(v=15, kWh=2.2)

    a = TdiLoadbank(data)
    b = Battery_Model(data)
    c = CarClass(data)

    d = DataInputClass("nedc.tsv")
    e = ControllerClass(d)


    print(a._v)
    print(b.update())

    print(data['wheel_front_right']._brake._temperature)
    print(data['wheel_front_left']._brake._temperature)

    print(b.kwh_to_joules(10.0))

    d.set_line(['Time','NEDC','Speed'])

    print(d.get_num_lines())

    while (d.update()):
        
        c.update()

        c.set_speed(d.get_line()[1])
        
        d.set_line([d.get_line()[0], d.get_line()[1], c.get_speed(), c._powertrain._dv, c._powertrain._motor.get_torque(), c._powertrain._wheel_front_left._brake._current_torque])

d.__del__()

data_out = np.genfromtxt("nedc_out.csv", delimiter=',', skip_header=1, skip_footer=1, names = ['x', 'v_set', 'v_true', 'dv', 'tq_motor', 'tq_brake'])

fig = plt.figure()
ax1 = fig.add_subplot(211)

ax1.plot(data_out['x'], data_out['v_set'], label='v_set')
ax1.plot(data_out['x'], data_out['v_true'], label='v_true')
ax1.set_ylabel('Speed')
leg1 = ax1.legend(loc='upper right', shadow=True)

ax2 = fig.add_subplot(212)
ax2.plot(data_out['x'], data_out['dv'], label='dv')
ax2.plot(data_out['x'], data_out['tq_motor'], label='tq_motor')
ax2.plot(data_out['x'], data_out['tq_brake'], label='tq_brake')
ax2.set_xlabel('Time /s')
ax2.set_ylabel('dV & Torque')
leg2 = ax2.legend(loc='upper right', shadow=True)

plt.show()

