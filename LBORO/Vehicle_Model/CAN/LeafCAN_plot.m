%% Plot Speed Data
clf;
subplot(2,1,1)
plot(time, veh_spd_1.*0.7895);
hold on;
plot(time, veh_spd_2.*0.0958);
plot(time, veh_spd_3.*0.0683);
plot(time, wheel_FR.*0.03308);
plot(time, wheel_FL.*0.03308);
hold off;

grid on;
xlabel('Time /s');
ylabel('Speed /mph');
l = legend('veh_spd_1','veh_spd_2','veh_spd_3','wheel_FR','wheel_FL');
set(l, 'Interpreter', 'none');
set(l, 'Location', 'southwest');

%% Plot Control Data
subplot(2,1,2)
plot(time, throttle./255.*100);
hold on;
plot(time, brk_force.*55./10);
plot(time, mot_amps.*176.23./30./10);
hold off;

grid on;
xlabel('Time /s');
l = legend('throttle %','brk_force (regen amps /10)','mot_amps /10');
set(l, 'Interpreter', 'none');
set(l, 'Location', 'southwest');

%% Clear vars
clear l ax h1 h2
