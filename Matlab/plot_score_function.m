function [ output_args ] = plot_score_function( a, b, range )
%%  Plots the value of the score function against scores in the range provided
%   This is done with the parameters of a and b substituded into the
%   equation.
    j = 1;
    for i = range
        y(j) = 1/(1 + exp(a*i - b));
        j = j + 1;
    end
    figure;
    plot(range, y);


end

