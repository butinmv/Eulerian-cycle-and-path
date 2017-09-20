#include "myImage.hpp"

myImage::myImage(string file_, int x_, int y_, int rotate_)
{
    file = file_;
    img.loadFromFile(resourcePath() + "img/" + file);
    img.createMaskFromColor(Color::Black);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    x = x_;
    y = y_;
    rotate = rotate_;
    sprite.setPosition(x_, y_);
    sprite.rotate(rotate_);
}

myImage::~myImage(void)
{
}
