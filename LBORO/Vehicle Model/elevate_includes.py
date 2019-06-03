#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################

# System level libraries
import telnetlib, time, sys, os, datetime, copy, math

from statistics import mean 

# Matlab libraries
import matlab.engine
import matplotlib
import matplotlib.pyplot as plt

# Python libraries
import numpy as np
import colorama

# User libraries
from CarClass import CarClass
from DataInputClass import DataIoClass, Continuous_dt
from RotatingThingClass import rads_to_rpm


###############################
###    UTILITY FUNCTIONS    ###
###############################

from math import sqrt
def rms(num):
	return sqrt(sum(n*n for n in num)/len(num))

# Convert mph to m/s
def mph_to_ms(mph:'mph') -> 'm/s':
    return mph / 2.23694

# Convert m/s to mph
def ms_to_mph(ms:'m/s') -> 'mph':
    return ms * 2.23694

# Convert kph to m/s
def kph_to_ms(kph:'kph') -> 'm/s':
    return kph / 3.60000

# Convert m/s to kph
def ms_to_kph(ms:'m/s') -> 'kph':
    return ms * 3.60000

# Constrain
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
            print("Hardware Simulation Model Version", version)
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
    ###          COST           ###
    ###############################
    def disp_cost(self, cost):
        print(colorama.Fore.YELLOW, colorama.Style.BRIGHT)
        print(cost)
        print('\n')
        print(colorama.Style.RESET_ALL)

    ###############################
    ###          TIME           ###
    ###############################
    def disp_time(self, _time):
        print(colorama.Fore.RED, colorama.Style.BRIGHT)
        print(_time)
        print('\n')
        print(colorama.Style.RESET_ALL)


###############################
###############################
######       END         ######
###############################
###############################