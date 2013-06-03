function [ weighting_vector, sum_weighting ] = weight_vector(head_weight, arm_weight, leg_weight, hip_weight, torso_weight)
    weighting_vector = ones(1, 15);
    weighting_vector(1+floor(1/4*index_of_joint('head'))) = head_weight;
    weighting_vector(1+floor(1/4*index_of_joint('neck'))) = head_weight;
    weighting_vector(1+floor(1/4*index_of_joint('left_hand'))) = arm_weight;
    weighting_vector(1+floor(1/4*index_of_joint('right_hand'))) = arm_weight;
    weighting_vector(1+floor(1/4*index_of_joint('left_elbow'))) = arm_weight;
    weighting_vector(1+floor(1/4*index_of_joint('right_elbow'))) = arm_weight;
    weighting_vector(1+floor(1/4*index_of_joint('left_foot'))) = leg_weight;
    weighting_vector(1+floor(1/4*index_of_joint('right_foot'))) = leg_weight;
    weighting_vector(1+floor(1/4*index_of_joint('left_knee'))) = leg_weight;
    weighting_vector(1+floor(1/4*index_of_joint('right_knee'))) = leg_weight;
    weighting_vector(1+floor(1/4*index_of_joint('left_hip'))) = hip_weight;
    weighting_vector(1+floor(1/4*index_of_joint('right_hip'))) = hip_weight;
    weighting_vector(1+floor(1/4*index_of_joint('left_shoulder'))) = torso_weight;
    weighting_vector(1+floor(1/4*index_of_joint('right_shoulder'))) = torso_weight;
    weighting_vector(1+floor(1/4*index_of_joint('torso'))) = torso_weight;

    sum_weighting = sum(weighting_vector);
   
end

