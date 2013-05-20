function [ score_window, score_window_av, score_window_joint ] = get_score_window( teacher_pos, student_pos, num_windows )
    
    % Truncate the longer signal to match the shorter one
    [teacher_pos, student_pos, signal_len] = truncate_signals(teacher_pos, student_pos);

    % WITH MEAN    
    % Mean of student and teacher to be subtracted from signal
    teacher_pos_mean = mean(teacher_pos);
    student_pos_mean = mean(student_pos);
    
    % Positions - mean
    for i = 1:signal_len
        teacher_pos(i, :) = teacher_pos(i, :) - teacher_pos_mean;
        student_pos(i, :) = student_pos(i, :) - student_pos_mean;
    end
    
    % Windowed score for the number of windows
    window_len = floor(signal_len/num_windows);
    score_window = zeros(num_windows, 60);

    for j = 1:num_windows
        error_window = teacher_pos((j-1)*window_len+1:j*window_len, : ) - student_pos((j-1)*window_len+1:j*window_len, : ); 
        error_window_sqr = error_window.^2;
        sum_error_window_sqr = sum(error_window_sqr);
        sum_teacher_window_sqr = sum(teacher_pos((j-1)*window_len+1:j*window_len, :  ).^2);
        score_window(j, :) = sum_error_window_sqr./sum_teacher_window_sqr; 
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

