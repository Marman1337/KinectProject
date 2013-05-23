function frame = get_motionless(data_mat,win_len)
    % Finds the motionless frame using the get_motionless_frame function on
    % the limb joints and finding the value with the highest absolute
    % frequency.
    values = zeros(1,24);

    % left elbow
    values(1) = get_motionless_frame(data_mat(:,index_of_joint('left_elbow')+0),win_len);
    values(2) = get_motionless_frame(data_mat(:,index_of_joint('left_elbow')+1),win_len);
    values(3) = get_motionless_frame(data_mat(:,index_of_joint('left_elbow')+2),win_len);
    % right elbow
    values(4) = get_motionless_frame(data_mat(:,index_of_joint('right_elbow')+0),win_len);
    values(5) = get_motionless_frame(data_mat(:,index_of_joint('right_elbow')+1),win_len);
    values(6) = get_motionless_frame(data_mat(:,index_of_joint('right_elbow')+2),win_len);
    % left hand
    values(7) = get_motionless_frame(data_mat(:,index_of_joint('left_hand')+0),win_len);
    values(8) = get_motionless_frame(data_mat(:,index_of_joint('left_hand')+1),win_len);
    values(9) = get_motionless_frame(data_mat(:,index_of_joint('left_hand')+2),win_len);
    % right hand
    values(10) = get_motionless_frame(data_mat(:,index_of_joint('right_hand')+0),win_len);
    values(11) = get_motionless_frame(data_mat(:,index_of_joint('right_hand')+1),win_len);
    values(12) = get_motionless_frame(data_mat(:,index_of_joint('right_hand')+2),win_len);
    % left knee
    values(13) = get_motionless_frame(data_mat(:,index_of_joint('left_knee')+0),win_len);
    values(14) = get_motionless_frame(data_mat(:,index_of_joint('left_knee')+1),win_len);
    values(15) = get_motionless_frame(data_mat(:,index_of_joint('left_knee')+2),win_len);
    % left foot
    values(16) = get_motionless_frame(data_mat(:,index_of_joint('left_foot')+0),win_len);
    values(17) = get_motionless_frame(data_mat(:,index_of_joint('left_foot')+1),win_len);
    values(18) = get_motionless_frame(data_mat(:,index_of_joint('left_foot')+2),win_len);
    % right knee
    values(19) = get_motionless_frame(data_mat(:,index_of_joint('right_knee')+0),win_len);
    values(20) = get_motionless_frame(data_mat(:,index_of_joint('right_knee')+1),win_len);
    values(21) = get_motionless_frame(data_mat(:,index_of_joint('right_knee')+2),win_len);
    % right foot
    values(22) = get_motionless_frame(data_mat(:,index_of_joint('right_foot')+0),win_len);
    values(23) = get_motionless_frame(data_mat(:,index_of_joint('right_foot')+1),win_len);
    values(24) = get_motionless_frame(data_mat(:,index_of_joint('right_foot')+2),win_len);

    % get unique frame numbers in values array
    unique_el = unique(values);

    % get frequency count of each value in the value array
    h = histc(values, unique_el);

    % get the most frequently occuring frame's index
    [~, index] = max(h);

    % return the starting frame
    frame = unique_el(index);

end