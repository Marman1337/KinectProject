function [ score_pos_av, score_pos_joint, teacher_pos, student_pos ] = get_score( teacher_pos, student_pos, delay )
   
    % Align signals according to the delay
    [teacher_pos, student_pos] = align_signals(teacher_pos, student_pos, delay);
    % Truncate the longer signal so that both signals are of the same
    % length
    [teacher_pos, student_pos, signal_len] = truncate_signals(teacher_pos, student_pos);
      
    % Find simple score for the entire signal using error squared pos
    error_pos = teacher_pos - student_pos;
    error_pos_sqr = error_pos.^2;
    sum_error_pos_sqr = sum(error_pos_sqr);
   
    score_pos = sum_error_pos_sqr./(signal_len);
    
    % Score based on position for each joint
    score_pos_joint = zeros(1,15); % preallocate
    for i = 0:14
        sum_score = score_pos(4*i+1);
        sum_score = sum_score + score_pos(4*i+2);
        sum_score = sum_score + score_pos(4*i+3);  
        score_pos_joint(i+1) = sum_score/3;
    end
    % Average score based on position
    score_pos_av = sum(score_pos_joint)/15;
   
end
