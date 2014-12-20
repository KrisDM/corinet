function barsRep = barsRepresented3(w,numRows,numCols,barWidth)
%Determine if the two wide bars are represented by a weightmatrix
%This function implements the representation criterium for double bars
%used in the JMLR2006 paper "Learning image components...".
%   numRepresented = barsRepresented1(w,numRows,numCols)
%w: a weightmatrix recorded from a single integrationSite
%numRows: number of rows in the input pattern
%numCols: number of colums in the input pattern

numNodes = size(w,2);
numBars = 2;
numInputs = numRows*numCols;

%ignore all negative weights
w(w<0) = 0;

%reshape the weightmatrix so that it corresponds to the input image
%resulting in a numRows*numCols matrix of weights for each node 
w = reshape(w,[numRows numCols numNodes]);
%get the sum of weights for each row and each column in the image
%each row in this matrix corresponds to a sum of weights
%each column in this matrix corresponds to a node in the block
horBar = squeeze(sum(sum(w(numRows-barWidth+1:numRows,:,:),2),1));
verBar = squeeze(sum(sum(w(:,numCols-barWidth+1:numCols,:),1),2));
barsRep = [];
if sum(horBar > 0.9),
    barsRep = [barsRep 1];
end
if sum(verBar > 0.9),
    barsRep = [barsRep 2];
end


