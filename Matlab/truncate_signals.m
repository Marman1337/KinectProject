function [ teacher_pos, student_pos, signal_len ] = truncate_signals( teacher_pos, student_pos )

    % Truncate longer signal to match the shorter one
    teacher_len = numel(teacher_pos(:,1));
    student_len = numel(student_pos(:,1));

    if teacher_len > student_len
        teacher_pos = teacher_pos(1:student_len,:);
        signal_len = student_len;
    else
        student_pos = student_pos(1:teacher_len,:);
        signal_len = teacher_len;
    end

end

