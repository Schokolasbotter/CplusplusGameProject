#include "ball.h"
#include <iostream>

ball::ball(float x, float y) {

	//Setup Primitive
	radius = 10;
	sphere.setRadius(radius);
	sphere.setPosition(x, y, 300);

	//Setup Variables
	mass = 0.17; //kg
	drag.set(0, 0, 0.1);
	gravity.set(0, -0.2, 0);
	isLaunched = false;
	ofLoadImage(ballTexture, "ballTexture.jpg");
	sphere.rotateDeg(90, 0, 1, 0);

}
ball::~ball() {
}

void ball::setup() {
	
}

void ball::draw() {
	ballTexture.bind();
	sphere.draw();
	ballTexture.unbind();
}

void ball::update() {

	if (isLaunched) {
		//add all accelerations to velocity
		velocity += acceleration;  //Throw
		velocity += drag; // Air Resistance
		velocity += gravity; // gravity
		//Reset Acceleration
		acceleration.set(0, 0, 0);
		ballPosition += velocity;
		sphere.setPosition(sphere.getPosition() + ballPosition);
		sphere.rotateDeg(-20, 1, 0, 0);
	}	
}

void ball::setPosition(float x, float y) {
	sphere.setPosition(x, y, 300);
}

ofVec3f ball::getPosition() {
	ofVec3f currentPosition = ofVec3f(sphere.getX(), sphere.getY(), sphere.getZ());
	return currentPosition;
}

void ball::setAcceleration(float force) {
	float zAcceleration = force / mass;
	acceleration.set(0, 0, -zAcceleration); //Minus since we launch towards negative Z
	std::cout << "Force: " << force << std::endl;
	std::cout << "Accleration: " << acceleration << std::endl;
}

bool ball::checkBoundaries() {
	float x = sphere.getPosition().x;
	float y = sphere.getPosition().y;
	float z = sphere.getPosition().z;

	if (x > 500 || x < -500 || y > 500 || y < -500 || z > 500 || z < -500) {
		return true;
	}
	return false;
}