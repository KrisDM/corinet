clear all;
readCorinet('Fig78Results.xml',1);

numCols = 9;
numRows = 9;
numCriteria = 2; %double or single width bars
numConfigs = 2; %either nndi or di
numRuns = 25; %trials for each setting
numCycles = numConfigs*numRuns;
results = zeros(numRuns,numConfigs,numCriteria);


    
cycleCounter = 0;
w32 = weights_D32_Ex1;
for c=1:numConfigs,
    for r=1:numRuns,
        cycleCounter = cycleCounter + 1;
        currentW32 = w32{cycleCounter}{2};
        results(r,c,1) = length(barsRepresented2(currentW32,numRows,numCols));
        results(r,c,2) = length(barsRepresented1(currentW32,numRows,numCols));
    end
end

clear cycleCounter c r currentW32 w32;