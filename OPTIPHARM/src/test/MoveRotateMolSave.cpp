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
#include "MoveAndRotate.h"

#include "Point3DDouble.h"
#include "ReadMolecule.h"
#include "WriteMolecule.h"
#include "Extras.h"

using namespace std;
/**
 * Hay que pasar la molecula y 7 parametros, los 6 que corresponden a las coordenadas del punto y el del angulo.
 * */
int main(int argc, char* argv[]) {

	if (argc != 12) {
		cout
				<< "Version: " << Extras::getName()<<"\n"
				<< "Uso: ./MRMS <pathMol2> <angleInRadian> <x1> <y1> <z1> <x2> <y2> <z2> <deltaX> <deltaY> <deltaZ> "
				<< endl;
		return -1;
	}
	char* pathMol2;
	double x1, y1, z1, x2, y2, z2, angle, deltaX, deltaY, deltaZ;
	// Obtenemos los argumentos
	pathMol2 = argv[1];
	angle = atof(argv[2]);
	x1 = atof(argv[3]);
	y1 = atof(argv[4]);
	z1 = atof(argv[5]);
	x2 = atof(argv[6]);
	y2 = atof(argv[7]);
	z2 = atof(argv[8]);
	deltaX = atof(argv[9]);
	deltaY = atof(argv[10]);
	deltaZ = atof(argv[11]);

	//cout << "Parametros: "<< angle <<" "<< x1<<" "<< y1<<" "<< z1<<" "<< x2<<" "<< y2<<" "<< z2<<" "<< deltaX<<" "<< deltaY<<" "<< deltaZ<< "\n";
	// Creamos los dos puntos
	Point3DDouble axis1;
	Point3DDouble axis2;
	axis1.x = x1;
	axis1.y = y1;
	axis1.z = z1;
	axis2.x = x2;
	axis2.y = y2;
	axis2.z = z2;

	if (x1 == x2 && y1 == y2 && z1 == z2) {
		cerr << "Error: Can not create rotation axis so there is not modification on the molecule.\n";
			return 0;
		}

	if (x1 == 0 && y1 == 0 && z1 == 0 && x2 ==0 && y2 ==0 && z2 ==0 ){
		angle = 0;
		axis1.x =1;
	}
	//Leemos la molecula
	Molecule * mol = new Molecule();
	Molecule * molRotated = new Molecule();
	ReadMolecule::readMol(pathMol2, mol, true, false);

	//Rotamos la molecula
	MoveAndRotate::RotateMolAccording1Axis(mol, angle, axis1, axis2,
			molRotated);

	MoveAndRotate::MolToNewPosition(molRotated, deltaX, deltaY, deltaZ);

	string name = ""+ mol->mol_name +"_Rotated.mol2";
	WriteMolecule::writeMol(name, molRotated);

	delete mol;
	delete molRotated;

	return 0;

}
