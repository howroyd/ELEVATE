#!/usr/bin/python3

class AerodynamicsClass(object):
<<<<<<< HEAD
    """description of class"""
    # Instance constructor
    def __init__(self, kwargs, name="aero"):
        self._force_drag_profile = 0.0
        self._force_drag_dynamic = 0.0
=======
    '''Calculate aerodynamic drag for a vehicle'''
    _force_drag_profile = 0.0
    _force_drag_dynamic = 0.0
    _area = None
    _cd   = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
>>>>>>> linking_overhaul
        self._area = kwargs['car_area']
        self._cd = kwargs['car_cd']
        self._data = dict()
        self._name = name
        return

    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, v):
        self._force_drag_dynamic = 0.5*1.225*v*v*self._area*self._cd #Total drag
        self._data.update({(self._name+'_dynamic') : self._force_drag_dynamic})
        return

<<<<<<< HEAD
    @property
    def data(self):
        return self._data

=======
    ###############################
    ###        GETTERS          ###
    ###############################
>>>>>>> linking_overhaul
    @property 
    def force(self):
        return self._force_drag_profile + self._force_drag_dynamic


###############################
###############################
######       END         ######
###############################
###############################