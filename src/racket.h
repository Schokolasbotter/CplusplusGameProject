#ifndef RACKET_H
#define RACKET_H

#include "ofMain.h"
#include "object.h"

class racket : public object
{
public:
	//Override Functions

	racket(float _x, float _y);

	void setup() override;
	void update() override;
	void draw() override;

private:
	//Objects
	ofCylinderPrimitive body;
	ofCylinderPrimitive head;
	ofMaterial material;
};
#endif //RACKET_H
