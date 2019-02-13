function [ v_end, amps_delivered, soc ] = sc_model_single_shot( v_start, amps_request, dt)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

    clear all;

    model = 'cap_eq_circuit_pascal5_single_shot_stack';
    %model = 'test_model';
    verbose = true;
    
    % Define simulation variables
    v_chg    = 10.0;
    time_on  = 0;
    time_off = 10;
    short_on = 5.0001;
    short_off= short_on + 5;
    sim_time = 20 + short_off;
    r_pwr    = 1e-3;
    r_load   = 1e0;
    
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
    v_end = v_end(end);
    
    amps_delivered = 0.0;
    soc = 0.5;
end

