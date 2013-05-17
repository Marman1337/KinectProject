function plot_joints( data , data_2, joint , xyz )
    % Plots joint  from both data sets using the following mapping for xyz:
    % 0: x
    % 1: y
    % 2: z
    figure;
    stem(data (:, index_of_joint(joint ))+xyz );
    hold on;
    stem(data_2(:, index_of_joint(joint ))+xyz , 'r');
    hold off;


end

