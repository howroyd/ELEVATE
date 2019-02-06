clf; clc; clear all; close all;

res = 0.2;

%% Initial conditions
dt = 1.0;
distribution_in = [0.0 0.0 0.0 0.0 0.0];
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [ distribution_in ; distribution_out ];
v_cc = [0.0;v_end];

%% Initial charge up
dt = 1.0;
distribution_in = distribution_out;
amps_in = 0.2;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Soak
dt = 10.0;
distribution_in = distribution_out;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Discharge
dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.05;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Soak
dt = 20.0;
distribution_in = distribution_out;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Plot

surf(my_distribution); hold all;

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

figure();
plot(v_cc);
grid on;