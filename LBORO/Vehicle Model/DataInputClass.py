#!/usr/bin/python3

###############################
###    IMPORT LIBRARIES     ###
###############################
import csv
import time

class Continuous_dt(object):
    ''' Class to synchronise simulation time with data timestamps'''
    dt_set     = None
    dt_scalar  = None
    _time_last = time.time()
    _flag      = False
    _dt        = None
    _sim_time  = 0

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, dt=None, scaler=10):
        self._dt_set = dt
        self._dt_scaler = scaler
        self._time_last = time.time()


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self):
        now = time.time()
        self._dt = (now - self._time_last) * self._dt_scaler
        self._sim_time += self._dt
        if (self._dt >= self._dt_set):
            self._flag = True
            self._time_last = now


    ###############################
    ###        GETTERS          ###
    ###############################

    # Simulation time
    @property
    def sim_time(self):
        return self._sim_time

    # Last time step delta
    @property
    def dt(self):
        return self._dt

    # New time available
    @property
    def flag(self):
        if self._flag:
            self._flag = False
            return True
        else: return False


###############################
###############################
######       END         ######
###############################
###############################



class DataIoClass(object):
    '''Class to fetch timestamped data from file and save data to another file'''
    _file_in       = None
    _file_out      = None
    _tsv_in        = None
    _csv_out       = None
    _num_lines     = None
    _num_this_line = -1
    _lineout       = []
    _dt            = 0.0
    _finished      = False
    _nextline      = None
    _previousline  = None
    _thisline      = None
    _new_data      = False

    ###############################
    ###     INITIALISATION      ###
    ###############################
    def __init__(self, filename):

        self._file_in = open(filename,'rt')
        self._file_out = open(filename.rsplit('.')[0]+"_out"+".csv",'w', newline="\n", encoding="utf-8")

        self._tsvin = csv.reader(self._file_in, delimiter='\t')
        self._csvout = csv.writer(self._file_out,quoting=csv.QUOTE_NONNUMERIC)

        self._num_lines = self.file_len(filename)

        self.update()


    ###############################
    ###      UPDATE LOOP        ###
    ###############################
    def update(self, sim_time=None):
        # Update output file
        if self._lineout:
                self._csvout.writerow(self._lineout)
                self._lineout = []

        # Update the input
        if (not sim_time or not self._nextline or not self._thisline or (sim_time >= self._nextline[0])):
            # Simtime is ahead of our next line so get a new line update
            try:
                self._previousline   = self._thisline
                self._thisline       = self._nextline
                self._nextline       = list(map(float,next(self._tsvin)))
                self._num_this_line += 1
                self._new_data       = True
            except ValueError:
                # Re-run if value error
                self.update(sim_time)
            except StopIteration:
                # Set flag if end of file
                self._finished = True

        else: self._new_data = False

        if self._thisline is None: self._new_data = False

        # If we get here we know that nextline is ahead of simtime
        self._dt = self._thisline[0] - self._previousline[0] if self._previousline else 0.0

        return self.finished
        

    ###############################
    ###      FILE NUM LINES     ###
    ###############################
    @staticmethod
    def file_len(fname) -> int:
        with open(fname) as f:
            for i, l in enumerate(f):
                pass
        return i + 1


    ###############################
    ###     CLASS DESTRUCTOR    ###
    ###############################
    def __del__(self):
        self._file_in.close()
        self._file_out.close()


    ###############################
    ###        GETTERS          ###
    ###############################

    # Last timestep delta
    @property
    def dt(self):
        return self._dt

    # EOF
    @property
    def finished(self):
        return self._finished

    # String of this timesteps line data
    @property
    def line(self):
        return self._thisline

    # String of the next lines data (for feed forward)
    @property
    def nextline(self):
        return self._nextline

    # Line number
    @property
    def line_number(self):
        return self._num_this_line

    # Total number of lines in file
    @property
    def num_lines(self):
        return self._num_lines

    # Boolean logic true if there is unread data for this timestep
    @property
    def new_data(self):
        return self._new_data

    # Percentage of file completed
    @property
    def percent_complete(self):
        return self._num_this_line / self._num_lines * 100.0


    ###############################
    ###        SETTERS          ###
    ###############################

    # Last timestep delta
    @dt.setter
    def dt(self, val):
        self._dt = val

    # String of this timesteps line data (output)
    @line.setter
    def line(self, data):
        for i in data:
            self._lineout.append(i)


###############################
###############################
######       END         ######
###############################
###############################