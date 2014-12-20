clear all;
readCorinet('Fig5Results.xml',1);

numCols = 8;
numRows = 8;
numTasks = 4; %linear bars or bars2 with 100 or 400 patterns
numConfigs = 2; %either nndi or di
numRuns = 25; %trials for each setting
numCycles = numConfigs*numRuns;
results = zeros(numRuns,numTasks,numConfigs);

for t=1:numTasks,
    cycleCounter = 0;
    switch (t),
        case 1,
            w32 = weights_D32_Ex1;
        case 2,
            w32 = weights_D32_Ex2;
        case 3,
            w32 = weights_D32_Ex3;
        case 4,
            w32 = weights_D32_Ex4;
    end
    for c=1:numConfigs,
        for r=1:numRuns,
            cycleCounter = cycleCounter + 1;
            currentW32 = w32{cycleCounter}{2};
            results(r,t,c) = length(barsRepresented1(currentW32,numRows,numCols));
        end
    end
end

clear cycleCounter t c r currentW32 w32;