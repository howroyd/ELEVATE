import csv

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
        self._time_last = 0.0

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

    def update(self):
        try:
            self._thisline = list(map(float,next(self._tsvin)))
            self.dt = self._thisline[0] - self._time_last
            self._time_last = self._thisline[0]
            if self._lineout:
                self._csvout.writerow(self._lineout)
                self._lineout = []
        except ValueError:
            self.update()
        except StopIteration:
            return 0
        return 1
        
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