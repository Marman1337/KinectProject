function [ teacher_pos, student_pos, len ] = align_truncate( teacher_pos, student_pos, delay )

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


end

