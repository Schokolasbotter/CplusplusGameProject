#include "object.h"

object::object(float _x, float _y) {
	//Set variables
	x = _x;
	y = _y + 100;
	z = -250;
	radius = 50;
}

object::~object() {

}

void object::setup() {
	//Set Cube Dimensions
	cube.set(radius);
	cube.setPosition(x, y, -250);
}

void object::update() {
	//Rotate Cube
	cube.rotateDeg(2, 0, 1, 0);
}

void object::draw() {
	ofSetColor(color); //Set Color
	cube.draw();
	ofSetColor(255, 255, 255); //Reset Color to white
}

bool object::collision(ofVec3f ballPosition,float ballRadius) {
	if (ofDist(ballPosition.x, ballPosition.y, ballPosition.z, x, y, z) <= radius + ballRadius) { //when distance is smaller then the sizes of the objects -> collision
		return true;
	}
	return false;
}

void object::setColor(ofColor _color) {
	color = _color;
}