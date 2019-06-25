clf; clc; clear all; close all;

model = "hybrid_new_eq_circuit_pascal5_single_shot_stack";

%driveCycle = readmatrix('DriveCycles/nedc2_kph.tsv','FileType','text');
driveCycle = readmatrix("../DriveCycles/nedc2_short_kph.tsv",'FileType','text');
%driveCycle = readmatrix('DriveCycles/step_quick_kph.tsv','FileType','text');

battery_pascal_order = 3;
capacitor_pascal_order = 5;
nSeries   = 3;

iDivisor  = 500.0;
tStep     = 10.0;
tDivisor  = 0.1;

vStart    = 4.2;

cCap      = 20.0;
cR        = [550 625 700 1400 4000];

bCap      = [0.03   0.8     2       1   1       0.1     20]; % F
bR        = [0.021  0.207   0.0055  2   0.05    0.02    1   0.023]; % FIXME TODO these R values are very low compared to the cap
bSoc      = 1.0; % pc 8.2v

current   = @(ampsIn)  -ampsIn ./ iDivisor;
time      = @(t)  t ./ tDivisor;

for i=1:length(driveCycle)
    driveCycle(i, 1) = time(driveCycle(i, 1));
    driveCycle(i, 2) = current(driveCycle(i, 2));
end

%tStep     = (driveCycle(2, 1) - driveCycle(1, 1)) ./ tStep;

myHybrid = ClassHybrid(tStep, vStart, nSeries,  model, battery_pascal_order, capacitor_pascal_order);
myHybrid.setup_battery(battery_pascal_order, vStart, bCap, bR);
myHybrid.setup_capacitor(capacitor_pascal_order, vStart, cCap, cR);

%% Drive
myHybrid = myHybrid.runCycle( driveCycle(:, 1), driveCycle(:, 2), tStep );

%% Save
save('model_out.mat', 'mySc');

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