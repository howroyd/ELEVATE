classdef ClassHybrid < handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties ( Access = private)
        t = 0.0;
        t_step = 10.0;

        model = '';
        n_series = 3;

        v_cc;
        i_cc;
        soc;

        battery_pascal_order;
        capacitor_pascal_order;

        h_battery = ClassBattery(3); % TODO is this a valid bodge to assign datatype
        h_capacitor = ClassSupercapacitor(5); % TODO is this a valid bodge to assign datatype

        h_plot_surface;
        h_plot_soc;
    end

    methods (Static)
        function capacitance_distribution = get_capacitance_distribution( ...
                                                h, pascal_order, n_series)
            capacitance_distribution = ones(1, pascal_order, n_series)

            for x=1:n_series
                capacitance_distribution(1,:,x) = h(x).get_capacitance_distribution();
            end
        end

        function resistance_distribution = get_resistance_distribution( ...
                                            h, pascal_order, n_series)
            resistance_distribution = ones(1, pascal_order, n_series)

            for x=1:n_series
                resistance_distribution(1,:,x) = h(x).get_resistance_distribution();
            end
        end

        function v_distribution = get_v_distribution( ...
                                    h, pascal_order, n_series)
            v_distribution = ones(1, pascal_order, n_series)

            for x=1:n_series
                v_distribution(1,:,x) = h(x).get_v_distribution();
            end
        end

        function obj = set_v_distribution( ...
                                    h, t, v_distribution, n_series)

            for x=1:n_series
                h(x).set_v_distribution(t, v_distribution);
            end
        end

        

        function [model, n_series] = set_model(model_requested, n_series_requested, ...
                                         order_battery_requested, order_capacitor_requested)

            validity = false;
            
            if (n_series_requested == 1 && contains(model_requested, 'single'))
                % Single cell model requested with correct n_series, all OK
                validity = true;
            elseif (n_series_requested > 1 && contains(model_requested, 'stack'))
                % Stack model requested with correct n_series, all OK
                validity = true;
            else
                validity = false;
                error(sprintf("Wrong n_series (%d%) set for model %s", n_series_requested, model_requested));
            end

            % TODO
            %if (order_battery_requested == 4 && contains(model_requested, 'pascal4batt'))
            %    % Single cell model requested with correct n_series, all OK
            %    validity = true;
            %elseif (n_series_requested > 1 && contains(model_requested, 'stack'))
            %    % Stack model requested with correct n_series, all OK
            %    validity = true;
            %else
            %    validity = false;
            %    error(sprintf("Wrong n_series (%d%) set for model %s", n_series_requested, model_requested));
            %end

            if ~(n_series_requested == 1 || n_series_requested == 3)
                validity = false;
                error("Model not implemented for n_series %d", n_series_requested);
            end

            if (validity == true)
                model = model_requested;
                n_series = n_series_requested;
                disp(sprintf("n_series=%d, model=%s", n_series, model));
            else
                model = '';
                n_series = 0;
                error("Undefined error");
            end
        end

        function t_step = set_t_step(t_step_requested)

            validity = false;

            if (t_step_requested > 0.0)
                validity = true;
            else
                validity = false;
                error(sprintf("Bad t_step (%f%) chosen", t_step_requested));
            end

            if (validity == true)
                t_step = t_step_requested;
                disp(sprintf("t_step=%f%", t_step));
            else
                t_step = 0.0;
                error("Undefined error");
            end
        end
    end
    
    methods
        function obj = ClassHybrid(t_step, v_start, n_series,  model, order_battery, order_capacitor)
            %Sc Construct an instance of this class
            %   Detailed explanation goes here
            
            ClassHybrid.killEmAll();

            obj.t_step                  = ClassHybrid.set_t_step(t_step);

            %obj.h_battery               = zeros(1, obj.n_series);
            %obj.h_capacitor             = zeros(1, obj.n_series);
            
            obj.v_cc                    = v_start;
            obj.i_cc                    = 0.0;
            
            obj.soc                     = 0.0; % TODO

            obj.h_plot_surface                = 1:n_series;
            obj.h_plot_soc                    = 1:n_series;

            % TODO check order
            if (nargin == 6)
                [obj.model, obj.n_series]   = ClassHybrid.set_model(model, n_series, order_battery, order_capacitor);
            elseif (nargin == 4)
                [obj.model, obj.n_series]   = ClassHybrid.set_model(model, n_series);
            else
                error("Bad constructor n arguments");
            end
        end
        
        function obj = setup_battery(obj, order, v, capacitance_distribution, resistance_distribution)
            for x=1:obj.n_series
                obj.h_battery(x) = ClassBattery(order, v, capacitance_distribution, resistance_distribution);
            end
        end
        
        function obj = setup_capacitor(obj, order, v, capacitance_distribution, resistance_distribution)
            for x=1:obj.n_series
                obj.h_capacitor(x) = ClassSupercapacitor(order, v, capacitance_distribution, resistance_distribution);
            end
        end

        function obj = runCycle(obj, t, ampsIn, tStep)
            f = waitbar(0, 'Starting...');
            %ft = get(get(f, 'CurrentAxis'), 'title');
            %set(ft, 'Interpreter', 'none');
            
            %% Initial conditions
            waitbar(0, f, '...Setting initial conditions...');
            
            obj      = obj.run(uint32(10.0 * tStep), 0.0);
            
            waitbar(1, f, '......done');
            pause(0.5);
            
            
            %% Drive
            waitbar(0, f, '...Starting drive...');
            
            
            i         = 1;
            while i < (length(t) / 100) % TODO remove the limit
                %try
                
                % Optimisation: If next time step current is the same then bulk
                % together so model is only one once for common, consecutive currents
                counter = 1;
                while (t(i+counter)-t(i) <  tStep)
                    counter = counter + 1;
                    
                    if (i + counter) == length(t)
                        % End of file
                        break;
                    end
                    
                    while ampsIn(i+counter) == ampsIn(i)
                        if (i + counter) == length(t)
                            % End of file
                            break;
                        else
                            % Look ahead one more timestep
                            counter = counter + 1;
                        end
                    end
                end
                
                fprintf('Bulking together timesteps %.2f to %.2f (of %.2f) at %.3fA\n',...
                    t(i, 1), t(i+counter, 1),...
                    t(end, 1), ampsIn(i));
                
                % Run the model
                obj = obj.run( (t(i+counter) - t(i)), ampsIn(i) );
                
                % Update the loop and skip ahead if required
                i    = i + counter;
                waitbar( i / length(t), f, strrep(sprintf('...Driving...%s', obj.model), '_', '\_'));
                %catch
                %    break;
                %end
                
                disp("Batt:");
                battSoc = [obj.getBattSoc(obj.batt_distribution, 1);
                    obj.getBattSoc(obj.batt_distribution, 2);...
                    obj.getBattSoc(obj.batt_distribution, 3)];
                disp(battSoc(end,:));
                
                disp("Cap:");
                capSoc = [obj.getCapSoc(obj.my_distribution, 1);
                    obj.getCapSoc(obj.my_distribution, 2);
                    obj.getCapSoc(obj.my_distribution, 3)];
                disp(capSoc(end,:));
                
            end
            
            waitbar(1, f, 'done');
            pause(1);
            close(f);
        end
           
        function obj = run(obj, t, amps)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            
            % TODO
            if (strcmp(obj.model, "hybrid_new_eq_circuit_pascal5_single_shot_stack"))
                [t, v, amps] = obj.hybrid_model_single_shot(t, amps);
            end
        end
        
        function obj = hybrid_model_single_shot(obj, t, v, amps)
            %sc_model_single_shot Summary of this function goes here
            %   Detailed explanation goes here
            
            % Define simulation variables
            sim_time = double(t);
            t_step = double(obj.t_step);

            amps_in = double(amps);

            battery_c = double(Hybrid.get_resistance_distribution(obj.h_battery, obj.battery_pascal_order, obj.n_series));
            battery_r = double(Hybrid.get_capacitance_distribution(obj.h_battery, obj.battery_pascal_order, obj.n_series));
            battery_v = double(Hybrid.get_v_distribution(obj.h_battery, obj.battery_pascal_order, obj.n_series));

            cap_c = double(Hybrid.get_resistance_distribution(obj.h_capacitor, obj.capacitor_pascal_order, obj.n_series));
            cap_r = double(Hybrid.get_capacitance_distribution(obj.h_capacitor, obj.capacitor_pascal_order, obj.n_series));
            cap_v = double(Hybrid.get_v_distribution(obj.h_capacitor, obj.capacitor_pascal_order, obj.n_series));
            
            % Run Simulation
            disp('Running simulation');
            
            warning('off');
            obj.simOut          = sim(obj.model,...
                'SrcWorkspace', 'current', 'ReturnWorkspaceOutputs', 'on');
            warning('on');
            
            disp('Done.');
            
            % Get output variables
            t                  = obj.simOut.get('t');
            v_cc               = obj.simOut.get('v_cc');
            amps               = obj.simOut.get('i_cc');

            v_battery          = obj.simOut.get('v_batt');
            v_capacitor        = obj.simOut.get('v_cap');
            
            Hybrid.set_v_distribution(obj.h_battery, t, v_battery, obj.n_series);
            Hybrid.set_v_distribution(obj.h_capacitor, t, v_capacitor, obj.n_series);
            
            obj.t               = [obj.t ; t];
            obj.v_cc            = [obj.v_cc ; v ];
            obj.i_cc            = [obj.i_cc ; amps ];

            % TODO
            %obj.soc             = [obj.soc  , soc];
        end

    
        function [ t, v_end, v, amps_delivered, soc, distribution_out ] ...
            = sc_model_single_shot(obj, t, resolution, amps_in, distribution_in)
            %sc_model_single_shot Summary of this function goes here
            %   Detailed explanation goes here
            
            invert_order        = false;
            
            % Define simulation variables
            sim_time            = double(t);
            distribution_in     = double(distribution_in);
            amps_in             = double(amps_in);
            capacitance         = double(obj.farads); % F
            
            bCapacity           = double(obj.bCapacity);
            bSoc                = double(obj.bSoc);
            
            if resolution <= 0.0
                resolution      = 0.1;
                warning('Overriding resolution');
            end
            
            resolution = double(resolution);
            tStep      = resolution;
            
            %fprintf(sprintf('sim_time=%.1f\tres=%.1f\n', sim_time, resolution));
            
            %v_init              = Sc.createInputArray(...
            %                        obj.pascalTri, obj.nSeries, distribution_in);
            
            v_init = distribution_in(end, :, :);
            
            %disp(v_init);
            
            % Run Simulation
            warning('off');
            obj.simOut          = sim(obj.model,...
                'SrcWorkspace', 'current', 'ReturnWorkspaceOutputs', 'on');
            warning('on');
            
            % Get output variables
            v_end               = obj.simOut.get('v_cc');
            v_dist              = obj.simOut.get('v_cap');
            amps_delivered      = obj.simOut.get('i_cc');
            t                   = obj.simOut.get('t');
            v                   = obj.simOut.get('v_cell');
            
            %fprintf('%.2f %.2f %.2f %.2f %.2f\n',...
            %    v_dist(1), v_dist(2), v_dist(6), v_dist(12), v_dist(16));
            %disp(v_dist);
            
            distribution_out    = Sc.createOutputArray(obj.pascalTri, obj.nSeries, v_dist);
            %soc                 = mean(distribution_out)./obj.vPeak;
            soc_temp            = obj.simOut.get('bSoc')';
            soc                 = soc_temp(end,:);
            
            %disp(distribution_out(end, :));
        end
        
        function [x y z] = get3d(obj, idCap)
            if nargin < 2
                idCap = 0;
            end
            
            x=0;y=0;z=0;
            
            x = 1:obj.pascalOrd;
            
            y = obj.t;
            
            z = obj.my_distribution(:,:,idCap);
            
        end
        
        function handle = plotSurface(obj, idCap)
            disp('...Plotting Surface...');
            
            [x, y, z] = obj.get3d(idCap);
            
            if length(y) > 3*60*60
                y = y ./ 3600.0;
                yUnits = 'hrs';
            elseif length(y) > 3*60
                y = y ./ 60.0;
                yUnits = 'mins';
            else
                yUnits = 'secs';
            end
            
            obj.hSurface(idCap) = figure(obj.hSurface(idCap));
            surf(x, y, z,...
                'edgecolor','none'); hold all;
            
            grid on;
            
            ylabel(sprintf('Time /%s', yUnits));
            
            xlabel('Pascal rungs 1 to 5');
            zlabel('Voltage');
            %title('5th order pascal eq circuit, starting at 1V across each cap.  Apply load and see the fast states discharge.  Then open circuit and see the redistribution aka self balancing');
            hold off;
            
            disp('...done');
        end
        
        function handle = plotSoc(obj, idCap)
            disp('...Plotting State of Charge (SoC)...');
            
            socCap = obj.getCapSoc(obj.my_distribution, idCap);
            socBat = obj.getBattSoc(obj.batt_distribution, idCap);
            
            v      = obj.v(:, idCap);
            
            t      = obj.t ./ 10.0;
            
            if t(end) > 3*60*60
                t = t ./ 3600.0;
                tUnits = 'hrs';
            elseif t(end) > 3*60
                t = t ./ 60.0;
                tUnits = 'mins';
            else
                tUnits = 'secs';
            end
            
            obj.hSoc(idCap) = figure(obj.hSurface(idCap));
            plot(t, socCap);
            hold all;
            plot(t, socBat);
            plot(t, v*10.0);
            
            grid on;
            
            xlabel(sprintf('Time /%s', tUnits));
            legend('Cap', 'Bat', 'V_{local}');
            ylabel('SoC /%, V_{local}*10 /V');
            %title('5th order pascal eq circuit, starting at 1V across each cap.  Apply load and see the fast states discharge.  Then open circuit and see the redistribution aka self balancing');
            hold off;
            
            disp('...done');
        end
        
        function obj = plotMovie(obj, filename, res)
            if nargin < 3
                res          = 1;
            end
            
            disp('...Plotting movie...');
            
            handle = figure();
            axis([0 6 0 8], 'manual');
            grid on;
            
            counter = 1;
            
            for i=1:res:size(obj.my_distribution, 1)
                %bar(mySc.my_distribution(i,:,1));
                
                bar( obj.my_distribution(i, 1:size(obj.my_distribution, 2)));
                
                axis([0 6 0 8], 'manual');
                grid on;
                M(counter) = getframe(handle);
                
                counter = counter + 1;
            end
            
            close(handle);
            
            v = VideoWriter(sprintf('%s.mp4', filename), 'MPEG-4');
            v.FrameRate = 5;
            open(v);
            writeVideo(v,M);
            close(v);
            
            disp('...done');
        end
        
    end
    
    methods (Static)
        
        function distribution   = appendDistribution(distributionSrc, distributionNew, nSeries)
            distribution = zeros( size(distributionSrc, 1)+size(distributionNew, 1), size(distributionSrc, 2), nSeries );
            if nSeries == 1
                distribution = [ distributionSrc ; distributionNew ];
            else
                for i=1:nSeries
                    distribution(:,:,i) = [ distributionSrc(:,:,i) ; distributionNew(:,:,i) ];
                end
            end
            
        end
        
        function str            = getDistributionString(distribution)
            str                 = '';
            
            for i=1:length(distribution)
                str             = [str, sprintf('%.2f\t', distribution(i))];
            end
        end
        
        function v_init         = createInputArray(pascalTri, nSeries, distribution, invert)
            
            if nargin < 4
                invert          = false;
            end
            
            x                   = size(distribution);
            
            % Do some checks
            if x(2) ~= size(pascalTri, 2)
                error('Wrong array size for pascal order in input');
            else
                if size(x, 3) == 1
                    % Only a single cap so all ok
                elseif x(3) ~= nSeries
                    error('Not enough caps defined in input array');
                end
            end
            
            v_init              = ones(x(1), 1, nSeries);
            
            if ~invert
                for i=1:x(1)
                    for j=1:nSeries
                        v_init(i, 1, j) = v_init(i, 1, j)...
                            .* distribution((x(1)+1) - i, j);
                    end
                end
            else
                for i=1:x(1)
                    for j=1:nSeries
                        v_init(i, 1, j) = v_init(i, 1, j) .* distribution(i, end, j);
                    end
                end
            end
        end
        
        function v_out          = createOutputArray(pascalTri, nSeries, distribution, invert)
            % TODO, but in this code
            % in      = 6.0000    6.0000    6.0000    6.0000    6.0000
            % mdl_out = 6.00 6.00 5.99 5.99 5.98
            % fn_out  = 5.7810    5.3742    5.3742    5.3742    5.3742
            
            if nargin < 4
                invert          = false; % TODO
            end
            
            x                   = size(distribution);
            
            % Do some checks
            if x(2) ~= sum(pascalTri) * nSeries
                error('Wrong array size for in output');
            end
            
            v_out = [];
            
            % Loop through each cap in series
            for i=1:nSeries
                % TODO make generic for pascal order
                v_out(:, 5, i) = mean(distribution(:, 1+16*(i-1)), 2);
                v_out(:, 4, i) = mean(distribution(:, 2+16*(i-1):5+16*(i-1)), 2);
                v_out(:, 3, i) = mean(distribution(:, 6+16*(i-1):11+16*(i-1)), 2);
                v_out(:, 2, i) = mean(distribution(:, 12+16*(i-1):15+16*(i-1)), 2);
                v_out(:, 1, i) = mean(distribution(:, 16+16*(i-1)), 2);
            end
            
        end
        

        
        function killEmAll
            set(0,'ShowHiddenHandles','on');
            delete(get(0,'Children'));
            set(0,'ShowHiddenHandles','off');
        end
        
    end
end

