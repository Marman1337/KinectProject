function [ are_equal ] = compare_matrices( mat_A, mat_B, max_error )
    % Compares if the two matrices, mat_A and mat_B, are equal element-wise to
    % within the max_error argument. Returns 1 if true and 0 if false.
    gt = all(all(mat_A > (mat_B - max_error)));
    lt = all(all(mat_A < (mat_B + max_error)));
    
   
    are_equal = gt && lt;
    
end

