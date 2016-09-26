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

    @staticmethod
    def file_len(fname) -> int:
        with open(fname) as f:
            for i, l in enumerate(f):
                pass
        return i + 1

    def update(self):
        try:
            self._thisline = list(map(int,next(self._tsvin)))
            if self._lineout:
                print(self._lineout[:4])
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