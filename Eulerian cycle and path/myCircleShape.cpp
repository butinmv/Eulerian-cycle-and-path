#include "myCircleShape.hpp"

myCircleShape::myCircleShape(int pc,  int xP, int yP, int xO, int yO, int rad, int rot,  int t, Color oC, Color fC)
{
    pointCount = pc;
    shape.setPointCount(pc);
    
    xPosition = xP;
    yPositon = yP;
    shape.setPosition(xP, yP);
    
    xOrigin = xO;
    yOrigin = yO;
    shape.setOrigin(xO, yO);
    
    radius = rad;
    shape.setRadius(rad);
    
    rotate = rot;
    shape.setRotation(rot);
    
    thinckness = t;
    shape.setOutlineThickness(t);
    
    fillColor = fC;
    shape.setFillColor(fC);
    
    outlineColor = oC;
    shape.setOutlineColor(oC);
}

void myCircleShape::rotateShape(float rot_2)
{
    rotate_2 = rot_2;
    shape.rotate(rot_2);
}

myCircleShape::~myCircleShape(void)
{
    
}

