import telnetlib, os, time
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
    def __init__(self, kwargs):
        self._host     = kwargs['host'] if 'host' in kwargs else '127.0.0.1'
        self._port     = kwargs['port'] if 'port' in kwargs else 23
        self._password = kwargs['password'] if 'password' in kwargs else ''

        self._mode = kwargs['mode'] if 'mode' in kwargs else 'CURRENT'
        self._tn   = None

        self._v_set     = kwargs['v']     if 'v'     in kwargs else 10.0
        self._v_set_min = kwargs['v_min'] if 'v_min' in kwargs else 0.0
        self._v_set_max = kwargs['v_max'] if 'v_max' in kwargs else 10.0
        self._i_set_max = kwargs['i_max'] if 'i_max' in kwargs else 10.0
        self._p_set_max = kwargs['p_max'] if 'p_max' in kwargs else 10.0

        self._dt = time.time()

        return super().__init__(kwargs)

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

        # Set safety limits
        self.set_v_min(self._v_set_min)
        self.set_v_max(self._v_set_max)
        self.set_i_max(self._i_set_max)
        self.set_p_max(self._p_set_max)

        # Set mode
        self.set_mode(self._mode)

        # Everything working, return 1
        return 1

    # Method to connect over Telnet
    @classmethod
    def _connect(cls, HOST, PORT, password):
        
        # Initiate connection
        tn = telnetlib.Telnet(HOST, PORT)
        
        # If we have a password...
        if password:
            
            # Wait for the loadbank to ask us for a password
            tn.read_until(b"Password ? ")
            
            # Write the password to the Loadbank
            tn.write(password.encode('ascii') + b"\r\n")
            
        # Clear the buffer
        cls._flush(tn)  # Flush read buffer (needed)
        
        # Return the Telnet handle
        return tn

    # Method to close down the connection
    def shutdown(self):
        time.sleep(0.4)
        self.load = False
        self.zero()
        self._tn.close()
        return 1

    # Method to zero the Loadbank
    def zero(self):
        time.sleep(0.4)
        if "VOLTAGE" in self.mode:
            self.voltage_constant = '0.0'
        elif "CURRENT" in self.mode:
            self.current_constant = '0.0'
        elif "POWER" in self.mode:
            self.power_constant = '0.0'

    # Method to clear the buffer
    @staticmethod
    def _flush(tn):
        tn.read_very_eager()  # Flush read buffer

    def set_v(self, v):
        # Overloaded
        self._set(self._tn, self.CONSTANT_VOLTAGE_COMMAND, v)
        self._v_set = v
    def set_v_min(self, v):
        self._set(self._tn, self.VOLTAGE_MINIMUM_COMMAND, v)
        self._v_set_min = v
    def set_v_max(self, v):
        self._set(self._tn, self.VOLTAGE_LIMIT_COMMAND, v)
        self._v_set_max = v

    def set_i(self, i):
        # Overloaded
        self._set(self._tn, self.CONSTANT_CURRENT_COMMAND, i)
        self._i_set = i
    def set_i_max(self, i):
        self._set(self._tn, self.CURRENT_LIMIT_COMMAND, i)
        self._i_set_max = i

    def set_p(self, p):
        # Overloaded
        self._set(self._tn, self.CONSTANT_POWER_COMMAND, p)
        self._p_set = p
    def set_p_max(self, p):
        self._set(self._tn, self.POWER_LIMIT_COMMAND , p)
        self._p_set_max = p

    def set_mode(self, mode):
        op_mode = op_mode.lower()  # Change any capitals to lower case
        if "vo" in op_mode or "cv" in op_mode:
            self._set(self._tn, self.MODE_COMMAND, self.CONSTANT_VOLTAGE_COMMAND)
            self._mode =  "VOLTAGE"            
        elif "cu" in op_mode or "ci" in op_mode:
            self._set(self._tn, self.MODE_COMMAND, self.CONSTANT_CURRENT_COMMAND)
            self._mode =  "CURRENT"
        elif "po" in op_mode or "cp" in op_mode:
            self._set(self._tn, self.MODE_COMMAND, self.CONSTANT_POWER_COMMAND)
            self._mode =  "POWER"
        return self._mode

    # Update electrical data
    def update(self):
        self._v = self._get_float(self._tn, self.VOLTAGE_COMMAND)
        self._i = self._get_float(self._tn, self.CURRENT_COMMAND)
        self._p = self._get_float(self._tn, self.POWER_COMMAND)

        self._dt = time.time() - self._dt

        self._e_in += self._v * self._i * self._dt
        self._e_total += self._e_in

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

    # Method to get a number **recursive**
    @classmethod
    def _get_float(cls, tn, command):
        
        # Get the raw data string
        data = cls._get(tn, command)
        
        # Look for a valid reply
        try:
            return float(data.split()[0])
            
        # No valid reply so run the method again
        except ValueError:
            return cls._get_float(tn, command) # **recursivity**

    # Method to handle data 2way telnet datastream
    @classmethod
    def _send(cls, tn, inbuf):
        
        # Flush the buffer
        cls._flush(tn)
        
        # Create some memory
        outbuf = ""

        # Send the query or command to the Loadbank
        tn.write(inbuf.encode('ascii'))

        # Was it a query? If so what is the expected reply?
        if '?' in inbuf:
            if 'v' in inbuf:
                expected = b'volts'
            elif 'i' in inbuf:
                expected = b'amps'
            elif 'p' in inbuf:
                expected = b'watts'
            elif 'rng' in inbuf:
                expected = b'AMP'
            else:
                expected = b'\r'

            # Check if the Loadbank acknowledged the query
            while not outbuf or outbuf.isspace():
                
                # Look for the expected reply or timeout
                outbuf = tn.read_until(expected, 0.1)  # Timeout = 0.1sec TODO
                
                # Decode the reply
                outbuf = outbuf.decode('ascii').strip('\r\n')
                
                # If the reply is not what we expected...
                if not outbuf or outbuf.isspace():
                    # Flush the buffer
                    cls._flush(tn)
                    
                    # Send the query again
                    tn.write(inbuf.encode('ascii'))

            # Return the query reply
            return outbuf
            
        # Was a command not a query, no reply expected.
        else:
            return inbuf