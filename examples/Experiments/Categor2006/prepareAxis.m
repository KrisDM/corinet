function prepareAxis(axisLimits,xLabelText,yLabelText,fontSize)

box on;
axis(axisLimits);
set(gca,'xTick',[]);
set(gca,'yTick',[]);
xlabel(xLabelText,'FontSize',fontSize);
ylabel(yLabelText,'FontSize',fontSize);