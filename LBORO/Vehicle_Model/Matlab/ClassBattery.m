classdef ClassBattery < ClassElectricityStorageDevice & handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        v_max = 4.2;
        v_min = 3.2;

        r = [0.0 0.0 0.0 0.0];
        c = [0.0 0.0 0.0];
    end
    
    methods
        function obj = ClassBattery(order, v, capacitance_distribution, resistance_distribution)
            %Battery Construct an instance of this class
            %   Provide Pascal order and starting voltage
            %   Usage Battery(order)
            %   or Battery(order, v, capacitance_distribution, resistance_distribution)

            obj = obj@ClassElectricityStorageDevice(order);

            if (nargin > 0)
                if (nargin == 4)
                    obj.setup_battery(v, capacitance_distribution, resistance_distribution);
                end
            end
        end

        function obj = setup_battery(obj, v, capacitance_distribution, resistance_distribution)
            obj.r = [resistance_distribution(1:3) resistance_distribution(8)];
            obj.c = capacitance_distribution(1:3);
            obj.setup(v, capacitance_distribution(4:end), resistance_distribution(4:7));
        end

        function resistance_distribution = get_resistance_distribution(obj)
            resistance_distribution = [obj.r(1:4) obj.resistance obj.r(8)];
        end

        function capacitance_distribution = get_capacitance_distribution(obj)
            capacitance_distribution = [obj.c(1:3) obj.capacitance];
        end
    end
end