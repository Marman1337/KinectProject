function [ theta_new ] = gradient_descent_specialise(X, y, theta, alpha, iterations)
%% Does gradient descent without changing theta(1). For the specialised case when 
% the y intercept is known.
    m = size(y, 1);
    theta_temp = theta;
    
    for i = 1:iterations
        sop = X' * (X*theta-y);
        theta_temp(2:end) = theta(2:end) - alpha/m * sop(2:end) ;
        theta = theta_temp;
    end
    
    theta_new = theta;
end

