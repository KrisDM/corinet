function readCorinet(fileName,createNames,execution)
%  Reads result files in corinet markup language file format
%   "readCorinet(fileName,createNames,execution)
%
%   "fileName" contains the path and name of the file to be read
%   "createNames" - optional - if 1, named variables are created in the
%   calling function; if 0, one cell array is created
%   "execution" - optional - a number; if specified, only the data 
%   associated with that execution are read

fid= fopen(fileName,'rt');

if (fid<0) 
    fprintf(2,'Error opening file %s. Does it exist? Are you sure?\n',fileName);
    return;
end

if (nargin == 1)
    createNames = 0;
end

token = fscanf(fid,'%c',1);
while (~feof(fid))
    if (strcmp(token,'<'))
        token = fscanf(fid,'%c',1);
        if (strcmp(token,'?')) %scan through the prolog
            scanUntil(fid,'>');
        elseif (strcmp(token,'!')) %scan trough a comment
            token = fscanf(fid,'%c',2);
            if (strcmp(token,'--')) %start of a comment, scan until the end
                scanUntil(fid,'-->');
            else
                scanUntil(fid,'>'); %start of a processing instruction, scan until the end
            end    
        elseif (strcmp(token,'/')) %scan through a closing tag
            tagName = scanTag(fid);
            switch (tagName)
                case 'v'
                    if (synapses)
                        vCounter = vCounter + 1;
                    end
                case 'w'
                    vCounter = vCounter + 1;
                case 'p'
                    vCounter = vCounter + 1;
                case 'cycle'
                    assignin('caller','tempLabels',thisCycleTimeLabels);
                    assignin('caller','tempResults',thisCycleResults);
                    if (createNames)
                        evalin('caller',sprintf('%s{%d}{1} = %s;',varName,cycleCounter,'tempLabels'));
                        evalin('caller',sprintf('%s{%d}{2} = %s;',varName,cycleCounter,'tempResults'));
                    else
                        if (netCounter) 
                            evalin('caller',sprintf('results{%d}{1}{%d}{%d}{%d}{1} = %s;',exCounter,netCounter,elCounter,cycleCounter,'tempLabels'));
                            evalin('caller',sprintf('results{%d}{1}{%d}{%d}{%d}{2} = %s;',exCounter,netCounter,elCounter,cycleCounter,'tempResults'));
                        else
                            evalin('caller',sprintf('results{%d}{2}{%d}{%d}{1} = %s;',exCounter,taskCounter,cycleCounter,'tempLabels'));
                            evalin('caller',sprintf('results{%d}{2}{%d}{%d}{2} = %s;',exCounter,taskCounter,cycleCounter,'tempResults'));
                        end
                    end
                    cycleCounter = cycleCounter + 1;
                case 'values'
                    elCounter = elCounter + 1;
                case 'weights'
                    elCounter = elCounter + 1;
                case 'synapses'
                    elCounter = elCounter + 1;
                case 'network'
                    netCounter = netCounter + 1;
                case 'task'
                    taskCounter = taskCounter + 1;
                case 'execution'
                    exCounter = exCounter + 1;
            end
        else %scan through an opening tag
            tagName = [token scanTag(fid)];
            switch (tagName)
                case 'annotation'
                    scanUntil(fid,'</annotation>');
                case 'results'
                    scanUntil(fid,'>');
                    exCounter = 1;
                    if (~createNames)
                        assignin('caller','results',cell(0));
                    end
                case 'execution'
                    if (~createNames)
                        evalin('caller',sprintf('results{%d} = cell(1,2);',exCounter));
                    end
                    if (nargin == 3) 
                        if (exCounter < execution) %skip this entire execution
                            scanUntil(fid,'</execution>');
                            exCounter = exCounter + 1;
                        elseif (exCounter > execution) %stop reading
                            break;
                        end
                    end
                    netCounter = 1;
                    taskCounter = 1;
                case 'network'
                    %scan the rest of this tag to see if it contains data
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    if (isempty(strfind(tagRemainder,'/')))
                        if (~createNames)
                            evalin('caller',sprintf('results{%d}{1}{%d} = cell(0);',exCounter,netCounter));
                        end
                        elCounter = 1;
                    end
                case 'task'
                    netCounter = 0;
                    %scan the rest of this tag to see if it contains data
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    if (isempty(strfind(tagRemainder,'/')))
                        idName = getAttrVal('id',tagRemainder);
                        if (createNames)
                            varName = sprintf('taskPatterns_%s_Ex%d',idName,exCounter);
                            assignin('caller',varName,cell(0));
                        else
                            evalin('caller',sprintf('results{%d}{2}{%d} = cell(0);',exCounter,taskCounter));
                        end
                        cycleCounter = 1;
                        numVals = 0;
                    end
                case 'values'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    if (isempty(strfind(tagRemainder,'/')))
                        idName = getAttrVal('id',tagRemainder);
                        typeName = getAttrVal('type',tagRemainder);
                        if (createNames)
                            varName = sprintf('%s_%s_Ex%d',typeName,idName,exCounter);
                            assignin('caller',varName,cell(0));
                        else
                            evalin('caller',sprintf('results{%d}{1}{%d}{%d} = cell(0);',exCounter,netCounter,elCounter));
                        end
                        cycleCounter = 1;
                        numVals = 0;
                    end
                    synapses = 0;
                case 'weights'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    if (isempty(strfind(tagRemainder,'/')))
                        idName = getAttrVal('id',tagRemainder);
                        if (createNames)
                            varName = sprintf('weights_%s_Ex%d',idName,exCounter);
                            assignin('caller',varName,cell(0));
                        else
                            evalin('caller',sprintf('results{%d}{1}{%d}{%d} = cell(0);',exCounter,netCounter,elCounter));
                        end
                        cycleCounter = 1;
                        numVals = 0;
                    end
                case 'synapses'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    if (isempty(strfind(tagRemainder,'/')))
                        idName = getAttrVal('id',tagRemainder);
                        if (createNames)
                            varName = sprintf('synapses_%s_Ex%d',idName,exCounter);
                            assignin('caller',varName,cell(0));
                        else
                            evalin('caller',sprintf('results{%d}{1}{%d}{%d} = cell(0);',exCounter,netCounter,elCounter));
                        end
                        cycleCounter = 1;
                        numVals = 0;
                    end
                    synapses = 1;
                case 'cycle'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    if (createNames)
                        evalin('caller',sprintf('%s{%d} = cell(1,2);',varName,cycleCounter));
                    else
                        if (netCounter)
                            evalin('caller',sprintf('results{%d}{1}{%d}{%d}{%d} = cell(1,2);',exCounter,netCounter,elCounter,cycleCounter));
                        else
                            evalin('caller',sprintf('results{%d}{2}{%d}{%d} = cell(1,2);',exCounter,taskCounter,cycleCounter));
                        end
                    end
                    thisCycleResults = [];
                    thisCycleTimeLabels= [];
                    vCounter = 1;   
                case 'w'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    iCounter = str2num(getAttrVal('i',tagRemainder)) + 1;
                    if (~isempty(findstr(tagRemainder,'s')))
                        sCounter = str2num(getAttrVal('s',tagRemainder)) + 1;
                    else
                        sCounter = 0;
                    end
                    thisCycleTimeLabels(vCounter,:) = [iCounter sCounter];
                    subCounter = 1;
                case 'p'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    iCounter = str2num(getAttrVal('i',tagRemainder)) + 1;
                    if (~isempty(findstr(tagRemainder,'s')))
                        sCounter = str2num(getAttrVal('s',tagRemainder)) + 1;
                    else
                        sCounter = 0;
                    end
                    thisCycleTimeLabels(vCounter,:) = [iCounter sCounter];
                    subCounter = 1;
                case 'v'
                    tagRemainder = scanUntilAndReturn(fid,'>');
                    iCounter = str2num(getAttrVal('i',tagRemainder)) + 1;
                    if (~isempty(findstr(tagRemainder,'s')))
                        sCounter = str2num(getAttrVal('s',tagRemainder)) + 1;
                    else
                        sCounter = 0;
                    end
                    thisCycleTimeLabels(vCounter,:) = [iCounter sCounter];
                    if (~synapses)
                        if (numVals) 
                            thisCycleResults(vCounter,:) = fscanf(fid,'%g',numVals)';
                        else
                            valuesStr = scanUntilAndReturn(fid,'<');
                            temp = str2num(valuesStr(1:end-1));
                            numVals = length(temp);
                            thisCycleResults(vCounter,:) = temp;
                        end
                        vCounter = vCounter + 1;
                    else
                        subCounter = 1;
                    end
                case 'n'
                    if (numVals) 
                        thisCycleResults(:,subCounter,vCounter) = fscanf(fid,'%g',numVals);
                    else
                        valuesStr = scanUntilAndReturn(fid,'<');
                        temp = str2num(valuesStr(1:end-1));
                        numVals = length(temp);
                        thisCycleResults(:,subCounter,vCounter) = temp;
                    end     
                    subCounter = subCounter + 1;
                case 'r'
                    if (numVals) 
                        thisCycleResults(subCounter,:,vCounter) = fscanf(fid,'%g',numVals)';
                    else
                        valuesStr = scanUntilAndReturn(fid,'<');
                        temp = str2num(valuesStr(1:end-1));
                        numVals = length(temp);
                        thisCycleResults(subCounter,:,vCounter) = temp;
                    end  
                    subCounter = subCounter + 1;
            end
        end
    end
    token = fscanf(fid,'%c',1);
end
evalin('caller','clear tempResults;');
evalin('caller','clear tempLabels;');
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
while (~strcmp(token,' ') & ~strcmp(token,'>'))
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


    