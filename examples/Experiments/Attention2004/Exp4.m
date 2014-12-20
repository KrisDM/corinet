%run the experiment and read the data
corinet Exp4.xml;
readCorinet('Exp4Results.xml',1);

numNodes1 = 8;
numNodes2 = 5;
plotSteps = 25;
tauY = 0.5;

%determine which two nodes in upper layer are responding to the two
%training patterns
famNode1 = find(weights_D5_Ex1{1}{2}(5,:,1) == max(weights_D5_Ex1{1}{2}(5,:,1)));
famNode2 = find(weights_D5_Ex1{1}{2}(1,:,1) == max(weights_D5_Ex1{1}{2}(1,:,1)));

xPlotLayer1 = 0:plotSteps;
xPlotLayer2 = 1:plotSteps;

%plot Fig11
rows1 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 1);
rows2 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 2);
rows107 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 107);
rows108 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 108);
yTemp1 = [blockOutput_L1Q2_Ex1{1}{2}(rows1(1:plotSteps),8),blockOutput_L1Q2_Ex1{1}{2}(rows2(1:plotSteps),8)];
yPlot1 = [zeros(1,2);attenuationTime(yTemp1,tauY)];
yTemp2 = [blockOutput_L1Q2_Ex1{1}{2}(rows107(1:plotSteps),8),blockOutput_L1Q2_Ex1{1}{2}(rows108(1:plotSteps),8)];
yPlot2 = [zeros(1,2);attenuationTime(yTemp2,tauY)];
yTemp3 = [blockOutput_L2_Ex1{1}{2}(rows1(1:plotSteps),famNode1),blockOutput_L2_Ex1{1}{2}(rows2(1:plotSteps),famNode1)];
yPlot3 = [attenuationTime(yTemp3,tauY)];
yTemp4 = [blockOutput_L2_Ex1{1}{2}(rows107(1:plotSteps),famNode1),blockOutput_L2_Ex1{1}{2}(rows108(1:plotSteps),famNode1)];
yPlot4 = [attenuationTime(yTemp4,tauY)];

figure;
set(gcf,'Name','Fig11a - Before training');
axes;
plot(xPlotLayer1,yPlot1(:,1),'r',xPlotLayer1,yPlot1(:,2),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('familiar','novel');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

axes('position',[0.55 0.17 0.3 0.3]);
plot(xPlotLayer2,yPlot3(:,1),'r',xPlotLayer2,yPlot3(:,2),'g--','lineWidth',3);
axis([min(xPlotLayer2) max(xPlotLayer2) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

figure;
set(gcf,'Name','Fig11b - After training');
axes;
plot(xPlotLayer1,yPlot2(:,1),'r',xPlotLayer1,yPlot2(:,2),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('familiar','novel');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

axes('position',[0.55 0.17 0.3 0.3]);
plot(xPlotLayer2,yPlot4(:,1),'r',xPlotLayer2,yPlot4(:,2),'g--','lineWidth',3);
axis([min(xPlotLayer2) max(xPlotLayer2) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

%plot Fig12
rows3 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 3);
rows109 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 109);
yTemp1 = [blockOutput_L1Q2_Ex1{1}{2}(rows3(1:plotSteps),8),blockOutput_L1Q2_Ex1{1}{2}(rows3(1:plotSteps),1)];
yPlot1 = [zeros(1,2);attenuationTime(yTemp1,tauY)];
yTemp2 = [blockOutput_L1Q2_Ex1{1}{2}(rows109(1:plotSteps),8),blockOutput_L1Q2_Ex1{1}{2}(rows109(1:plotSteps),1)];
yPlot2 = [zeros(1,2);attenuationTime(yTemp2,tauY)];
yTemp3 = [blockOutput_L2_Ex1{1}{2}(rows3(1:plotSteps),famNode1),blockOutput_L2_Ex1{1}{2}(rows3(1:plotSteps),famNode2)];
yPlot3 = [attenuationTime(yTemp3,tauY)];
yTemp4 = [blockOutput_L2_Ex1{1}{2}(rows109(1:plotSteps),famNode1),blockOutput_L2_Ex1{1}{2}(rows109(1:plotSteps),famNode2)];
yPlot4 = [attenuationTime(yTemp4,tauY)];

figure;
set(gcf,'Name','Fig12a - Before training');
axes;
plot(xPlotLayer1,yPlot1(:,1),'r',xPlotLayer1,yPlot1(:,2),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('familiar','novel');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

axes('position',[0.55 0.17 0.3 0.3]);
plot(xPlotLayer2,yPlot3(:,1),'r',xPlotLayer2,yPlot3(:,2),'g--','lineWidth',3);
axis([min(xPlotLayer2) max(xPlotLayer2) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

figure;
set(gcf,'Name','Fig12b - After training');
axes;
plot(xPlotLayer1,yPlot2(:,1),'r',xPlotLayer1,yPlot2(:,2),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('familiar','novel');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

axes('position',[0.55 0.17 0.3 0.3]);
plot(xPlotLayer2,yPlot4(:,1),'r',xPlotLayer2,yPlot4(:,2),'g--','lineWidth',3);
axis([min(xPlotLayer2) max(xPlotLayer2) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

%plot Fig13
rows4 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 4);
rows110 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 110);
yTemp1 = [blockOutput_L1Q2_Ex1{1}{2}(rows4(1:plotSteps),8),blockOutput_L1Q2_Ex1{1}{2}(rows4(1:plotSteps),1)];
yPlot1 = [zeros(1,2);attenuationTime(yTemp1,tauY)];
yTemp2 = [blockOutput_L1Q2_Ex1{1}{2}(rows110(1:plotSteps),8),blockOutput_L1Q2_Ex1{1}{2}(rows110(1:plotSteps),1)];
yPlot2 = [zeros(1,2);attenuationTime(yTemp2,tauY)];

figure;
set(gcf,'Name','Fig13a - Before training');
axes;
plot(xPlotLayer1,yPlot1(:,1),'r',xPlotLayer1,yPlot1(:,2),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('figure','noise');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

figure;
set(gcf,'Name','Fig13b - After training');
axes;
plot(xPlotLayer1,yPlot2(:,1),'r',xPlotLayer1,yPlot2(:,2),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
[lh,oh,ph,ts] = legend('figure','noise');
for t=1:length(oh),
    if (strcmp(get(oh(t),'Type'),'text'))
        set(oh(t),'FontSize',15);
    end
end
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

%plot Fig14
rows5 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 5);
rows6 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 6);
rows111 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 111);
rows112 = find(blockOutput_L1Q2_Ex1{1}{1}(:,1) == 112);
yTemp1 = [blockOutput_L1Q2_Ex1{1}{2}(rows5(1:plotSteps),5:8),blockOutput_L1Q2_Ex1{1}{2}(rows5(1:plotSteps),1:4)];
yPlot1 = [zeros(1,8);attenuationTime(yTemp1,tauY)];
yTemp2 = [blockOutput_L1Q2_Ex1{1}{2}(rows111(1:plotSteps),5:8),blockOutput_L1Q2_Ex1{1}{2}(rows111(1:plotSteps),1:4)];
yPlot2 = [zeros(1,8);attenuationTime(yTemp2,tauY)];
yTemp3 = [blockOutput_L1Q2_Ex1{1}{2}(rows6(1:plotSteps),5:8),blockOutput_L1Q2_Ex1{1}{2}(rows6(1:plotSteps),1:4)];
yPlot3 = [zeros(1,8);attenuationTime(yTemp3,tauY)];
yTemp4 = [blockOutput_L1Q2_Ex1{1}{2}(rows112(1:plotSteps),5:8),blockOutput_L1Q2_Ex1{1}{2}(rows112(1:plotSteps),1:4)];
yPlot4 = [zeros(1,8);attenuationTime(yTemp4,tauY)];


figure;
set(gcf,'Name','Fig14a - Before training');
plot(xPlotLayer1,yPlot1(:,1:4),'r','lineWidth',4);
hold on;
plot(xPlotLayer1,yPlot1(:,5:8),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

figure;
set(gcf,'Name','Fig14a - After training');
plot(xPlotLayer1,yPlot2(:,1:4),'r','lineWidth',4);
hold on;
plot(xPlotLayer1,yPlot2(:,5:8),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

figure;
set(gcf,'Name','Fig14c - Before training');
plot(xPlotLayer1,yPlot3(:,1:4),'r','lineWidth',4);
hold on;
plot(xPlotLayer1,yPlot3(:,5:8),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

figure;
set(gcf,'Name','Fig14d - After training');
plot(xPlotLayer1,yPlot4(:,1:4),'r','lineWidth',4);
hold on;
plot(xPlotLayer1,yPlot4(:,5:8),'g--','lineWidth',4);
axis([min(xPlotLayer1) max(xPlotLayer1) 0 1]);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel('Time','FontSize',15);
ylabel('Response','FontSize',15);

clear rows1 rows2 rows3 rows4 rows5 rows6 rows107 rows108 rows109 rows110 rows111 rows112 yTemp1 yTemp2 yTemp3 yTemp4 yPlot1 yPlot2 yPlot3 yPlot4 ...
    lh oh ph ts t xPlotLayer1 xPlotLayer2;