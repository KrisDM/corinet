corinet Exp3.xml;
readCorinet('Exp3Results.xml',1);
trainSet = readPatternSet('../../PatternSets/Categor2006/Fig8.xml');

%constants from execution
numRuns = 20;
numNodes = 6;
numCols1 = 29;
numCols2 = 20;
numExemplars = length(trainSet);
numPrototypes = 1;
tollerance = 5;
tauY = 0.4;

%patterns
exemplars = ones(numCols1,numExemplars);
prototype = ones(numCols1,numPrototypes);
for p=1:numExemplars,
    exemplars(1:numCols2,p) = trainSet{p}';
    prototype = prototype&exemplars(:,p);
end

%determine how well exemplars or prototype have been learned
exemplarRuns = zeros(1,numRuns);
prototypeRuns = zeros(1,numRuns);
for r=1:numRuns,
    currentW = weights_D2_Ex1{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,exemplars,tollerance);
    if (sum(patPresent) == numExemplars)
        exemplarRuns(r) = 1;
    end
    currentW = weights_D2_Ex2{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,prototype,tollerance);
    if (sum(patPresent) == numPrototypes)
        prototypeRuns(r) = 1;
    end
end

fprintf(1,'Exemplar learning success rate: %d/%d. ',sum(exemplarRuns),numRuns);
if (sum(exemplarRuns)<numRuns)
    fprintf(1,'Incorrect runs: ');
    fprintf(1,'%d ',find(~exemplarRuns));
end
fprintf(1,'\n');
fprintf(1,'Prototype learning success rate: %d/%d. ',sum(prototypeRuns),numRuns);
if (sum(prototypeRuns)<numRuns)
    fprintf(1,'Incorrect runs: ');
    fprintf(1,'%d ',find(~prototypeRuns));
end
fprintf(1,'\n');

if (~sum(exemplarRuns) || ~sum(prototypeRuns))
    fprintf(1,'Cannot plot figure 8\n');
else
    %plot figs 8a, 8b and 8c
    figure;
    set(gcf,'Name','Figure 8');
    for p=1:numExemplars,
        subplot(3,numNodes,p+1);
        plotPattern(exemplars(:,p),0.1);
    end
    
    successRuns = find(exemplarRuns);
    plotRun = successRuns(1);
    for n=1:numNodes,
        subplot(3,numNodes,n+6);
        plotPattern(weights_D2_Ex1{plotRun}{2}(:,n),0.1);
    end
    
    successRuns = find(prototypeRuns);
    plotRun = successRuns(1);
    for n=1:numNodes,
        subplot(3,numNodes,n+12);
        plotPattern(weights_D2_Ex2{plotRun}{2}(:,n),0.1);
    end
end

clear n p plotRun successRuns patList repNodes currentW numCols1 numCols2 r trainSet;


