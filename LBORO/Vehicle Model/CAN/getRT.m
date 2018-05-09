function [ names, data ] = getRT( input_args )

    VarNames = [];
    Data=[];

    %% Get raw file
    run(input_args);

    %% Parse
    % Multiply up by 100 to undo RT message scaling
    for i=2:22
        Data(:,i) = Data(:,i) .* 100.0;
    end
    
    names = split(VarNames, ']');
    
    for i=1:length(names)
        names(i) = strcat(names(i), ']');
    end
    
    names = names(1:end-1)';
    data = Data;
    
    names = horzcat(names(1:end,1:2-1), names(1:end,7+1:end));
    data = horzcat(data(1:end,1:2-1), data(1:end,7+1:end));
    
end

