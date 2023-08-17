#include "ofApp.h"
#include <iostream>
#include <algorithm>
#include <vector>

//--------------------------------------------------------------
void ofApp::setup(){
	//Window Setup
	ofSetWindowShape(1280, 720);
	ofSetWindowPosition(200, 200);
	ofHideCursor();
	ofSetFrameRate(30);
	//Background
	ofSetBackgroundColor(0, 0, 0);
	//Camera
	cam.setPosition(0, 250, 500);
	//Setup Room
	setupRoom();
	//Setup Shelf
	setupShelf();
	//Setup Force UI
	forceBackground.set(12, 27);
	forceMeter.set(10, 25);
	//Physics
	force = 0;
	//Colors
	red.set(255, 0, 0);
	green.set(0, 255, 0);
	blue.set(0, 0, 255);
	colors.push_back(red);
	colors.push_back(green);
	colors.push_back(blue);
	//Objects
	setupObjects();
	//Game Logic
	respawnTimer = 0;
	nextSpawn = 60;
	gameTimer = 120;
	gameOn = false;
	score = 0;
	//GUI
	font.load("Roboto-Bold.ttf", 25);
}

//--------------------------------------------------------------
void ofApp::update(){
	//Update Light
	pointLight.setPosition(cam.getPosition().x, cam.getPosition().y, 400);
	//Update the ball
	throwBall->update();
	//Increase force if mouse is pressed
	if (isPressing) {
		//Increase Force
		//force += 0.05;
		force = ofClamp(force+0.05, 0, 1.7);
		//Update Force UI
		forceBackground.setPosition(cam.getPosition().x + 20, cam.getPosition().y, 300);		
		forceMeter.setPosition(cam.getPosition().x + 20, cam.getPosition().y - ofMap(force, 0, 1.7, 11, 0), 301);
		//Update Height of the meter depending on force
		forceMeter.set(10, ofMap(force, 0, 1.7, 0, 25));
	}
	//Update Objects
	updateObjects();
	//Game Logic
	if (gameOn) { //When GameMode is on
		gameTimer -= 0.033; //30FPS -> 1/30 reduced every frame
	}
	if (gameTimer <= 0) { //Endgame when Timer reaches 0
		gameTimer = 0; // Set to 0;
		gameOn = false; // Swap of gameMode
	}
	//Respawn Logic
	vector<int> emptyPositions; //Create local vector
	respawnTimer += 1; // Incr Respawn Timer		
	if (respawnTimer >= nextSpawn) { //When Timer runs out
		//Check for empty spaces
		for (int i = 0; i < 9; i++) {
			if (positionsArray[i].activeStatus == 0)
			{
				//Remember which positions are empty				
				emptyPositions.push_back(i);				
			}
		}
		//when there is an empty position
		if (emptyPositions.size() != 0) {
			//Create new object on random position of empty ones
			int randomIndex = roundf(ofRandom(0, emptyPositions.size() - 1));			
			spawnNewObject(emptyPositions[randomIndex]); //Create Object
		}
		//Dynamic SpawnRate 
		if (emptyPositions.size() <= 2) { // 0, 1 or 2 empty cases -> every 3 seconds
			nextSpawn = 90;
		}
		else if (emptyPositions.size() <= 5) { // 3, 4, 5 empty cases -> every 2 seconds
			nextSpawn = 60;
		}
		else if (emptyPositions.size() <= 9) { // 6, 7, 8 ,9 empty cases -> every second
			nextSpawn = 30;
		}
		//Reset respawnTimer
		respawnTimer = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){	
	ofEnableDepthTest(); //3D Setup	
	pointLight.enable(); //Light	
	cam.begin(); //Camera
	//Axis
	//drawAxis(); //Visual Help
	//Draw Room
	drawRoom();
	//Draw Shelf
	drawShelf();
	//ball
	throwBall->draw();
	//When mouse button is being held
	if (isPressing) {
		//Force UI
		forceBackground.draw();
		ofSetColor(255, 0, 0);
		forceMeter.draw();
		ofSetColor(255);
	}
	//Objects
	drawObjects();
	cam.end(); //Camera end
	pointLight.disable(); //Light End
	ofDisableDepthTest(); //3D End
	//Text on Screen
	ofSetColor(0);
	font.drawString("Score: " + ofToString(score),50, 50);
	font.drawString("Timer: " + ofToString(gameTimer), ofGetWidth()- 250, 50);
	font.drawString("[SPACE]  Start Game \n[MOUSE] Aim \n[MOUSE CLICK] Charge Shot", 10, ofGetHeight()-120);
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::exit() {
	//When app is being closed delete dynamic memory
	delete throwBall; // delete pointer when exiting app
	//Objects
	delete object0;
	delete object1;
	delete object2;
	delete object3;
	delete object4;
	delete object5;
	delete object6;
	delete object7;
	delete object8;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 32) { //Spacebar
		//Set Staring values
		gameTimer = 120;
		score = 0;
		gameOn = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//Update Camera
	cam.setPosition(ofClamp(x, ofGetWidth()/4, ofGetWidth()*3/4) - ofGetWidth() / 2,250-(ofClamp(y,0,ofGetHeight()*3/4) - ofGetHeight()/2),500);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//Update Camera
	cam.setPosition(ofClamp(x, ofGetWidth() / 4, ofGetWidth() * 3 / 4) - ofGetWidth() / 2, 250 - (ofClamp(y, 0, ofGetHeight() * 3 / 4) - ofGetHeight() / 2), 500);
	//Update Ball
	throwBall->setPosition(ofClamp(x, ofGetWidth() / 4, ofGetWidth() * 3 / 4) - ofGetWidth() / 2, 250 - (ofClamp(y, 0, ofGetHeight() * 3 / 4) - ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	isPressing = true; // Signal for mouse being held down
	//Create new ball at camera coordinates
	delete throwBall;
	throwBall = new ball{ cam.getPosition().x,cam.getPosition().y };
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	isPressing = false; // Signal for mouse is not being held anymore
	//Launch ball
	throwBall->setAcceleration(force);
	throwBall->isLaunched = true;
	force = 0; //reset force
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::setupRoom() {
	//Setup Primitives
	floor.set(1000, 1000);
	floor.rotateDeg(90, 1, 0, 0);
	wall1.set(1000, 1500);
	wall1.setPosition(0, 750, -500);
	wall2.set(1000, 1500);
	wall2.setPosition(-500, 750, 0);
	wall2.rotateDeg(90, 0, 1, 0);
	wall3.set(1000, 1500);
	wall3.setPosition(500, 750, 0);
	wall3.rotateDeg(90, 0, 1, 0);
	//Get Textures
	ofDisableArbTex();
	ofLoadImage(floorTexture, "floorTexture.jpg");
	ofLoadImage(wallTexture, "wallTexture.jpg");
	//Light
	pointLight.setPointLight();
	pointLight.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
	pointLight.setPosition(cam.getPosition().x, cam.getPosition().y,310);
}

//--------------------------------------------------------------
void ofApp::drawRoom() {
	//Draw the room
	floorTexture.bind();
	floor.draw();
	floorTexture.unbind();
	wallTexture.bind();
	wall1.draw();
	wall2.draw();
	wall3.draw();
	wallTexture.unbind();
}

//--------------------------------------------------------------
void ofApp::setupShelf() {
	horizontal1.setWidth(700);
	horizontal1.setHeight(20);
	horizontal1.setDepth(100);
	horizontal1.setMaterialColor(ofFloatColor(255));
	horizontal2.setWidth(700);
	horizontal2.setHeight(20);
	horizontal2.setDepth(100);
	horizontal2.setMaterialColor(ofFloatColor(255));
	horizontal3.setWidth(700);
	horizontal3.setHeight(20);
	horizontal3.setDepth(100);
	horizontal3.setMaterialColor(ofFloatColor(255));
	horizontal4.setWidth(700);
	horizontal4.setHeight(20);
	horizontal4.setDepth(100);
	horizontal4.setMaterialColor(ofFloatColor(255));
	vertical1.setWidth(20);
	vertical1.setHeight(620);
	vertical1.setDepth(100);
	vertical1.setMaterialColor(ofFloatColor(255));
	vertical2.setWidth(20);
	vertical2.setHeight(620);
	vertical2.setDepth(100);
	vertical2.setMaterialColor(ofFloatColor(255));
	vertical3.setWidth(20);
	vertical3.setHeight(620);
	vertical3.setDepth(100);
	vertical3.setMaterialColor(ofFloatColor(255));
	vertical4.setWidth(20);
	vertical4.setHeight(620);
	vertical4.setDepth(100);
	vertical4.setMaterialColor(ofFloatColor(255));
	ofLoadImage(shelfTexture, "shelfTexture.jpg");

	//Positions Array
	positionsArray[0] = objectPositions{ -240,420,1 };
	positionsArray[1] = objectPositions{ 0,420,1 };
	positionsArray[2] = objectPositions{ 230,420,1 };
	positionsArray[3] = objectPositions{ -240,220,1 };
	positionsArray[4] = objectPositions{ 0,220,1 };
	positionsArray[5] = objectPositions{ 230,220,1 };
	positionsArray[6] = objectPositions{ -240,20,1 };
	positionsArray[7] = objectPositions{ 0,20,1 };
	positionsArray[8] = objectPositions{ 230,20,1 };
}

//--------------------------------------------------------------
void ofApp::drawShelf() {
	//Draw Shelf with texture applied
	shelfTexture.bind();
	horizontal1.draw();
	horizontal2.draw();
	horizontal3.draw();
	horizontal4.draw();
	vertical1.draw();
	vertical2.draw();
	vertical3.draw();
	vertical4.draw();
	shelfTexture.unbind();
}

//--------------------------------------------------------------
void ofApp::spawnNewObject(int i) {
	//Input is the id of which position needs to be filled
	switch (i)
	{
	case 0:
		switch (rand()%4) //Chose Ranomdly which object to create
		{
		case 0:
			object0 = new object{ positionsArray[0].x, positionsArray[0].y };
			break;
		case 1:
			object0 = new snowman{ positionsArray[0].x, positionsArray[0].y };
			break;
		case 2:
			object0 = new spear{ positionsArray[0].x, positionsArray[0].y };
			break;
		case 3:
			object0 = new racket{ positionsArray[0].x, positionsArray[0].y };
		default:
			break;
		}
		object0->setup();
		object0->setColor(colors[rand()%colors.size()]); //Decide randomly on color
		positionsArray[0].activeStatus = 1; //Mark position as filled
		break;
	case 1:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object1 = new object{ positionsArray[1].x, positionsArray[1].y };
			break;
		case 1:
			object1 = new snowman{ positionsArray[1].x, positionsArray[1].y };
			break;
		case 2:
			object1 = new spear{ positionsArray[1].x, positionsArray[1].y };
			break;
		case 3:
			object1 = new racket{ positionsArray[1].x, positionsArray[1].y };
		default:
			break;
		}
		object1->setup();
		object1->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[1].activeStatus = 1; //Mark position as filled
		break;
	case 2:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object2 = new object{ positionsArray[2].x, positionsArray[2].y };
			break;
		case 1:
			object2 = new snowman{ positionsArray[2].x, positionsArray[2].y };
			break;
		case 2:
			object2 = new spear{ positionsArray[2].x, positionsArray[2].y };
			break;
		case 3:
			object2 = new racket{ positionsArray[2].x, positionsArray[2].y };
		default:
			break;
		}
		object2->setup();
		object2->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[2].activeStatus = 1; //Mark position as filled
		break;
	case 3:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object3 = new object{ positionsArray[3].x, positionsArray[3].y };
			break;
		case 1:
			object3 = new snowman{ positionsArray[3].x, positionsArray[3].y };
			break;
		case 2:
			object3 = new spear{ positionsArray[3].x, positionsArray[3].y };
			break;
		case 3:
			object3 = new racket{ positionsArray[3].x, positionsArray[3].y };
		default:
			break;
		}
		object3->setup();
		object3->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[3].activeStatus = 1; //Mark position as filled
		break;
	case 4:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object4 = new object{ positionsArray[4].x, positionsArray[4].y };
			break;
		case 1:
			object4 = new snowman{ positionsArray[4].x, positionsArray[4].y };
			break;
		case 2:
			object4 = new spear{ positionsArray[4].x, positionsArray[4].y };
			break;
		case 3:
			object4 = new racket{ positionsArray[4].x, positionsArray[4].y };
		default:
			break;
		}
		object4->setup();
		object4->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[4].activeStatus = 1; //Mark position as filled
		break;
	case 5:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object5 = new object{ positionsArray[5].x, positionsArray[5].y };
			break;
		case 1:
			object5 = new snowman{ positionsArray[5].x, positionsArray[5].y };
			break;
		case 2:
			object5 = new spear{ positionsArray[5].x, positionsArray[5].y };
			break;
		case 3:
			object5 = new racket{ positionsArray[5].x, positionsArray[5].y };
		default:
			break;
		}
		object5->setup();
		object5->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[5].activeStatus = 1; //Mark position as filled
		break;
	case 6:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object6 = new object{ positionsArray[6].x, positionsArray[6].y };
			break;
		case 1:
			object6 = new snowman{ positionsArray[6].x, positionsArray[6].y };
			break;
		case 2:
			object6 = new spear{ positionsArray[6].x, positionsArray[6].y };
			break;
		case 3:
			object6 = new racket{ positionsArray[6].x, positionsArray[6].y };
		default:
			break;
		}
		object6->setup();
		object6->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[6].activeStatus = 1; //Mark position as filled
		break;
	case 7:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object7 = new object{ positionsArray[7].x, positionsArray[7].y };
			break;
		case 1:
			object7 = new snowman{ positionsArray[7].x, positionsArray[7].y };
			break;
		case 2:
			object7 = new spear{ positionsArray[7].x, positionsArray[7].y };
			break;
		case 3:
			object7 = new racket{ positionsArray[7].x, positionsArray[7].y };
		default:
			break;
		}
		object7->setup();
		object7->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[7].activeStatus = 1; //Mark position as filled
		break;
	case 8:
		switch (rand() % 4) //Chose Ranomdly which object to create
		{
		case 0:
			object8 = new object{ positionsArray[8].x, positionsArray[8].y };
			break;
		case 1:
			object8 = new snowman{ positionsArray[8].x, positionsArray[8].y };
			break;
		case 2:
			object8 = new spear{ positionsArray[8].x, positionsArray[8].y };
			break;
		case 3:
			object8 = new racket{ positionsArray[8].x, positionsArray[8].y };
		default:
			break;
		}
		object8->setup();
		object8->setColor(colors[rand() % colors.size()]); //Decide randomly on color
		positionsArray[8].activeStatus = 1; //Mark position as filled
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::setupObjects() {
	//Create Starting objects and setup  and chose color
	object0 = new snowman{ positionsArray[0].x, positionsArray[0].y };
	object0->setup();
	object0->setColor(red);
	object1 = new spear{ positionsArray[1].x, positionsArray[1].y };
	object1->setup();
	object1->setColor(red);
	object2 = new racket{ positionsArray[2].x, positionsArray[2].y };
	object2->setup();
	object2->setColor(red);
	object3 = new object{ positionsArray[3].x, positionsArray[3].y };
	object3->setup();
	object3->setColor(red);
	object4 = new object{ positionsArray[4].x, positionsArray[4].y };
	object4->setup();
	object4->setColor(red);
	object5 = new object{ positionsArray[5].x, positionsArray[5].y };
	object5->setup();
	object5->setColor(red);
	object6 = new object{ positionsArray[6].x, positionsArray[6].y };
	object6->setup();
	object6->setColor(red);
	object7 = new object{ positionsArray[7].x, positionsArray[7].y };
	object7->setup();
	object7->setColor(red);
	object8 = new object{ positionsArray[8].x, positionsArray[8].y };
	object8->setup();
	object8->setColor(red);
}

//--------------------------------------------------------------
void ofApp::updateObjects() {
	object0->update();
	if (object0->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object0->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object0;
		object0 = new object{ 1000, 1000 };
		object0->setup();
		positionsArray[0].activeStatus = 0;
	}
	object1->update();
	if (object1->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object1->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object1;
		object1 = new object{ 1000, 1000 };
		object1->setup();
		positionsArray[1].activeStatus = 0;
	}
	object2->update();
	if (object2->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object2->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object2;
		object2 = new object{ 1000, 1000 };
		object2->setup();
		positionsArray[2].activeStatus = 0;
	}
	object3->update();
	if (object3->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object3->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object3;
		object3 = new object{ 1000, 1000 };
		object3->setup();
		positionsArray[3].activeStatus = 0;
	}
	object4->update();
	if (object4->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object4->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object4;
		object4 = new object{ 1000, 1000 };
		object4->setup();
		positionsArray[4].activeStatus = 0;
	}
	object5->update();
	if (object5->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object5->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object5;
		object5 = new object{ 1000, 1000 };
		object5->setup();
		positionsArray[5].activeStatus = 0;
	}
	object6->update();
	if (object6->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object6->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object6;
		object6 = new object{ 1000, 1000 };
		object6->setup();
		positionsArray[6].activeStatus = 0;
	}
	object7->update();
	if (object7->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object7->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object7;
		object7 = new object{ 1000, 1000 };
		object7->setup();
		positionsArray[7].activeStatus = 0;
	}
	object8->update();
	if (object8->collision(throwBall->getPosition(), throwBall->radius)) { //Collosion detection
		increaseScore(object8->color); //Increase score depening on color
		//Delete Object and create on outside of view and mark position as empty
		delete object8;
		object8 = new object{ 1000, 1000 };
		object8->setup();
		positionsArray[8].activeStatus = 0;
	}
}

//--------------------------------------------------------------
void ofApp::drawObjects() {
	//Draw objects
	object0->draw();
	object1->draw();
	object2->draw();
	object3->draw();
	object4->draw();
	object5->draw();
	object6->draw();
	object7->draw();
	object8->draw();
}

//--------------------------------------------------------------
void ofApp::increaseScore(ofColor color) {
	if (gameOn) { //When game is running increase score depending on which color it had
		if (color == red) {
			score += 100;
		}
		else if (color == green) {
			score += 200;
		}
		else if (color == blue) {
			score += 300;
		}
	}
}

//--------------------------------------------------------------
//Draws an indicator of the x, y, z axis directions at the center of our screen
void ofApp::drawAxis() {
	ofPushStyle();

	// X = RED = sideways = WIDTH
	ofSetLineWidth(3);
	ofSetColor(255, 0, 0);
	ofDrawLine(0, 0, 0, 100, 0, 0);

	// Y = GREEN = upward and downward = HEIGHT
	ofSetLineWidth(3);
	ofSetColor(0, 255, 0);
	ofDrawLine(0, 0, 0, 0, 100, 0);

	// Z = BLUE = toward / backward from camera = DEPTH
	ofSetLineWidth(3);
	ofSetColor(0, 0, 255);
	ofDrawLine(0, 0, 0, 0, 0, 100);

	ofPopStyle();
}
