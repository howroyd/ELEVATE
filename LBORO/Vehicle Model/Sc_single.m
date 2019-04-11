classdef Sc_single
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        distribution_in;
        res;
        t = [0];
        v_cc = [0.0];
        my_distribution;
    end
    
    methods
        function obj = Sc_single(order, vStart, res)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            obj.distribution_in = ones(order) .* vStart;
            obj.res             = res;
            obj.my_distribution = obj.distribution_in;
        end
        
        function obj = run(obj, dt, ampsIn)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            [ v_end, amps_delivered, soc, distribution_out ] = ...
                sc_model_single_shot( dt, obj.res, ampsIn, obj.distribution_in );
            
            obj.distribution_in = distribution_out;
            obj.my_distribution = [obj.my_distribution ; distribution_out];
            obj.v_cc = [ obj.v_cc ; v_end ];
            obj.t = [ obj.t ; (obj.t(end):obj.res:(obj.t(end)+dt))' ]; % TODO duplicate timestamp
        end
    end
end

