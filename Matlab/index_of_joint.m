function [ index ] = index_of_joint( joint )
% index =s index of joint specified

    switch joint
        case 'head'           
            index = 1;
        case 'left_shoulder'           
            index = 5;
        case 'left_elbow'  
            index = 9;
        case 'right_shoulder' 
            index = 13;
        case 'right_elbow'     
            index = 17;
        case 'left_hand'    
            index = 21;
        case 'right_hand'      
            index = 25;
        case 'torso'     
            index = 29;
        case 'left_hip'          
            index = 33;
        case 'right_hip'      
            index = 37;
        case 'left_knee'      
            index = 41;
        case 'left_foot'      
            index = 45;
        case 'right_knee'     
            index = 49;
        case 'neck'      
            index = 53;
        case 'right_foot'     
            index = 57;        
    end

end