function yOut = attenuationTime(y,tauY)

numSteps = size(y,1);
numNodes = size(y,2);

yOut = zeros(numSteps,numNodes);
yTemp = zeros(1,numNodes);

yOut(1,:) = tauY*y(1,:);

for i=2:numSteps,
    yTemp = tauY*y(i,:) + (1-tauY)*yOut(i-1,:);
    yOut(i,:) = yTemp;
end
