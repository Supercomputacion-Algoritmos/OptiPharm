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
#include "Extras.h"
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
	delete token;
	return name;
}
/**
 * Hay que pasar la molecula
 * */
//----- Read all the argument -----------------------------------------
int readArguments(int argc, char** argv, int* indexArray) {

	if (argc < 3) {
		cout	<< "Version: " << Extras::getName()<<"\n"
				<< "HowToUse: ./OP_SS -q <pathMol1> -d <pathMol2> [-h 0] [-w 1] [-T 1]\n"
				<< "Parameters: \n"
				<< "\t-q: path of molecule MOL2 1. \n"
				<< "\t-d: path of molecule MOL2 2. \n"
				<< "\t-h: considers atoms of Hydrogens. Default: 0 (no). \n"
				<< "\t-w: set the same Van der Waals radius (1.8) to all the atoms. Default: 1 (yes).\n"
				<< "\t-T: get normlized value (Tanimoto). Default 1 (yes).\n";
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
		} else if (arg == "-T") { // Tanimoto
			indexArray[4] = i + 1;
			//cout << "-T: " << argNext << endl;
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
	//Obtenemos nombre de segunda
	pathMol2 = argv[indexArray[1]];

	//Leemos la molecula 2
	Molecule * mol2 = new Molecule();
	ReadMolecule::readMol(pathMol2, mol2, considerHydrogens,
			sameVanDerWaalsRadius);
	string name2 = getNameMol(argv[indexArray[1]]);
	double valueWEGA;
	double valueROCS;
	if (indexArray[4] != -1) {
		if (argv[indexArray[4]][0] == '0') {

			//Calculamos el ShapeSimilarity Absoluto
			valueWEGA = VolumeOverlap::overlapWEGA(mol, mol2,
					sameVanDerWaalsRadius);
			//valueROCS = VolumeOverlap::overlapROCS(mol, mol2);
		}
	} else {
		/*double vAA =
		 VolumeOverlap::calculateOverlapVolumeGaussAnalyticWeightWEGA(
		 mol, mol);
		 double vBB =
		 VolumeOverlap::calculateOverlapVolumeGaussAnalyticWeightWEGA(
		 mol2, mol2);
		 double vAB =
		 VolumeOverlap::calculateOverlapVolumeGaussAnalyticWeightWEGA(
		 mol, mol2);
		 */

		//FORMA ACTUAL

		// CON ARRAYS
		mol->setArraysAtoms(mol->atoms.size());
		mol->ObjectToArray(mol->getAtomsXYZ(), mol->getRadiusAtoms(),
				mol->getWeightAtoms(), true);

		double vAA = VolumeOverlap::preciseOverlapWEGA(mol->getAtomsXYZ(),
				mol->atoms.size(), mol->getWeightAtoms(), mol->getRadiusAtoms(),
				mol->getAtomsXYZ(), mol->atoms.size(), mol->getWeightAtoms(),
				mol->getRadiusAtoms(), true);



		mol2->setArraysAtoms(mol2->atoms.size());
				mol2->ObjectToArray(mol2->getAtomsXYZ(), mol2->getRadiusAtoms(),
						mol2->getWeightAtoms(), true);
				double vBB = VolumeOverlap::preciseOverlapWEGA(mol2->getAtomsXYZ(),
						mol2->atoms.size(), mol2->getWeightAtoms(), mol2->getRadiusAtoms(),
						mol2->getAtomsXYZ(), mol2->atoms.size(), mol2->getWeightAtoms(),
						mol2->getRadiusAtoms(), true);

				double vAB = VolumeOverlap::preciseOverlapWEGA(
					mol->getAtomsXYZ(),
					mol->atoms.size(), mol->getWeightAtoms(),
					mol->getRadiusAtoms(), mol2->getAtomsXYZ(),
							mol2->atoms.size(),
							mol2->getWeightAtoms(),
							mol2->getRadiusAtoms(),
							true);
		//CON OBJETOS
				/*
		double vAA = VolumeOverlap::overlapWEGA(mol, mol,
				sameVanDerWaalsRadius);
		double vBB = VolumeOverlap::overlapWEGA(mol2, mol2,
				sameVanDerWaalsRadius);
		double vAB = VolumeOverlap::overlapWEGA(mol, mol2,
				sameVanDerWaalsRadius);
				*/
		valueWEGA = (vAB / (vAA + vBB - vAB));


		//COUTS


		vAA = VolumeOverlap::overlapROCS(mol, mol);
		vBB = VolumeOverlap::overlapROCS(mol2, mol2);
		vAB = VolumeOverlap::overlapROCS(mol, mol2);
		valueROCS = (vAB / (vAA + vBB - vAB));


	}

	/*cout << name1 << " " << mol->atoms.size() << " " << name2 << " "
			<< mol2->atoms.size() << " WEGA " << valueWEGA << " ROCS "
			<< valueROCS << endl;*/
	cout << "query,target,shapesimilarity"<< "\n";

	cout <<mol->mol_name <<","<<mol2->mol_name<<","<< valueWEGA <<"\n";//<< ","<<valueROCS<<"\n";
	delete mol;
	delete mol2;
	delete[] indexArray;
	return 0;

}
