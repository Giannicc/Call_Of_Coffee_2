/*
Created by Gianni Ciccarelli
This code creates a Rig class from the vector of models passed as a parameter
to the constructor

IMPORTANT:
Whatever model is at position 0 in the vector will be used as the root model
when drawing the Rig
*/
#include <queue>
#include "ReadObj.h"

/*
Base Rig class
*/
class Rig {
public:
	//Empty default constructor
	Rig() {
	}
	//Constructor
	Rig(vector<Model> submodels);

	//Store a vector of all submodels that comprise a whole rig
	//NOTE:  whatever model is at position 0 in the vector will be used
	//as the root model!
	vector<Model> modelParts;
	void drawRig();
	void recursiveDraw(deque<Model*> subModels);
};

/*
Subclass for the general cultist rig, specifies cultist animation behavior
*/
class CultistRig_0 : public Rig {
public:
	//Constructors
	CultistRig_0() {
	}
	CultistRig_0(vector<Model> submodels) : Rig(submodels) {
	}

	//Animation function, just makes them nod their heads in prayer
	void doAnimate();

	//Keeps track of what animation we're performing
	int animationStage = 0;
};