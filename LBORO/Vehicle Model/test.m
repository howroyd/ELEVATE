clf; clc; clear all; close all;

f = waitbar(0, 'Starting...');

driveCycle = readmatrix('DriveCycles/nedc2_kph.tsv','FileType','text');
%driveCycle = readmatrix('DriveCycles/step_kph.tsv','FileType','text');

pascalOrd = 5;
iDivisor  = 5.0;
tDivisor  = 1.0;
vStart    = 6.0;
tStep     = 100.0;
farads    = 200.0;
nSeries   = 1;
ptr       = 1;

current   = @(ampsIn) ampsIn ./ iDivisor;
time      = @(t)      t      ./ tDivisor;

for i=1:length(driveCycle)
    driveCycle(i, 1) = time(driveCycle(i, 1));
end

%tStep     = (driveCycle(2, 1) - driveCycle(1, 1)) ./ tStep;



waitbar(0, f, '...Constructing supercapacitor class...');

mySc      = Sc(pascalOrd, nSeries, vStart, farads, tStep);

waitbar(1, f, '......done');
pause(0.5);


%% Initial conditions
waitbar(0, f, '...Setting initial conditions...');

mySc      = mySc.run(uint32(10.0 * tStep), current(0.0));

waitbar(1, f, '......done');
pause(0.5);


%% Drive
waitbar(0, f, '...Starting drive...');

i         = 1;
while i < length(driveCycle)
    
    % Optimisation: If next time step current is the same then bulk
    % together so model is only one once for common, consecutive currents
    counter = 1;
    while (driveCycle(i+counter, 1)-driveCycle(i, 1) <  tStep)
        counter = counter + 1;
        
        if (i + counter) == length(driveCycle)
            % End of file
            break;
        end
        
        while driveCycle(i+counter, 2) == driveCycle(i, 2)
            if (i + counter) == length(driveCycle)
                % End of file
                break;
            else
                % Look ahead one more timestep
                counter = counter + 1;
                
                
                
            end
        end
    end
    
    fprintf('Bulking together timesteps %.2f to %.2f (of %.2f) at %.3fA\n',...
        driveCycle(i, 1), driveCycle(i+counter, 1),...
        driveCycle(end, 1), current(driveCycle(i, 2)));
    
    % Run the model
    mySc = mySc.run( (driveCycle(i+counter, 1) - driveCycle(i, 1)),...
        current(-driveCycle(i, 2)) );
    
    % Update the loop and skip ahead if required
    i    = i + counter;
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