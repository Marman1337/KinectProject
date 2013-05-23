function [ name ] = name_of_joint( index_of_joint )
    temp = ceil(index_of_joint/4);
    
    switch temp
        case 1           
            name = 'head';
        case 2           
            name = 'left_shoulder';
        case 3  
            name = 'left_elbow';
        case 4 
            name = 'right_shoulder';
        case 5    
            name = 'right_elbow';
        case 6    
            name = 'left_hand';
        case 7    
            name = 'right_hand';
        case 8   
            name = 'torso';
        case 9        
            name = 'left_hip';
        case 10       
            name = 'right_hip';
        case  11     
            name = 'left_knee';
        case 12      
            name = 'left_foot';
        case 13     
            name = 'right_knee';
        case 14     
            name = 'neck';
        case 15    
            name = 'right_foot' ;        
    end
    

end

