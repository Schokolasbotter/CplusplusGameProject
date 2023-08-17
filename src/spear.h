#ifndef SPEAR_H
#define SPEAR_H

#include "ofMain.h"
#include "object.h"

class spear : public object
{
public:
	//Override Functions

	spear(float _x, float _y);

	void setup() override;
	void update() override;
	void draw() override;

private:
	//Objects
	ofCylinderPrimitive body;
	ofConePrimitive head;
	ofMaterial material;
};
#endif //SPEAR_H
