%run the experiment
corinet('Exp1.xml');
%read the data
readCorinet('Exp1Results.xml');
x1 = results{1}{1}{1}{1}{1}{2};
y1 = results{1}{1}{1}{2}{1}{2};
w1 = results{1}{1}{1}{3}{1}{2};

figure;
for i=1:8,
    subplot(2,4,i);
    plotNetwork(x1(i,:),w1,y1(i,:),1);
end

clear results i