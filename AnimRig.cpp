/*
Rig Class function definitions
*/
#include "AnimRig.h"
Rig::Rig(vector<Model> submodels) {
	modelParts = submodels;
	/*
	The names of models in a Rig are checked, and if they match
	the name of a string in childNames then that model is passed by reference
	to the children model pointer vector
	*/
	for (int i = 0; i < modelParts.size(); i++) {
		for (int childIndex = 0; childIndex < modelParts[i].childNames.size(); childIndex++) {
			for (int j = 0; j < modelParts.size(); j++) {
				if (modelParts[j].name == modelParts[i].childNames[childIndex]) {
					modelParts[i].children.push_back(&(modelParts[j]));
					break;
				}
			}
		}
	}
}

void Rig::drawRig() {
	glPushMatrix();
	//the model at pos 0 in modelParts is the root
	glTranslatef(modelParts[0].pivotX, modelParts[0].pivotY, modelParts[0].pivotZ);
	glRotatef(modelParts[0].rotX, 1.0, 0.0, 0.0);
	glRotatef(modelParts[0].rotY, 0.0, 1.0, 0.0);
	glRotatef(modelParts[0].rotZ, 0.0, 0.0, 1.0);
	modelParts[0].drawTextured();
	deque<Model*> subModels;
	//Add the models in modelParts to the subModels deque to be drawn
	for (int i = 1; i < modelParts.size(); i++) {
		subModels.push_back(&modelParts[i]);
	}
	for (int i = 0; i < modelParts[0].children.size(); i++) {
		//prevent re-adding of models
		for (int j = 0; j < subModels.size(); j++) {
			if ((*subModels[j]).name == (*modelParts[0].children[i]).name) {
				subModels.erase(subModels.begin() + j);
				break;
			}
		}
		subModels.push_back(modelParts[0].children[i]);
	}
	recursiveDraw(subModels);
	glPopMatrix();	//root pop
}

/*
As it turns out a recursive function to call matrix pushes and pops is perfect!
recursiveDraw draws every model in subModels, but if a model has children
it pushes all those models to the front of the deque to be drawn next
*/
void Rig::recursiveDraw(deque<Model*> subModels) {
	if (!subModels.empty()) {
		int colorArray[] = {
			255, 255, 255
		};
		glPushMatrix();
		glTranslatef(
			(*subModels.front()).pivotX + (*subModels.front()).x,
			(*subModels.front()).pivotY + (*subModels.front()).y,
			(*subModels.front()).pivotZ + (*subModels.front()).z);
		glRotatef((*subModels.front()).rotX, 1.0, 0.0, 0.0);
		glRotatef((*subModels.front()).rotY, 0.0, 1.0, 0.0);
		glRotatef((*subModels.front()).rotZ, 0.0, 0.0, 1.0);
		glTranslatef(
			-(*subModels.front()).pivotX,
			-(*subModels.front()).pivotY,
			-(*subModels.front()).pivotZ);
		(*subModels.front()).drawTextured();
		Model placeHolder = (*subModels.front());
		subModels.pop_front();
		for (int i = 0; i < placeHolder.children.size(); i++) {
			subModels.push_front(placeHolder.children[i]);
		}
		recursiveDraw(subModels);
		glPopMatrix();
	}
}

void CultistRig_0::doAnimate() {
	/*
	The animation state keeps track of whether we're raising the head (state 0)
	or lowering the head (state 1)
	Then based on that we actually change the rotation data of the model
	*/
	Model *top = NULL, *hands = NULL;
	for (int i = 0; i < modelParts.size(); i++) {
		if (modelParts[i].name == "cultist_0_robe_top") top = &(modelParts[i]);
	}
	if ((*top).rotX > 40) animationStage = 1;
	else if ((*top).rotX <= 1) animationStage = 0;
	switch (animationStage) {
	case 0:
		(*top).rotX += .5;
		break;
	case 1:
		(*top).rotX -= .5;
		break;
	}
}