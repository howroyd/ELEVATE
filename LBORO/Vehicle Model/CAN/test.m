

for i=1:length(mot_amps_2)
    mot_amps_2_unparsed(i) = uint16(mot_amps_2(i)) - 2^11;
end

mot_amps_2_parsed   = convert_to_signed(mot_amps_2_unparsed, 12);

subplot(2,1,1);
plot(time, mot_amps_2_unparsed);
subplot(2,1,2);
plot(time, mot_amps_2_parsed);