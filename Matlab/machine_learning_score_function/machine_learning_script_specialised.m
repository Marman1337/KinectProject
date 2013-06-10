%% Input data: mx2 matrix of (x, y) tuples.
close all;
x =  0:0.025:1;

%% Add noise to data to resemble more realistic data.
y = build_polynomial([100 -20 -80]', x);
y = y + 4*randn(size(y));
y(1) = 100;
data_set = [x' y'];
plot(x, y, 'x');

%% Split data into 3 different sets for training, cross validation and
%  testing.
[training_set, cv_set, test_set] = split_data_set(data_set);

%% Find theta for different orders of hypothesis.
max_order = 7;
% Some gradient descent settings
iterations = 200000;
alpha = 0.001;
    
[ theta_order_mat ] = theta_order_matrix_specialised( training_set, max_order, iterations, alpha );

%% Find order of hypothesis that minimizes the cross validation cost function.
[ ~, best_order ] = order_theta_least_cost( cv_set, theta_order_mat );

%% -- Now we have the order. -- 

%% Iterate over different values of lambda to get the different values of theta.
lambda_range = [0.0001 0.001 0.01 0.1 0.2 0.4 0.8 1.6 3.2 6.4 12.8];
[ theta_lambda_mat ] = theta_lambda_matrix_specialised( training_set, lambda_range, iterations, alpha, best_order  );

%% Find theta which gives lowest cost. This will have the same index as the lambda
%  that gives the lowest cost. Use the cross validation cost function.
[ theta, best_lambda_index ] = lambda_least_cost( cv_set, theta_lambda_mat );
best_lambda = lambda_range(best_lambda_index);

%% Use test set and the test cost function to get average cost (error).
%  NOT DONE

%% Plot data
y_new = build_polynomial(theta ,x);
hold on;
plot(x, y_new, 'r');
title('Score vs Error');
legend('Data Set', 'Estimate');
xlabel('Error');
ylabel('Score');