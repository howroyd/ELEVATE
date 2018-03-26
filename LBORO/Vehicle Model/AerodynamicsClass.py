class AerodynamicsClass(object):
    """description of class"""
    # Instance constructor
    def __init__(self, kwargs, name="aero"):
        self._force_drag_profile = 0.0
        self._force_drag_dynamic = 0.0
        self._area = kwargs['car_area']
        self._cd = kwargs['car_cd']
        self._data = dict()
        self._name = name
        return

    def update(self, v):
        self._force_drag_dynamic = 0.5*1.225*v*v*self._area*self._cd #Total drag
        self._data.update({(self._name+'_dynamic') : self._force_drag_dynamic})
        return

    @property
    def data(self):
        return self._data

    @property 
    def force(self):
        return self._force_drag_profile + self._force_drag_dynamic
