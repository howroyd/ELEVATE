import telnetlib, os
import ElectricalDeviceClass

class TdiLoadbank(ElectricalDeviceClass.ElectricalDevice):
    '''DESCRIPTION'''
    # Define Loadbank commands
    LOAD_COMMAND = "load"
    RANGE_COMMAND = "rng"
    MODE_COMMAND = "mode"
    VOLTAGE_COMMAND = "v"
    CURRENT_COMMAND = "i"
    POWER_COMMAND = "p"
    VOLTAGE_LIMIT_COMMAND = "vl"
    CURRENT_LIMIT_COMMAND = "il"
    POWER_LIMIT_COMMAND = "pl"
    VOLTAGE_MINIMUM_COMMAND = "uv"
    CONSTANT_VOLTAGE_COMMAND = "cv"
    CONSTANT_CURRENT_COMMAND = "ci"
    CONSTANT_POWER_COMMAND = "cp"

    # Instance constructor
    def __init__(self, **kwargs):
        self._host     = kwargs['host'] if 'host' in kwargs else '127.0.0.1'
        self._port     = kwargs['port'] if 'port' in kwargs else 23
        self._password = kwargs['password'] if 'password' in kwargs else ''

        self._mode = TdiLoadbank.CONSTANT_CURRENT_COMMAND

        self._tn   = None
        return super().__init__(**kwargs)

    # Method to connect over the network
    def connect(self):
        
        # Ping the loadbank first to see if it is there
        if os.system("ping -c 1 -w 2 " + self.__HOST + " > /dev/null 2>&1"): # TODO: for Windows
            print("Failed to detect a loadbank on network")
            return 0
        print("Loadbank found! Connecting...", end="")

        # Connect using telnet
        self._tn = self._connect(self._host, self._port, self._password)

        if self._tn:
            print("connected!\n")
        else:
            print("Failed, check password?\n")
            return 0

        # Get safety limits
        self.set_v(0.0) # TODO
        self.set_i(0.0)
        self.set_p(0.0)

        # Get current mode
        self.mode = self._get(self._tn, self.__MODE_COMMAND)

        # Everything working, return 1
        return 1

    def set_v(self, v):
        # Overloaded
        pass

    def set_p(self, i):
        # Overloaded
        pass

    def set_p(self, p):
        # Overloaded
        pass

    def set_mode(self, mode):
        
        pass

    @classmethod
    def _set(cls, tn, command, value):
        # Build the command in the correct format
        buf = (command + ' ' + value + '\r')
        
        # Send the command over the network
        cls._send(tn, buf)

    # Method to clear the buffer
    @staticmethod
    def _flush(tn):
        tn.read_very_eager()  # Flush read buffer

    # Method to get a string of text
    @classmethod
    def _get(cls, tn, command):
        
        # Queries end with a '?', append if necessary
        if not command.endswith('?'):
            command += '?'
            
        # Build the query in the correct format
        buf = (command + '\r')
        
        # Send the query over the network
        return str(cls._send(tn, buf))