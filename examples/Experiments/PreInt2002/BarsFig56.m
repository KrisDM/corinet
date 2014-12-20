%run the experiment
corinet('BarsFig56.xml');
%read the data
fprintf(1,'Reading data...');
fprintf(1,' this may take a while...');
readCorinet('BarsFig56Results.xml',1); %this reads data into named variables
fprintf(1,' done!\n');

%get how many bars are represented in each weight recording
numRows = 8;
numCols = 8;
for w=1:3,
    switch w,
        case 1,
            currentSet = weights_D0_Ex1;
        case 2,
            currentSet = weights_D1_Ex2;
        case 3,
            currentSet = weights_D2_Ex2;
    end
    numRuns = length(currentSet);
    currentIterations = currentSet{1}{1}(:,1);
    numRecordings = length(currentIterations);
    repBars = zeros(numRuns,numRecordings);
    for r=1:numRuns,
        currentRun = currentSet{r}{2};
        for n=1:numRecordings,
            currentWeights = currentRun(:,:,n);
            repBars(r,n) = barsRepresented1(currentWeights,numRows,numCols);
        end
    end
    switch w,
        case 1,
            configuration1 = repBars(1:25,:); %beta = 1, betaneg = 1/64
            configuration2 = repBars(26:50,:); %beta = 1, betaneg = 1
            configuration3 = repBars(51:75,:); %beta = 0.25, betaneg = 1/64
        case 2,
            configuration4 = repBars; %32 nodes
        case 3,
            configuration5 = repBars; %20 nodes, constructive
    end
end
errorBarIndex = 2:2:32;
errorLower1 = mean(configuration1) - min(configuration1);
errorUpper1 = max(configuration1) - mean(configuration1);
errorLower4 = mean(configuration4) - min(configuration4);
errorUpper4 = max(configuration4) - mean(configuration4); 

%Figure 5a
figure;
hold on;
h = plot(currentIterations,mean(configuration1));
set(h,'LineWidth',2,'LineStyle','-','Color','b');
h = plot(currentIterations,mean(configuration2));
set(h,'LineWidth',2,'LineStyle','--','Color','g');
h = plot(currentIterations,mean(configuration3));
set(h,'LineWidth',2,'LineStyle','-.','Color','r');
h = plot(currentIterations,16*ones(1,numRecordings));
set(h,'LineWidth',1,'LineStyle',':','Color','k');
h = errorbar(currentIterations(errorBarIndex),mean(configuration1(:,errorBarIndex)),errorLower1(errorBarIndex),errorUpper1(errorBarIndex),'b.');
set(h,'MarkerSize',1);
box on;
axis([0 800 0 18]);
set(gca,'XTick',0:200:800);
set(gca,'YTick',0:2:16);
xlabel('training cycles');
ylabel('number of bars represented');
legend('\beta = 1.0, \beta^-=0.0156','\beta = 1.0, \beta^-=1.0','\beta = 0.25,\beta^-=0.0156',4);

%Figure 5b
figure;
hold on;
h = plot(currentIterations,mean(configuration1));
set(h,'LineWidth',2,'LineStyle','-','Color','b');
h = plot(currentIterations,mean(configuration4));
set(h,'LineWidth',2,'LineStyle','--','Color','g');
h = plot(currentIterations,mean(configuration5));
set(h,'LineWidth',2,'LineStyle','-.','Color','r');
h = plot(currentIterations,16*ones(1,numRecordings));
set(h,'LineWidth',1,'LineStyle',':','Color','k');
h = errorbar(currentIterations(errorBarIndex),mean(configuration4(:,errorBarIndex)),errorLower4(errorBarIndex),errorUpper4(errorBarIndex),'g.');
set(h,'MarkerSize',1);
box on;
axis([0 800 0 18]);
set(gca,'XTick',0:200:800);
set(gca,'YTick',0:2:16);
xlabel('training cycles');
ylabel('number of bars represented');
legend('n = 16','n = 32','n \leq 20',4);

%Figure 6
currentIndex = find(weights_D1_Ex2{1}{1}(:,1) == 500);
currentWeights = weights_D1_Ex2{1}{2}(:,:,currentIndex);
currentWeights = reshape(currentWeights,[numRows numCols 32]);
figure;
for r=1:2,
    for c=1:16,
        subplot(2,16,(r-1)*16+c);
        plotHinton(currentWeights(:,:,(r-1)*16+c),0.125,3,1,1);
    end
end

clear numRows numCols currentSet numRuns currentIterations numRecordings r currentRun n currentWeights w h;
clear repBars errorLower1 errorUpper1 errorLower4 errorUpper4 errorBarIndex currentIndex r c;