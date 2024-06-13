/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ReadWriteMol2.cpp
 * Author: savins
 *
 * Created on 09 de December 2016, 12:32
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* atof */

#include "Point3DDouble.h"
#include "ReadMolecule.h"
#include "WriteMolecule.h"

using namespace std;
/**
 * Test para comprobar que se leen las moleculas
 */
int main(int argc, char* argv[]) {


	vector<Molecule> conformations;
	ReadMolecule::readDBMol2(argv[1],
			&conformations, true, false);


	for (int i = 0; i<conformations.size();i++){
		cout << conformations.size()<<endl;
		cout<<i<<" " << conformations[i].mol_name<<endl;
	}

	return 0;

}
