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
        self.dt = 0.0

    @staticmethod
    def file_len(fname) -> int:
        with open(fname) as f:
            for i, l in enumerate(f):
                pass
        return i + 1

    def get_dt(self):
        self._file_in.seek(0)
        self.update()
        self.update()
        self.update()
        var1 = self._thisline[0]
        self.update()
        var2 = self._thisline[0]
        self._file_in.seek(0)
        self._dt = var2-var1
        
        return self._dt

    def update(self):
        try:
            self._thisline = list(map(float,next(self._tsvin)))
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