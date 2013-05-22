function [ diff_array ] = get_diff( input_arr)

    % Get length of the input array
    len_in = numel(input_arr);
    % Difference array will have one less element
    diff_array = zeros(1,len_in-1);
    
    for i = 1:len_in-1
        % Fill the difference array
        diff_array(i) = input_arr(i)-input_arr(i+1);
        if diff_array(i) == 0
            diff_array(i) = 100000;
        end
    end

end