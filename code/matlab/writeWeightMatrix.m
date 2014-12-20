function writeWeightMatrix(filename,W)
%  Writes a single weightMatrix to corinet markup language file format
%    "writeWeightMatrix(filename,W)"
%
%  "fileName" contains the path and name of the file to be written
%  "W" is a 2D matrix, with one column for each node

fid= fopen(filename,'wt');

[numInputs,numNodes] = size(W);

if (fid<0) 
    fprintf(2,'Error opening file %s.\n',filename);
else
    fprintf(fid,'<?xml version="1.0" encoding="UTF-8"?>\n');
    fprintf(fid,'<w xmlns="http://www.corinet.org/namespaces/CORINETSetup" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">\n');
    for j=1:numNodes,
        fprintf(fid,'    <n>');
        fprintf(fid,'%-.4g  ',W(:,j));
        fprintf(fid,'    </n>\n');   
    end
    fprintf(fid,'</w>\n');
    fclose(fid);
end
