%% Script that calls the wrapper function on all of the cases that we have for the data analysis section
%  and then saves all the variables.

[score_w_coordinate_correct, score_w_av_correct, s_window_joint_correct, score_arr_correct, teacher_correct, student_correct]=wrapper('teacher_new.txt','case1_new.txt');
[score_w_coordinate_mistake, score_w_av_mistake, s_window_joint_mistake, score_arr_mistake, teacher_mistake, student_mistake]=wrapper('teacher_new.txt','case2_new.txt');
[score_w_coordinate_error, score_w_av_error, s_window_joint_error, score_arr_error, teacher_error, student_error]=wrapper('teacher_new.txt','case3_new.txt');
[score_w_coordinate_off, score_w_av_off, s_window_joint_off, score_arr_off, teacher_off, student_off]=wrapper('teacher_new.txt','case4_new.txt');
figure;
bar_chart = [mean(score_function(10, 3, score_w_av_correct)) mean(score_function(10, 3, score_w_av_mistake)) mean(score_function(10, 3, score_w_av_error)) mean(score_function(10, 3, score_w_av_off))];
bar(bar_chart);
xlabel('Case Number');
ylabel('Average Normalised Error');
title('Bar chart of case number vs the average normalised error for 4 different cases');



%% Plot graphs of normalised error vs window number for each of the test cases
figure;
subplot(2,2,1);
bar(score_function(10, 3, score_w_av_correct));
title('Plot square root of the normalised error of Case 1 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');

%axis([1 10 0 30]);
subplot(2,2,2);
bar(score_function(10, 3,score_w_av_mistake));
title('Plot of the normalised error of Case 2 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');
%axis([1 10 0 30]);

subplot(2,2,3);
bar(score_function(10, 3,score_w_av_error));
title('Plot of the normalised error squared of Case 3 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');
%axis([1 10 0 30]);


subplot(2,2,4);
bar(score_function(10, 3,score_w_av_off));

title('Plot square root of the normalised error of Case 4 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');
%axis([1 10 0 30]);
