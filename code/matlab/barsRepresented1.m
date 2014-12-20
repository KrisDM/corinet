function numRepresented = barsRepresented1(w,numRows,numCols)
%Get the number of bars represented by a weightmatrix
%This function implements the representation criterium
%used in the NC2002 paper "Pre-integration lateral...".
%   numRepresented = barsRepresented1(w,numRows,numCols)
%w: a weightmatrix recorded from a single integrationSite
%numRows: number of rows in the input pattern
%numCols: number of colums in the input pattern

numNodes = size(w,2);
numBars = numRows + numCols;

%ignore all negative weights
w(w<0) = 0;

%reshape the weightmatrix so that it corresponds to the input image
%resulting in a numRows*numCols matrix of weights for each node 
w = reshape(w,[numRows numCols numNodes]);
%get the sum of weights for each row and each column in the image
%each row in this matrix corresponds to a sum of weights
%each column in this matrix corresponds to a node in the block
[sumRowCol,barIndex] = sort([squeeze(sum(w,2));squeeze(sum(w,1))]);

%for each node, get the bar with the heighest weights
maxBarIndex = barIndex(numBars,:);

%select only those bars that have a sum-of-weights more than twice as much
%than any other bar, and make sure each bar is counted only once
numRepresented = length(unique(maxBarIndex(sumRowCol(numBars,:) > 2*sumRowCol(numBars-1,:))));


