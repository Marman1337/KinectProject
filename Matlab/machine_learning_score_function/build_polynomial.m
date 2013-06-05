function [ y ] = build_polynomial( coefficient_vec, range)
    j = 1;
    for i = range
        
        y(j) = polynomial_matrix(i, size(coefficient_vec, 1)-1)*coefficient_vec;
        j = j+1;
    end
end

