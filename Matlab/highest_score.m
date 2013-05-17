
score = zeros(1, 21);
for i = -10:10
    score(i+11) = get_score('TestFile1.txt', 'TestFile2.txt', i);
end