function plot_score_function( a, b, range )
%%  Plots the value of the score function against scores in the range provided
%   This is done with the parameters of a and b substituded into the
%   equation.
    j = 1;
    y_offset = 100*(1 - 1/(1 + exp(0 - b)));
    for i = range
        y(j) = 100/(1 + exp(a*i - b)) + y_offset;
        j = j + 1;
    end
    figure;
    plot(range, y);


end

