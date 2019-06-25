clc;
clear all;

%% Get raw file
[file,path,~] = uigetfile;
[names,data]  = getRT(fullfile(path,file));
clear file path indx;


%% Name data
for i=1:length(names)
    newName  = strsplit(names(i));
    names(i) = newName(1);

    eval(sprintf('%s = data(:,%d);', names(i), i));
end
clear i newName;

veh_spd_1     = Passthru01;
veh_spd_2     = Passthru02;
mot_amps      = Passthru03;
throttle      = Passthru04;
mot_spd       = Passthru05;
wheel_FR      = Passthru06;
wheel_FL      = Passthru07;
veh_spd_3     = Passthru08;
batt_12_volts = Passthru09;
brk_force     = Passthru10;
clim_pwr      = Passthru11;
SOC           = Passthru12;
SOH           = Passthru13;
GIDs          = Passthru14;
odometer      = Passthru15;

%% Clear Vars
clear -regexp ^Passthru;
