function returnVal = corinet(fileName,flag)
%  Runs the external corinet program
%    returnVal = corinet(fileName,flag)
%
%  fileName: the name of a corinet markup language file in the working directory
%  flag: optional, one of the flags allowed in running corinet
%  returnVal: the return code from corinet, 0 if it ran successfully, non-zero if
%  not successful

if (nargin == 1)
    flag = '';
end

%get the current directory and construct an absolute path
dirName = pwd;
fullPath = [dirName '/' fileName];

%set quotes around a path that contains spaces
if (~isempty(findstr(fullPath,' ')))
    fullPath = ['"' fullPath '"'];
end

fullCommand = ['corinet ' flag ' ' fullPath];
systemCommand = ['system(''' fullCommand ''')'];
returnVal = evalin('caller',systemCommand);
