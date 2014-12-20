corinet Exp1.xml;
readCorinet('Exp1Results.xml',1);
trainSet = readPatternSet('../../PatternSets/Categor2006/Fig3.xml');

%constants from execution
numRuns = 20;
numNodes = 6;
numCols1 = 29;
numCols2 = 20;
numPatterns1 = 2;
numPatterns2 = 2;
tollerance = 5;
tauY = 0.4;

%constants for plotting
fontSize = 15;
plotSteps = 25;
xPlotLayer1 = 0:plotSteps;
xPlotLayer2 = 1:plotSteps;
axisLimits1 = [min(xPlotLayer1) max(xPlotLayer1) 0 1];
axisLimits2 = [min(xPlotLayer2) max(xPlotLayer2) 0 1];
smallAxisPosition = [0.55 0.17 0.3 0.3];

%patterns
diagnosticRows = ones(numCols1,numPatterns1);
diagnosticRows(1:numCols2,1) = [trainSet{1}&trainSet{2}]';
diagnosticRows(1:numCols2,2) = [trainSet{3}&trainSet{4}]';
diagnosticCols = ones(numCols1,numPatterns2);
diagnosticCols(1:numCols2,1) = [trainSet{1}&trainSet{3}]';
diagnosticCols(1:numCols2,2) = [trainSet{2}&trainSet{4}]';

%determine how well grouping-by-row or grouping-by-col has been learned
groupingByRow = zeros(1,numRuns);
rowNodes = cell(1,numRuns);
groupingByCol = zeros(1,numRuns);
colNodes = cell(1,numRuns);
for r=1:numRuns,
    currentW = weights_D2_Ex2{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,diagnosticRows,tollerance);
    if (sum(patPresent) == numPatterns1)
        groupingByRow(r) = 1;
        rowNodes{r} = repNodes;
    end
    currentW = weights_D2_Ex3{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,diagnosticCols,tollerance);
    if (sum(patPresent) == numPatterns2)
        groupingByCol(r) = 1;
        colNodes{r} = repNodes;
    end
end

fprintf(1,'Grouping-by-row success rate: %d/%d. ',sum(groupingByRow),numRuns);
if (sum(groupingByRow)<numRuns)
    fprintf(1,'Incorrect runs: ');
    fprintf(1,'%d ',find(~groupingByRow));
end
fprintf(1,'\n');
fprintf(1,'Grouping-by-column success rate: %d/%d. ',sum(groupingByCol),numRuns);
if (sum(groupingByCol)<numRuns)
    fprintf(1,'Incorrect runs: ');
    fprintf(1,'%d ',find(~groupingByCol));
end
fprintf(1,'\n');

if (~sum(groupingByRow) || ~sum(groupingByCol))
    fprintf(1,'Cannot plot figures 4, 5 and 6\n');
else

    %plot fig 4
    successRuns = find(groupingByRow);
    plotRun = successRuns(1);
    for n=1:numNodes,
        subplot(2,numNodes,n);
        plotPattern(weights_D2_Ex2{plotRun}{2}(:,n),0.1);
    end
    
    successRuns = find(groupingByCol);
    plotRun = successRuns(1);
    for n=1:numNodes,
        subplot(2,numNodes,n+6);
        plotPattern(weights_D2_Ex3{plotRun}{2}(:,n),0.1);
    end
    
    %data for fig 5c
    %get the first run where categorisation has been learned correctly
    lineSet1 = [4 13 16];
    lineSet2 = [14 15 17];
    yTemp1 = blockOutput_B0_Ex1{1}{2}(1:plotSteps,lineSet1);
    yPlot1 = [zeros(1,3);attenuationTime(yTemp1,tauY)];
    yTemp2 = blockOutput_B0_Ex1{1}{2}(1:plotSteps,lineSet2);
    yPlot2 = [zeros(1,3);attenuationTime(yTemp2,tauY)];
    yTemp3 = blockOutput_B1_Ex1{1}{2}(1:plotSteps,:);
    yPlot3 = attenuationTime(yTemp3,tauY);
    
    %plot fig 5c
    figure;
    set(gcf,'Name','Fig5c - Before training');
    hold on;
    plot(xPlotLayer1,yPlot1,'r','LineWidth',3)
    plot(xPlotLayer1,yPlot2,'k--','LineWidth',3);
    prepareAxis(axisLimits1,'Time','Response',fontSize);
    axes('position',smallAxisPosition);
    plot(xPlotLayer2,yPlot3,'k:','LineWidth',2);
    prepareAxis(axisLimits2,'Time','Response',fontSize);
    
    %data for fig 5d
    successRuns = find(groupingByRow);
    plotRun = successRuns(1);
    yTemp1 = blockOutput_B0_Ex2{plotRun}{2}(1:plotSteps,lineSet1);
    yPlot1 = [zeros(1,3);attenuationTime(yTemp1,tauY)];
    yTemp2 = blockOutput_B0_Ex2{plotRun}{2}(1:plotSteps,lineSet2);
    yPlot2 = [zeros(1,3);attenuationTime(yTemp2,tauY)];
    yTemp3 = blockOutput_B1_Ex2{plotRun}{2}(1:plotSteps,:);
    yPlot3 = attenuationTime(yTemp3,tauY);
    nodesPat1 = rowNodes{plotRun}{1};
    nodesPat2 = rowNodes{plotRun}{2};
    remainingNodes = setdiff(1:numNodes,[nodesPat1,nodesPat2]);
    
    %plot fig 5d
    figure;
    set(gcf,'Name','Fig5d - Grouping by row');
    hold on;
    plot(xPlotLayer1,yPlot1,'r','LineWidth',3)
    plot(xPlotLayer1,yPlot2,'k--','LineWidth',3);
    prepareAxis(axisLimits1,'Time','Response',fontSize);
    axes('position',smallAxisPosition);
    hold on;
    plot(xPlotLayer2,yPlot3(:,nodesPat1),'g--','LineWidth',2);
    plot(xPlotLayer2,yPlot3(:,nodesPat2),'r','LineWidth',2);
    plot(xPlotLayer2,yPlot3(:,remainingNodes),'k:','LineWidth',2);
    prepareAxis(axisLimits2,'Time','Response',fontSize);
    
    %data for fig 5e
    successRuns = find(groupingByCol);
    plotRun = successRuns(1);
    yTemp1 = blockOutput_B0_Ex3{plotRun}{2}(1:plotSteps,lineSet1);
    yPlot1 = [zeros(1,3);attenuationTime(yTemp1,tauY)];
    yTemp2 = blockOutput_B0_Ex3{plotRun}{2}(1:plotSteps,lineSet2);
    yPlot2 = [zeros(1,3);attenuationTime(yTemp2,tauY)];
    yTemp3 = blockOutput_B1_Ex3{plotRun}{2}(1:plotSteps,:);
    yPlot3 = attenuationTime(yTemp3,tauY);
    nodesPat1 = colNodes{plotRun}{1};
    nodesPat2 = colNodes{plotRun}{2};
    remainingNodes = setdiff(1:numNodes,[nodesPat1,nodesPat2]);
    
    %plot fig 5e
    figure;
    set(gcf,'Name','Fig5e - Grouping by row');
    hold on;
    plot(xPlotLayer1,yPlot1,'r','LineWidth',3)
    plot(xPlotLayer1,yPlot2,'k--','LineWidth',3);
    prepareAxis(axisLimits1,'Time','Response',fontSize);
    axes('position',smallAxisPosition);
    hold on;
    plot(xPlotLayer2,yPlot3(:,nodesPat1),'b-.','LineWidth',2);
    plot(xPlotLayer2,yPlot3(:,nodesPat2),'m--','LineWidth',2);
    plot(xPlotLayer2,yPlot3(:,remainingNodes),'k:','LineWidth',2);
    prepareAxis(axisLimits2,'Time','Response',fontSize);
    
    %plot fig 6b
    lineSet1 = [4 13 16];
    lineSet2 = [8 11 18];
    successRuns = find(groupingByRow);
    plotRun = successRuns(1);
    
    for f=202:206,
        rowIndices = find(blockOutput_B0_Ex2{plotRun}{1}(:,1) == f);
        yTemp1 = blockOutput_B0_Ex2{plotRun}{2}(rowIndices(1:plotSteps),lineSet1);
        yPlot1 = [zeros(1,3);attenuationTime(yTemp1,tauY)];
        yTemp2 = blockOutput_B0_Ex2{plotRun}{2}(rowIndices(1:plotSteps),lineSet2);
        yPlot2 = [zeros(1,3);attenuationTime(yTemp2,tauY)];
        yTemp3 = blockOutput_B1_Ex2{plotRun}{2}(rowIndices(1:plotSteps),:);
        yPlot3 = attenuationTime(yTemp3,tauY);
        nodesPat1 = rowNodes{plotRun}{1};
        nodesPat2 = rowNodes{plotRun}{2};
        remainingNodes = setdiff(1:numNodes,[nodesPat1,nodesPat2]);
        figure;
        hold on;
        plot(xPlotLayer1,yPlot1,'r','LineWidth',3)
        plot(xPlotLayer1,yPlot2,'g--','LineWidth',3);
        prepareAxis(axisLimits1,'Time','Response',fontSize);
        axes('position',smallAxisPosition);
        hold on;
        plot(xPlotLayer2,yPlot3(:,nodesPat1),'g--','LineWidth',2);
        plot(xPlotLayer2,yPlot3(:,nodesPat2),'r','LineWidth',2);
        plot(xPlotLayer2,yPlot3(:,remainingNodes),'k:','LineWidth',2);
        prepareAxis(axisLimits2,'Time','Response',fontSize);
    end
end

clear yTemp1 yPlot1 yTemp2 yPlot2 yTemp3 yPlot3 rowIndices nodesPat1 nodesPat2 remainingNodes xPlotLayer1 xPlotLayer2 axisLimits1 axisLimits2 plotRun f n;
clear currentW lineSet1 lineSet2 fontSize smallAxisPosition r patList repNodes successRuns numCols1 numCols2 trainSet plotSteps;