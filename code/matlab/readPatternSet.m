function patternSet = readPatternSet(filename)
%  Reads patternSet files in CORINET Markup Language file format
%   "patternSet = readPatternSet(filename)"
%
%  "fileName" contains the path and name of the file to be read
%  "patternSet" is a cell array, with one cell for each pattern.

patternSet = cell(0);
pCounter = 1;

fid= fopen(filename,'rt');

if (fid<0) 
    fprintf(2,'Error opening file %s. Does it exist? Are you sure?\n',filename);
    return;
end

columns = 1;
rows = 1;
token = fscanf(fid,'%c',1);

while (~feof(fid))
    if (strcmp(token,'<'))
        token = fscanf(fid,'%c',1);
        if (strcmp(token,'?')) %scan through the prolog
            scanUntil(fid,'>');
        elseif (strcmp(token,'!')) %scan through a comment
            token = fscanf(fid,'%c',2);
            if (strcmp(token,'--')) %start of a comment, scan until the end
                scanUntil(fid,'-->');
            else
                scanUntil(fid,'>'); %start of a processing instruction, scan until the end
            end    
        elseif (strcmp(token,'/')) %scan through a closing tag
            tagName = scanTag(fid);
            switch (tagName) 
                case 'p' %the closing tag of a pattern
                    patternSet{pCounter} = temp;
                    pCounter = pCounter + 1;
                case 'r'
                    eCounter = eCounter + 1;
                case 'c'
                    eCounter = eCounter + 1;
                case 'patternSet' %the closing tag of the set, leave the while loop
                    break;
            end
        else %scan through an opening tag
            tagName = [token scanTag(fid)];
            switch (tagName)
                case 'p'
                    eCounter = 1;
                    temp = zeros(rows,columns);
                case 'r'
                    temp(eCounter,:) = fscanf(fid,'%g',columns)';
                case 'c'
                    temp(:,eCounter) = fscanf(fid,'%g',rows);
                case 'patternSet'
                    attr = scanUntilAndReturn(fid,'>');
                    columns = str2num(getAttrVal('columns',attr));
                    if (~isempty(strfind(attr,'rows')))
                        rows = str2num(getAttrVal('rows',attr));
                    end
                case 'annotation'
                    scanUntil(fid,'</annotation>');
            end
        end
    end
    token = fscanf(fid,'%c',1);    
end
fclose(fid);

%---------------------------------------------------------------------
function attrVal = getAttrVal(attrName,str)
%  Get the attribute value
attrStart = strfind(str,attrName);
attrVal = strtok(str(attrStart+length(attrName)+2:end),'"');

function tagName = scanTag(fid)
%  Scan the tag name
tagName = '';
token = '';
while (~strcmp(token,' ') && ~strcmp(token,'>'))
    tagName = [tagName token];
    token = fscanf(fid,'%c',1);
end

function scanUntil(fid,str)
%  Scans until it encounters the string 'str'
token = '';
while (1)
    while (~strcmp(token,str(1)))
        token = fscanf(fid,'%c',1);
    end
    if (length(str) > 1)
        token = [token fscanf(fid,'%c',length(str)-1)];
    end
    if (strcmp(token,str))
        break;
    else
        fseek(fid,-length(str)+1,0);
    end
end

function returnStr = scanUntilAndReturn(fid,str)
%  Scans until it encounters the string 'str' and returns the scanned
%  string.
token = '';
returnStr = '';
while (1)
    while (~strcmp(token,str(1)))
        returnStr = [returnStr token];
        token = fscanf(fid,'%c',1);
    end
    if (length(str) > 1)
        token = [token fscanf(fid,'%c',length(str)-1)];
    end
    if (strcmp(token,str))
        returnStr = [returnStr token];
        break;
    else
        returnStr = [returnStr token(1)];
        fseek(fid,-length(str)+1,0);
    end
end