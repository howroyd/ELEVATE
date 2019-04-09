clf; clc; clear all; close all;

res = 1.0;
t=[0];

%set_param('cap_eq_circuit_pascal5_single_shot_stack','AlgebraicLoopSolver','LineSearch');

distribution_in = [ 1 1 1 1 1 ] .* 6.0;


%% Initial conditions
dt = 10.0;
%distribution_in = 0.0;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [ distribution_out ];
v_cc = [0.0;v_end];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp


%% Urban Drive
for x=0:3
    dt = 5.0;
    distribution_in = distribution_out;
    amps_in = -0.075;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.15;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 5.0;
    distribution_in = distribution_out;
    amps_in = -0.075;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 20.0;
    distribution_in = distribution_out;
    amps_in = 0.0;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    
    
    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.15;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 20.0;
    distribution_in = distribution_out;
    amps_in = -0.30;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.15;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 20.0;
    distribution_in = distribution_out;
    amps_in = 0.0;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    
    
    
    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.15;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.37;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.50;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 20.0;
    distribution_in = distribution_out;
    amps_in = -0.37;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 10.0;
    distribution_in = distribution_out;
    amps_in = -0.15;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

    dt = 20.0;
    distribution_in = distribution_out;
    amps_in = 0.0;
    [ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
    my_distribution = [my_distribution ; distribution_out];
    v_cc = [ v_cc ; v_end ];
    t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

end

dt = 10.0;
distribution_in = distribution_out;
amps_in = -0.15;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 10.0;
distribution_in = distribution_out;
amps_in = -0.37;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 10.0;
distribution_in = distribution_out;
amps_in = -0.50;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 50.0;
distribution_in = distribution_out;
amps_in = -0.70;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 70.0;
distribution_in = distribution_out;
amps_in = -0.50;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 50.0;
distribution_in = distribution_out;
amps_in = -0.70;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 10.0;
distribution_in = distribution_out;
amps_in = -0.85;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 30.0;
distribution_in = distribution_out;
amps_in = -1.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 10.0;
distribution_in = distribution_out;
amps_in = -1.2;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 5.0;
distribution_in = distribution_out;
amps_in = -1.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.85;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.70;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.50;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.37;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp

dt = 5.0;
distribution_in = distribution_out;
amps_in = -0.15;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp



dt = 10000.0;
distribution_in = distribution_out;
amps_in = 0.0;
[ v_end, amps_delivered, soc, distribution_out ] = sc_model_single_shot( dt, res, amps_in, distribution_in );
my_distribution = [my_distribution ; distribution_out];
v_cc = [ v_cc ; v_end ];
t= [ t ; (t(end):res:(t(end)+dt))' ]; % TODO duplicate timestamp


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


fprintf('\n\nFinished!\n');

%return;

h2 = figure();
axis([0 6 0 8], 'manual');
grid on;

for i=1:length(my_distribution)
    bar(my_distribution(i,1:5));
    axis([0 6 0 8], 'manual');
    grid on;
    M(i) = getframe(h2);
end

close(h2);

v = VideoWriter('pretty_vid.mp4', 'MPEG-4');
v.FrameRate = 5;
open(v);
writeVideo(v,M);
close(v);


%movie(M, 1);

%figure();
%plot(v_cc);
%grid on;


fprintf('\n\nFinished!\n');
