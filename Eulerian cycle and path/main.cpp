#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "ResourcePath.hpp"
#include "libs/programmObject.hpp"
#include "libs/button.hpp"
#include "myImage.hpp"
#include "myCircleShape.hpp"


using namespace std;
using namespace sf;



// FUNCTION PROTOTYPES


// INTERFACE VARIABLES
Color white_255 = Color(255, 255, 255);
Color white_255_1 = Color(255, 255, 255, 100);
Color blue = Color(0, 255, 251);
Color blue_1 = Color(0, 255, 251, 100);
Color black = Color(0, 0, 0);

int main(int, char const**)
{
    // Windows settings
    ContextSettings settings;
    settings.antialiasingLevel = 100;
    VideoMode videoMode;
    videoMode.width = 3840;
    videoMode.height = 2160;
    string name = "RetroWave";
    RenderWindow window(videoMode, name, Style::Default, settings);
    
    // Icon settings
    Image icon;
    if (!icon.loadFromFile(resourcePath() + "img/icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    Texture texture;
    if (!texture.loadFromFile(resourcePath() + "img/background.jpg"))
    {
        return EXIT_FAILURE;
    }
    Sprite sprite(texture);
    
    // Settings font
    Font font;
    if (!font.loadFromFile(resourcePath() + "font/din.otf"))
    {
        return EXIT_FAILURE;
    }
    
    // Settings music
    Music music;
    if (!music.openFromFile(resourcePath() + "music/nightcall.ogg"))
    {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.play();
    
    myImage lw("lw.png", 2800, 100, -3);
    myImage clan("clan.png", 3100, 250, 0);
    myImage alg("alg.png", 2950, 500, 0);
        
    
    myCircleShape shapeBlue_1(3, 3300, 300, 350, 350, 350, 180, 30, blue, Color(0, 0, 0, 0));
    myCircleShape shapeWhite_1(3, 3300, 300, 320, 320, 320, 180, 30, white_255, Color(0, 0, 0, 0));
    myCircleShape shapeBlue_2(3, 3300, 300, 290, 290, 290, 180, 20, blue, Color(0, 0, 0, 0));
    myCircleShape shapeWhite_2(3, 3300, 300, 320, 320, 320, 180, 30, white_255_1, Color(0, 0, 0, 0));
    shapeWhite_2.rotateShape(4);
    myCircleShape shapeWhite_3(3, 3300, 300, 320, 320, 320, 180, 30, white_255_1, Color(0, 0, 0, 0));
    shapeWhite_3.rotateShape(-4);
    
    
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
        window.draw(sprite);
        
        
        
        // Display circles
        window.draw(shapeBlue_1.shape);
        window.draw(shapeWhite_1.shape);
        window.draw(shapeBlue_2.shape);
        window.draw(shapeWhite_2.shape);
        shapeWhite_2.rotateShape(0.3);
        window.draw(shapeWhite_3.shape);
        shapeWhite_3.rotateShape(-0.5);
        
        // Display sprites
        window.draw(lw.sprite);
        window.draw(clan.sprite);
        window.draw(alg.sprite);
        
        
        // Draw the string
        //window.draw(text);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
