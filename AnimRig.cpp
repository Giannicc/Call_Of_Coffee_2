/*
Rig Class function definitions
*/
#include "AnimRig.h"
Rig::Rig(vector<Model> submodels) {
	//note to self: try passing submodels by reference and make modelParts a
	//pointer to see if that speeds things up, cause I think making a deep copy
	//may or may not require reading the obj files again...
	modelParts = submodels;
	for (int i = 0; i < modelParts.size(); i++) {
		for (int childIndex = 0; childIndex < modelParts[i].childNames.size(); childIndex++) {
			for (int j = 0; j < modelParts.size(); j++) {
				if (modelParts[j].name == modelParts[i].childNames[childIndex]) {
					Model child = modelParts[j];
					modelParts[i].children.push_back(child);
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
	deque<Model> subModels;
	for (int i = 0; i < modelParts[0].children.size(); i++) {
		subModels.push_back(modelParts[0].children[i]);
	}
	recursiveDraw(subModels);
	glPopMatrix();	//root pop
}

void Rig::recursiveDraw(deque<Model> subModels) {
	if (!subModels.empty()) {
		int colorArray[] = {
			255, 255, 255
		};
		glPushMatrix();
		glTranslatef(
			subModels.front().pivotX + subModels.front().x,
			subModels.front().pivotY + subModels.front().y,
			subModels.front().pivotZ + subModels.front().z);
		glRotatef(subModels.front().rotX, 1.0, 0.0, 0.0);
		glRotatef(subModels.front().rotY, 0.0, 1.0, 0.0);
		glRotatef(subModels.front().rotZ, 0.0, 0.0, 1.0);
		glTranslatef(
			-subModels.front().pivotX,
			-subModels.front().pivotY,
			-subModels.front().pivotZ);
		(subModels.front()).drawTextured();
		Model placeHolder = subModels.front();
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
	mmkay so what I'm thinking for this one is:
	1) check the animation state
	2) use switch statement to decide how to manipulate the model
	based on animation state.
	3) each animation state has a finishing position/rotation for the model,
	so if the model's data equals that, move to the next animation state
	May need to set pos/rot for the model at the beginning of each animation
	state just to make sure they're where they should be, have to make sure to
	do that only once though
	4) otherwise just follow the animation instructions that move the model
	to the desired spot every time the animate function is called
	*/
	Model *top = NULL, *hands = NULL;
	for (int i = 0; i < modelParts.size(); i++) {
		if (modelParts[i].name == "cultist_0_robe_top") top = &(modelParts[i]);
		if (modelParts[i].name == "cultist_0_hands") hands = &(modelParts[i]);
	}
	if ((*top).rotX > 45) animationStage = 1;
	else if ((*top).rotX <= 1) animationStage = 0;
	switch (animationStage) {
	case 0:
		(*top).rotX += 1;
		break;
	case 1:
		(*top).rotX -= 1;
		break;
	}
}