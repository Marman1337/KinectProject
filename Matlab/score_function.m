function [ score ] = score_function( x_scale, x_offset, error_score )
    y_offset = 100*(1 - 1/(1 + exp(-x_offset)));
    score = 100./(1 + exp(x_scale*error_score - x_offset)) + y_offset;
end

