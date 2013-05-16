% compute cross-correlations for all the axes of each joint
% delay between signals are found
% make an array of delays

% find the delay between the signals for each joint

data_joints_1 = TestFile1;
data_joints_2 = TestFile2;

delay_est = delay_estimate(data_joints_1, data_joints_2);
[data_joints_1_correct, data_joints_2_correct] = align_signals(data_joints_1, data_joints_2, delay_est);