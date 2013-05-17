function plot_joints( data_1 , data_2, joint , xyz )
    % Plots joint  from both data sets using the following mapping for xyz:
    % 0: x
    % 1: y
    % 2: z
    figure;
    stem( data_1(:,index_of_joint(joint)+xyz) , 'b' );
    hold on;
    stem( data_2(:,index_of_joint(joint)+xyz) , 'g' );
    hold off;

end

