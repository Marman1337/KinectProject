function [ theta_new ] = gradient_descent_specialised_regularised(X, y, theta, alpha, iterations, lambda)
%% Does gradient descent without changing theta(1). For the specialised case when 
%  the y intercept is known. Also uses regularisation.
    m = size(y, 1);
    theta_temp = theta;
    
    for i = 1:iterations
        sop = X' * (X*theta-y);
        theta_temp(2:end) = theta(2:end) - alpha/m * (sop(2:end) + lambda*theta(2:end));
        theta = theta_temp;
    end
    
    theta_new = theta;
end

