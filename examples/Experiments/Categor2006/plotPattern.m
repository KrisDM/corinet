function plotPattern(w,maxVal)

set(gcf,'Color',[1,1,1]);
hold on;

%horizontal lines
plot([0,1],[2,2],'LineWidth',3,'Color',cv(w(1),maxVal));
plot([1,2],[2,2],'LineWidth',3,'Color',cv(w(2),maxVal));
plot([0,1],[1,1],'LineWidth',3,'Color',cv(w(3),maxVal));
plot([1,2],[1,1],'LineWidth',3,'Color',cv(w(4),maxVal));
plot([0,1],[0,0],'LineWidth',3,'Color',cv(w(5),maxVal));
plot([1,2],[0,0],'LineWidth',3,'Color',cv(w(6),maxVal));
%vertical
plot([0,0],[1,2],'LineWidth',5,'Color',cv(w(7),maxVal));
plot([1,1],[1,2],'LineWidth',5,'Color',cv(w(8),maxVal));
plot([2,2],[1,2],'LineWidth',3,'Color',cv(w(9),maxVal));
plot([0,0],[0,1],'LineWidth',3,'Color',cv(w(10),maxVal));
plot([1,1],[0,1],'LineWidth',4,'Color',cv(w(11),maxVal));
plot([2,2],[0,1],'LineWidth',4,'Color',cv(w(12),maxVal));
%diagonals
if w(17)>w(13)
  plot([0,1],[2,1],'LineWidth',3,'Color',cv(w(13),maxVal));
  plot([0,1],[1,2],'LineWidth',3,'Color',cv(w(17),maxVal));
else
  plot([0,1],[1,2],'LineWidth',3,'Color',cv(w(17),maxVal));
  plot([0,1],[2,1],'LineWidth',3,'Color',cv(w(13),maxVal));
end
if w(18)>w(14)
  plot([1,2],[2,1],'LineWidth',3,'Color',cv(w(14),maxVal));
  plot([1,2],[1,2],'LineWidth',3,'Color',cv(w(18),maxVal));
else
  plot([1,2],[1,2],'LineWidth',3,'Color',cv(w(18),maxVal));
  plot([1,2],[2,1],'LineWidth',3,'Color',cv(w(14),maxVal));
end
if w(19)>w(15)
  plot([0,1],[1,0],'LineWidth',3,'Color',cv(w(15),maxVal));
  plot([0,1],[0,1],'LineWidth',3,'Color',cv(w(19),maxVal));
else
  plot([0,1],[0,1],'LineWidth',3,'Color',cv(w(19),maxVal));
  plot([0,1],[1,0],'LineWidth',3,'Color',cv(w(15),maxVal));
end  
if w(20)>w(16)
  plot([1,2],[1,0],'LineWidth',3,'Color',cv(w(16),maxVal)); 
  plot([1,2],[0,1],'LineWidth',3,'Color',cv(w(20),maxVal));
else
  plot([1,2],[0,1],'LineWidth',3,'Color',cv(w(20),maxVal));
  plot([1,2],[1,0],'LineWidth',3,'Color',cv(w(16),maxVal)); 
end

%dots
plot(0,0,'o','MarkerSize',12,'Color',cv(w(21),maxVal),'MarkerFaceColor',cv(w(21),maxVal));
plot(1,0,'o','MarkerSize',12,'Color',cv(w(22),maxVal),'MarkerFaceColor',cv(w(22),maxVal));
plot(2,0,'o','MarkerSize',12,'Color',cv(w(23),maxVal),'MarkerFaceColor',cv(w(23),maxVal));
plot(0,1,'o','MarkerSize',12,'Color',cv(w(24),maxVal),'MarkerFaceColor',cv(w(24),maxVal));
plot(1,1,'o','MarkerSize',12,'Color',cv(w(25),maxVal),'MarkerFaceColor',cv(w(25),maxVal));
plot(2,1,'o','MarkerSize',12,'Color',cv(w(26),maxVal),'MarkerFaceColor',cv(w(26),maxVal));
plot(0,2,'o','MarkerSize',12,'Color',cv(w(27),maxVal),'MarkerFaceColor',cv(w(27),maxVal));
plot(1,2,'o','MarkerSize',12,'Color',cv(w(28),maxVal),'MarkerFaceColor',cv(w(28),maxVal));
plot(2,2,'o','MarkerSize',12,'Color',cv(w(29),maxVal),'MarkerFaceColor',cv(w(29),maxVal));
axis tight;
axis off;
axis equal;

function c=cv(w,maxVal)
if w>0
  c=1-[1,1,1].*min(1,max(w,0)/maxVal)^2;
else
  c=1-[0,1,1].*min(1,min(w,0)/maxVal)^2;
end
