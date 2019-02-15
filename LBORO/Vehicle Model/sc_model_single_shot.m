function [ v_end, amps_delivered, soc, distribution_out, simOut ] ...
    = sc_model_single_shot( dt, resolution, amps_in, distribution_in)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


    %clear all;

    model = 'cap_eq_circuit_pascal5_single_shot_stack';
    %model = 'test_model';
    verbose = true;
    
    % Define simulation variables
    sim_time = dt;
    
    capacitance = 0.1 % F
    
    v_start = mean(distribution_in(end,:));
    
    disp(['Requested ' num2str(amps_in) ' Amps']);
    
    if resolution <= 0.0
        resolution = 0.1;
    end
    
        
    x=size(distribution_in);
    x=x(2);
    
    v_init1 = ones(5,1);
    v_init2 = ones(5,1);
    v_init3 = ones(5,1);
        
    if x==1
        v_init1 = v_init1 .* v_start;
        v_init2 = v_init2 .* v_start;
        v_init3 = v_init3 .* v_start;
        disp('Assuming capacitors are balanced');
    elseif x==15
        v_init1(1) = v_init1(1) .* distribution_in(end, 5);
        v_init1(2) = v_init1(2) .* distribution_in(end, 4);
        v_init1(3) = v_init1(3) .* distribution_in(end, 3);
        v_init1(4) = v_init1(4) .* distribution_in(end, 2);
        v_init1(5) = v_init1(5) .* distribution_in(end, 1);
        
        v_init2(1) = v_init2(1) .* distribution_in(end, 10);
        v_init2(2) = v_init2(2) .* distribution_in(end, 9);
        v_init2(3) = v_init2(3) .* distribution_in(end, 8);
        v_init2(4) = v_init2(4) .* distribution_in(end, 7);
        v_init2(5) = v_init2(5) .* distribution_in(end, 6);
        
        v_init3(1) = v_init3(1) .* distribution_in(end, 15);
        v_init3(2) = v_init3(2) .* distribution_in(end, 14);
        v_init3(3) = v_init3(3) .* distribution_in(end, 13);
        v_init3(4) = v_init3(4) .* distribution_in(end, 12);
        v_init3(5) = v_init3(5) .* distribution_in(end, 11);

        %disp(['Distribution: ' num2str([v_init1, v_init2, v_init3])]);
    else
        error('Unknown distribution')
    end
        
    if verbose
        disp(['Running ' model]);
    end

    % Run Simulation
    %sim(model, model_cs, 'ReturnWorkspaceOutputs', 'on');
    warning('off');
        simOut = sim(model, 'SrcWorkspace', 'current', 'ReturnWorkspaceOutputs', 'on');
    warning('on');
    if verbose
        disp('...done!');
    end
    v_end = simOut.get('v_cc');
    %v_end = v_end(end);
    
    v_dist = simOut.get('v_cap');
    %v_dist = v_dist(end, :);
    
    distribution_out(:, 1)  = v_dist(:, 1);
    distribution_out(:, 2)  = mean(v_dist(:, 2:5), 2);
    distribution_out(:, 3)  = mean(v_dist(:, 6:11), 2);
    distribution_out(:, 4)  = mean(v_dist(:, 12:15), 2);
    distribution_out(:, 5)  = v_dist(:, 16);
    
    distribution_out(:, 6)  = v_dist(:, 16+1);
    distribution_out(:, 7)  = mean(v_dist(:, 16+2:16+5), 2);
    distribution_out(:, 8)  = mean(v_dist(:, 16+6:16+11), 2);
    distribution_out(:, 9)  = mean(v_dist(:, 16+12:16+15), 2);
    distribution_out(:, 10) = v_dist(:, 16+16);
    
    distribution_out(:, 11) = v_dist(:, 32+1);
    distribution_out(:, 12) = mean(v_dist(:, 32+2:32+5), 2);
    distribution_out(:, 13) = mean(v_dist(:, 32+6:32+11), 2);
    distribution_out(:, 14) = mean(v_dist(:, 32+12:32+15), 2);
    distribution_out(:, 15) = v_dist(:, 32+16);
    

    amps_delivered = simOut.get('i_cc');
    %amps_delivered = amps_delivered(end);
    
    soc = 0.5;
end

