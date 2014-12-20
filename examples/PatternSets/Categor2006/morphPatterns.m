function newSet = morphPatterns(set)
% newSet = morphPatterns(set)
% input argument 'set' is the original set of four patterns of Fig3.xml in the same directory


newSet = cell(1,16);
cellCounter = 1;

for k=0:3,
    for j=0:3,
        newSet{cellCounter} = (3-k)*(3-j)/9*set{1} + k*(3-j)/9*set{2} + (3-k)*j/9*set{3} + k*j/9*set{4};
        cellCounter = cellCounter + 1;
    end
end


