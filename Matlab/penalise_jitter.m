function [ scaling_factor ] = penalise_jitter( input_jitter )
%UNTITLED11 Summary of this function goes here
%   Detailed explanation goes here
      scaling_factor = -0.5*exp(-((0.3*input_jitter).^2)/2) + 1.5;    
end

