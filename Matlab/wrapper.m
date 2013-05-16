function [ out1 , out2 ] = wrapper(input1, input2)

    % import data if not already in a matrix
    if(ischar(input1))
        input1 = importdata(input1);
    end
    if(ischar(input2))
        input2 = importdata(input2);
    end

    % get motionless frame for each file
    frame1 = get_motionless(input1, 30);
    frame2 = get_motionless(input2, 30);

    % translate both files
    out1 = translate(input1,frame1);
    out2 = translate(input2,frame2);

end