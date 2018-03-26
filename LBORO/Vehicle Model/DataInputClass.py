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
        self._dt = (now - self._time_last) * self._dt_scaler
        self._sim_time += self._dt
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

class DataOutputClass(object):
    def __init__(self, filename):
        self._file_out = open(filename+"_out"+".csv",'w', newline="\n", encoding="utf-8")
        self._csvout = csv.writer(self._file_out,quoting=csv.QUOTE_NONNUMERIC)
        self._lineout = []
        self.update()

    def __del__(self):
        self._file_out.close()

    def update(self, sim_time=None):
        # Update output file
        if self._lineout:
                self._csvout.writerow(self._lineout)
                self._lineout = []
        return

    @property
    def line(self):
        return self._thisline
    @line.setter
    def line(self, data):
        for i in data:
            self._lineout.append(i)

class DataInputClass(object):
    """description of class"""
    def __init__(self, filename, filenameout=None):

        self._data = list()

        num_lines_in_file = self.file_len(filename)-1

        with open(filename,'rt') as f:
            reader = csv.reader(f, delimiter='\t')
            
            for row in reader:
                try:
                    self._data.append(list(map(float, row)))
                except:
                    pass

        self._num_lines = len(self._data)

        if round(num_lines_in_file) is not round(self._num_lines): print("Warning: Difference between input file length and parsed data length;", num_lines_in_file, "vs", self._num_lines, '\n')

        if filenameout is None:
            self._file_out = open(filename.rsplit('.')[0]+"_out"+".csv",'w', newline="\n", encoding="utf-8")
        else:
            self._file_out = open(filenameout,'w', newline="\n", encoding="utf-8")
        
        self._csvout = csv.writer(self._file_out,quoting=csv.QUOTE_NONNUMERIC)

        self._num_this_line = -1
        self._new_data = False
        self._lineout = []
        self._dt = 0.0
        self._finished = False

        return




        # Old code

        self._file_in = open(filename,'rt')
        if filenameout is None:
            self._file_out = open(filename.rsplit('.')[0]+"_out"+".csv",'w', newline="\n", encoding="utf-8")
        else:
            self._file_out = open(filenameout,'w', newline="\n", encoding="utf-8")

        self._tsvin = csv.reader(self._file_in, delimiter='\t')
        self._csvout = csv.writer(self._file_out,quoting=csv.QUOTE_NONNUMERIC)

        self._num_lines = self.file_len(filename)
        self._num_this_line = -1

        self._lineout = []
        self._dt = 0.0
        self._finished = False

        self._nextline = None
        self._previousline = None
        self._thisline = None

        self._new_data = False

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

        try:
            if (not sim_time or not self._data[self._num_this_line]) or (sim_time >= self._data[self._num_this_line+1][0]):
                # Simtime is ahead of our next line so get a new line update
                self._num_this_line += 1
                if self._num_this_line >= self._num_lines-1:
                    self._num_this_line = self._num_lines-1
                    self._finished = True
                    self._file_out.flush()
                    self._file_out.close()
                else:
                    self._new_data = True
            else:
                self._new_data = False

            if self._data[self._num_this_line] is None:
                self._new_data = False

            # If we get here we know that nextline is ahead of simtime
            self._dt = self._data[self._num_this_line][0] - self._data[self._num_this_line-1][0] if self._data[self._num_this_line-1][0] else 0.0

        except IndexError:
            self._num_this_line = self._num_lines-1
            print("End of file;", self._num_this_line+1, "of", self._num_lines)
            self._finished = True
            self._file_out.flush()
            self._file_out.close()

        return self.new_data


        # Old code

        # Update the input
        if (not sim_time or not self._nextline or not self._thisline) or (sim_time >= self._nextline[0]):
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
                self._file_out.flush() # TODO might not be necessary

        else: self._new_data = False

        if self._thisline is None: self._new_data = False

        # If we get here we know that nextline is ahead of simtime
        self._dt = self._thisline[0] - self._previousline[0] if self._previousline else 0.0

        return self.new_data
        
    @property
    def line(self):
        return self._data[min(self._num_this_line, self._num_lines-1)]
    @line.setter
    def line(self, data):
        for i in data:
            self._lineout.append(i)

    @property
    def nextline(self):
        return self._data[self._num_this_line+1]

    def read_ahead(self, vision=1):
        _vision = vision + self._num_this_line
        return self._data[min(max(0, _vision), self._num_lines-1)]

    @property
    def line_number(self):
        return self._num_this_line

    @property
    def num_lines(self):
        return self._num_lines

    @property
    def new_data(self):
        return self._new_data

    @property
    def percent_complete(self):
        return self._num_this_line / self._num_lines * 100.0

    def __del__(self):
        self._file_in.close()
        self._file_out.close()