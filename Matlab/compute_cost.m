function [ J ] = compute_cost(X, y, theta)
%% Calculates the cost of using the column vector theta on the data of
%  X (mxn matrix) to give y (mx1 vector).
    m = size(y, 1);
    J = 1/(2*m) * sum((X*theta-y).^2);
end

