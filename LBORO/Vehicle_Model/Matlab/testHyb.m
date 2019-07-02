clf; clc; clear all; close all;

%driveCycle = readmatrix('DriveCycles/nedc2_kph.tsv','FileType','text');
driveCycle = readmatrix('../DriveCycles/nedc2_short_kph.tsv','FileType','text');
%driveCycle = readmatrix('DriveCycles/step_quick_kph.tsv','FileType','text');

pascalOrd = 5;
nSeries   = 3;
ptr       = 1;

iDivisor  = 500.0;
tDivisor  = 0.1;
resolution= 0.5;
tStep     = 1.0;

vStart    = 4.2;

cCap      = [20  20  20  20   20];
cR        = [550 625 700 1400 4000] ./ 1e3;

bCap      = [0.03 0.8 2 1 1 0.1 20] .* 1e2; % F
bR        = [0.021 0.207 0.0055 2 0.05 0.02 1 0.023] .* 1e2; % FIXME TODO these R values are very low compared to the cap
bSoc      = 1.0; % pc 8.2v

current   = @(ampsIn)  -ampsIn ./ iDivisor;
time      = @(t)       t       ./ tDivisor;

for i=1:length(driveCycle)
    driveCycle(i, 1) = time(driveCycle(i, 1));
    driveCycle(i, 2) = current(driveCycle(i, 2));
end

%tStep     = (driveCycle(2, 1) - driveCycle(1, 1)) ./ tStep;

mySc      = Sc(pascalOrd, nSeries, vStart, resolution);
mySc      = mySc.setupCap(cCap, cR);
mySc      = mySc.setupBattery(bCap, bR);

%% Drive
mySc = mySc.runCycle( driveCycle(:, 1), driveCycle(:, 2), tStep );
%[sim_time, amps_in, distribution_in, capacitance,...
%                            bCapacity, bSoc, resolution, tStep, v_init]...
%                                                = mySc.fakeRun( 10, 0.1 );

%% Save
save('model_out_all.mat');
save('model_out.mat', 'mySc');
pause(1);

%% Plot surface
mySc.plotSoc(1);
mySc.plotSoc(2);
mySc.plotSoc(3);
%mySc.plotSurface(2);
%mySc.plotSurface(3);

%% Plot movie
%mySc.plotMovie('pretty_vid', 100);

%% End
%load('handel.mat');
%player = audioplayer(y, Fs);
%play(player);
disp('Finished!');