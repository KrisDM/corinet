function barsRep = barsRepresented2(w,numRows,numCols)
%Determine which double bars are represented by a weightmatrix
%This function implements the representation criterium for double bars
%used in the JMLR2006 paper "Learning image components...".
%   numRepresented = barsRepresented1(w,numRows,numCols)
%w: a weightmatrix recorded from a single integrationSite
%numRows: number of rows in the input pattern
%numCols: number of colums in the input pattern

numNodes = size(w,2);
numBars = numRows-1 + numCols-1;
numInputs = numRows*numCols;

%ignore all negative weights
w(w<0) = 0;

%reshape the weightmatrix so that it corresponds to the input image
%resulting in a numRows*numCols matrix of weights for each node 
w = reshape(w,[numRows numCols numNodes]);
%get the sum of weights for each row and each column in the image
%each row in this matrix corresponds to a sum of weights
%each column in this matrix corresponds to a node in the block
[sumRowCol,barIndex] = sort([squeeze(sum(w(1:end-1,:,:),2)+sum(w(2:end,:,:),2));squeeze(sum(w(:,1:end-1,:),1)+sum(w(:,2:end,:),1))]);
minRowCol = [squeeze(min(min(w(1:end-1,:,:),[],2),min(w(2:end,:,:),[],2)));squeeze(min(min(w(:,1:end-1,:),[],1),min(w(:,2:end,:),[],1)))];
minW = diag(minRowCol(barIndex(numBars,:),1:numNodes));

%for each node, get the bar with the heighest weights
maxBarIndex = barIndex(numBars,:);

%select only those bars that have a sum-of-weights more than twice as much
%than any other bar, and make sure each bar is counted only once
barsRep = unique(maxBarIndex((sumRowCol(numBars,:) > 1.5*sumRowCol(numBars-1,:)) & (minW' > 1/numInputs)));


