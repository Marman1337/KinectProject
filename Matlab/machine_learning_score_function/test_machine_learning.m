
% %% Create training set
% x = [0; 1; 2; 5; 6; 7; 10];
% X = polynomial_matrix(x, 2);
% y = [100; 89; 76; 25; 4; -19; -100];
% 
% %% Create training set
% x = [0; 0.05; 0.075; 0.1; 0.2; 0.3; 0.35; 0.4; 0.45;0.36; 0.42; 0.41;0.362; 0.421; 0.49; 0.5; 0.6; 0.7; 0.85; 0.9; 1; 1.1; 1.2; 1.3; 1.4; 1.5];
% X = polynomial_matrix(x, 15);
% y = [100; 99; 98; 93; 86; 80; 72; 58; 57;72; 58; 57 ;72; 58; 57 ; 56; 50;  44; 30; 8; 2; 1.5; 1; 0.05; 0.02; 0.01];

%% Create training set
x = 0:0.125:1.25;
x = x';
X = polynomial_matrix(x, 3);
y = [100; 98.5; 95; 85; 70; 50; 30; 12.5; 5; 3; 2.2];

%% Create initial theta
theta = [100; -13.678; 500; 1];

%% Some gradient descent settings
iterations = 1500000;
alpha = 0.002;
lambda = 0;

%% compute and display initial cost
compute_cost_regularised(X, y, theta, lambda)

%% run gradient descent
theta = gradient_descent_specialised_regularised(X, y, theta, alpha, iterations, lambda);



%% compute and display initial cost
compute_cost_regularised(X, y, theta, lambda)

%% print theta to screen
fprintf('Theta found by gradient descent: \n');
fprintf('%f %f %f %f \n\n', theta(1), theta(2), theta(3), theta(4));

j = 1;
h = 0:0.05:1.25;
for i = 0:0.05:1.25
    h(j) = theta'*[1;i;i^2;i^3];
    j = j + 1;
end

close all;
plot(0:0.05:1.25, h);
hold on;
plot(x, y, 'o');
pause;