function [ val_out ] = convert_to_signed( val_in, bytelength )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
val = uint16(val_in);

val_out = double(0);

for i=1:length(val)
    
    isNegative =  bitget(val(i),bytelength-1);
    
    if isNegative
        temp = int16(0);
        for j=1:bytelength
            temp = bitset(temp, j, ~bitget(val(i),j));
        end
        temp = (temp+1);
        val_out(i) = double(temp) * -1 + 2^(bytelength-1);
        disp(sprintf('old=%d, new=%d\n',val(i), val_out(i)))
        %val_out(i) = val_out(i) * -1;
    else
        val_out(i) = double(val(i));
    end
    

    
end
val_out = val_out';

end

