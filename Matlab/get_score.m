function [ score_window, score_window_av, score_pos_av, score_pos_joint, teacher_pos, student_pos ] = get_score( teacher_pos, student_pos, delay, num_windows )
   
    % Align signals according to the delay
    [teacher_pos, student_pos, signal_len] = align_truncate(teacher_pos, student_pos, delay);

  
    % WITH MEAN
    % Initial position error for each joint (x, y, z)
    error_start_pos_sqr = (teacher_pos(1, :) - student_pos(1, :)).^2/teacher_pos(1, :).^2;
    
    % Mean of student and teacher to be subtracted from signal
    teacher_pos_mean = mean(teacher_pos);
    student_pos_mean = mean(student_pos);
    
    % Positions - mean
    for i = 1:signal_len
        teacher_pos(i, :) = teacher_pos(i, :) - teacher_pos_mean;
        student_pos(i, :) = student_pos(i, :) - student_pos_mean;
    end    
%         
    % Find score using error squared pos
    error_pos = teacher_pos - student_pos;
    error_pos_sqr = error_pos.^2;
    sum_error_pos_sqr = sum(error_pos_sqr);
    sum_teacher_pos_sqr = sum(teacher_pos.^2);
    score_pos = sum_error_pos_sqr./sum_teacher_pos_sqr;

    score_pos_joint = zeros(1,15);
    
    % Score based on position for each joint
    for i = 0:14
        sum_score = score_pos(4*i+1);
        sum_score = sum_score + score_pos(4*i+2);
        sum_score = sum_score + score_pos(4*i+3);  
        score_pos_joint(i+1) = sum_score/3;
    end
    % Average score based on position
    score_pos_av = sum(score_pos_joint)/15;
    
    window_len = floor(signal_len/num_windows);
    score_window = zeros(num_windows, 60);

    for j = 1:num_windows
        error_window = teacher_pos((j-1)*window_len+1:j*window_len, : ) - student_pos((j-1)*window_len+1:j*window_len, : ); 
        error_window_sqr = error_window.^2;
        sum_error_window_sqr = sum(error_window_sqr);
        sum_teacher_window_sqr = sum(teacher_pos((j-1)*window_len+1:j*window_len, :  ).^2);
        score_window(j, :) = sum_error_window_sqr./sum_teacher_window_sqr; 
    end

    score_window_joint = zeros(num_windows,15);
    
    % Score based on position for each joint
    for i = 0:14
        sum_score = score_window(:,4*i+1);
        sum_score = sum_score + score_window(:, 4*i+2);
        sum_score = sum_score + score_window(:, 4*i+3);  
        score_window_joint(:, i+1) = sum_score/3;
    end    

    % Average score based on position
    score_window_av = sum(score_window_joint, 2)/15;    


end