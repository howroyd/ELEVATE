# elevate_includes

import telnetlib, time, sys, os, datetime, copy
import matlab.engine
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
#from TdiLoadbankClass import TdiLoadbank
from battery_sw import Battery_Model
from CarClass import CarClass
from DataInputClass import DataInputClass, DataOutputClass
from DataInputClass import Continuous_dt
from ControllerClass import ControllerClass
from Cars import Nissan_Leaf
import threading
import colorama
from colorama import Fore, Back, Style
import random
from Filters import LowPassFilter

def mph_to_ms(mph):
    return mph / 2.23694

class Display(object):
    def __init__(self, version=None):
        colorama.init()
        self.ver = version
        print(Fore.GREEN, Style.BRIGHT)
        print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")

        if version is not None:
            print("Hardware Simulation Model Version", VERSION)
        else:
            print("Hardware Simulation Model")

        print("Simon Howroyd", datetime.date.today().year)
        print("Loughborough University")
        print(Style.RESET_ALL)
        print(sys.version, '\n')

    def disp(self, my_string, end='\n'):
        print(my_string, end=end)

    def disp_testfile(self, filename):
        print("\nTest file", filename)
        print('\n')

    def disp_feed_forward(self, bin_val):
        if bin_val:
            print("\nFeed forward control enabled\n")
