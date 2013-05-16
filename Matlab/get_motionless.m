function frame = get_motionless(data_mat,win_len)
    % Finds the motionless frame using the get_motionless_frame function on
    % the limb joints and finding the value with the highest absolute
    % frequency.
    values = zeros(1,24);

    % left elbow
    values(1) = get_motionless_frame(data_mat(:,17),win_len);
    values(2) = get_motionless_frame(data_mat(:,18),win_len);
    values(3) = get_motionless_frame(data_mat(:,19),win_len);
    % right elbow
    values(4) = get_motionless_frame(data_mat(:,21),win_len);
    values(5) = get_motionless_frame(data_mat(:,22),win_len);
    values(6) = get_motionless_frame(data_mat(:,23),win_len);
    % left hand
    values(7) = get_motionless_frame(data_mat(:,25),win_len);
    values(8) = get_motionless_frame(data_mat(:,26),win_len);
    values(9) = get_motionless_frame(data_mat(:,27),win_len);
    % right hand
    values(10) = get_motionless_frame(data_mat(:,29),win_len);
    values(11) = get_motionless_frame(data_mat(:,30),win_len);
    values(12) = get_motionless_frame(data_mat(:,31),win_len);
    % left knee
    values(13) = get_motionless_frame(data_mat(:,45),win_len);
    values(14) = get_motionless_frame(data_mat(:,46),win_len);
    values(15) = get_motionless_frame(data_mat(:,47),win_len);
    % left foot
    values(16) = get_motionless_frame(data_mat(:,49),win_len);
    values(17) = get_motionless_frame(data_mat(:,50),win_len);
    values(18) = get_motionless_frame(data_mat(:,51),win_len);
    % right knee
    values(19) = get_motionless_frame(data_mat(:,53),win_len);
    values(20) = get_motionless_frame(data_mat(:,54),win_len);
    values(21) = get_motionless_frame(data_mat(:,55),win_len);
    % right foot
    values(22) = get_motionless_frame(data_mat(:,57),win_len);
    values(23) = get_motionless_frame(data_mat(:,58),win_len);
    values(24) = get_motionless_frame(data_mat(:,59),win_len);

    % get unique frame numbers in values array
    unique_el = unique(values);

    % get frequency count of each value in the value array
    h = histc(values, unique_el);

    % get the most frequently occuring frame's index
    [~, index] = max(h);

    % return the starting frame
    frame = unique_el(index);

end