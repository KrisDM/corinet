function plotNetwork(x,W,y,labely)
% Plot a network specified by a single weightmatrix
%   plotNetwork(x,W,y,labely)
% x: a vector containing the input to the network
% W: a matrix containing network weights (each node 1 column)
% y: a vector containing the output of the network
% labely: bool, if true, output values are used as labels 

if nargin<4
   labely=0;
end

m=length(x);
n=length(y);
%if number of inputs and nodes differ
moffset=0;
noffset=0;
if m>n
   noffset=0.5*(m-n);
end
if m>n
   moffset=0.5*(n-m);
end

units=get(gca,'Units');
set(gca,'Units','points');
loc=get(gca,'Position');
ptspernode=min([loc(3)./(max([m,n])+1),loc(4)./2]);
markersize=fix(ptspernode*0.8);
fntsize=max(8,fix(ptspernode/4));
set(gca,'Units',units);

for i=1:m
   for j=1:n
	if W(i,j)>0.01,
	  plot([i+moffset,j+noffset],[0,1],'b-','LineWidth',4*W(i,j));
	  hold on
	  z=0.25;
	  Halign='center'; 
      if i+moffset>j+noffset, 
          Halign='right';
	  elseif i+moffset<j+noffset, 
          Halign='left'; 
      end
	end
	if W(i,j)<-0.01;
	  plot([i+moffset,j+noffset],[0,1],'r--','LineWidth',-4*W(i,j));
	  hold on
	  z=0.75;
	  Halign='center'; 
      if i+moffset>j+noffset, 
          Halign='right';
	  elseif i+moffset<j+noffset,
          Halign='left'; 
      end
	end
   end
end

%don't label tiny activation values
x(find(x<0.01))=0;
y(find(y<0.01))=0;
y = floor(y*100)/100;

for i=1:m
 text(i+moffset,0-0.10,num2str(x(i),3),'HorizontalAlignment','center','VerticalAlignment','top','FontSize',fntsize)
end
for j=1:n
   plot(j+noffset,1,'ko','MarkerSize',markersize,'MarkerFaceColor','w');
   if y(j)>0.0,
     plot(j+noffset,1,'go','MarkerSize',y(j)*markersize,'MarkerFaceColor','g'); 
   end
   if labely,
       labelText = sprintf('%g',y(j));
       if (labelText(1) == '0')
           if (length(labelText) > 1)
               labelText = labelText(2:end);
           else
               labelText = '';
           end
       end
      text(j+noffset,1+markersize/80,labelText,'HorizontalAlignment','center','VerticalAlignment','bottom','FontSize',fntsize);
   end
end

axis([0.5,max([m,n])+0.5,-0.5,1.5])
axis off
