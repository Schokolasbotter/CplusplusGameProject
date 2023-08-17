#include "racket.h"

racket::racket(float _x, float _y) :object(_x, _y) {

}

void racket::setup() {
	//Set racket Dimensions
	body.setHeight(radius * 2/3);
	body.setRadius(radius / 10);
	body.setPosition(x, y - 50, -250);
	head.setRadius(radius * 0.7);
	head.setResolutionRadius(20);
	head.setHeight(radius / 10);
	head.rotateDeg(90, 1, 0, 0);
	head.setParent(body);
	head.setPosition(0, radius * 1/3 + radius* 0.7, 0);
	body.rotateDeg(30, 0, 0, 1);
}

void racket::update() {
	body.rotateDeg(2, 0, 1, 0);
}

void racket::draw() {
	ofSetColor(color); //Set Color
	body.draw();
	head.draw();
	ofSetColor(255, 255, 255); //Reset Color to white
}