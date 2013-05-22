function [ diff_mat ] = get_diff( input_mat)

    % Get length of the input matrix
    num_rows = size(input_mat, 1);
    num_cols = size(input_mat, 2);

    if num_rows == 1
        input_mat = input_mat';
        temp = num_rows;
        num_rows = num_cols;
        num_cols = temp;
    end

    % Difference array will have one less element
    diff_mat = zeros(num_rows-1,num_cols);
    

    for i = 1:num_rows-1
        diff_mat(i, :) = input_mat(i, :) - input_mat(i+1, :);
        if diff_mat(i, :) == 0
            diff_mat(i) = 100000;
        end
    end


end