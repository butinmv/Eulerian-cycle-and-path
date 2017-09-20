#ifndef myCircleShape_hpp
#define myCircleShape_hpp

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace sf;

class myCircleShape
{
public:
    CircleShape shape;
    int pointCount;
    int radius;
    int xOrigin;
    int yOrigin;
    int thinckness;
    int rotate;
    int xPosition;
    int yPositon;
    float rotate_2;
    Color outlineColor;
    Color fillColor;
    
    // constructor
    myCircleShape(int pc,  int xP, int yP, int xO, int yO, int rad, int rot,  int t, Color oC, Color fC);
    
    void rotateShape(float rot_2);
    
    // destractor
    ~myCircleShape(void);
};



#endif
