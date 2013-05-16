function [ delay_est ] = delay_estimate( data_joints_1, data_joints_2 )
    % compute cross-correlations for all the axes of each joint
    % delay between signals are found
    % make an array of delays

    % For every joint
    delay_joints = zeros(1,60);
    for i = 1:60
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

    % calculate overall average delay
    delay_est = round((sum(x_delay)/numel(x_delay) + sum(y_delay)/numel(y_delay))/2);


end

