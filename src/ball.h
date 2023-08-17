#ifndef BALL_H
#define BALL_H
#include "ofMain.h"

class ball
{
public:
	ball(float x, float y);
	~ball();

	void setup();
	void update();
	void draw();

	void setPosition(float x, float y);
	ofVec3f getPosition();
	void setAcceleration(float force);
	bool checkBoundaries();

	//Public Variables
	bool isLaunched;
	float radius;

private:
	//Object
	ofSpherePrimitive sphere;
	ofTexture ballTexture;
	

	//Physics Variables
	ofVec3f ballPosition;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f drag;
	ofVec3f gravity;
	float mass;
};
#endif //BALL_H
