function [ out ] = translate(dataMat,frame)

    % Crop the data to start from the motionless frame
    dataMat = dataMat(frame:size(dataMat,1),:);

    % Get (x, y, z) coordinates from the torso at the frame
    x = dataMat(1, 33);
    y = dataMat(1, 34);
    z = dataMat(1, 35);

    % Translate the data to treat the torso as the origin
    for i = 0:14
        dataMat(:, 4*i+1) = dataMat(:, 4*i+1) - x;
        dataMat(:, 4*i+2) = dataMat(:, 4*i+2) - y;
        dataMat(:, 4*i+3) = dataMat(:, 4*i+3) - z;
    end

    out = dataMat;

end