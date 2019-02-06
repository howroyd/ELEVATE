function [ v_end, amps_delivered, soc, distribution_out ] ...
    = sc_model_single_shot( dt, resolution, amps_in, distribution_in)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


    %clear all;

    model = 'cap_eq_circuit_pascal5_single_shot';
    %model = 'test_model';
    verbose = true;
    
    % Define simulation variables
    sim_time = dt;
    
    v_start = mean(distribution_in(end,:));
    
    disp(['Requested ' num2str(amps_in) ' Amps']);
    
    if resolution <= 0.0
        resolution = 0.1
    end
    
        
    x=size(distribution_in);
    x=x(2);
    
    if x==1
        v_init1 = v_start;
        v_init2 = v_start;
        v_init3 = v_start;
        v_init4 = v_start;
        v_init5 = v_start;
        disp('Assuming capacitors are balanced');
    else if x==5
        v_init1 = distribution_in(end,5);
        v_init2 = distribution_in(end,4);
        v_init3 = distribution_in(end,3);
        v_init4 = distribution_in(end,2);
        v_init5 = distribution_in(end,1);
        disp(['Distribution: ' num2str([v_init1, v_init2, v_init3, v_init4, v_init5])]);
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
    
    distribution_out(:, 1) = v_dist(:, 1);
    distribution_out(:, 2) = mean(v_dist(:, 2:5),2);
    distribution_out(:, 3) = mean(v_dist(:, 6:11),2);
    distribution_out(:, 4) = mean(v_dist(:, 12:15),2);
    distribution_out(:, 5) = v_dist(:, 16);
    
%     distribution_out(5, :) = v_dist(:, 1)';
%     distribution_out(4, :) = mean(v_dist(2:5),2)';
%     distribution_out(3, :) = mean(v_dist(6:11),2)';
%     distribution_out(2, :) = mean(v_dist(12:15),2)';
%     distribution_out(1, :) = v_dist(:, 16)';
    
    amps_delivered = simOut.get('i_cc');
    %amps_delivered = amps_delivered(end);
    
    soc = 0.5;
end

