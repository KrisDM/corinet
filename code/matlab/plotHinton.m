function plotHinton(W,scale,colour,type,equal)
% Plot a network consisting of a single weightmatrix
% in a format specified by Hinton.
%   plotHinton(W,scale,colour,type,equal)
% W: a matrix containing network weights (each node 1 column)
% scale: a scaling factor for weight magnitudes
% colour: 1 for red, 2 for green, 3 for blue
% type=0: variable size boxes (size relates to strength)
% type=1: image (color intensity relates to strength)
% type=2: equal size squares (color intensity relates to strength)
% equal: 1 if aspect ratio should be equal, 0 if not

numInputs = size(W,1);
numNodes = size(W,2);

W(W<0)=0; %reset all negative weights

if type==0, %draw as squares: strength indicated by size of square
    colstr = ['r' 'g' 'b'];
    if(equal==0)
        %calc aspect ratio - if not going to set axis equal
	    plot(numInputs+0.5,numNodes-0.5,'bx');
	    hold on 
	    plot(0.5,-0.5,'bx');
	    axis equal
	    a=axis;
	    aspectX=numInputs/abs(a(2)-a(1));
	    aspectY=numNodes/abs(a(4)-a(3));
	    aspectXX=aspectX./max(aspectX,aspectY);
	    aspectYY=aspectY./max(aspectX,aspectY);
	    hold off;
    else
	    aspectXX=1;
	    aspectYY=1;
    end
    for i=1:numInputs,
	    for j=1:numNodes,
	        box_widthX=aspectXX*0.5*W(i,j)/(scale);
	        box_widthY=aspectYY*0.5*W(i,j)/(scale);  
	        fill([i-box_widthX,i+box_widthX,i+box_widthX,i-box_widthX],numNodes+1-[j-box_widthY,j-box_widthY,j+box_widthY,j+box_widthY],colstr(colour));
	        hold on;
	    end
    end
    if equal==1, 
        axis equal; 
    end
    axis ij;
    axis([0.5,numInputs+0.5,0.5,numNodes+0.5])
elseif type==1
    %draw as an image: strength indicated by pixel darkness
    %W is true data value (greater than 0) and is scaled to be between 0 and 255
    image(uint8(round((W'./scale)*255)),'CDataMapping','scaled'),
    colormap(gray)
    map=colormap;
    map=flipud(map);
    map(1:64,colour)=map(1:64,colour)*0.0+1;%*0.33+0.66;
    colormap(map)
    caxis([0,255])%if we remove this then each subplot is scaled independently
    axis on;
    axis ij;
    if(equal==1), 
        axis equal;
        axis tight;
    end
else
    %draw as equal sized squares: strength indicated by darkness of square
    if(equal==0)
	    %calc aspect ratio - if not going to set axis equal
	    plot(numInputs+0.5,numNodes-0.5,'bx');
	    hold on 
	    plot(0.5,-0.5,'bx');
	    axis equal
	    a=axis;
	    aspectX=numInputs/abs(a(2)-a(1));
	    aspectY=numNodes/abs(a(4)-a(3));
	    aspectXX=aspectX./max(aspectX,aspectY);
	    aspectYY=aspectY./max(aspectX,aspectY);
	    hold off;
    else
	    aspectXX=1;
	    aspectYY=1;
    end
    box_widthX=aspectXX*0.33;
    box_widthY=aspectYY*0.33;
    for i=1:numInputs
	    for j=1:numNodes
	        fill([i-box_widthX,i+box_widthX,i+box_widthX,i-box_widthX],numNodes+1-[j-box_widthY,j-box_widthY,j+box_widthY,j+box_widthY],ones(1,4).*round((W(i,j)./scale)*255),'FaceColor','flat');
	        hold on
	    end
    end
    colormap(gray)
    map=colormap;
    map=flipud(map);
    map(1:64,colour)=map(1:64,colour)*0.0+1;%*0.33+0.66;
    colormap(map)
    caxis([0,255])%if we remove this then each subplot is scaled independently
    if(equal==1), 
        axis equal; 
    end
    axis ij;
    axis([0.5,numInputs+0.5,0.5,numNodes+0.5])
end
set(gca,'YTick',[])
set(gca,'XTick',[])
drawnow

