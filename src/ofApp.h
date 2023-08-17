#pragma once

#include "ofMain.h"
#include "superbox.h"
#include "ball.h"
#include "object.h"
#include "snowman.h"
#include "spear.h"
#include "racket.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Scene Functions
		void setupRoom();
		void drawRoom();
		void setupShelf();
		void drawShelf();

		//Axis
		void drawAxis();

		//Camera
		ofCamera cam;

		//Room Setup
		ofPlanePrimitive floor;
		ofPlanePrimitive wall1, wall2, wall3;
		ofTexture floorTexture;
		ofTexture wallTexture;
		ofLight pointLight;

		//Shelf
		SuperBox horizontal1{ 0, 10, -250 }, horizontal2{ 0, 210, -250 }, horizontal3{ 0, 410, -250 }, horizontal4{ 0, 610, -250 }, vertical1{ -360,310,-250 }, vertical2{ -125,310,-250 }, vertical3{ 110,310,-250 }, vertical4{ 360,310,-250 };
		ofTexture shelfTexture;
		struct objectPositions { float x; float y; bool activeStatus;};
		objectPositions positionsArray[9];

		//Ball
		ball* throwBall = new ball{ 1000,1000 };
		float force;

		//Force UI
		ofPlanePrimitive forceBackground;
		ofPlanePrimitive forceMeter;

		//Other Variables
		bool isPressing;

		//Objects
		object *object0, *object1, *object2, *object3, *object4, *object5, *object6, *object7, *object8;
		void spawnNewObject(int id);
		void setupObjects();
		void updateObjects();
		void drawObjects();

		//Colors
		ofColor red;
		ofColor green;
		ofColor blue;
		vector<ofColor> colors;

		//Game Logic
		float respawnTimer;
		int nextSpawn;
		float gameTimer;
		bool gameOn;
		int score;
		void increaseScore(ofColor color);

		//Interface Text
		ofTrueTypeFont font;
};
