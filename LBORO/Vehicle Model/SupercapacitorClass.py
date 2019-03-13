#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
from ElectricityClass import kwh_to_joules
from ElectricalDeviceClass import ElectricalDeviceClass
from MatlabClass import MatlabClass
import matlab
import os
import colorama
from time import sleep

from mpl_toolkits import mplot3d
#%matplotlib notebook
import numpy as np
import matplotlib.pyplot as plt

class SupercapacitorClass(ElectricalDeviceClass):
    '''Supercapacitor for an electric vehicle'''
    _v_min           = None
    _v_max           = None
    _i_max_charge    = None
    _i_max_discharge = None
    _p_max           = None
    _soc             = 0.0
    _distribution    = np.zeros(5)
    _res             = 0.1
    _pascal_order    = 5
    _num_series_caps = 3

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        self._v_min           = kwargs.get('sc_v_min')
        self._v_max           = kwargs.get('sc_v_max')
        self._farads          = kwargs.get('sc_F')
        self._esr             = kwargs.get('sc_esr')
        self._soc             = kwargs.get('sc_soc') # TODO
        self._eng_obj         = MatlabClass(None)
        self._eng             = self._eng_obj.engine_handle
        #self._i_max_charge    = kwargs.get('i_max_charge')
        #self._i_max_discharge = kwargs.get('i_max_discharge')
        #self._p_max           = kwargs.get('p_max')

        #sc_e_max            = kwh_to_joules(kwargs.get('sc_kwh'))

        #sc_e_min            = 0.0

        #_e_start  = ((sc_e_max - sc_e_min) * kwargs.get('sc_soc') / 100.0) + sc_e_min

        # Matlab
        #res= 0.25 # TODO
        #num_rungs = 15 # TODO


        distribution = np.asarray([ self._v_max ] * self.num_rungs)

        
        distribution = np.dot( distribution, self._soc/100.0 )
        self._distribution = matlab.double(distribution.tolist())
        print('\nInitial supercapacitor distribution:\n', self._distribution, end='\n')
        #dt = 1.0
        #amps_in = 0.0
        #[ v_end, amps_delivered, soc, distribution_out ] = self._eng.sc_model_single_shot(dt, res/dt, amps_in, distribution, nargout=4)
        #my_distribution = np.asarray(distribution_out)

        #dt = 100.0
        #amps_in = 15.0
        #[ v_end, amps_delivered, soc, distribution_out ] = self._eng.sc_model_single_shot(dt, res/dt, amps_in, distribution_out, nargout=4)
        #my_distribution = np.append(my_distribution, distribution_out, axis=0)

        #dt = 10.0
        #amps_in = 0.0
        #[ v_end, amps_delivered, soc, distribution_out ] = self._eng.sc_model_single_shot(dt, res/dt, amps_in, distribution_out, nargout=4)
        #my_distribution = np.append(my_distribution, distribution_out, axis=0)

        #dt = 5.0
        #amps_in = -0.05
        #[ v_end, amps_delivered, soc, distribution_out ] = self._eng.sc_model_single_shot(dt, res/dt, amps_in, distribution_out, nargout=4)
        #my_distribution = np.append(my_distribution, distribution_out, axis=0)

        #dt = 500.0
        #amps_in = 0.0
        #[ v_end, amps_delivered, soc, distribution_out ] = self._eng.sc_model_single_shot(dt, res/dt, amps_in, distribution_out, nargout=4)
        #my_distribution = np.append(my_distribution, distribution_out, axis=0)

        #X = np.arange(num_rungs)
        #Y = np.arange(my_distribution.shape[0])

        #print('x=', X, ' y=', Y)

        #Xv, Yv = np.meshgrid(X, Y)

        #Z = my_distribution

        #X, Y = np.meshgrid(X, Y)

        # summer_r, PiYG, Greens, CMRmap_r, BuGn

        #fig = plt.figure()
        #ax = plt.axes(projection='3d')
        #ax.plot_surface(X, Y, Z, cmap='Greens')
        #ax.view_init(elev=25, azim=-130)
        #ax.set_xlabel('Pascal Rungs of Series Stack')
        #ax.set_ylabel('Time /s')
        #ax.set_zlabel('Voltage /V')

        #plt.show()

        #while True:
        #    pass

        return #super().__init__(dict(e_min=sc_e_min, e_max=sc_e_max, e_start=_e_start))


    ###############################
    ###       DESTRUCTOR        ###
    ###############################
    def __del__(self):
        self._eng.quit() #  Automatically run anyway when python is quit without this

    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, dt):
        self._run_model(dt)
        super().update(dt) # TODO might be a bug here
		
		
    ###############################
    ###      MATLAB MODEL       ###
    ###############################
    def _run_model(self, dt):
        #print('dt=', dt, end='\n')

        print('\nPython out: ', end='')
        print('\nMatLab out: %.2f %.2f %.2f %.2f %.2f', self._distribution[1], self._distribution[2], self._distribution(3), self._distribution(4), self._distribution(5) );

        [ v_end, amps_delivered, soc, distribution_out ] = self._eng.sc_model_single_shot( 
                dt, dt*self._res, self.current, self._distribution, nargout=4 )

        #sleep(1)
        #print(end='\n')
        #print('Distribution_out: ', distribution_out, end='\n')
        self._distribution = distribution_out
        self._soc          = soc
        self.voltage       = float(v_end[0][0])
        self.current       = float(amps_delivered[0][0])

        #print('v_end: ', self.voltage, end='\n')
        #print('soc: ', self.voltage, end='\n')
        #print('current: ', self.current, end='\n')


    ###############################
    ###        GETTERS          ###
    ###############################

    # State of charge
    @property
    def soc(self):
        #return self.energy / self._e_max
        return self._soc

    # Pascal order
    @property
    def pascal_order(self):
        #return self.energy / self._e_max
        return self._pascal_order
		
    # Distribution
    @property
    def distribution(self):
        return np.asarray(self._distribution)

    # Total number of rungs
    @property
    def num_rungs(self):
        return self._pascal_order * self._num_series_caps
		
    # Minimum voltage limit
    @property
    def v_min(self):
        return self._v_min

    # Maximum voltage limit
    @property
    def v_max(self):
        return self._v_max

    # Maximum current limit
    @property
    def i_max(self):
        return self._i_max

    # Maximum power limit
    @property
    def p_max(self):
        return self._p_max

    # Battery data
    @property
    def sc_data(self):
        #_sc_data = { 'soc' : self.soc, 'total_energy_in' : self._e_in, 'total_energy_out' : self._e_out,
        #                    'energy' : self._e_total, 'energy_to_empty' : self.e_to_empty, 'energy_to_full' : self.e_to_full }
        _sc_data = { 'soc' : self.soc, 'total_energy_in' : self._e_in, 'total_energy_out' : self._e_out,
					'energy' : self._e_total}
        _sc_data.update(self.electricity_data)
        return _sc_data


###############################
###############################
######       END         ######
###############################
###############################