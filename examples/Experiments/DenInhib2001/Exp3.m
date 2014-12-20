%run the experiment
corinet('Exp3.xml');
%read the data
readCorinet('Exp3Results.xml');
x3 = results{1}{1}{1}{1}{1}{2};
y3 = results{1}{1}{1}{2}{1}{2};
w3 = results{1}{1}{1}{3}{1}{2};

figure;
for i=1:8,
    subplot(2,4,i);
    plotNetwork(x3(i,:),w3,y3(i,:),1);
end

clear results i