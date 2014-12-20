corinet Exp4.xml;
readCorinet('Exp4Results.xml',1);
trainSet9 = readPatternSet('../../PatternSets/Categor2006/Fig9.xml');
trainSet10 = readPatternSet('../../PatternSets/Categor2006/Fig10.xml');

%constants from execution
numRuns1 = 100;
numRuns2 = 20;
numRuns3 = 20;
numNodes = 6;
numCols1 = 29;
numCols2 = 20;
numExemplars = length(trainSet9);
numPrototypes = 1;
tollerance = 5;
onVal = 0.75;
tauY = 0.4;

%constants for plotting
fontSize = 15;
plotSteps = 25;
xPlotLayer2 = 1:plotSteps;
axisLimits2 = [min(xPlotLayer2) max(xPlotLayer2) 0 0.5];
fig11Legend = cell(1,6);
fig11Legend{1} = 'b-.';
fig11Legend{2} = 'c-.';
fig11Legend{3} = 'g-.';
fig11Legend{4} = 'm-.';
fig11Legend{5} = 'r-';
fig11Legend{6} = 'k:';

%patterns
exemplars9 = ones(numCols1,numExemplars);
prototype9 = ones(numCols1,numPrototypes);
exemplars10 = ones(numCols1,numExemplars);
for p=1:numExemplars,
    exemplars9(1:numCols2,p) = trainSet9{p}';
    prototype9 = prototype9&exemplars9(:,p);
    exemplars10(1:numCols2,p) = trainSet10{p}';
end

%determine how well exemplars and/or the prototype have been learned
exemplarRuns1 = zeros(numExemplars,numRuns1);
prototypeRuns1 = zeros(numPrototypes,numRuns1);
exemplarRuns2 = zeros(numExemplars,numRuns2);
prototypeRuns2 = zeros(numPrototypes,numRuns2);
exemplarRuns3 = zeros(numExemplars,numRuns3);
exemplarNodes = cell(1,numRuns2);
prototypeNodes = cell(1,numRuns2);
    
for r=1:numRuns1,
    currentW = weights_D2_Ex1{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,exemplars9,tollerance);
    exemplarRuns1(:,r) = patPresent'; 
    [patPresent,repNodes] = patternsRepresented(currentW,prototype9,tollerance);
    if (sum(patPresent) == numPrototypes)
        prototypeRuns1(r) = 1;
    end
end
for r=1:numRuns2,
    currentW = weights_D2_Ex2{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,exemplars9,tollerance);
    exemplarRuns2(:,r) = patPresent'; 
    exemplarNodes{r} = repNodes;
    [patPresent,repNodes] = patternsRepresented(currentW,prototype9,tollerance);
    if (sum(patPresent) == numPrototypes)
        prototypeRuns2(r) = 1;
        prototypeNodes{r} = repNodes;
    end
end
for r=1:numRuns3,
    currentW = weights_D2_Ex3{r}{2};
    [patPresent,repNodes] = patternsRepresented(currentW,exemplars10,tollerance);
    exemplarRuns3(:,r) = patPresent'; 
end

%determine success rates and plot figure 9
totalRuns = 20;
figNums = 'bcdefg';
subplotTotal = 3;
subplotOffset = 0;

%plot fig 9a
figure;
set(gcf,'Name','Figure 9a, b and c');
for p=1:numExemplars,
    subplot(subplotTotal,numNodes,p+1);
    plotPattern(onVal*exemplars9(:,p),1);
end

%plot fig 9b, c d, e, f and g
for f=1:7,
    learned2 = [];
    message2 = '';
    subplotOffset = subplotOffset + 1;
    switch f,
        case 1,
            runIndices = 1:20;
            learned1 = prototypeRuns1(runIndices);
            feedbackType = 'No attentional feedback:';
            message1 = 'prototype learned: ';
            currentWEx = weights_D2_Ex1;
        case 2,
            runIndices = 1:20;
            learned1 = sum(exemplarRuns2) == 4;
            learned2 = (sum(exemplarRuns2) + prototypeRuns2) == 5;
            feedbackType = 'Feedback to random node in lower region:';
            message1 = 'exemplars learned: ';
            message2 = 'exemplars and prototype learned: ';
            currentWEx = weights_D2_Ex2;
        case 3,
            runIndices = 21:40;
            learned1 = exemplarRuns1(4,runIndices)&prototypeRuns1(runIndices);
            feedbackType = 'Feedback to lower left vertical bar:';
            message1 = 'prototype and particular exemplar learned: ';
            figure;
            set(gcf,'Name','Figure 9d, e, f and g');
            subplotOffset = 0;
            subplotTotal = 4;
            currentWEx = weights_D2_Ex1;
        case 4,
            runIndices = 41:60;
            learned1 = prototypeRuns1(runIndices);
            feedbackType = 'Feedback to lower right vertical bar:';
            message1 = 'prototype learned: ';
            currentWEx = weights_D2_Ex1;
        case 5,
            runIndices = 61:80;
            learned1 = sum(exemplarRuns1(:,runIndices)) == 4;
            learned2 = (sum(exemplarRuns1(:,runIndices)) + prototypeRuns1(runIndices)) == 5;
            feedbackType = 'Feedback to lower middle vertical bar:';
            message1 = 'exemplars learned: ';
            message2 = 'exemplars and prototype learned: ';
            currentWEx = weights_D2_Ex1;
        case 6,
            runIndices = 81:100;
            learned1 = prototypeRuns1(runIndices);
            feedbackType = 'Feedback to all bars from prototype:';
            message1 = 'prototype learned: ';
            currentWEx = weights_D2_Ex1;
        case 7,
            subplotTotal = 2;
            figure;
            set(gcf,'Name','Figure 10a and b');
            for p=1:numExemplars,
                subplot(subplotTotal,numNodes,p+1);
                plotPattern(onVal*exemplars10(:,p),1);
            end
            runIndices = 1:20;
            learned1 = sum(exemplarRuns3(:,runIndices)) == 4;
            feedbackType = 'Stronger contrast for unique exemplar features:';
            message1 = 'exemplars learned: ';
            subplotOffset = 1;
            currentWEx = weights_D2_Ex3;
    end
    fprintf(1,'%s\n\t\t%s%d/%d. ',feedbackType,message1,sum(learned1),totalRuns);
    if (sum(learned1) < totalRuns)
        fprintf(1,'Incorrect runs: ');
        fprintf(1,'%d ',runIndices(find(~learned1)));
    end
    fprintf(1,'\n');
    if (~isempty(learned2))
        fprintf(1,'\t\t%s%d/%d. ',message2,sum(learned2),totalRuns);
        if (sum(learned2) < totalRuns)
            fprintf(1,'Incorrect runs: ');
            fprintf(1,'%d ',runIndices(find(~learned2)));
        end
        fprintf(1,'\n');
    end
    if (~sum(learned1)),
        if (f < 7),
            fprintf(1,'Cannot plot figure 9%s\n',figNums(f));
        else
            fprintf(1,'Cannot plot figure 10b\n');
        end
    else
        successRuns = find(learned1);
        plotRun = runIndices(successRuns(1));
        if (f == 2) %keep information for plotting of figure 11
            successRuns = find(learned2);
            plotRun = runIndices(successRuns(1));
            plotFig11Run = plotRun;
        end
        for n=1:numNodes,
            subplot(subplotTotal,numNodes,subplotOffset*numNodes+n);
            plotPattern(currentWEx{plotRun}{2}(:,n),0.1);
        end
    end        
end

%plot fig 11a
figure;
set(gcf,'Name','Fig11a');
repNodesEx = exemplarNodes{plotFig11Run}; 
repNodeProt = prototypeNodes{plotFig11Run};
lineCodes = 6*ones(1,numNodes);
for n=1:numNodes,
    for e=1:numExemplars,
        if (sum(ismember(repNodesEx{e},n)))
            lineCodes(n) = e;
            break;
        end
    end
    if lineCodes(n) == 6,
        if (sum(ismember(repNodeProt{1},n)))
            lineCodes(n) = 5;
        end
    end
    subplot(1,6,n);
    plotPattern(weights_D2_Ex2{plotFig11Run}{2}(:,n),0.1);
    plot([0 2],[-1 -1],fig11Legend{lineCodes(n)},'lineWidth',2);
end
 
%data for fig 11b
for i=201:207,
    rowIndices = find(blockOutput_B1_Ex2{plotFig11Run}{1}(:,1) == i);
    yTemp1 = blockOutput_B1_Ex2{plotFig11Run}{2}(rowIndices(1:plotSteps),:);
    yPlot1 = attenuationTime(yTemp1,tauY);
    figure;
    hold on;
    for g=1:numNodes,
        plot(xPlotLayer2,yPlot1(:,g),fig11Legend{lineCodes(g)},'LineWidth',3);
    end
    prepareAxis(axisLimits2,'Time','Response',fontSize);
end


%     figure;
%     axes;
%     hold on;
%     plot(xPlot,[repmat(0,1,3);yPlot1],'r','LineWidth',3)
%     plot(xPlot,[repmat(0,1,3);yPlot2],'g--','LineWidth',3);
%     box on;
%     axis([0 plotSteps 0 1]);
%     set(gca,'xTick',[]);
%     set(gca,'yTick',[]);
%     xlabel('Time','FontSize',12);
%     ylabel('Response','FontSize',12);
% 
%     axes('position',[0.55 0.17 0.3 0.3]);
%     hold on;
%     plot(xPlot(2:end),yPlot3(:,rowNodes(2,plotRun)),'r','LineWidth',2);
%     plot(xPlot(2:end),yPlot3(:,rowNodes(1,plotRun)),'g--','LineWidth',2);
%     plot(xPlot(2:end),yPlot3(:,setdiff(1:numNodes,rowNodes(:,plotRun))),'k:','LineWidth',2);
%     box on;
%     axis([1 plotSteps 0 1]);
%     set(gca,'xTick',[]);
%     set(gca,'yTick',[]);
%     xlabel('Time','FontSize',12);
%     ylabel('Response','FontSize',12);
% end

