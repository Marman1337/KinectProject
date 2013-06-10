function [ J ] = compute_cost_regularised(X, y, theta, lambda)
%% Calculates the cost of using the column vector theta on the data of
%  X (mxn matrix) to give y (mx1 vector).
    m = size(y, 1);
    J = 1/(2*m) * (sum((X*theta-y).^2) + lambda* sum(theta.^2));
end

