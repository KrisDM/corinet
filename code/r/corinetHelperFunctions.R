getAttrVal <- function(attrName,str)
#  Get the attribute value
{
	tokens <- strsplit(str," ")[[1]]
	attrNum <- grep(attrName,tokens)
	attrVal <- strsplit(tokens[attrNum],split='"')[[1]][2]
}

scanTag <- function(fid)
#  Scan the tag name
{
	tagName <- ""
	token <- ""
	while (!identical(token," ") && !identical(token,">")) {
		tagName <- append(tagName,token)
		token <- readChar(fid,1)
	}
	tagName <- paste(tagName,sep="",collapse="")
}

scanUntil <- function(fid,str)
#  Scans until it encounters the string 'str'
{
    token <- ""
	while (1) {
		while (!(identical(token,substr(str,1,1)))) {
			token <- readChar(fid,1)
		}
		if (nchar(str) > 1) {
			token <- append(token,readChar(fid,nchar(str)-1))
		}
		token <- paste(token,sep="",collapse="")
		if (identical(token,str)) {
			break
		}
		else {
			token <- readChar(fid,1)
		}
	}
}

scanUntilAndReturn <- function(fid,str)
#  Scans until it encounters the string 'str' and returns the scanned string
{
	returnStr <- ""
	token <- ""
	while (1) {
		while (!(identical(token,substr(str,1,1)))) {
			if (identical(token,"\n")) {
				token <- " "
			}
			returnStr <- append(returnStr,token)
			token <- readChar(fid,1)
		}
		if (nchar(str) > 1) {
			token <- append(token,readChar(fid,nchar(str)-1))
		}
		token <- paste(token,sep="",collapse="")
		if (identical(token,str)) {
			break
		}
		else {
			returnStr <- append(returnStr,token)
			token <- readChar(fid,1)
		}
	}
	returnStr <- paste(returnStr,sep="",collapse="")
}
