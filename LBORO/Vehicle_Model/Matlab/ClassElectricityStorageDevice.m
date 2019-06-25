classdef ( Abstract ) ClassElectricityStorageDevice < ClassPascalTriangle & handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here

    properties ( Abstract )
        v_max;
        v_min;
    end

    properties ( Access = protected )
        soc;
        v_distribution;
        capacitance;
        resistance;
        t;
    end

    methods ( Access = public )
        function soc = get_soc(obj)
            soc = ClassElectricityStorageDevice.calc_soc(obj.v_distribution, obj.v_max, obj.v_min);
        end

        function capacitance_distribution = get_capacitance_distribution(obj)
            capacitance_distribution = obj.capacitance;
        end

        function resistance_distribution = get_resistance_distribution(obj)
            resistance_distribution = obj.resistance;
        end

        function v_distribution = get_v_distribution(obj)
            v_distribution = obj.v_distribution;
        end
    end

    methods ( Static, Access = protected )
        function soc = calc_soc(v_distribution, v_min, v_max)
            v_mean = mean(v_distribution(end, :));
            soc = (v_mean - v_min) / v_max;
        end
    end
    
    methods
        function obj = ClassElectricityStorageDevice(order, v, capacitance_distribution, resistance_distribution)
            %Supercapacitor Construct an instance of this class
            %   Provide Pascal order and starting voltage
            %   Usage Supercapacitor(order)
            %   or Supercapacitor(order, v, capacitance_distribution, resistance_distribution)

            obj = obj@ClassPascalTriangle(order);
            
            if (nargin > 0)
                if (nargin == 4)
                    obj.setup(v, capacitance_distribution, resistance_distribution);
                end
            end
        end

        function obj = setup(obj, v, capacitance_distribution, resistance_distribution)
            if (size(capacitance_distribution, 2) == 1)
                % Assuming all equal
                obj.capacitance = ones(1, sum(obj.get_triangle())) .* capacitance_distribution;
            elseif (size(capacitance_distribution, 2) == sum(obj.get_triangle()))
                obj.capacitance = capacitance_distribution;
            else
                error(sprintf("Invalid capacitance distribution (%d) for pascal order (%d)", size(capacitance_distribution, 2), sum(obj.get_triangle()) ));
            end

            if (size(resistance_distribution, 2) == 1)
                % Assuming all equal
                obj.resistance = ones(1, sum(obj.get_pascal_triangle())) .* resistance_distribution;
            elseif (size(resistance_distribution, 2) == sum(obj.get_triangle()))
                obj.resistance = resistance_distribution;
            else
                error(sprintf("Invalid resistance distribution (%d) for pascal order (%d)", size(resistance_distribution, 2), obj.get_order() ));
            end

            obj.set_voltage_distribution(v);

            obj.t = 0.0;
        end

        function obj = update(t, v_distribution)
            if (size(t, 1) ~= size(v_distribiution, 1))
                error("Dimention mismatch between time and v_distribution");
            end
            
            obj.update_voltage_distribution(v_distribiution);
            obj.t = [obj.t ; t];
        end
    end

    methods ( Access = private )
        function obj = set_voltage_distribution(obj, v)
            distribution = ones(1, sum(obj.get_triangle()));

            obj.v_distribution = distribution .* v;
            obj.soc = obj.get_soc();
        end

        function obj = update_voltage_distribution(obj, v_distribiution)
            if (size(v_distribiution, 2) ~= sum(obj.get_triangle()))
                error("Dimention mismatch between new v_distribution and Pascal order")
            end

            obj.v_distribution = [obj.v_distribution ; v_distribiution];
            obj.soc = [obj.soc ; obj.get_soc()];
        end
    end
end

