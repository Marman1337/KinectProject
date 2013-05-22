function [ score_av, score_joint, teacher_pos, student_pos ] = get_score( teacher_pos, student_pos, delay )
   
    % Align signals according to the delay
    [teacher_pos, student_pos] = align_signals(teacher_pos, student_pos, delay);
    % Truncate the longer signal so that both signals are of the same
    % length
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
         
    % Find simple score for the entire signal using error squared pos
    error_pos = teacher_pos - student_pos;
    error_pos_sqr = error_pos.^2;
    sum_error_pos_sqr = sum(error_pos_sqr);
    sum_teacher_pos_sqr = sum(teacher_pos.^2);
    score_pos = sum_error_pos_sqr./sum_teacher_pos_sqr;
    %score_pos = sum_error_pos_sqr./signal_len;

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

%     teacher_vel = -1.*get_diff(teacher_pos);
%     student_vel = -1.*get_diff(student_pos);
%     % Find simple score for the entire signal using error squared pos
%     error_vel = teacher_vel - student_vel;
%     error_vel_sqr = error_vel.^2;
%     sum_error_vel_sqr = sum(error_vel_sqr);
%     sum_teacher_pos_sqr = sum(teacher_pos.^2);
%     score_pos = sum_error_pos_sqr./sum_teacher_pos_sqr;
%     %score_vel = sum_error_vel_sqr./(signal_len-1);

%     % Score based on position for each joint
%     score_vel_joint = zeros(1,15); % preallocate
%     for i = 0:14
%         sum_score = score_vel(4*i+1);
%         sum_score = sum_score + score_vel(4*i+2);
%         sum_score = sum_score + score_vel(4*i+3);  
%         score_vel_joint(i+1) = sum_score/3;
%     end
%     % Average score based on position
%     score_vel_av = sum(score_vel_joint)/15;

%     score_av = score_pos_av.*0.5 + score_vel_av.*0.5;
%     score_joint = score_pos_joint .*0.5 + score_vel_joint.*0.5;
      score_joint = score_pos_joint;
      score_av = score_pos_av;
end
