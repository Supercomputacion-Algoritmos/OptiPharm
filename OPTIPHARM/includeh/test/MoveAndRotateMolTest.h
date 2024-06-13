/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   moveAndRotateMolTest.h
 * Author: savins
 *
 * Created on 24 de febrero de 2016, 12:32
 */

#ifndef MOVEANDROTATEMOLTEST_H
#define MOVEANDROTATEMOLTEST_H

#include <stdlib.h>
#include <iostream>
#include <vector>


#include <math.h>

#include "Molecule.h"
#include "Atom.h"
#include "MoveAndRotate.h"
#include "ReadMoleculeSD.h"

class MoveAndRotateMolTest{
public:
	void static moveAtom();
	void static moveAtom2();
	void static moveAtom3();
	int static testMoveAndRotateMolTest(void);
private:
};


#endif /* MOVEANDROTATEMOLTEST_H */

