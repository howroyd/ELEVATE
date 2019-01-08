#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
from ElectricityClass import kwh_to_joules
from ElectricalDeviceClass import ElectricalDeviceClass
import matlab.engine
import os
import colorama



class SupercapacitorClass(ElectricalDeviceClass):
    '''Supercapacitor for an electric vehicle'''
    _v_min           = None
    _v_max           = None
    _i_max_charge    = None
    _i_max_discharge = None
    _p_max           = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        #self._v_min           = kwargs.get('v_min')
        #self._v_max           = kwargs.get('v_max')
        #self._i_max_charge    = kwargs.get('i_max_charge')
        #self._i_max_discharge = kwargs.get('i_max_discharge')
        #self._p_max           = kwargs.get('p_max')

        #sc_e_max            = kwh_to_joules(kwargs.get('sc_kwh'))

        #sc_e_min            = 0.0

        #_e_start  = ((sc_e_max - sc_e_min) * kwargs.get('sc_soc') / 100.0) + sc_e_min

        # Matlab
        print('Starting MATLAB engine...')
        print(colorama.Fore.RED, '\tAlt+F4 to save your sanity while you still can!!!')
        print(colorama.Style.RESET_ALL, end='')
        self._eng = matlab.engine.connect_matlab()
        print('\t...MATLAB engine started, impending doom')

        self._path = os.path.dirname(os.path.abspath(__file__))
        print('\t...changing MATLAB path to ', self._path)
        self._eng.cd(self._path)

        mynum = 11

        if self._eng.isprime(mynum):
            print('\t', "MATLAB says ", mynum, "is PRIME")
        else:
            print('\t', "MATLAB says ", mynum, "is NOT PRIME")

        print(self._eng.sc_model_single_shot(5.0, 1.5, 1.0, nargout=3))

        while True:
            pass

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
        super().update(dt)
        self._v = self.calculate_v()
        

    ###############################
    ###      VOLTAGE MODEL      ###
    ###############################
    def calculate_v(self):
        return self._e_total * ((self._v_max - self._v_min) / self._e_max) + self._v_min


    ###############################
    ###        GETTERS          ###
    ###############################

    # State of charge
    @property
    def soc(self):
        return self.energy / self._e_max

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
        _sc_data = { 'soc' : self.soc, 'total_energy_in' : self._e_in, 'total_energy_out' : self._e_out,
                            'energy' : self._e_total, 'energy_to_empty' : self.e_to_empty, 'energy_to_full' : self.e_to_full }
        _sc_data.update(self.electricity_data)
        return _sc_data


###############################
###############################
######       END         ######
###############################
###############################