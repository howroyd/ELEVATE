clf; clc; clear all; close all;

res = 0.25;

%set_param('cap_eq_circuit_pascal5_single_shot_stack','AlgebraicLoopSolver','LineSearch');

distribution_in = [ 1 1 1 1 1 ...
                    1 1 1 1 1 ...
                    1 1 1 1 1 ] .* 8;


%% Initial conditions
dt = 1.0;
%distribution_in = 0.0;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [ distribution_out ];
v_cc = [0.0;v_end];

%% Initial charge up
dt = 100.0;
distribution_in = distribution_out;
amps_in = -5.0;
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
dt = 500.0;
distribution_in = distribution_out;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, dt\res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];

%% Plot

h1 = figure;
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

h2 = figure();
axis([0 16 0 8], 'manual');
grid on;

for i=1:length(my_distribution)
    bar(my_distribution(i,1:15));
    axis([0 16 0 8], 'manual');
    grid on;
    M(i) = getframe(h2);
end

close(h2);

v = VideoWriter('pretty_vid.mp4', 'MPEG-4');
open(v);
writeVideo(v,M);
close(v);

%movie(M, 1);

%figure();
%plot(v_cc);
%grid on;