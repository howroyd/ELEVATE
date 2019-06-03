classdef Sc
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        distribution_in;
        res;
        t = [0];
        v_cc = [0.0];
        v;
        my_distribution;
        pascalOrd;
        model;
        soc;
        farads;
        nSeries;
        pascalTri;
        simOut;
        hSurface;
        hSoc;
        bCapacity;
        bSoc;
    end
    
    properties (Constant)
        vPeak = 8.0;
    end
    
    methods
        function obj = Sc(order, nSeries, vStart, farads, res, model)
            %Sc Construct an instance of this class
            %   Detailed explanation goes here
            
            Sc.killEmAll();
            
            if nargin < 6
                if nSeries == 1
                    model = 'single';
                else
                    model = 'stack';
                end
            end
            
            if ( strcmp(model, 'single') && nSeries > 1 ) || ...
                    ( strcmp(model, 'stack') && nSeries == 1 )
                error('Wrong model selected for number of caps')
            end
            
            if ~( nSeries == 1 || nSeries == 3 )
                error('Unimplimented model required');
            end
            
            if strcmp(model, 'single')
                obj.model       = 'cap_eq_circuit_pascal5_single_shot';
            elseif strcmp(model, 'stack')
                obj.model       = 'battery_eq_circuit_pascal5_single_shot_stack';
            end
            
            %load_system(obj.model);
            disp(obj.model);
            
            obj.res             = res;
            obj.pascalOrd       = order;
            obj.pascalTri       = Sc.pascal_triangle(order);
            obj.nSeries         = nSeries;
            obj.farads          = farads;
            
            obj.v               = zeros(1, nSeries);
            
            obj.distribution_in = ones(1, order, nSeries) .* vStart;
            obj.my_distribution = obj.distribution_in;
            obj.soc             = mean(obj.my_distribution) / obj.vPeak;
            obj.hSurface        = 1:nSeries;
            obj.hSoc            = 1:nSeries;
        end
        
        function [sim_time, amps_in, distribution_in, capacitance,...
                bCapacity, bSoc, resolution, tStep, v_init] = fakeRun(obj, t, ampsIn)
            
            [sim_time, amps_in, distribution_in, capacitance,...
                bCapacity, bSoc, resolution, tStep, v_init] = ...
                obj.returnAsGlobals(t, obj.res, ampsIn, obj.distribution_in);
        end
        
        function obj = setupBattery(obj, capacity, soc)
            obj.bCapacity = ones(1, obj.nSeries) .* capacity;
            obj.bSoc      = ones(1, obj.nSeries) .* soc;
        end
        
        function h = buildModel(obj)
            warning('off');
            h = Simulink.BlockDiagram.buildRapidAcceleratorTarget(obj.model);
            warning('on');
        end
        
        function obj = run(obj, t, ampsIn)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            
            %[ t, v_end, amps_delivered, soc, distribution_out ] = ...
            %    obj.sc_model_single_shot( t, obj.res, ampsIn, obj.distribution_in );
            [ t, v_end, v, amps_delivered, soc, bSoc, distribution_out ] = ...
                obj.hybrid_model_single_shot( t, obj.res, ampsIn, obj.distribution_in );
            
            obj.distribution_in = distribution_out;
            obj.my_distribution = Sc.appendDistribution(...
                obj.my_distribution, obj.distribution_in, obj.nSeries);
            obj                 = obj.updateVcc(v_end);
            obj                 = obj.updateT(t+obj.t(end)+obj.res);
            
            obj.v               = [obj.v ; v ];
            
            % TODO duplicate timestamp
            obj.soc             = [obj.soc  , soc];
            obj                 = obj.updateBattSoc(bSoc);
            %disp(obj.bSoc(end,:));
        end
        
        function obj = runCycle(obj, t, ampsIn, tStep)
            f = waitbar(0, 'Starting...');
            
            %% Initial conditions
            waitbar(0, f, '...Setting initial conditions...');
            
            obj      = obj.run(uint32(10.0 * tStep), 0.0);
            
            waitbar(1, f, '......done');
            pause(0.5);
            
            
            %% Drive
            waitbar(0, f, '...Starting drive...');
            
            i         = 1;
            while i < length(t)
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
                waitbar( i / length(t), f, sprintf('...Driving...%s', obj.model));
                %catch
                %    break;
                %end
            end
            
            waitbar(1, f, 'done');
            pause(1);
            close(f);
        end
        
        function obj = updateVcc(obj, vcc)
            obj.v_cc = [ obj.v_cc ; vcc ];
        end
        
        function obj = updateT(obj, t)
            obj.t = [ obj.t ; t ];
        end
        
        function obj = updateBattSoc(obj, battSoc)
            obj.bSoc = [ obj.bSoc ; battSoc ];
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
        
        function [ t, v_end, v, amps_delivered, soc, bSoc, distribution_out ] ...
                = hybrid_model_single_shot(obj, t, resolution, amps_in, distribution_in)
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
            disp('Running simulation');
            
            warning('off');
            obj.simOut          = sim(obj.model,...
                'SrcWorkspace', 'current', 'ReturnWorkspaceOutputs', 'on');%,...
            %    'SimulationMode','rapid');
            warning('on');
            
            disp('Done.');
            
            % Get output variables
            v_end               = obj.simOut.get('v_cc');
            v_dist              = obj.simOut.get('v_cap');
            amps_delivered      = obj.simOut.get('i_cc');
            t                   = obj.simOut.get('t');
            
            %fprintf('%.2f %.2f %.2f %.2f %.2f\n',...
            %    v_dist(1), v_dist(2), v_dist(6), v_dist(12), v_dist(16));
            %disp(v_dist);
            
            distribution_out    = Sc.createOutputArray(obj.pascalTri, obj.nSeries, v_dist);
            v                   = [mean(distribution_out(:,1:5,1), 2)...
                mean(distribution_out(:,1:5,2), 2)...
                mean(distribution_out(:,1:5,3), 2)]; % TODO generalise for nSeries
            soc                 = mean(distribution_out)./obj.vPeak;
            bSoc                = obj.simOut.get('bSoc');
            %disp(bSoc);
        end
        
        function [sim_time, amps_in, distribution_in, capacitance,...
                bCapacity, bSoc, resolution, tStep, v_init]...
                = returnAsGlobals(obj, t_, resolution_, amps_in_, distribution_in_)
            
            sim_time            = double(t_);
            distribution_in     = double(distribution_in_);
            amps_in             = double(amps_in_);
            capacitance         = double(obj.farads); % F
            
            bCapacity           = double(obj.bCapacity);
            bSoc                = double(obj.bSoc);
            
            if resolution_ <= 0.0
                resolution_      = 0.1;
                warning('Overriding resolution');
            end
            
            resolution = double(resolution_);
            tStep      = resolution_;
            
            v_init = distribution_in_(end, :, :);
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
            
            socCap = mean(obj.my_distribution(:, :, idCap), 2) / 8.0 * 100.0;
            socBat = obj.bSoc(:,idCap);
            
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
        
        function pt             = pascal_triangle(n)
            
            % The first two rows are constant
            pt(1, 1) = 1;
            pt(2, 1 : 2) = [1 1];
            
            % If only two rows are requested, then exit
            if n < 3
                return
            end
            
            for r = 3 : n
                % The first element of every row is always 1
                pt(r, 1) = 1;
                
                % Every element is the addition of the two elements
                % on top of it. That means the previous row.
                for c = 2 : r-1
                    pt(r, c) = pt(r-1, c-1) + pt(r-1, c);
                end
                
                % The last element of every row is always 1
                pt(r, r) = 1;
            end
            
            pt = pt(n,:);
        end
        
        function killEmAll
            set(0,'ShowHiddenHandles','on');
            delete(get(0,'Children'));
            set(0,'ShowHiddenHandles','off');
        end
        
    end
end

