clf; clc; clear all; close all;

regen = 1.0; % off
%regen = -1.0; % on

pascalOrd = 5;
iDivisor  = 1.0;
vStart    = 6.0;
tStep     = 1.0;

current = @(ampsIn) ampsIn ./ iDivisor;

mySc = Sc_single(pascalOrd, vStart, tStep);


%% Initial conditions
mySc = mySc.run(10.0, current(0.0));

%% Urban Drive
for x=0:3
    mySc = mySc.run(5.0, current(-0.075));
    mySc = mySc.run(10.0, current(-0.15));
    mySc = mySc.run(5.0, current(-0.75)*regen);
    mySc = mySc.run(20.0, current(0.0));
    mySc = mySc.run(10.0, current(-0.15));
    mySc = mySc.run(20.0, current(-0.3));
    mySc = mySc.run(10.0, current(-0.15)*regen);
    mySc = mySc.run(20.0, current(0.0));
    mySc = mySc.run(10.0, current(-0.15));
    mySc = mySc.run(10.0, current(-0.37));
    mySc = mySc.run(10.0, current(-0.5));
    mySc = mySc.run(20.0, current(-0.37)*regen);
    mySc = mySc.run(10.0, current(-0.15)*regen);
    mySc = mySc.run(20.0, current(0.0));
end

%% High Speed
mySc = mySc.run(10.0,     current(-0.15));
mySc = mySc.run(10.0,     current(-0.37));
mySc = mySc.run(10.0,     current(-0.5));
mySc = mySc.run(50.0,     current(-0.7));
mySc = mySc.run(70.0,     current(-0.5));
mySc = mySc.run(50.0,     current(-0.7));
mySc = mySc.run(10.0,     current(-0.85));
mySc = mySc.run(30.0,     current(-1.0));
mySc = mySc.run(10.0,     current(-1.2));
mySc = mySc.run(5.0,      current(-1.0)*regen);
mySc = mySc.run(5.0,      current(-0.85)*regen);
mySc = mySc.run(5.0,      current(-0.7)*regen);
mySc = mySc.run(5.0,      current(-0.5)*regen);
mySc = mySc.run(5.0,      current(-0.37)*regen);
mySc = mySc.run(5.0,      current(-0.15)*regen);
mySc = mySc.run(10000.0,  current(0.0));

fprintf('\n\nFinished!\n');
%return;

%% Plot

h1 = figure;
surf(mySc.my_distribution,...
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

for i=1:length(mySc.my_distribution)
    bar(mySc.my_distribution(i, 1:size(mySc.my_distribution, 2)));
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
