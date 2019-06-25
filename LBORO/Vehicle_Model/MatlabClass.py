#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import matlab.engine
import os
import colorama


class MatlabClass(object):
    '''Supercapacitor for an electric vehicle'''
    engine_handle    = None

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, kwargs):

        # Matlab
        print('Starting MATLAB engine...')
        print(colorama.Fore.RED, '\tAlt+F4 to save your sanity while you still can!!!')
        print(colorama.Style.RESET_ALL, end='')

        while True: # TODO this is dirty
            try:
                MatlabClass.engine_handle = matlab.engine.connect_matlab()
                break
            except:# EngineError:
                print('Failed, trying again...')
                pass

        print('\t...MATLAB engine started, impending doom')

        self._path = os.path.dirname(os.path.abspath(__file__))

        print('\t...changing MATLAB path to ', self._path)

        MatlabClass.engine_handle.cd(self._path)

        mynum = 11

        if MatlabClass.engine_handle.isprime(mynum):
            print('\t', "MATLAB says ", mynum, "is PRIME")
        else:
            print('\t', "MATLAB says ", mynum, "is NOT PRIME")

        return #super().__init__(dict(e_min=sc_e_min, e_max=sc_e_max, e_start=_e_start))


    ###############################
    ###       DESTRUCTOR        ###
    ###############################
    def __del__(self):
        MatlabClass.engine_handle.quit() #  Automatically run anyway when python is quit without this


    ###############################
    ###        GETTERS          ###
    ###############################

    # Maximum power limit
    @property
    def engine_handle(self):
        return MatlabClass.engine_handle


###############################
###############################
######       END         ######
###############################
###############################