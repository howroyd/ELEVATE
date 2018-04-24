#!/usr/bin/python3

###############################
###    UTILITY FUNCTIONS    ###
###############################

# Convert kWh to Joules
def kwh_to_joules(kwh:'kilowatt hours') -> 'joules':
    return kwh * 3.6e+6
    
# Convert Joules to kWh
def joules_to_kwh(joules:'joules') -> 'kilowatt hours':
    return joules / 3.6e+6


class ElectricityClass(object):
    '''Base class defining electrical fundamentals'''
    _key_voltage = 'voltage'
    _key_current = 'current'
    _key_power   = 'power'
    _v = 0.0
    _i = 0.0
    
    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self):
        return 


    ###############################
    ###        GETTERS          ###
    ###############################

    # Data strcture of important data
    @property
    def electricity_data(self):
        return {self._key_voltage : self._v, self._key_current : self._i, self._key_power : self.power}

    # Voltage
    @property
    def voltage(self):
        return self._v

    # Current
    @property
    def current(self):
        return self._i

    # Power
    @property
    def power(self):
        return self._v * self._i


    ###############################
    ###        SETTERS          ###
    ###############################

    # Data strcture of important data
    @electricity_data.setter
    def electricity_data(self, data_dict):
        self.voltage = data_dict.get(self._key_voltage)
        self.current = data_dict.get(self._key_current)

    # Voltage
    @voltage.setter
    def voltage(self, v):
        self._v = v

    # Current
    @current.setter
    def current(self, i):
        self._i = i


###############################
###############################
######       END         ######
###############################
###############################
