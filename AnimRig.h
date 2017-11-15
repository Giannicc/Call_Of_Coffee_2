#include <queue>
#include "ReadObj.h"

/*
Base Rig class
*/
class Rig {
public:
	Rig(vector<Model> submodels);
	//Store a vector of all submodels that comprise a whole rig
	//NOTE:  whatever model is at position 0 in the vector will be used
	//as the root model!
	vector<Model> modelParts;
	void drawRig();
	void recursiveDraw(deque<Model*> childModels);
};

/*
Subclass for the cultist rig, will define animation here
*/
class CultistRig_0 : public Rig {
public:
	CultistRig_0(vector<Model> submodels) : Rig(submodels) {

	}
	void doAnimate();
	int animationStage = 0;
};