#ifndef USRINTF_H
#define USRINTF_H

////////////////////////////////////////////////////////////
// $Id: usrintf.h,v 2.7 1998/04/01 21:05:18 jelasity Exp $
// usrintf.h
// defines for the main modul of the user interface
////////////////////////////////////////////////////////////
// modification history:
//	jelasity 98 01 17 DEFAULT_MESSAGE, VERSION
//	jelasity 98 01 24 DEFAULT_MESSAGE, VERSION
////////////////////////////////////////////////////////////

#define UEGO_ININAME "OPini"
#define DEFAULT_MESSAGE "./executable -c <ext> -q <query.mol2> -d <database.mol2> [-o ./] [-h 0] [-w 1] [-N <>] [-M <>] [-L <>] [-R <>] [-pre 0] [-pz 0] [-smol 0] [-fvdwr <file>] [-lowL 0.00]\n\
	The parameters: \n\
		-c: extension of the configuration file. \n\
		-q: path of query molecule. \n\
		-d: path of database with molecule or multiple molecules being compared with the query. \n\
		-o: path of outputFiles save by the algorithm. Default: ./. \n\
		-h: considers atoms of hydrogen. Default: 0 (no). \n\
		-w: set the same Van der Waals radius to all the atoms. Default: 1 (yes).\n\
		-N: max. number of evaluations (int). \n\
		-M: max. number of species (int). \n\
		-L: levels (int). \n\
		-R: smallest radius (double).\n\
		-align: align molecule before running the algorithm. Default: 1 (yes).\n\
		-pz: set P2 as 0,0,0. Default: 0 (no). \n\
		-smol: save solution in mol2 files.  Default: 0 (no). \n\
		-fvdwr: indicate the file with van der Waals radius. \n\
		-lowL: lower limit that we consider to execute the algorithm. \n\
		-S: only first solution is shown. \n\
	\n\n"

#endif

