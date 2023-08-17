#include "superbox.h"
#include <iostream>

SuperBox::SuperBox(float x, float y, float z)
{
    setPosition(x, y, z);
    setMaterialColor(ofFloatColor(1.0, 0, 0));
    useTexture = false;
    useWireframe = false;
}

void SuperBox::setPosition(float pX, float pY, float pZ)
{
    box.setPosition(pX, pY, pZ);
}

void SuperBox::move(ofVec3f direction)
{
    box.move(direction);//this just keeps adding these amounts to current position
}

void SuperBox::setWidth(float w){
    box.setWidth(w);
}

void SuperBox::setHeight(float h){
    box.setHeight(h);
}

void SuperBox::setDepth(float d){
    box.setDepth(d);
}

void SuperBox::draw()
{
    ofPushMatrix();

    if (useTexture){
        texture.getTexture().bind();
        if(useWireframe){
            box.drawWireframe();
        }else{
            box.draw();
        }
        texture.getTexture().unbind();
    }
    else {
        material.begin();
        if(useWireframe){
            box.drawWireframe();
        }else{
            box.draw();
        }
        material.end();
    }

    ofPopMatrix();
}

//Axis Y for example is ofVec3f(0,1,0)
//Axis X is ofVec3f(1,0,0)
//etc
void SuperBox::rotateDeg(float angle, ofVec3f axis)
{
    box.rotateDeg(angle, axis);
}

void SuperBox::setMaterialColor(ofFloatColor col)
{
    material.setDiffuseColor(col);
    useTexture = false; // they just set the material color so
                        // assume they don't want to use the texture
}

void SuperBox::setTexture(ofImage tex)
{
    texture = tex;
    useTexture = true;// they just set the texture, so
                      // assume they want to use it!
}

void SuperBox::setDrawWireframe(bool setUseWireframe){
    useWireframe = setUseWireframe;
}
