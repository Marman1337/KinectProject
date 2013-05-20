function [ index ] = index_of_joint( joint )
% index =s index of joint specified

    switch joint
        case 'head'
            index = 1;
        case 'neck'
            index = 5;
        case 'left_shoulder'
            index = 9;
        case 'right_shoulder'
            index = 13;
        case 'left_elbow'
            index = 17;
        case 'right_elbow'
            index = 21;
        case 'left_hand'
            index = 25;
        case 'right_hand'
            index = 29;
        case 'torso'
            index = 33;
        case 'left_hip'
            index = 37;
        case 'right_hip'
            index = 41;
        case 'left_knee'
            index = 45;
        case 'right_knee'
            index = 49;
        case 'left_foot'
            index = 53;
        case 'right_foot'
            index = 57;        
    end

end