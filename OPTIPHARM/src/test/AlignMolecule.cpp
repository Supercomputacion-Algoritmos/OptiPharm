/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MoveRotateMolSave.cpp
 * Author: savins
 *
 * Created on 22 de septiembre, 12:32
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* atof */
#include <Parameters.h>
#include <ReadMolecule.h>
#include <WriteMolecule.h>
#include "Extras.h"

using namespace std;
/**
 * Hay que pasar la molecula y 7 parametros, los 6 que corresponden a las coordenadas del punto y el del angulo.
 * */
int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "Version: " << Extras::getName() << "\n"
			 << "Uso: ./OP_ALIGN <pathMol2>  -h [0|1]"
			 << endl;
		return -1;
	}
	char* pathMol2;
	// Obtenemos los argumentos
	pathMol2 = argv[1];
	bool considerHydrogen = true;
	if (argv[3][0] == '0'){
		considerHydrogen = false;
	}
	//Leemos la molecula
	Molecule * mol = new Molecule();
	ReadMolecule::readMol(pathMol2, mol, considerHydrogen, true);
	Parameters::alignMolecule(mol);
	mol->setArraysAtoms(mol->atoms.size());

	mol->ObjectToArray(mol->getAtomsXYZ(), mol->getRadiusAtoms(),mol->getWeightAtoms(), true);


	//UPDATING COORDINATES
	unsigned iterador = 0;
		for (unsigned i =0; i< mol->num_atoms;i++){
					iterador = i * 3;
					mol->atoms[i].x = mol->getAtomsXYZ()[iterador];
					mol->atoms[i].y = mol->getAtomsXYZ()[iterador+1];
					mol->atoms[i].z = mol->getAtomsXYZ()[iterador+2];
				}
	std::string str(pathMol2);
	string base_filename = str.substr(str.find_last_of("/\\") + 1);
	std::string::size_type const p(base_filename.find_last_of('.'));
	std::string file_without_extension = base_filename.substr(0, p);

	string name= file_without_extension + "_Aligned.mol2";
	WriteMolecule::writeMol(name, mol);

	delete mol;


	return 0;

}
