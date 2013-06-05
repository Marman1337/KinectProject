function [ theta, best_order ] = order_theta_least_cost( cv_set, theta_mat )
    
    x = cv_set(:, 1);
    y = cv_set(:, 2);
    for order = 1:size(theta_mat, 2)
        X = polynomial_matrix(x, order);
        curr_theta = theta_mat(:, order);
        curr_cost = compute_cost(X, y, curr_theta(1:order+1)); 
        
        if order == 1
            old_cost = curr_cost;
            best_order = order;
        elseif curr_cost < old_cost
            old_cost = curr_cost;
            best_order = order;
        end     
    end
    theta = theta_mat(:, best_order);
    theta = theta(1:best_order+1);

end

