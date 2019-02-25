#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################

# System level libraries
import telnetlib, time, sys, os, datetime, copy

# Matlab libraries
#import matlab.engine
import matplotlib
import matplotlib.pyplot as plt

# Python libraries
import numpy as np
import colorama
import progressbar

# User libraries
from CarClass import CarClass
from DataInputClass import DataIoClass, Continuous_dt, Discrete_dt
from RotatingThingClass import rads_to_rpm


###############################
###    UTILITY FUNCTIONS    ###
###############################

# Convert mph to m/s
def mph_to_ms(mph:'mph') -> 'm/s':
    return mph / 2.23694

# Convert m/s to mph
def ms_to_mph(ms:'m/s') -> 'mph':
    return ms * 2.23694

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
    def disp(self, *my_string:str, end="\n"):
        for x in my_string:
            print(x, end='')
        print(end, end='')

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def disp_testfile(self, filename):
        print("\nTest file", filename)

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