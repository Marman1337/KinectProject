function [ theta, best_lambda_index ] = lambda_least_cost( cv_set, theta_lambda_mat )
    x = cv_set(:, 1);
    y = cv_set(:, 2);
    order = size(theta_lambda_mat, 1)-1;
    X = polynomial_matrix(x, order);    
    for lambda_index = 1:size(theta_lambda_mat, 2)
        curr_theta = theta_lambda_mat(:, lambda_index);
        curr_cost = compute_cost(X, y, curr_theta); 
        
        if lambda_index == 1
            old_cost = curr_cost;
            best_lambda_index = lambda_index;
        elseif curr_cost < old_cost
            old_cost = curr_cost;
            best_lambda_index = lambda_index;
        end     
    end
    theta = theta_lambda_mat(:, best_lambda_index);

end

