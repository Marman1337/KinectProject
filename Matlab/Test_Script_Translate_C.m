%% Check if translate function of C++ code works to within a reasonable error

load DataFiles/translate_results.txt
load DataFiles/teacher_new.txt

% Max error between results of C++ and Matlab
max_error = 0.001;
% Results from Matlab
teacher_translated_actual = translate(teacher_new, 30);
% If they are equal
are_equal = compare_matrices(teacher_translated_actual, translate_results, max_error);