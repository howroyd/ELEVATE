clf; clc; clear all; close all;

res = 0.25;

set_param('cap_eq_circuit_pascal5_single_shot_stack','AlgebraicLoopSolver','LineSearch');

distribution_in = [ 0 0 0 0 0 ...
                    1 1 1 1 1 ...
                    0 0 0 0 0];


%% Initial conditions
dt = 1.0;
%distribution_in = 0.0;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out, simout1 ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [ distribution_out ];
v_cc = [0.0;v_end];

%% Initial charge up
dt = 100.0;
distribution_in = distribution_out;
amps_in = 15.0;
[ v_end, amps_delivered, soc, distribution_out, simout2 ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Soak
dt = 10.0;
distribution_in = distribution_out;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out, simout3 ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Discharge
dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.05;
[ v_end, amps_delivered, soc, distribution_out, simout4 ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Soak
dt = 500.0;
distribution_in = distribution_out;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out, simout5 ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Plot

surf(my_distribution,...
    'edgecolor','none'); hold all;

%surf(my_distribution,...
%    'edgecolor','none'); hold all;

%for i=1:10
%    [ v_end, amps_delivered, soc, distribution ] = sc_model_single_shot( dt, amps_in, distribution );
%    plot(distribution); hold all;
%end

%for i=1:10
%    [ v_end, amps_delivered, soc, distribution ] = sc_model_single_shot( dt, amps_in, distribution );
%    plot(distribution); hold all;
%end

grid on;
ylabel('time');
xlabel('Pascal rungs 1 to 5');
zlabel('Voltage');
%title('5th order pascal eq circuit, starting at 1V across each cap.  Apply load and see the fast states discharge.  Then open circuit and see the redistribution aka self balancing');
hold off;

%figure();
%plot(v_cc);
%grid on;