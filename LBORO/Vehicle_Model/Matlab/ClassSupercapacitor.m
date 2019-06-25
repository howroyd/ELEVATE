classdef ClassSupercapacitor < ClassElectricityStorageDevice & handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        v_max = 8.0;
        v_min = 0.0;
    end
    
    methods
        function obj = ClassSupercapacitor(order, v, capacitance_distribution, resistance_distribution)
            %Supercapacitor Construct an instance of this class
            %   Provide Pascal order and starting voltage
            %   Usage Supercapacitor(order)
            %   or Supercapacitor(order, v, capacitance_distribution, resistance_distribution)
            
            obj = obj@ClassElectricityStorageDevice(order);
            
            if (nargin > 0)
                if (nargin == 4)
                    obj.setup(v, capacitance_distribution, resistance_distribution);
                end
            end
        end
        
        function obj = setup_supercapacitor(v, capacitance_distribution, resistance_distribution)
            obj.setup(v, capacitance_distribution, resistance_distribution);
        end
    end
end