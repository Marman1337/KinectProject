function [ score_window, score_window_av, score_window_joint ] = get_score_window( teacher_pos, student_pos, num_windows )
    
    % Truncate the longer signal to match the shorter one
    [teacher_pos, student_pos, signal_len] = truncate_signals(teacher_pos, student_pos);

    % Windowed score for the number of windows
    window_len = floor(signal_len/num_windows);
    score_window = zeros(num_windows, 60);
    
    for j = 1:num_windows
        old_mean = 1e+15;
        for i = -10:10
            if((j-1)*window_len+1+i < 1 || j*window_len+i > signal_len)
                continue;
            end
            error_window = teacher_pos((j-1)*window_len+1:j*window_len, : ) - student_pos((j-1)*window_len+1+i : j*window_len+i, : );
            error_window_sqr = error_window.^2;
            sum_error_window_sqr = sum(error_window_sqr);
            current_score = sum_error_window_sqr./(3*10000*window_len);
            mean_score = mean(remove_confidence_levels(current_score)); % 1x45
            if(mean_score*penalise_jitter(i) < old_mean)
               old_mean = mean_score*penalise_jitter(i);
               score_window(j, :) = current_score*penalise_jitter(i);
            end
        end
    end
    
    % Score based on position for each joint
    score_window_joint = zeros(num_windows,15); % preallocate
    for i = 0:14
        sum_score = score_window(:,4*i+1);
        sum_score = sum_score + score_window(:, 4*i+2);
        sum_score = sum_score + score_window(:, 4*i+3);  
        score_window_joint(:, i+1) = sum_score/3;
    end    

    % Average score based on position
    score_window_av = sum(score_window_joint, 2)/15;

end

