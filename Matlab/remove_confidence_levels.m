function [ output_mat ] = remove_confidence_levels( input_mat)
    num_rows = size(input_mat, 1);
    num_cols = size(input_mat, 2);
    output_mat = zeros(num_rows, ceil(num_cols*0.75));
    j = 1;
    for i = 1:num_cols
        if mod(i, 4) ~=0
            output_mat(:, j) = input_mat(:, i);
            j = j + 1;
        end
    end
end

