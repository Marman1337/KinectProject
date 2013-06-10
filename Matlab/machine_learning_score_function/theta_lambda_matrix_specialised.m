function [ theta_lambda_mat ] = theta_lambda_matrix_specialised( training_set, lambda_range, iterations, alpha, theta_order  )
    theta_lambda_mat = zeros(theta_order+1, size(lambda_range, 2));
    training_x = training_set(:, 1);
    training_y = training_set(:, 2);
    X = polynomial_matrix(training_x, theta_order);
    
    theta = [100;zeros(theta_order, 1)];
    j = 1;
    for lambda = lambda_range
        theta_lambda_mat(:, j) = gradient_descent_specialised_regularised(X, training_y, theta, alpha, iterations, lambda);
        j = j + 1;
    end
end

