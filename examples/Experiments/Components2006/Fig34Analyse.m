clear all;
readCorinet('Fig34Results.xml',1);

numCols = 8;
numRows = 8;
numNetworks = 2; %either 32 or 16 nodes
numTasks = 2; %either a set of 100 or 400 training patterns
numConfigs = 2; %either nndi or di
numRuns = 25; %trials for each setting
numCycles = numConfigs*numRuns;
results = zeros(numRuns,numTasks,numConfigs,numNetworks);

for t=1:numTasks,
    cycleCounter = 0;
    switch (t),
        case 1,
            w32 = weights_D32_Ex1;
            w16 = weights_D16_Ex1;
        case 2,
            w32 = weights_D32_Ex2;
            w16 = weights_D16_Ex2;
    end
    for c=1:numConfigs,
        for r=1:numRuns,
            cycleCounter = cycleCounter + 1;
            currentW32 = w32{cycleCounter}{2};
            currentW16 = w16{cycleCounter}{2};
            results(r,t,c,1) = length(barsRepresented1(currentW32,numRows,numCols));
            results(r,t,c,2) = length(barsRepresented1(currentW16,numRows,numCols));
        end
    end
end

clear cycleCounter t c r currentW32 currentW16 w32 w16;