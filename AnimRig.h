#include <queue>
#include "ReadObj.h"

/*
Base Rig class
*/
class Rig {
public:
	Rig() {

	}
	Rig(vector<Model> submodels);
	//Store a vector of all submodels that comprise a whole rig
	//NOTE:  whatever model is at position 0 in the vector will be used
	//as the root model!
	vector<Model> modelParts;
	void drawRig();
	void recursiveDraw(deque<Model*> subModels);
	/*
	Rig & operator=(const Rig &original) {
		for (int i = 0; i < original.modelParts.size(); i++) {
			Model newModel = original.modelParts[i];
			modelParts.push_back(newModel);
		}
		return *this;
	}
	*/
};

/*
Subclass for the general cultist rig, will define animation here
*/
class CultistRig_0 : public Rig {
public:
	CultistRig_0() {

	}
	CultistRig_0(vector<Model> submodels) : Rig(submodels) {

	}
	void doAnimate();
	int animationStage = 0;
};

/*
Subclass for the lead cultist
*/
class CultistRig_1 : public Rig {
public:
	CultistRig_1(vector<Model> submodels) : Rig(submodels) {

	}
	void doAnimate();
	int animationStage = 0;
};