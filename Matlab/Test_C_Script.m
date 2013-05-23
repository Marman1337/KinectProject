
%% Load Data

if(ischar(input_file_teacher))
    teacher_mat = importdata(input_file_teacher);
end
if(ischar(input_file_student))
    student_mat = importdata(input_file_student);
end

%% get motionless frame for each file
motionless_frame_teacher = get_motionless(teacher_mat, 30);
motionless_frame_student = get_motionless(student_mat, 30);

%% C++ file of Initial Frame Detector result should also be generated and 
%  should be tested against the Matlab results.

fprintf('Testing Motionless Frame Detector.\n');
motionless_frame_teacher_c = importdata('motionless_teacher_c.txt');
motionless_frame_student_c = importdata('motionless_student_c.txt');

if motionless_teacher == motionless_frame_teacher_c
    fprintf('  Motionless frame of teacher is correct.\n');
end
if motionless_student == motionless_frame_student_c
    fprintf('  Motionless frame of student is correct.\n');
end


%% translate both files
teacher_translated = translate(teacher_mat, motionless_frame_teacher);
student_translated = translate(student_mat, motionless_frame_student);

%% C++ file of Translation Module results should also be generated and 
%  should be tested against the Matlab results.

fprintf('Testing Translation Module.\n');
teacher_translated_c = importdata('teacher_translated_c.txt');
student_translated_c = importdata('student_translated_c.txt');

if teacher_translated == teacher_translated_c
    fprintf('  Translated signal of teacher is correct.\n');
end
if student_translated == student_translated_c
    fprintf('   Translated signal of student is correct.\n');
end

%% Find the estimate of the delay so that the signals can be aligned
delay_est = delay_estimate(teacher_translated, student_translated);

%% C++ file of Delay Estimate results should also be generated and 
%  should be tested against the Matlab results.

fprintf('Testing Delay Estimate.\n');
delay_estimate_c = importdata('delay_estimate_c.txt');

if delay_est == delay_estimate_c
    fprintf('  Delay Estimate is correct.\n');
end


%% shift one of the signals so that there is little mismatch between
%  them
[teacher, student] = align_signals(teacher_translated, student_translated, delay_est); 

%% C++ file of Alignment Module results should also be generated and 
%  should be tested against the Matlab results.

fprintf('Testing Alginment Module.\n');
teacher_aligned_c = importdata('teacher_aligned_c.txt');
student_aligned_c = importdata('student_aligned_c.txt');

if teacher_aligned == teacher_aligned_c
    fprintf('  Aligned Signal of teacher is correct.\n');
else
    if size(teacher_aligned_c, 1) ~= size(teacher, 1);
         fprintf('  ERROR: Size mismatch between teacher signals.\n');
    end
end
if student_aligned == student_aligned_c
    fprintf('  Aligned Signal of student is correct.\n');
else
    if size(student_aligned_c, 1) ~= size(student, 1);
         fprintf('  ERROR: Size mismatch between student signals.\n');
    end
end

%% We give a maximum threshold of (+/-)1/3 seconds for the dances to be
% apart. This is represented as 21 different delay values.
score_arr = zeros(1, 21);
for i = -10:10
    score_arr(i+11) = get_score(teacher, student, i);
end

%% identify the best score and present the signals with their best
% possible alignment
[~,min_index] = min(score_arr);
min_delay = min_index - 11;
[opt_teacher, opt_student] = align_signals(teacher, student, min_delay);

%% C++ file of Optimal Aligned Signals results should also be generated and 
%  should be tested against the Matlab results.

fprintf('Testing Optimal Alginment Module.\n');
teacher_opt_aligned_c = importdata('teacher_opt_aligned_c.txt');
student_opt_aligned_c = importdata('student_opt_aligned_c.txt');

if opt_teacher == teacher_opt_aligned_c
    fprintf('  Optimally Aligned Signal of teacher is correct.\n');
else
    if size(teacher_aligned_c, 1) ~= size(teacher, 1);
         fprintf('  ERROR: Size mismatch between teacher signals.\n');
    end
end
if opt_student == student_opt_aligned_c
    fprintf('  Optimally Aligned Signal of student is correct.\n');
else
    if size(student_aligned_c, 1) ~= size(student, 1);
         fprintf('  ERROR: Size mismatch between student signals.\n');
    end
end

%% get windowed score for the best alignment
[score_window, score_window_av, score_window_joint] = get_score_window(opt_teacher, opt_student, 10);

%% NEED TO ADD TEST FOR SCORES

