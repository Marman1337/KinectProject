function [signal_1_correct, signal_2_correct] = align_signals( signal_1, signal_2, delay_est )
    % Shift the relevant data set by the amount of delay
    % If delay is positive shift the first set of data points, vice versa
    if delay_est >= 0
       signal_1_correct = signal_1(delay_est:length(signal_1),:);
       signal_2_correct = signal_2;
    else
       signal_2_correct = signal_2(delay_est:length(signal_2),:);
       signal_1_correct = signal_1;
    
    end

end

