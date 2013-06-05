function [ theta_mat ] = theta_order_matrix( training_set, max_order, iterations, alpha )
%% Returns an output matrix of theta. Each column is the value taken by theta
%  if theta is to take an order equal to the column's index.

    theta_mat = zeros(max_order+1, max_order);

%     theta_temp = zeros(max_order+1);
    training_x = training_set(:, 1);
    training_y = training_set(:, 2);
    

    % For each order get values of theta
    for order = 1:max_order
        X = polynomial_matrix(training_x, order);
        theta = zeros(order+1,1);
        theta_mat(:, order) = [gradient_descent(X, training_y, theta, alpha, iterations); zeros(max_order-order, 1)];      
    end

end

