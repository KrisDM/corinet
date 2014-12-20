%run the experiment
corinet('AFFig2.xml');
%read the data
readCorinet('AFFig2Results.xml');
x2 = results{1}{1}{1}{1}{1}{2};
y2 = results{1}{1}{1}{2}{1}{2};
w2 = results{1}{1}{1}{3}{1}{2};

figure;
for i=1:12,
    subplot(2,6,i);
    plotNetwork(x2(i,:),w2,y2(i,:),1);
end

clear results i