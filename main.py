import telnetlib, time, sys, os
import matlab.engine
from TdiLoadbankClass import TdiLoadbank

# Main run function
if __name__ == "__main__":
    print("Hello world!")

    #eng = matlab.engine.start_matlab('-nojvm')

    #print(eng.sqrt(4.0))

    print(time.time())
    print(sys.version)

    #eng.quit()

    a = TdiLoadbank(v=15)

    print(a._v)