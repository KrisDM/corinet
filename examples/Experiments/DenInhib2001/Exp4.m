%run the experiment
corinet('Exp4.xml');
%read the data
readCorinet('Exp4Results.xml');
x4 = results{1}{1}{1}{1}{1}{2};
y4 = results{1}{1}{1}{2}{1}{2};
w4 = results{1}{1}{1}{3}{1}{2};

figure;
for i=1:10,
    subplot(2,5,i);
    plotNetwork(x4(i,:),w4,y4(i,:),1);
end

clear results i