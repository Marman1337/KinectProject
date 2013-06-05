function [ training_set, cv_set, test_set ] = split_data_set( input_data )
%% Splits data set, (x, y) tuples, into 3 other matrices. One for training (60%),
%  one for cross validation (20%) and the rest for testing (20%).
    
    num_samples = size(input_data, 1);
    % Get random indices in the range of the number of rows of the input
    % data.
    rand_indices = randperm(num_samples);
    
    training_set_end_index = floor(0.6 * num_samples);
    cv_set_end_index = floor(0.8 * num_samples);
    test_set_end_index = num_samples;
    
    training_set = input_data(rand_indices(1:training_set_end_index),:);
    cv_set = input_data(rand_indices(training_set_end_index+1:cv_set_end_index),:);
    test_set = input_data(rand_indices(cv_set_end_index+1:test_set_end_index),:);
    

end

