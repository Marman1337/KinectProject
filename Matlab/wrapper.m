function [ score_window, score_window_av, score_window_joint, score_arr , opt_teacher, opt_student ] = wrapper(input1, input2)

    % import data if not already in a matrix
    if(ischar(input1))
        input1 = importdata(input1);
    end
    if(ischar(input2))
        input2 = importdata(input2);
    end

    % get motionless frame for each file
    frame1 = get_motionless(input1, 30);
    frame2 = get_motionless(input2, 30);

    % translate both files
    translated1 = translate(input1,frame1);
    translated2 = translate(input2,frame2);
    
    % Find the estimate of the delay so that the signals can be aligned
    delay_est = delay_estimate(translated1, translated2);
    % shift one of the signals so that there is little mismatch between
    % them
    [teacher, student] = align_signals(translated1, translated2, delay_est); 
   
    % We give a maximum threshold of (+/-)1/3 seconds for the dances to be
    % apart. This is represented as 21 different delay values.
    score_arr = zeros(1, 21);
    for i = -10:10
        score_arr(i+11) = get_score(teacher, student, i);
    end
    
    % identify the best score and present the signals with their best
    % possible alignment
    [~,min_index] = min(score_arr);
    min_delay = min_index - 11;
    [opt_teacher, opt_student] = align_signals(teacher, student, min_delay);
    
    % get windowed score for the best alignment
    [score_window, score_window_av, score_window_joint] = get_score_window(opt_teacher, opt_student, 10);

end
