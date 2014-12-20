corinet Exp2.xml;
readCorinet('Exp2Results.xml',1);
trainSet = readPatternSet('../../PatternSets/Categor2006/Fig7.xml');

%constants from execution
numTrainingIterations = 500;
numRuns = 10;
numNodes = 29;
numPatterns = 16;
numSteps = 21;
patternGridSize = 4;
tauY = 0.4;

betweenRowsByRow = zeros(3,4);
betweenColsByRow = zeros(4,3);
betweenRowsByCol = zeros(3,4);
betweenColsByCol = zeros(4,3);

yU = zeros(numPatterns,numNodes);
for p=1:numPatterns,
    rowIndices = find(blockOutput_B0_Ex1{1}{1}(:,1) == p);
    yTemp = attenuationTime(blockOutput_B0_Ex1{1}{2}(rowIndices,:),tauY);
    yU(p,:) = yTemp(numSteps,:);
end
yU = reshape(yU,patternGridSize,patternGridSize,numNodes);

for r=1:numRuns,
    yTR = zeros(numPatterns,numNodes);
    yTC = zeros(numPatterns,numNodes);
    for p=1:numPatterns,
        rowIndices = find(blockOutput_B0_Ex2{r}{1}(:,1) == p+numTrainingIterations);
        yTemp = attenuationTime(blockOutput_B0_Ex2{r}{2}(rowIndices,:),tauY);
        yTR(p,:) = yTemp(numSteps,:);
        yTemp = attenuationTime(blockOutput_B0_Ex3{r}{2}(rowIndices,:),tauY);
        yTC(p,:) = yTemp(numSteps,:);
    end
    yTR = reshape(yTR,patternGridSize,patternGridSize,numNodes);
    yTC = reshape(yTC,patternGridSize,patternGridSize,numNodes);
    for i=1:patternGridSize-1,
        for j=1:patternGridSize,
            betweenRowsByRow(i,j) = betweenRowsByRow(i,j) + calcDeltaEpsilon(squeeze(yU(i,j,:)),squeeze(yTR(i,j,:)),squeeze(yU(i+1,j,:)),squeeze(yTR(i+1,j,:)));
            betweenRowsByCol(i,j) = betweenRowsByCol(i,j) + calcDeltaEpsilon(squeeze(yU(i,j,:)),squeeze(yTC(i,j,:)),squeeze(yU(i+1,j,:)),squeeze(yTC(i+1,j,:)));
        end
    end
    for i=1:patternGridSize,
        for j=1:patternGridSize-1,
            betweenColsByRow(i,j) = betweenColsByRow(i,j) + calcDeltaEpsilon(squeeze(yU(i,j,:)),squeeze(yTR(i,j,:)),squeeze(yU(i,j+1,:)),squeeze(yTR(i,j+1,:)));
            betweenColsByCol(i,j) = betweenColsByCol(i,j) + calcDeltaEpsilon(squeeze(yU(i,j,:)),squeeze(yTC(i,j,:)),squeeze(yU(i,j+1,:)),squeeze(yTC(i,j+1,:)));
        end
    end
end

betweenRowsByRow = betweenRowsByRow/numRuns;
betweenRowsByCol = betweenRowsByCol/numRuns;
betweenColsByRow = betweenColsByRow/numRuns;
betweenColsByCol = betweenColsByCol/numRuns;

trainSet = reshape(trainSet,patternGridSize,patternGridSize);
figure,
set(gcf,'Name','Figure 7a');
plotCounter = 0;
for p1=1:patternGridSize,
    for p2=1:patternGridSize,
        plotCounter = plotCounter + 1;
        subplot(patternGridSize,patternGridSize,plotCounter);
        pat = ones(1,numNodes);
        pat(1,1:20) = trainSet{p1,p2};
        pat = 0.75*pat;
        plotPattern(pat,1);
    end
end

width = 0.1;
figure;
set(gcf,'Name','Figure 7b');
hold on;
box on;
axis off;
axis square;
for i=0:4  
  plot([i,i],[0,4],'k');
  plot([0,4],[i,i],'k');
end

for i=1:3,
    for j=1:4,
        height = betweenRowsByRow(i,j);
        if (height > 0.0)
            col = 'b';
        else
            col = 'w';
        end
        centreX = j - 0.5;
        centreY = 4 - i;
        fill([centreX-width,centreX-width,centreX+width,centreX+width],[centreY+height,centreY-height,centreY-height,centreY+height],col);
    end
end
for i=1:4,
    for j=1:3,
        height = betweenColsByRow(i,j);
        if (height > 0.0)
            col = 'b';
        else
            col = 'w';
        end
        centreX = j;
        centreY = 4 - i + 0.5;
        fill([centreX-height,centreX-height,centreX+height,centreX+height],[centreY+width,centreY-width,centreY-width,centreY+width],col);
    end
end

figure;
set(gcf,'Name','Figure 7c');
hold on;
box on;
axis off;
axis square;
for i=0:4  
  plot([i,i],[0,4],'k');
  plot([0,4],[i,i],'k');
end

for i=1:3,
    for j=1:4,
        height = betweenRowsByCol(i,j);
        if (height > 0.0)
            col = 'b';
        else
            col = 'w';
        end
        centreX = j - 0.5;
        centreY = 4 - i;
        fill([centreX-width,centreX-width,centreX+width,centreX+width],[centreY+height,centreY-height,centreY-height,centreY+height],col);
    end
end
for i=1:4,
    for j=1:3,
        height = betweenColsByCol(i,j);
        if (height > 0.0)
            col = 'b';
        else
            col = 'w';
        end
        centreX = j;
        centreY = 4 - i + 0.5;
        fill([centreX-height,centreX-height,centreX+height,centreX+height],[centreY+width,centreY-width,centreY-width,centreY+width],col);
    end
end


clear yU yTR yTC r i j numNodes numRuns patternGridSize height width col centreX centreY p1 p2;

