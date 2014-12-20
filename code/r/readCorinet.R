readCorinet <-function(fileName,createNames = FALSE,execution = 0)
#  Reads result files in CORINET Markup Language file format
#   "readCorinet(fileName,execution)
#
#   "fileName" contains the path and name of the file to be read
#   "createNames" - optional - if TRUE, named variables are created in the
#   calling function; if FALSE, one cell array is created
#   "execution" if > 0 only the data 
#   associated with that execution are read

{
	helperPath <- paste(Sys.getenv("CORINETROOT"),"code/r/corinetHelperFunctions.R",sep="")
	source(helperPath)

	fid <- file(description = fileName,open = "rt")
	caller = parent.frame()
    
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
          	    if (identical(tagName,'results')) {
          	        eval(expression(rm(exName,elemName,cycleName)),envir=caller)
				    break
				} 
				else if (identical(tagName,'execution')) {
				    exCounter <- exCounter + 1
		        }
				else if (identical(tagName,'cycle')) {
				    assign('tempLabels',matrix(thisCycleTimeLabels,ncol=2,byrow=TRUE,dimnames=list(c(),c('iteration','step'))),caller)
				    assign('tempValues',thisCycleValues,caller)
				    eval(expression(results[[exName]][[elemName]][[cycleName]]$time <- tempLabels),envir=caller)
				    eval(expression(results[[exName]][[elemName]][[cycleName]]$values <- tempValues),envir=caller)
				    eval(expression(rm(tempLabels,tempValues)),envir=caller)
				    cycleCounter <- cycleCounter + 1
				}
				else if (identical(tagName,'v') && noSubs) {
				    thisCycleValues[[vCounter]] <- tempVals
				    vCounter <- vCounter + 1
				}
				else if ((identical(tagName,'v') && !noSubs) || identical(tagName,'w')) {
				    thisCycleValues[[vCounter]] <- matrix(data=tempVals,ncol=subCounter,byrow=FALSE)
				    vCounter <- vCounter + 1
				}
				else if (identical(tagName,'p')) {
				    thisCycleValues[[vCounter]] <- matrix(data=tempVals,nrow=subCounter,byrow=TRUE)
				    vCounter <- vCounter + 1
				}
			}
			else {#scan through an opening tag
			    tagName <- append(token,scanTag(fid))
           	    tagName <- paste(tagName,sep="",collapse="")
				if (identical(tagName,'annotation')) {
                    scanUntil(fid,'</annotation>')
				}
                else if (identical(tagName,'results')) {
                    scanUntil(fid,'>')
                    exCounter <- 1
                    eval(expression(results <- list()),env=caller)
				}
				else if (identical(tagName,'execution')) {
				    assign('exName',sprintf('execution%d',exCounter),env=caller)
                    eval(expression(results[[exName]] <- list()),envir=caller)
                    if (execution > 0) {
                        if (exCounter < execution) {#skip this entire execution
                            scanUntil(fid,'</execution>')
                            exCounter <- exCounter + 1
                        }
                        else if (exCounter > execution) {#stop reading
                            break
                        }
                    }
				}
				else if (identical(tagName,'network')) {
                    tagRemainder <- scanUntilAndReturn(fid,'>')
				}
				else if (identical(tagName,'task') || identical(tagName,'synapses') || identical(tagName,'weights') || identical(tagName,'values')) {
                    tagRemainder <- scanUntilAndReturn(fid,'>')
                    noSubs <- FALSE
                    if (!length(grep('/',tagRemainder))) {
                        idName <- getAttrVal('id',tagRemainder)
                        if (identical(tagName,'task')) {
                            assign('elemName',sprintf('taskPatterns_%s',idName),envir=caller)
                        }
                        else if (identical(tagName,'synapses')) {
                            assign('elemName',sprintf('synapses_%s',idName),envir=caller)
                        }
                        else if (identical(tagName,'weights')) {
                            assign('elemName',sprintf('weights_%s',idName),envir=caller)
                        }
                        else if (identical(tagName,'values')) {
                            assign('elemName',sprintf('%s_%s',getAttrVal('type',tagRemainder),idName),envir=caller)
                            noSubs = TRUE
                        }
                        eval(expression(results[[exName]][[elemName]] <- list()),envir=caller)
                        cycleCounter <- 1
                        numVals <- 0
                    }
				}
				else if (identical(tagName,'cycle')) {
				    tagRemainder <- scanUntilAndReturn(fid,'>')
				    assign('cycleName',sprintf('cycle%d',cycleCounter),caller)
				    eval(expression(results[[exName]][[elemName]][[cycleName]] <- list('time'=0,'values'=0)),envir=caller)
				    thisCycleTimeLabels <- vector()
				    thisCycleValues <- list()
                    vCounter <- 1   
				}
				else if (identical(tagName,'p') || identical(tagName,'w') || identical(tagName,'v')) {
				    tagRemainder <- scanUntilAndReturn(fid,'>')
                    iteration <- type.convert(getAttrVal('i',tagRemainder))[1] + 1
                    if (length(grep('s',tagRemainder))) {
                        step <- type.convert(getAttrVal('s',tagRemainder))[1] + 1
                    }
                    else {
                        step <- 0
                    }
                    thisCycleTimeLabels <- append(thisCycleTimeLabels,c(iteration,step))
                    tempVals <- vector()
                    subCounter <- 0
				}
				if (identical(tagName,'r') || identical(tagName,'n') || (identical(tagName,'v') && noSubs)) {
				    valstr = scanUntilAndReturn(fid,"<")
                    vals = strsplit(valstr,split=" ")[[1]]
                    for(j in 1:length(vals)) {
                        if (!identical(vals[j],"")) {
                            tempVals <- append(tempVals,type.convert(vals[j]))
                   	    }
                   	}
                    subCounter <- subCounter + 1
				}
			}
	    }
	    else {
	        token <- readChar(fid,1)
	    }
    }
    close(fid)
}