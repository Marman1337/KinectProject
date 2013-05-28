%% Check if calculateCoordinateScoreWindow function of C++ code works to within a reasonable error

load DataFiles/coordinateScoreWindow.txt
load DataFiles/jointScoreWindow.txt
load DataFiles/avgScoreWindow.txt
load DataFiles/teacher_new.txt
load DataFiles/case4_new.txt

% Max error between results of C++ and Matlab
max_error = 0.001;
% Results from Matlab
[coordinate_score_window_matlab, avg_score_window_matlab, joint_score_window_matlab ] = get_score_window(teacher_new, case4_new, 10);
% If they are equal
are_equal_coordinate = compare_matrices(coordinate_score_window_matlab, coordinateScoreWindow, max_error);
are_equal_avg = compare_matrices(avg_score_window_matlab, avgScoreWindow, max_error);
are_equal_joint = compare_matrices(joint_score_window_matlab, jointScoreWindow, max_error);