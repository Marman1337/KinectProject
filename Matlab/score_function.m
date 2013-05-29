function [ score ] = score_function( error_score )
    score = -2.^(6.652410119*(0.3*error_score+0.8))+140;
    
    for i = 1:size(score,1)
        for j = 1:size(score,2)
            if(score(i,j) < 0)
                score(i,j) = 0;
            end
        end
    end
end

