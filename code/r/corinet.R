corinet <- function(fileName)
#  Runs the external corinet program
#    "corinet(fileName)"
#
#   "fileName" the name of a corinet markup language file in the working directory

{
	dirName <- getwd()
	fullPath <- paste(dirName,fileName,sep="/")

	if (length(grep(" ",fullPath))) {
		fullPath <- paste('"',fullPath,'"',sep="");
	}
	
	eval(system(paste('corinet ',fullPath,sep=""),show.output.on.console = TRUE))
}