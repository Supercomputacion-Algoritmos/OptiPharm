/**
 * ESte es el main original sin ninguna modificacion. Es el main de Juani.
 */

#include "time.h"
#include <string.h>
#include "usrintf.h"
#include "uego.h"
#include "configur.h"

////////////////////////////////////////////////////////////
// $Id: main.cc,v 2.5 1998/03/17 23:14:55 jelasity Exp $
// main.cc
// main modul of the user interface
////////////////////////////////////////////////////////////
// modification history:
//	jelasity 98 01 17 command line configure
//		98 02 14 non-documented command line passing feature
////////////////////////////////////////////////////////////

Ini* Master::_ini = NULL; 	// initialization of static member
void setMsgLevel(char);

//--- The following is a non-documented feature, to use it in a modul -----
//--- declare global variables as 'extern' --------------------------------

char** RemArgv = NULL;	// command line pars after '--'
int RemArgc = 0;	// num. of command line pars after '--'

void CutCommandLine(int* argc, char** argv) {

	for (int i = 0; i < *argc; ++i) {
		if (strcmp(argv[i], "--") == 0) {
			RemArgc = *argc - (i + 1);
			if (i != *argc - 1)
				RemArgv = argv + (i + 1);
			*argc = i;
			break;
		};
	};
}
;

//--- These are local to this modul ------------------------------------

unsigned long saveflags;	// GetPars() sets it
long repcount;	// GetPars() sets it
char *trace,		// GetPars() sets it
		msg[250];	// working

//-----------------------------------------------------------------------

char GetPars(int argc, char** argv) {
// sets repcount and trace; returns false on failure

	trace = NULL;
	repcount = 1;
	saveflags = 0;

	for (int i = 0; i < argc; ++i) {
		switch (argv[i][1]) {
		case 'T':
			if (trace != NULL)
				delete trace;
			trace = new char[strlen(argv[i] + 2) + 1];
			if (trace == NULL) {
				message("No memory for comm. line.", MSG_ERROR);
				return 1 == 0;
			}
			;
			strcpy(trace, argv[i] + 2);
			break;
		case 'r':
			if (sscanf(argv[i] + 2, "%ld", &repcount) != 1) {
				message("Bad repeate count.", MSG_ERROR);
				return 1 == 0;
			}
			;
			break;
		case 's':
			saveflags |= SHORT_SAVE;
			break;
		};
	};

	return 1 == 1;
}
;

//-----------------------------------------------------------------------

int main(int argc, char** argv) {

	int errcode = 0;
	Ini *ini = NULL;
	Master *master = NULL;
	FILE *inifile = NULL;
	double tiemporeloj;
	time_t t1, t2;
	clock_t clock1, clock2;

	setMsgLevel( MSG_INFORMATION);

	CutCommandLine(&argc, argv);	// cuts things after '--'

	if (argc < 2) { //Execute nothing
		sprintf(msg,
				"Version: %s                              Contact: jelasity@usa.net\n\n",
				UEGO_VERSION);
		message(msg, MSG_NOTHING);
		message( DEFAULT_MESSAGE, MSG_NOTHING);
		return 0;
	} else if (argv[1][0] != '-') // assuming ini filename extension
			{
		sprintf(msg, "Opening ini file %s.%s", UEGO_ININAME, argv[1]);
		message(msg, MSG_INFORMATION);
		sprintf(msg, "%s.%s", UEGO_ININAME, argv[1]);
		inifile = fopen(msg, "rt");
	} else if (argv[1][1] != 'c') {
		message("Bad or unknown command line parameters.", MSG_ERROR);
		return 6;
	} else  // configure
	{
		sprintf(msg, "%s.%s", UEGO_ININAME, argv[1] + 2);
		Configure::Config(msg, argc - 2, argv + 2);
		if (Configure::Fail())
			return 7;
		else
			return 0;
	};

	// --- Starting optimalization -------------------------------------
	message("Reading ini file.", MSG_INFORMATION);
	ini = new Ini(inifile);
	if (ini == NULL || ini->Fail()) {
		message("Could not read ini file.", MSG_ERROR);
		errcode = 1;
	} else {
		message("Creating master.", MSG_INFORMATION);
		if (GetPars(argc - 2, argv + 2))
			master = new Master(ini, trace);

		if (master == NULL || master->Fail()) {
			message("Could not create master.", MSG_ERROR);
			errcode = 2;
		} else {
			message("Starting optimalization.", MSG_INFORMATION);
			// --- doing repcount experiments -----------------------
			for (long i = 1; i <= repcount; ++i) {
				t1 = time(NULL);
				//clock1=clock();
				sprintf(msg, "Starting experiment %ld.", i);
				message(msg, MSG_INFORMATION);
				master->Go();
				t2 = time(NULL);
				//clock2=clock();
				tiemporeloj = (double) t2 - t1;
				//tiemporeloj=(double)(clock2-clock1)/(double)CLOCKS_PER_SEC; 

				if (master->Fail()) {
					errcode = 3;
					break;
				} else {
					message("Saving results.", MSG_INFORMATION);
					master->Save( stdout, tiemporeloj, saveflags);
					if (master->Fail()) {
						errcode = 4;
						break;
					};
				};
			};
		}
	};

	if (errcode == 0)
		message("Success.", MSG_INFORMATION);

	if (master != NULL)
		delete master;
	if (ini != NULL)
		delete ini;
	if (trace != NULL)
		delete trace;

	return errcode;
}
;
