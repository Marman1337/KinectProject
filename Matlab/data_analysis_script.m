%% Script that calls the wrapper function on all of the cases that we have for the data analysis section
%  and then saves all the variables.

[score_w_coordinate_correct, score_w_av_correct, s_window_joint_correct, score_arr_correct, teacher_correct, student_correct]=wrapper('./DataFiles/teacher_new.txt','./DataFiles/case1_new.txt');
[score_w_coordinate_mistake, score_w_av_mistake, s_window_joint_mistake, score_arr_mistake, teacher_mistake, student_mistake]=wrapper('./DataFiles/teacher_new.txt','./DataFiles/case2_new.txt');
[score_w_coordinate_error, score_w_av_error, s_window_joint_error, score_arr_error, teacher_error, student_error]=wrapper('./DataFiles/teacher_new.txt','./DataFiles/case3_new.txt');
[score_w_coordinate_off, score_w_av_off, s_window_joint_off, score_arr_off, teacher_off, student_off]=wrapper('./DataFiles/teacher_new.txt','./DataFiles/case4_new.txt');
bar_chart_error = [min(score_w_av_correct) min(score_w_av_mistake) min(score_w_av_error) min(score_w_av_off)];
% bar_chart = [mean(score_function(10, 3, score_w_av_correct)) mean(score_function(10, 3, score_w_av_mistake)) mean(score_function(10, 3, score_w_av_error)) mean(score_function(10, 3, score_w_av_off))];
bar_chart = [mean(score_function( score_w_av_correct)) mean(score_function( score_w_av_mistake)) mean(score_function(score_w_av_error)) mean(score_function( score_w_av_off))];

figure;
subplot(1,2,1);
bar(bar_chart_error, 'r');
xlabel('Case Number');
ylabel('Average Normalised Error');
title('Bar chart of Normalised Error vs Case Number for 4 different cases');
subplot(1,2,2);
bar(bar_chart);
xlabel('Case Number');
ylabel('Average Score');
title('Bar chart of Average Score vs Case Number for 4 different cases');



%% Plot graphs of normalised error vs window number for each of the test cases
figure;
subplot(2,2,1);
bar(score_function(score_w_av_correct));

title('Plot square root of the normalised error of Case 1 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');

subplot(2,2,2);
bar(score_function(score_w_av_mistake));

title('Plot of the normalised error of Case 2 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');

subplot(2,2,3);
bar(score_function(score_w_av_error));
title('Plot of the normalised error squared of Case 3 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');

subplot(2,2,4);
bar(score_function(score_w_av_off));
title('Plot square root of the normalised error of Case 4 for 10 windows')
ylabel('Normalised error');
xlabel('Window Number');
