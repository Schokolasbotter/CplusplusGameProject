#include "snowman.h"

snowman::snowman(float _x, float _y) :object(_x, _y) {

}

void snowman::setup() {
	//Set Snowman Dimensions
	body.setRadius(radius / 2);
	body.setPosition(x, y - 25, -250);
	head.setRadius(radius / 3);
	head.setParent(body);
	head.setPosition(0, radius / 2 + radius / 4, 0);
	head.rotateAroundDeg(30, glm::vec3(0, 0, 1), glm::vec3(x, y - radius / 2 + radius / 4, -250));
}

void snowman::update() {
	body.rotateDeg(2, 0, 1, 0);
}

void snowman::draw() {	
	ofSetColor(color); //Set Color
	body.draw();
	head.draw();
	ofSetColor(255, 255, 255); //Reset Color to white
}