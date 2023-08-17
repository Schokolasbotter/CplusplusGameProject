#include "spear.h"

spear::spear(float _x, float _y) :object(_x, _y) {

}

void spear::setup() {
	//Set spear Dimensions
	body.setHeight(radius *1.5);
	body.setRadius(radius / 10);
	body.setPosition(x, y - 25, -250);
	head.setRadius(radius / 3);
	head.setHeight(radius*2/3);
	head.rotateDeg(180, 0, 0, 1);
	head.setParent(body);
	head.setPosition(0, radius*1.5 / 2 + radius *1/3, 0);
	body.rotateDeg(30, 0, 0, 1);
}

void spear::update() {
	body.rotateDeg(2, 0, 1, 0);
}

void spear::draw() {
	ofSetColor(color); //Set Color
	body.draw();
	head.draw();
	ofSetColor(255, 255, 255); //Reset Color to white
}