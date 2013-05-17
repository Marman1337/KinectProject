function [ score_pos_av, score_vel_av, score_pos_joint, score_vel_joint, teacher_pos, student_pos ] = get_score( teacher_pos, student_pos, delay )
    
    % Align signals according to the delay
    [teacher_pos, student_pos] = align_signals(teacher_pos, student_pos, delay);
    % Truncate longest signal
    teacher_len = numel(teacher_pos(:,1));
    student_len = numel(student_pos(:,1));

    if teacher_len > student_len
        teacher_pos = teacher_pos(1:student_len,:);
        len = student_len;
    else
        student_pos = student_pos(1:teacher_len,:);
        len = teacher_len;
    end

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

    % Get derivative vector (velocity)
    teacher_vel = zeros(len-1, 60);
    student_vel = zeros(len-1, 60);
    for i = 1:60    
        teacher_vel(:,i) = get_diff(teacher_pos(:,i));
        student_vel(:,i) = get_diff(student_pos(:,i));
    end

    error_vel = teacher_vel - student_vel;
    error_vel_sqr = error_vel.^2;
    sum_error_vel_sqr = sum(error_vel_sqr);
    sum_teacher_vel_sqr = sum(teacher_vel.^2);
    score_vel = sum_error_vel_sqr./sum_teacher_vel_sqr;

    score_vel_joint = zeros(1,15);
    % Score based on position for each joint
    for i = 0:14
        sum_score = score_vel(4*i+1);
        sum_score = sum_score + score_vel(4*i+2);
        sum_score = sum_score + score_vel(4*i+3);  
        score_vel_joint(i+1) = sum_score/3;
    end
    % Average score based on position
    score_vel_av = sum(score_vel_joint)/15;

end