function [ index ] = index_of_joint( joint )
% index =s index of joint specified

    switch joint
        case 'head'           % 1
            index = 1;
        case 'neck'           % 2
            index = 5;
        case 'left_shoulder'  % 3
            index = 9;
        case 'right_shoulder' % 4
            index = 13;
        case 'left_elbow'     % 5
            index = 17;
        case 'right_elbow'    % 6
            index = 21;
        case 'left_hand'      % 7
            index = 25;
        case 'right_hand'     % 8
            index = 29;
        case 'torso'          % 9
            index = 33;
        case 'left_hip'       % 10
            index = 37;
        case 'right_hip'      % 11
            index = 41;
        case 'left_knee'      % 12
            index = 45;
        case 'right_knee'     % 13
            index = 49;
        case 'left_foot'      % 14
            index = 53;
        case 'right_foot'     % 15
            index = 57;        
    end

end