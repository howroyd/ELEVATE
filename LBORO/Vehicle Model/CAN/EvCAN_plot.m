%% Plot Speed Data
clf;
subplot(2,1,1)
plot(time, whl_spd_L);
hold on;
plot(time, whl_spd_R);
plot(time, whl_spd_ave);
hold off;

grid on;
xlabel('Time /s');
ylabel('Speed');
l = legend('whl_spd_L','whl_spd_R','whl_spd_ave');
set(l, 'Interpreter', 'none');
set(l, 'Location', 'northwest');

%% Plot Control Data
subplot(2,1,2)
plot(time, mot_amps_1);
hold on;
plot(time, mot_amps_2);
plot(time, batt_amps);
hold off;

grid on;
xlabel('Time /s');
l = legend('mot_amps_1','mot_amps_2','batt_amps');
set(l, 'Interpreter', 'none');
set(l, 'Location', 'northwest');

%% Clear vars
clear l ax h1 h2
