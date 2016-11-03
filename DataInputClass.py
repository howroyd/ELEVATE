import csv
import time

class Continuous_dt(object):
    def __init__(self, dt=None, scaler=10):
        self._dt_set = dt
        self._dt_scaler = scaler
        self._time_last = time.time()
        self._flag = False
        self._dt = None
        self._sim_time = 0
    
    def update(self):
        now = time.time()
        self._dt = (now - self._time_last)
        self._sim_time += self._dt * self._dt_scaler
        if (self._dt >= self._dt_set):
            self._flag = True
            self._time_last = now
    @property
    def sim_time(self):
        return self._sim_time

    @property
    def dt(self):
        return self._dt

    @property
    def flag(self):
        if self._flag:
            self._flag = False
            return True
        else: return False



class DataInputClass(object):
    """description of class"""
    def __init__(self, filename):

        self._file_in = open(filename,'rt')
        self._file_out = open(filename.rsplit('.')[0]+"_out"+".csv",'w', newline="\n", encoding="utf-8")

        self._tsvin = csv.reader(self._file_in, delimiter='\t')
        self._csvout = csv.writer(self._file_out,quoting=csv.QUOTE_NONNUMERIC)

        self._num_lines = self.file_len(filename)

        self._lineout = []
        self._dt = 0.0
        self._finished = False

        self._nextline = None
        self._previousline = None
        self._thisline = None

        self.update()

    @staticmethod
    def file_len(fname) -> int:
        with open(fname) as f:
            for i, l in enumerate(f):
                pass
        return i + 1

    @property
    def dt(self):
        return self._dt
    @dt.setter
    def dt(self, val):
        self._dt = val

    @property
    def finished(self):
        return self._finished

    def update(self, sim_time=None):
        # Update output file
        if self._lineout:
                self._csvout.writerow(self._lineout)
                self._lineout = []

        # Update the input
        if (not sim_time or not self._nextline or not self._thisline or (sim_time >= self._nextline[0])):
            # Simtime is ahead of our next line so get a new line update
            try:
                self._previousline = self._thisline
                self._thisline = self._nextline
                self._nextline = list(map(float,next(self._tsvin)))
            except ValueError:
                # Re-run if value error
                self.update()
            except StopIteration:
                # Set flag if end of file
                self._finished = True

        # If we get here we know that nextline is ahead of simtime
        self._dt = self._thisline[0] - self._previousline[0] if self._previousline else 0.0

        return self.finished
        

    def get_line(self):
        return self._thisline

    def get_num_lines(self):
        return self._num_lines

    def set_line(self, data):
        for i in data:
            self._lineout.append(i)

    def __del__(self):
        self._file_in.close()
        self._file_out.close()