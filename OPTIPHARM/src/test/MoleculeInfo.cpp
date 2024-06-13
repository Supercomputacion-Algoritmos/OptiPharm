/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MoveRotateMolSave.cpp
 * Author: savins
 *
 * Created on 05 de octubre, 8:56
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* atof */

#include <string.h>
#include <stdio.h>
#include "Point3DDouble.h"
#include "ReadMolecule.h"
#include "VolumeOverlap.h"

using namespace std;
string getNameMol(char* const path) {
	const char s[2] = "/";
	char *token;

	/* get the first token */
	token = strtok(path, s);

	/* walk through other tokens */
	string name;

	while (token != NULL) {
		name = token;
		token = strtok(NULL, s);
	}

	token = new char[name.length() + 1];
	strcpy(token, name.c_str());
	name = strtok(token, ".");
	return name;
}
/**
 * Hay que pasar la molecula
 * */
//----- Read all the argument -----------------------------------------
int readArguments(int argc, char** argv, int* indexArray) {

	if (argc < 3) {
		cout	<< "Get information about a molecule"
				<< "HowTo: ./OP_MI -q <pathMol2> [-h 0] [-w 1]"
				<< "\n";
		return -1;
	}

	// Vamos obteniendo el valor de cada variable y lo mostramos
	for (int i = 0; i < argc - 1; i++) {
		string arg(argv[i]);
		string argNext(argv[i + 1]);
		if (arg == "-q") { // query file
			indexArray[0] = i + 1;
			//cout << "-q: " << argNext << endl;
		} else if (arg == "-d") { // database molecule with compare the query file
			indexArray[1] = i + 1;
			//cout << "-d: " << argNext << endl;
		} else if (arg == "-h") { // consider hidrogens atoms
			indexArray[2] = i + 1;
			//cout << "-h: " << argNext << endl;
		} else if (arg == "-w") { // consider same Van der Waals radius
			indexArray[3] = i + 1;
			//cout << "-w: " << argNext << endl;
		}
	}
	return 0;
}
int main(int argc, char* argv[]) {
	int* indexArray = NULL;
	int lenghtIndexArray = 5;
	indexArray = new int[lenghtIndexArray];

	for (int i = 0; i < lenghtIndexArray; i++) {
		indexArray[i] = -1;
	}

	//0: -q, 1: -d, 2: -h, 3: -w, 4: -T
	if (readArguments(argc, argv, indexArray) == -1) {
		return -1;
	}

	bool considerHydrogens = false; // 0
	bool sameVanDerWaalsRadius = true; // 1
	if (indexArray[2] != -1) {
		if (argv[indexArray[2]][0] == '1') {
			considerHydrogens = true;
		}
	}
	if (indexArray[3] != -1) {
		if (argv[indexArray[3]][0] == '0') {
			sameVanDerWaalsRadius = false;
		}
	}
	char* pathMol2;
	// Obtenemos nombre de primera
	pathMol2 = argv[indexArray[0]];

	//Leemos la molecula 1
	Molecule * mol = new Molecule();
	ReadMolecule::readMol(pathMol2, mol, considerHydrogens,
			sameVanDerWaalsRadius);
	string name1 = getNameMol(argv[indexArray[0]]);

	mol->setTanimoto(mol->getAtomsXYZ(),mol->atoms.size(), mol->getWeightAtoms(), mol->getRadiusAtoms(), sameVanDerWaalsRadius);

	// MOSTRAR DATOS
	cout << "fileName: " << name1;
	cout << "\n--------------------------\nMolecule Info:\n--------------------------\n";
	cout <<mol->toString();
	cout << "\n--------------------------\nData:\n--------------------------\n";
	cout << "Volumen: "<< mol->tanimoto<<"\nFIN\n\n";
	delete mol;
	return 0;

}
