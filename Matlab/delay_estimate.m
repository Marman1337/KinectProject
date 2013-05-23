function [ delay_est ] = delay_estimate( data_joints_1, data_joints_2 )
    % compute cross-correlations for all the axes of each joint
    % delay between signals are found
    % make an array of delays

    % For every joint
    delay_joints = zeros(1,60);
    for i = 1:60
        % Skip correlation of z-dimension and the confidence vector
        if(mod(i,4) ==  0 || mod(i,4) == 3)
            continue;
        end
        % Find the maximum value and the index of the correlation
        [~,index_of_max] = max(xcorr(data_joints_1(:,i),data_joints_2(:,i)));
        % Save into an estimate of delays for each joint
        delay_joints(i) = index_of_max;
    end;

    x_delay = zeros(1,15);
    y_delay = zeros(1,15);

    % extract x and of y axis delays for each joint
    for j = 0:14
        x_delay(j+1) = delay_joints(j*4+1);
        y_delay(j+1) = delay_joints(j*4+2);
    end;

    % find the centre of cross-correlation results
    cor_length = length(xcorr(data_joints_1(:,1),data_joints_2(:,1)));
    offset_pt = round(cor_length/2);

    % remove the cross-correlation offset
    x_delay = x_delay - offset_pt;
    y_delay = y_delay - offset_pt;

    % Calculate the mean and std of the delay offsets, and use them later
    % to estimate the delay only using the values which lie within one
    % standard deviation from the mean, i.e. eliminate outliers
    x_mean = mean(x_delay);
    y_mean = mean(y_delay);
    x_std = std(x_delay);
    y_std = std(y_delay);

    % Identify outliers, accumulate the delays which are within one std
    sum_del = 0;
    count_el = 0;
    for i = 1:15
        if(x_delay(i) < x_mean + x_std && x_delay(i) > x_mean - x_std)
            sum_del = sum_del + x_delay(i);
            count_el = count_el + 1;
        end
        if(y_delay(i) < y_mean + y_std && y_delay(i) > y_mean - y_std)
            sum_del = sum_del + y_delay(i);
            count_el = count_el + 1;
        end
    end
    
    % Estimate the frame shift by averaging
    delay_est = round(sum_del / count_el);

end
