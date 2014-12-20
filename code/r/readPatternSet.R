readPatternSet <- function(fileName)
#  Reads patternSet files in CORINET Markup Language file format
#   "patternSet <- readPatternSet(filename)"
#
#  "fileName" contains the path and name of the file to be read
#  "patternSet" is a list, with one element for each pattern.

{
	helperPath <- paste(Sys.getenv("CORINETROOT"),"code/r/corinetHelperFunctions.R",sep="")
	source(helperPath)
	patternSet <- list(0)
	pCounter <- 1

	fid <- file(description = fileName,open = "rt")

	columns <- 1
	rows <- 1
	token <- readChar(fid,1)
	while (length(token)) {
    	if (identical(token,"<")) {
        	token <- readChar(fid,1)
        	if (identical(token,"?")) {#scan through the prolog
           		scanUntil(fid,">")
			}
       	    else if (identical(token,'!')) {#scan through a comment
           	    token <- readChar(fid,2)
           	    if (identical(token,'--')) {#start of a comment, scan until the end
               	    scanUntil(fid,'-->')
			    }
                else {#start of a processing instruction, scan until the end
                    scanUntil(fid,'>') 
			    }
		    }
       	    else if (identical(token,'/')) {#scan through a closing tag
          	    tagName = scanTag(fid)
			    if (identical(tagName,'p')) {#the closing tag of a pattern
                    patternSet[[pCounter]] <- temp
                    pCounter <- pCounter + 1
			    }
				else if (identical(tagName,'patternSet')) {
                    break
				}
			}
            else {#scan through an opening tag
			    tagName <- append(token,scanTag(fid))
           	    tagName <- paste(tagName,sep="",collapse="")
				if (identical(tagName,'p')) {#the opening tag of a pattern
                  	eCounter <- 1
                   	temp <- matrix(nrow=rows,ncol=columns)
				}
                else if (identical(tagName,'r')) {
                    valstr = scanUntilAndReturn(fid,"<")
                    vals = strsplit(valstr,split=" ")
                   	temp[eCounter,] <- type.convert(vals[[1]])
                   	eCounter <- eCounter + 1
				}
				else if (identical(tagName,'c')) {
				    valstr = scanUntilAndReturn(fid,"<")
                    vals = strsplit(valstr,split=" ")
                   	temp[,eCounter] <- type.convert(vals[[1]])
                   	eCounter <- eCounter + 1
				}
				else if (identical(tagName,'patternSet')) {
                   	attr <- scanUntilAndReturn(fid,">")
                   	columns <- type.convert(getAttrVal('columns',attr))[1]
                   	if (length(grep("rows",attr))) {
                   		rows <- type.convert(getAttrVal('rows',attr))[1]
                   	}
				}
				else if (identical(tagName,'annotation')) {
				    scanUntil(fid,'</annotation>')
				}
			}
		}
		else {
   	        token <- readChar(fid,1)
   	    }
	}
    close(fid)
    patternSet
}