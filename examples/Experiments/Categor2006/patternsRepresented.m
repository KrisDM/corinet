function [patPresent,repNodes] = patternsRepresented(w,pat,tol)
%returns the list of patterns of p that are represented in w
%  patList = patternsRepresented(w,pat,tol)
%p is a 2-dimensional matrix, one pattern per column
%w is a 2-dimensional weight matrix, one node per column
%tol is the tollerance: none of absent features may be higher in w than
%1/numFeatures/tol 

numNodes = size(w,2);
numPatterns = size(pat,2);
numInputs = size(w,1);
numFeatures = sum(pat > 0);

patPresent = zeros(1,numPatterns);
repNodes = cell(1,numPatterns);

for p=1:numPatterns,
    patMat = repmat((pat(:,p)>0),1,numNodes);
    patTol = (max(reshape(w(~patMat),numInputs-numFeatures(p),numNodes)) < 1/numFeatures(p)/tol) & (min(reshape(w(patMat),numFeatures(p),numNodes)) > 1/numFeatures(p)/tol);
    if (sum(patTol))
        patPresent(p) = 1;
        repNodes{p} = find(patTol);
    end
end

   