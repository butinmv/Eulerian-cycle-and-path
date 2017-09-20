#ifndef myImage_hpp
#define myImage_hpp

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace sf;
using namespace std;

// CLASS FOR IMAGE
class myImage
{
public:
    Image img;          // sfml image
    Texture texture;    // sfml texture
    Sprite sprite;      // sfml sprite
    string file;        // file with extension
    int x;              // coordinate x for sprite
    int y;              // coordinate y for sprite
    int rotate;         // rotate for sprite

    // constructor
    myImage(string file_, int x_, int y_, int rotate_);

    // destructor
    ~myImage(void);
};


#endif
