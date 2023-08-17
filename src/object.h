#ifndef OBJECT_H
#define OBJECT_H
#include "ofMain.h"

class object
{
public:
	object(float _x, float _y);
	~object();

	//Functions
	virtual void setup();
	virtual void update();
	virtual void draw();
	bool collision(ofVec3f ballPosition, float ballRadius);
	void setColor(ofColor _color);
	ofColor color;

private:
	//Objects
	ofBoxPrimitive cube;	

protected:
	//Variables
	float x;
	float y;
	float z;
	float radius;
	
};
#endif //OBJECT_H
