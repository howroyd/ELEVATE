clc; clear all; clf;

for counter=1:5
    % Define simulation variables
    v_chg    = 1.0;
    time_on  = 0;
    time_off = 5;
    short_on = 5.0001;
    short_off= short_on + counter;
    sim_time = 20 + short_off;
    r_pwr    = 1e-3;
    
    % Run Simulation
    sim('cap_eq_circuit_pascal5_simple', 'ReturnWorkspaceOutputs', 'on');
    
    % Find short circuit time in data
    loc = find(tout >= short_off);
    
    % Create output data array of rebound only
    out = [ tout(loc(1):end)- tout(loc(1)), v_cc(loc(1):end) ];
    
    % Create plot of data
    my_fig = plot(out(:,1),out(:,2));
    hold all;
    
    % Create savefile name
    fn = sprintf('cap_pascal7_%ds_short',counter);
    
    % Save raw data as .mat
    save(strcat(fn,'.mat'),'out');
    
    % Save raw data as .csv
    csvwrite(strcat(fn,'.csv'), out);
end

% Fancify the plot
grid on;
xlabel('Time /s');
ylabel('Voltage /V');
legend('1s Short','2s Short','3s Short','4s Short','5s Short');

% Save figure
save('cap_pascal7_short.fig', 'my_fig');
saveas(my_fig, 'cap_pascal7_short.png');
saveas(my_fig, 'cap_pascal7_short', 'epsc');

disp('Done!');