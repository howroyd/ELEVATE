class LowPassFilter(object):
    def __init__(self, gain):
        self._k = gain
        self._last = 0.0

    def get(self, new_val):
        self._last = self._last + self._k*(new_val - self._last)
        return self._last
    def reset(self):
        self._last = 0
        return self._last