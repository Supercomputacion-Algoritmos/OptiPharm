#include <iostream>
#include "gtest/gtest.h"


// IndependentMethod is a test case - here, we have 2 tests for this 1 test case
TEST(IndependentMethod, ResetsToZero) {
	int i = 3;
	i = 0;
	EXPECT_EQ(0, i);

	i = 0;
	EXPECT_EQ(0,i);
}

TEST(IndependentMethod, ResetsToZero2) {
	int i = 0;
	EXPECT_EQ(0, i);
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

