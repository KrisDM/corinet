writePatternSet <- function(fileName,set)
#  Writes patternSet files in CORINET Markup Language file format
#    "writePatternSet(filename,set,precision)"
#
#  "fileName" contains the path and name of the file to be written
#  "set" is a list, with one cell for each pattern

{
	rows <- nrow(set[[1]])
	cols <- ncol(set[[1]])
	
	if (length(set) > 1) {
		for (i in 2:length(set)) {
			if (!identical(rows,nrow(set[[i]])) || !identical(cols,ncol(set[[i]]))) {
				cat(paste("Size of pattern ",i," is different from size of other patterns.\n",sep=""))
				cat(paste("I will continue writing the <patternSet>, so that you can check and correct this error.\n"))
			} 
		}
	}

	fid <- file(fileName,open = "wt")
	cat('<?xml version="1.0" encoding="UTF-8"?>\n',file=fid)
	cat('<!--Change the path in xsi:schemaLocation to reflect the location of the schema file-->\n',file=fid)
	cat('<patternSet xmlns="http://www.corinet.org/namespaces/CORINETSetup" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\n',file=fid)
	cat('xsi:schemaLocation="http://www.corinet.org/namespaces/CORINETSetup ./code/xml/Setup/experimentSetup.xsd"\n',file=fid)
	cat(paste('columns="',cols,'"',sep=""),file=fid)
	if (rows > 1) {
		cat(paste(' rows="',rows,'"',sep=""),file=fid)
	}
	cat('>\n',file=fid)
	
	for (i in 1:length(set)) {
		cat('  <p>\n',file=fid)
		temp <- set[[i]]
		for (j in 1:nrow(temp)) {
			cat('    <r>',file=fid)
			cat(format(temp[j,],digits=4),file=fid)
			cat('</r>\n',file=fid)
		}
		cat('  </p>\n',file=fid)
	}
	cat('</patternSet>\n',file=fid)
	close(fid)
}
