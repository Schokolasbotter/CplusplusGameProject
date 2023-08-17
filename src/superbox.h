#ifndef SUPERBOX_H
#define SUPERBOX_H

#include "ofMain.h"

class SuperBox
{
public:
    SuperBox(float x, float y, float z);

    void draw();

    void setPosition(float pX, float pY, float pZ);
    
    void move(ofVec3f direction);

    void rotateDeg(float angle, ofVec3f axis);

    void setMaterialColor(ofFloatColor col);

    void setTexture(ofImage tex);
    
    void setDrawWireframe(bool setUseWireframe);

    void setWidth(float w);
    void setHeight(float h);
    void setDepth(float d);

private:

    bool useTexture;
    bool useWireframe;
    ofMaterial material;
    ofBoxPrimitive box;
    ofImage texture;

};

#endif // SUPERBOX_H
