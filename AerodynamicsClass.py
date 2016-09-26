class AerodynamicsClass(object):
    """description of class"""
    # Instance constructor
    def __init__(self, kwargs):
        self._force_drag_profile = 0.0
        self._force_drag_dynamic = 0.0
        self._area = 0.725 # Nissan Leaf
        self._cd = 0.29 # Nissan Leaf
        return

    def update(self, v):
        self._force_drag_dynamic = 0.5*1.225*v*v*self._area*self._cd
        return

    def get_drag(self):
        return self._force_drag_profile + self._force_drag_dynamic