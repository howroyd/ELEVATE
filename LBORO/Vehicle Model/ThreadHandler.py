import threading
import random

class MyThread(threading.Thread):
    '''DESCRIPTION'''

    _instance_counter = 0

    # Instance constructor
    def __init__(self, name):
        threading.Thread.__init__(self)
        self._threadID = self._get_new_instance_id()
        self.name = name
        return

    @classmethod
    def _get_new_instance_id(cls):
        Midend._instance_counter += 1
        return Midend._instance_counter

    def get_threadID(self):
        return self._threadID




class ThreadHandler(object):
    '''DESCRIPTION'''

    _car_list

    # Instance constructor
    def __init__(self, kwargs):
        

    

    

