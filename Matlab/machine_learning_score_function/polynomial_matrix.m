function [ x_mat ] = polynomial_matrix( x_vec, order )
%% Returns a matrix where each column is the column x_vec raised to the
%  column index -1.

    x_mat = zeros(size(x_vec, 1), order+1);
    x_mat(:, 1:2) = [ones(size(x_vec, 1), 1) x_vec];
    
    if order >= 2
        for i = 2:order
            x_mat(:, i+1) = x_vec.^i; 
        end
    end

end

