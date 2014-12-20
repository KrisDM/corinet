%run the experiment and read the data
corinet Exp3.xml;
readCorinet('Exp3Results.xml',1);

numNodes = 2;
numIterations = 4;
calcSteps = 20;
zeroSteps = 7;
plotSteps = calcSteps + zeroSteps;
tauY = 0.5;

yOut = zeros(plotSteps,numNodes,numIterations);

for i=1:numIterations,
    rowIndices = find(netOutput_N0_Ex1{1}{1}(:,1) == i);
    yTemp = zeros(plotSteps,numNodes);
    yTemp(1:calcSteps,:) = netOutput_N0_Ex1{1}{2}(rowIndices(1:calcSteps),:);
    yOut(:,:,i) = attenuationTime(yTemp,tauY);
end

xPlot = 1:plotSteps;
yPlot = squeeze(yOut(:,1,:));
figure;
set(gcf,'Name','Fig8c - Effect of featural attention');
hold on;
plot(xPlot,yPlot(:,1),'r--','lineWidth',2);
plot(xPlot,yPlot(:,2),'g-.','lineWidth',2);
plot(xPlot,yPlot(:,3),'r-','lineWidth',3);
plot(xPlot,yPlot(:,4),'g','lineWidth',2);
box on;
axis([min(xPlot) max(xPlot) 0 0.05+max(yPlot(:))]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('pref attend pref','poor attend poor','pair attend pref','pair attend poor');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

clear i yTemp xPlot yPlot lh oh ph ts t rowIndices;