<<<<<<< HEAD
import battery_sw
import PowertrainClass
import AerodynamicsClass
import WheelClass
import MotorClass
import BrakesClass
import EscClass

=======
>>>>>>> linking_overhaul
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
<<<<<<< HEAD
        self._data = dict(batt_soc=100.0,
                    batt_v_min=240.0,
                    batt_v_max=398.4,
                    batt_v_nom=360.0,
=======
        self._data = dict(batt_soc=62.7161,
                    batt_v_min=300.0,
                    batt_v_max=400.0,
>>>>>>> linking_overhaul
                    batt_i_max=266.0,
                    batt_p_max=90000.0,
                    batt_kwh_max=30.0,
                    car_cd=0.28,
                    car_cda=0.768,
                    car_area=2.744,
                    car_mass=1521.0,
<<<<<<< HEAD
                    wheel_diameter=0.432,
                    brake_diameter=[0.1]*4, # assumed
                    brake_max_torque=[373.0]*4,
                    motor_max_torque=280,
                    motor_v_min = 400.0, # assumed
                    motor_v_nom = 345.0,
                    motor_v_max=300.0, # assumed
=======
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
>>>>>>> linking_overhaul
                    motor_i_max=266.0, # assumed
                    motor_p_max=80000.0, # assumed
                    motor_p_min=-20000.0, # assumed
                    motor_reduction_ratio=7.9377,
                    motor_max_rpm=10390
                    )
<<<<<<< HEAD
        self._data.update(batt_model_array=[battery_sw.Battery_Model(self._data)])
        self._data.update(aero_model=AerodynamicsClass.AerodynamicsClass(self._data))
        self._data.update(brake_model_array=[BrakesClass.BrakesClass(self._data['brake_diameter'][0],self._data['brake_max_torque'][0],self._data)]*4)
        self._data.update(wheel_model_array=[WheelClass.WheelClass(self._data['brake_model_array'][0],self._data,name='front_left'), # Front left
                                            WheelClass.WheelClass(self._data['brake_model_array'][1],self._data,name='front_right'),  # Front right
                                            WheelClass.WheelClass(self._data['brake_model_array'][2],self._data,name='rear_left'),  # Rear left
                                            WheelClass.WheelClass(self._data['brake_model_array'][3],self._data,name='rear_right')]  # Rear right
                                            )
        self._data.update(motor_model_array=[MotorClass.MotorClass([self._data['wheel_model_array'][0],self._data['wheel_model_array'][1]],self._data)])
        self._data.update(esc=EscClass.ESC(self._data))
        self._data.update(powertrain_model_array=[PowertrainClass.PowertrainClass([self._data['batt_model_array'][0]],[self._data['motor_model_array'][0]],self._data['wheel_model_array'],self._data)])
        for ptr in self._data['wheel_model_array']: # Dodgy cyclic link
            ptr.powertrain_model_reference = self._data['powertrain_model_array'][0]

=======
>>>>>>> linking_overhaul
        super().__init__()
