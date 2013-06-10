function [ theta_new ] = gradient_descent(X, y, theta, alpha, iterations)
    m = size(y, 1);
    
    for i = 1:iterations
        theta_temp = theta - alpha/m * X' * (X*theta-y);
        theta = theta_temp;
    end
    
    theta_new = theta;
end

