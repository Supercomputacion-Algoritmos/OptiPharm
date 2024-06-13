#include <iostream>
#include "gtest/gtest.h"

#include "Point3DDouble.h"
#include "Molecule.h"
#include "ReadMolecule.h"
#include "MoveAndRotate.h"
#include "Quaternion.h"

// IndependentMethod is a test case - here, we have 2 tests for this 1 test case
TEST(RotationMethod, onehundredegress) {
	char* pathMol2 = "../gtestOP/file/example1.mol2";
		double x1, y1, z1, x2, y2, z2, angle;
		// Obtenemos los argumentos

		angle = 3.14159265359;
		x1 = 0;
		y1 = 1;
		z1 = 0;
		x2 = 0;
		y2 = 0;
		z2 = 0;

		// Creamos los dos puntos
		Point3DDouble axis1;
		Point3DDouble axis2;
		axis1.x = x1;
		axis1.y = y1;
		axis1.z = z1;
		axis2.x = x2;
		axis2.y = y2;
		axis2.z = z2;
		//Leemos la molecula
		Molecule * mol = new Molecule();
		Molecule * molRotated = new Molecule();
		ReadMolecule::readMol(pathMol2, mol, true, false);
		//Rotamos la molecula
		MoveAndRotate::RotateMolAccording1Axis(mol, angle, axis1, axis2,
				molRotated);

		ASSERT_NEAR( molRotated->atoms[0].x, -1.0,0.0001);
		ASSERT_NEAR( molRotated->atoms[0].y, 0.0, 0.0001);
		ASSERT_NEAR( molRotated->atoms[0].z, 0.0, 0.0001);
		//cout << "Test 1: " <<molRotated->atoms[0].x <<", " <<  molRotated->atoms[0].y <<", "<< molRotated->atoms[0].z<<endl;
		delete mol;
		delete molRotated;
}

TEST(RotationMethod, onehundredegress2) {
	char* pathMol2 = "../gtestOP/file/example2.mol2";
		double x1, y1, z1, x2, y2, z2, angle;
		// Obtenemos los argumentos

		angle = 3.14159265359/8;
		x1 = 9;
		y1 = 2;
		z1 = 6;
		x2 = 7;
		y2 = 0;
		z2 = 1;

		// Creamos los dos puntos
		Point3DDouble axis1;
		Point3DDouble axis2;
		axis1.x = x1;
		axis1.y = y1;
		axis1.z = z1;
		axis2.x = x2;
		axis2.y = y2;
		axis2.z = z2;
		//Leemos la molecula
		Molecule * mol = new Molecule();
		Molecule * molRotated = new Molecule();
		ReadMolecule::readMol(pathMol2, mol, true, false);
		//Rotamos la molecula
		MoveAndRotate::RotateMolAccording1Axis(mol, angle, axis1, axis2,
				molRotated);

		ASSERT_NEAR( molRotated->atoms[0].x, 4.19614872,0.001);
		ASSERT_NEAR( molRotated->atoms[0].y, 5.65305114,0.001);
		ASSERT_NEAR( molRotated->atoms[0].z, 3.86032006,0.001);
		//cout << "Test 4: " <<molRotated->atoms[0].x <<", " <<  molRotated->atoms[0].y <<", "<< molRotated->atoms[0].z<<endl;
		delete mol;
		delete molRotated;
}

// The fixture for testing class Project1. From google test primer.
class Project1Test : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	Project1Test() {
		// You can do set-up work for each test here.
	}

	virtual ~Project1Test() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}


};

