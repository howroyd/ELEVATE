class CarData(object):
    _data=dict()

    @property
    def data(self):
        return self._data
    @data.setter
    def data(self, val):
        raise Exception("Cannot change default values!")

class Nissan_Leaf(CarData):
    def __init__(self):
        self._data = dict(batt_soc=62.7161,
                    batt_v_min=300.0,
                    batt_v_max=400.0,
                    batt_i_max=266.0,
                    batt_p_max=90000.0,
                    batt_kwh_max=30.0,
                    car_cd=0.28,
                    car_cda=0.768,
                    car_area=2.744,
                    car_mass=1521.0,
                    wheel_diameter=0.2159*2,
                    wheel_mass=9.0, # Rough google search
                    wheel_width=0.3, # APPROX
                    #brake_diameter=[0.1]*4, # assumed
                    brake_diameter=0.1, # assumed
                    #brake_max_torque=[500.0]*4,
                    brake_max_torque=500.0,
                    motor_rotor_mass=13.6,
                    motor_rotor_diameter=0.130,
                    motor_max_torque=280,#280.0,
                    motor_max_rpm=10390,
                    motor_reduction_ratio=7.9377,
                    motor_v_max = 400.0, # assumed
                    motor_v_min=300.0, # assumed
                    motor_i_max=266.0, # assumed
                    motor_p_max=80000.0, # assumed
                    motor_p_min=-20000.0 # assumed
                    )

        super().__init__()
