#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "ofMain.h"
#include "object.h"

class snowman : public object
{
public:
	//Override Functions

	snowman(float _x, float _y);

	void setup() override;
	void update() override;
	void draw() override;

private:
	//Objects
	ofSpherePrimitive body;
	ofSpherePrimitive head;
	ofMaterial material;
};
#endif //SNOWMAN_H
