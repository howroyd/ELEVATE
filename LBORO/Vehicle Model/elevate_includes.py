#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################

# System level libraries
import telnetlib, time, sys, os, datetime, copy

# Matlab libraries
import matlab.engine
import matplotlib
import matplotlib.pyplot as plt

# Python libraries
import numpy as np
import colorama

# User libraries
from AerodynamicsClass import AerodynamicsClass
from BatteryManagementClass import BatteryManagementClass
from CarClass import CarClass
import Cars
from DataInputClass import DataIoClass, Continuous_dt


###############################
###    UTILITY FUNCTIONS    ###
###############################

# Convert mph to m/s
@staticmethod
def mph_to_ms(mph:'mph') -> 'm/s':
    return mph / 2.23694

# Constrain
@staticmethod
def constrain(val, _min, _max):
    return min(_max, max(_min, val))


class Display(object):
    '''Print to screen wrapper'''

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, version=None):
        colorama.init()
        self.ver = version
        print(colorama.Fore.GREEN, colorama.Style.BRIGHT)
        print("\nELEVATE (ELEctrochemical Vehicle Advanced TEchnology)")

        if version is not None:
            print("Hardware Simulation Model Version", VERSION)
        else:
            print("Hardware Simulation Model")

        print("Simon Howroyd", datetime.date.today().year)
        print("Loughborough University")
        print(colorama.Style.RESET_ALL)
        print(sys.version, '\n')

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def disp(self, my_string, end='\n'):
        print(my_string, end=end)

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def disp_testfile(self, filename):
        print("\nTest file", filename)
        print('\n')

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def disp_feed_forward(self, bin_val):
        if bin_val:
            print("\nFeed forward control enabled\n")


###############################
###############################
######       END         ######
###############################
###############################