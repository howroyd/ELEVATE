import ElectricalDeviceClass

class ElectricalManagementClass(ElectricalDeviceClass.ElectricalDevice):
    """Connects battery, ESC and motors together correctly and passes the electricity between them"""
    def __init__(self, battery_array, esc, motor_array):
        self._battery_array = battery_array    
        self._esc           = esc    
        self._motor_array   = motor_array
        self._error         = False

    def set_motor(self, ctrl_sig):
        pass

    def update(self, dt):
        demand = list()

        # get elec demand from motor
        for ptr in self._motor_array:
            demand.append(ptr.electricity)

        # pass elec demand from motor to esc
        self._esc.electricity_array = demand

        # get elec demand from esc
        demand = self._esc.electricity

        # pass elec demand from esc to battery
        if (length(self._battery_array) > 1): demand.i /= length(self._battery_array)

        pgood = True
        for ptr in self._battery_array:
            ptr.electricity = demand
            pgood &= ptr.power_good
        
        while not pgood:
            num_batts_not_max = 0
            for ptr in self._battery_array:
                # Count number of batteries not maxed out
                if not ptr.power_good:
                    num_batts_not_max += 1
                    ptr.max_power() 

            if (num_batts_not_max < 1):
                print("Can't supply enough battery power!")
                self._error = True
                break
            else:
                self._error = False
                # One of the batteries can't supply enough current
                deficit = demand.i - sum(ptr.i for ptr in self._battery_array)

                for ptr in self._battery_array:
                    # Add deficit to non-maxed batteries
                    if ptr.power_good: ptr.i += deficit/num_batts_not_max
                    else: ptr.set_max_power() # Set max power for over demanded batteries (should reset pgood)

        # get elec provided from battery
        i = sum(ptr.i for ptr in self._battery_array)

        # pass battery elec from battery to esc
        self._esc.set_i = i

        # get elec provided from esc
        elec = self._esc.electricity_array

        # pass elec from esc to motor
        if (self._error):
            # Batteries can't supply the current required, so reduce what the motors asked for
            for ptr in self._motor_array:
                temp = ptr.electricity
                temp.i = min(temp.i, elec.i/length(self._motor_array))
                ptr.electricity = temp
            
        # if regen braking, the negative electricity may be below the demand!!!!!

    @staticmethod
    def _load_share(battery_array, elec):
        counter = 0
        even_share = [elec.i / length(battery_array)] * length(battery_array)

        # while (counter < 5):
            
        
