clf; clc; clear all; close all;

f = waitbar(0, 'Starting...');

driveCycle = readmatrix('DriveCycles/nedc2_kph.tsv','FileType','text');

pascalOrd = 5;
iDivisor  = 1.0;
vStart    = 6.0;
tStep     = 100.0;
farads    = 200.0;
nSeries   = 3;

current = @(ampsIn) ampsIn ./ iDivisor;

waitbar(0, f, '...Constructing supercapacitor class...');

mySc = Sc(pascalOrd, nSeries, vStart, farads, tStep);

waitbar(1, f, '......done');
pause(0.5);


%% Initial conditions
waitbar(0, f, '...Setting initial conditions...');

mySc = mySc.run(uint32(10.0 * tStep), current(0.0));

waitbar(1, f, '......done');
pause(0.5);


%% Drive
waitbar(0, f, '...Starting drive...');
tLast = 0.0;

for i=1:length(driveCycle)
    % Calculate time since the model was last run (seconds)
    dt = round(driveCycle(i, 1) - tLast);
    
    % Check if this current timestep is ahead of the last timestep + dt
    if round(driveCycle(i, 1)) > ( round(tLast) + tStep )
        
        %fprintf('New timestep at %.2f\n', driveCycle(i, 1));
        
        % Run the model
        mySc = mySc.run(dt, current(-driveCycle(i, 2)));
        
        % Update our last run timer
        tLast = driveCycle(i, 1);
    end
    
    waitbar( i / length(driveCycle), f);
end

waitbar(1, f, 'done');
pause(1);
close(f);
clearvars -EXCEPT mySc;

%% Save
save('model_out.mat', 'mySc');

%% Plot surface
mySc.plotSurface();

%% Plot movie
mySc.plotMovie('pretty_vid', 100);

%% End
disp('Finished!');