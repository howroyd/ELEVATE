clf; clc; clear all; close all;

driveCycle = readmatrix('DriveCycles/nedc2_kph.tsv','FileType','text');
%driveCycle = readmatrix('DriveCycles/step_kph.tsv','FileType','text');

pascalOrd = 5;
iDivisor  = 5.0;
tDivisor  = 1.0;
vStart    = 6.0;
tStep     = 10.0;
farads    = 200.0;
nSeries   = 3;
ptr       = 1;

current   = @(ampsIn) -ampsIn ./ iDivisor;
time      = @(t)       t      ./ tDivisor;

for i=1:length(driveCycle)
    driveCycle(i, 1) = time(driveCycle(i, 1));
    driveCycle(i, 2) = current(driveCycle(i, 2));
end

%tStep     = (driveCycle(2, 1) - driveCycle(1, 1)) ./ tStep;

mySc      = Sc(pascalOrd, nSeries, vStart, farads, tStep);


%% Drive
mySc = mySc.runCycle( driveCycle(:, 1), driveCycle(:, 2), tStep );

%% Save
save('model_out.mat', 'mySc');

%% Plot surface
mySc.plotSurface(1);
mySc.plotSurface(2);
mySc.plotSurface(3);

%% Plot movie
%mySc.plotMovie('pretty_vid', 100);

%% End
disp('Finished!');