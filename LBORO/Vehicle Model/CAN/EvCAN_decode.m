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


% x=false;
% if x
% 
%     mot_amps_1   = convert_to_signed(Passthru04.*10, 12); % 2's
%     mot_amps_2   = convert_to_signed(Passthru06.*10, 12); % 2's
%     batt_amps    = convert_to_signed(Passthru08.*10, 11); % 2's
% else
    mot_amps_1   = Passthru04.*10 - 2048; % 2's
    mot_amps_2   = Passthru06.*10 - 2048; % 2's
    batt_amps    = Passthru08.*10 - 1024; % 2's
%end

ac_pwr       = Passthru01.*10;
ptc_pwr      = Passthru02.*10;
SOC          = Passthru03.*10;
inv_volts    = Passthru05.*10;
mot_spd      = Passthru07.*10;
batt_volts   = Passthru09.*10;
hv_pwr_avail = Passthru10.*10;
whl_spd_L    = Passthru11.*10;
whl_spd_R    = Passthru12.*10;
whl_spd_ave  = Passthru13.*10;
%GIDs          = Passthru14;
%odometer      = Passthru15;

%% Clear Vars
clear -regexp ^Passthru;