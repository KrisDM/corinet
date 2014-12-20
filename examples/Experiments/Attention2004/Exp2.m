%run the experiment and read the data
corinet Exp2.xml;
readCorinet('Exp2Results.xml',1);

numIterations = 2;
numCycles = 5;
calcSteps = 25;
zeroSteps = 7;
plotSteps = calcSteps + zeroSteps;
tauY = 0.5;

yOut = zeros(plotSteps,numIterations,numCycles);

for c=1:numCycles,
    for i=1:numIterations,
        rowIndices = find(netOutput_N0_Ex1{c}{1}(:,1) == i);
        yTemp = zeros(plotSteps,1);
        yTemp(1:calcSteps) = netOutput_N0_Ex1{c}{2}(rowIndices(1:calcSteps),1);
        yOut(:,i,c) = attenuationTime(yTemp,tauY);
    end
end

figure;
set(gcf,'Name','Fig6c - Effect of stimulus contrast');
xPlot = 1:plotSteps;
for c=1:numCycles,
    subplot(1,5,c);
    yPlot = squeeze(yOut(:,:,c));
    hold on;
    plot(xPlot,yPlot(:,1),'b','lineWidth',3);
    plot(xPlot,yPlot(:,2),'r','lineWidth',5);
    box on;
    axis([min(xPlot) max(xPlot) 0 0.05+max(yOut(:))]);
    set(gca,'xTick',[]);
    set(gca,'yTick',[]);
    xlabel('Time','FontSize',15);
    if (c==1)
        ylabel('Response','FontSize',15);
        [lh,oh,ph,ts] = legend('attend away','attend RF');
        for t=1:length(oh),
            if (strcmp(get(oh(t),'Type'),'text'))
                set(oh(t),'FontSize',15);
            end
        end
    end
end

clear i c yTemp xPlot yPlot lh oh ph ts t rowIndices;
