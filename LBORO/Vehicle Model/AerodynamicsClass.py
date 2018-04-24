#!/usr/bin/python3

class AerodynamicsClass(object):
    '''Calculate aerodynamic drag for a vehicle'''
    _force_drag_profile = 0.0
    _force_drag_dynamic = 0.0
    _area = None
    _cd   = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):
        self._area = kwargs['car_area']
        self._cd = kwargs['car_cd']
        return

    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, v):
        self._force_drag_dynamic = 0.5*1.225*v*v*self._area*self._cd
        return

    ###############################
    ###        GETTERS          ###
    ###############################
    @property 
    def force(self):
        return self._force_drag_profile + self._force_drag_dynamic


###############################
###############################
######       END         ######
###############################
###############################