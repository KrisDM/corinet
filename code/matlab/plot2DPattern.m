function plot2DPattern(P,colour,equal)
% Plot a single 2D pattern
%   plot2DPattern(P,colour,equal)
% P: a 2D matrix containing a single pattern
% colour: 1 for red, 2 for green, 3 for blue
% equal: 1 if aspect ratio should be equal, 0 if not

%draw as an image: strength indicated by pixel darkness
%P is true data value (greater than 0) and is scaled to be between 0 and 255
image(uint8(round((P)*255)),'CDataMapping','scaled'),
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
set(gca,'YTick',[]);
set(gca,'XTick',[]);
drawnow;

