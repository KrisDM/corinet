%run the experiment
corinet('Exp1.xml');
%read the data
fprintf(1,'Reading data...');
readCorinet('Exp1ResultsFig2.xml'); %this reads data into unnamed 'results' variable
fprintf(1,' this may take a while...');
readCorinet('Exp1ResultsPage5.xml',1); %this reads data into named variables
fprintf(1,' done!\n');

%these commands generate Figure 2 from the paper
x1 = results{1}{1}{1}{1}{1}{2};
y1 = results{1}{1}{1}{2}{1}{2};
w1 = results{1}{1}{1}{3}{1}{2};
clear results;

figure;
subplot(1,3,1);
plotHinton(w1,1,3,0,1);
xlabel('Input');
ylabel('Node');
title('Synaptic Weights');
set(gca,'XTick',1:6);
set(gca,'XTickLabel',{'a';'b';'c';'d';'e';'f'});
set(gca,'YTick',1:6);
set(gca,'YTickLabel',{'6';'5';'4';'3';'2';'1'});
y1(y1<0.01) = 0;
subplot(1,3,2);
plotHinton(y1(1:6,:),1,2,0,1);
xlabel('Input Pattern');
ylabel('Node');
title('Node Activations');
set(gca,'XTick',1:6);
set(gca,'XTickLabel',{'a';'ab';'abc';'cd';'de';'def'});
set(gca,'YTick',1:6);
set(gca,'YTickLabel',{'6';'5';'4';'3';'2';'1'});
subplot(1,3,3);
plotHinton(y1(7:12,:),1,2,0,1);
xlabel('Input Pattern');
ylabel('Node');
title('Node Activations');
set(gca,'XTick',1:6);
set(gca,'XTickLabel',{'abcd';'abcde';'abcdef';'abcdf';'bcde';'acef'});
set(gca,'YTick',1:6);
set(gca,'YTickLabel',{'6';'5';'4';'3';'2';'1'});


%these commands generate the data from page 5
for e=1:2,
    if e==1,
        currentExec = weights_D0_Ex1;
    else
        currentExec = weights_D1_Ex2;
    end
    numRuns = length(currentExec);
    convTimes = zeros(1,numRuns);
    for r=1:numRuns;
        currentIterations = currentExec{r}{1}(:,1);
        currentRun = currentExec{r}{2};
        numRecordings = length(currentIterations);
        for n=1:numRecordings,
            currentWeights = currentRun(:,:,n);
            currentRepresentation = zeros(1,6);
            for c=1:6,
                currentCol = currentWeights(:,c);
                if (currentCol(1) > 0.95) %this is pattern A
                    currentRepresentation(1) = 1;
                elseif (sum(currentCol(1:2)) > 0.95)
                    currentRepresentation(2) = 1; %pattern AB
                elseif (sum(currentCol(1:3)) > 0.95)
                    currentRepresentation(3) = 1; %pattern ABC
                elseif (sum(currentCol(3:4)) > 0.95)
                    currentRepresentation(4) = 1; %pattern CD
                elseif (sum(currentCol(4:5)) > 0.95)
                    currentRepresentation(5) = 1; %pattern DE
                elseif (sum(currentCol(4:6)) > 0.95)
                    currentRepresentation(6) = 1; %pattern DEF 
                end
            end
            if (sum(currentRepresentation) == 6)
                convTimes(r) = currentIterations(n);
                break;
            end
        end
        if (convTimes(r) == 0)
            convTimes(r) = currentIterations(end);
        end
    end
    if e==1,
        convTimesEx1 = convTimes;
    else
        convTimesEx2 = convTimes;
    end
end

fprintf(1,'Execution 1: median = %d, min = %d, max = %d\n',median(convTimesEx1),min(convTimesEx1),max(convTimesEx1));
fprintf(1,'Execution 2: median = %d, min = %d, max = %d\n',median(convTimesEx2),min(convTimesEx2),max(convTimesEx2));

clear e currentExec numRuns convTimes r currentIterations currentRun numRecordings n currentWeights currentCol currentRepresentation c;

            
    
