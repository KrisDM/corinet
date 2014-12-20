function writePatternSet(filename,set)
%  Writes patternSet files in corinet markup language file format
%    "writePatternSet(filename,set)"
%
%  "fileName" contains the path and name of the file to be written
%  "set" is a cell array, with one cell for each pattern

fid= fopen(filename,'wt');

[rows,cols] = size(set{1});

for i=2:length(set)
    if (rows ~= size(set{i},1) || cols ~= size(set{i},2))
        fprintf(2,'Size of pattern %d is different from size of other patterns.\n',i);
        fprintf(2,'I will continue writing the <patternSet>, so that you can check and correct this error.\n');
    end
end

if (fid<0) 
    fprintf(2,'Error opening file %s.\n',filename);
else
    fprintf(fid,'<?xml version="1.0" encoding="UTF-8"?>\n');
    fprintf(fid,'<patternSet xmlns="http://www.corinet.org/namespaces/CORINETSetup" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\n');
    fprintf(fid,'columns="%d"',cols);
    if (rows > 1)
        fprintf(fid,' rows="%d"',rows);
    end
    fprintf(fid,'>\n');
    for i=1:length(set),
        fprintf(fid,'    <p>\n');
        temp = set{i};
        for j=1:size(temp,1),
            fprintf(fid,'        <r>');
            fprintf(fid,'%-.4g  ',temp(j,:));
            fprintf(fid,'</r>\n');
        end
        fprintf(fid,'    </p>\n');   
    end
    fprintf(fid,'</patternSet>\n');
    fclose(fid);
end
