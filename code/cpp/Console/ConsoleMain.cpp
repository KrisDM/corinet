/*********************************************************************************************
 * Name      :  ConsoleMain.cpp
 *
 * Purpose   :  Entry point for the console application.
 *
 * Notes	 :	
 *
 * Info      :	http://www.corinet.org
 *
 * Copyright :	2006, King's College London
 *		
 * License   :  This program is free software; you can redistribute it and/or modify
 *				it under the terms of the GNU General Public License as published by
 *				the Free Software Foundation; either version 2 of the License, or
 *				(at your option) any later version.
 *
 *				This program is distributed in the hope that it will be useful,
 *				but WITHOUT ANY WARRANTY; without even the implied warranty of
 *				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *				GNU General Public License in $CORINETROOT/licenses for more details.
 *
 **********************************************************************************************/

#include <Platform/Platform.h>
#include <Util/Util.h>
#include <Setup/Makers.h>
#include <Client/ClientRegister.h>
#include <Client/Client.h>
#include <iostream>
#include <ctime>
#include <cstring>

namespace {//unnamed namespace to ensure local linking
	
void usage() 
{
	std::cout << "\n*************************************\n"
		"***      corinet Version 2        ***\n"
		"*************************************\n"
		"Usage:\n"
		"   corinet -?|-t \n"
		"   corinet [-v|-q] fileName \n\n"
		"  \"fileName\": - file in local directory (not starting with '.', '/' or '\\')\n"
		"              - path relative to CORINETROOT (starting with '.' or '..')\n"
		"              - fully qualified path\n\n"
		"Flags:\n"
		"   -?  Show this help message\n"
		"   -t  Test compatibility issues\n"
		"   -v  Check validity of files only; do not run experiment or generate code\n"
		"   -q  Run quietly, without progress indicator\n"
		"\n\n"
		"This program is free software; you can redistribute it and/or modify\n"
 		"it under the terms of the GNU General Public License as published by\n"
 		"the Free Software Foundation; either version 2 of the License, or\n"
 		"(at your option) any later version.\n\n"
 		"This program is distributed in the hope that it will be useful,\n"
 		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
 		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
 		"GNU General Public License in $CORINETROOT/licenses for more details.\n"
	<< std::flush;
}

}//end unnamed namespace

int main(int argc,char* argv[])
{
	///////////////////////////////////////////////////////////////////////////////////////
	//Check the CORINETROOT environment variable
	///////////////////////////////////////////////////////////////////////////////////////
	if (!GetRoot()) {
		std::cout << "Environment variable \"CORINETROOT\" is undefined.\n";
		std::cout << "Please refer to the documentation for assistance.\n" << std::flush;;
		return 1;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//process the command line arguments
	///////////////////////////////////////////////////////////////////////////////////
	bool bCreate = true;
	bool bQuiet = false;

	if ((argc < 2) || (argc > 3)) {
		usage();
		return 1;
	}
	else if (argc == 2) {
		if (argv[1][0] == '-') {
			if (!strcmp(argv[1],"-?")) {
				usage();
				return 0;
			}
			else if (!strcmp(argv[1],"-t")) {
				if (TestCompatibility()) {
					std::cout << "\n\n\nCompatibility testing successful!\n\n\n" << std::flush;;
					return 0;
				}
				else {
					std::cout << "\n\n\nCompatibility testing failed!!!\n\n\n";
					std::cout << "Please refer to the documentation for assistance.\n" << std::flush;;
					return 1;
				}
			}
			else {
				usage();
				return 1;
			}
		}
	}
	else if (argc == 3) {
		if (argv[1][0] == '-') {
			if (!strcmp(argv[1],"-v")) {
				bCreate = false;
			}
			else if (!strcmp(argv[1],"-q")) {
				bQuiet = true;
			}
			else {
				usage();
				return 1;
			}
		}
		else {
			usage();
			return 1;
		}
	}

	const char* fileName = argv[argc - 1];

	CORINET::CClient* theClient = 0;

	int returnVal = 0;

	try {
		theClient = CORINET::CClientRegister::GetClient("xml","console",bQuiet);
		time_t start,finish;
		time(&start);
		////////////////////////////////////
		theClient->Handle(fileName,bCreate);
		////////////////////////////////////
		time(&finish);
		if (!bQuiet) {
			int elapsed_time = static_cast<int>(difftime(finish,start));
			std::cout << "\n\nTotal execution time ";
			if (elapsed_time >= 86400) {
				std::cout << elapsed_time/86400;
				if (elapsed_time > 86400*2)
					std::cout << " days, ";
				else
					std::cout << " day, ";
				elapsed_time %= 86400;
			}
			if (elapsed_time >= 3600) {
				std::cout << elapsed_time/3600;
				if (elapsed_time > 3600*2)
					std::cout << " hours, ";
				else
					std::cout << " hour, ";
				elapsed_time %= 3600;
			}
			if (elapsed_time >= 60) {
				std::cout << elapsed_time/60;
				if (elapsed_time > 60*2)
					std::cout << " minutes and ";
				else
					std::cout << " minute and ";
				elapsed_time %= 60;
			}
			if (elapsed_time == 1) {
				std::cout << elapsed_time << " second.\n\n" << std::flush;;
			}
			else {
				std::cout << elapsed_time << " seconds.\n\n" << std::flush;;
			}
		}
	}
	catch(CORINET::ECreation& e) {
		std::cout << "\n" <<  e.message << "\n\n" << std::flush;
		returnVal = 1;
	}
	catch(...) {
		std::cout << "\nProcessing interrupted...\n\n" << std::flush;
		returnVal = 1;
	}
		
	CORINET::CClientRegister::Release(theClient);
		
	return returnVal;
}





