function [ min_index ] = get_motionless_frame( data_vec, win_len )
    % Returns the frame index with the least amount of motion
    % from a data vector for a single joint. This is to find the point at
    % which the student is standing still. 
    % Window length should be less than half the number of frames per second
    % assuming that the subject stands still for 1 second.

    % Find the remainder when divided by win_len.
    % To have an exact fit to the number of windows. 
    % (To make sure we do not get an out of bound error in for loop.)
    r = mod(numel(data_vec),win_len); 
    % Chop the last r elements off the vector.
    data_vec = data_vec(1:numel(data_vec)-r);
    % Length of the data vector
    data_len = numel(data_vec);
    % Initialise the minimum window to 1
    min_window = 1;

    % For each window in the data vector
    % for 15 seconds.
    for i = 1:min([floor(450/win_len), data_len/win_len])
        % Get the new window
        win_arr = data_vec((i-1)*win_len+1:i*win_len);

        % Get cost of window
        cost = sum(abs(get_diff(win_arr)));

        if(i == 1)
            min_cost = cost;
        else
            if(min_cost > cost)
                min_cost = cost;
                min_window = i;
            end
        end

    end

    % Find the min index
    min_index = (min_window-1)*win_len+1;
    
end