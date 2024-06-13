/**
 * Este main lo utilizo para probar las especies. Porque me tuve que crear una lista y comprobar que funcionaba.
 */
#include "time.h"
#include <string.h>
#include "usrintf.h"
#include "uego.h"
#include "configur.h"
#include "managespecies.h"
////////////////////////////////////////////////////////////
// $Id: main.cc,v 2.5 1998/03/17 23:14:55 jelasity Exp $
// main.cc
// main modul of the user interface
////////////////////////////////////////////////////////////
// modification history:
//	jelasity 98 01 17 command line configure
//		98 02 14 non-documented command line passing feature
////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------
#include <iostream>
using namespace std;
int main(int argc, char** argv) {

	ManageSpecies *ms = new ManageSpecies();
	ms->addnode();
	ms->addnode();
	ms->display();
	ms->delnode();
	ms->display();
	ms->addnode();
	ms->display();
	return 0;
}

