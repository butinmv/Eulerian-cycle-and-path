#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "ResourcePath.hpp"
#include "libs/programmObject.hpp"
#include "libs/button.hpp"
#include "myImage.hpp"
#include "myCircleShape.hpp"


using namespace std;
using namespace sf;



// FUNCTION PROTOTYPES
void readFile(string file);         // read graph from file
void showGraph();                   // display graph on console
void findEulerPath();               // find eulerian cycle and path


// GLOBAL VARIABLES
vector <vector <int> * > graph;     // graph
int countVertex;                    // count of vertex
vector<int> degree;                 // degree vector


// INTERFACE VARIABLES
Color white_255 = Color(255, 255, 255);
Color white_255_1 = Color(255, 255, 255, 100);
Color blue = Color(0, 255, 251);
Color blue_1 = Color(0, 255, 251, 100);
Color black = Color(0, 0, 0);
Color dark_red = Color(219, 15, 70);
Color orange = Color(255, 82, 8);
vector<int> x,y;


int main(int, char const**)
{
    
//////////////////////////////////////////////////////////////////////////////////////////////INTERFACE//////////////////////////////////////////////////////////////////////////////////////////////
    // Windows settings
    ContextSettings settings;
    settings.antialiasingLevel = 100;
    VideoMode videoMode;
    videoMode.width = 3840;
    videoMode.height = 2160;
    string name = "Eulerian cycle and path";
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
    Text text("", font, 35);
    text.setFillColor(dark_red);
    text.setOutlineThickness(1);
    text.setOutlineColor(orange);
    
    // Settings music
    Music music;
    if (!music.openFromFile(resourcePath() + "music/nightcall.ogg"))
    {
        return EXIT_FAILURE;
    }
    
    // Play the music
    //music.play();
    
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
    
    // Circle for vertex
    int r = 30;
    CircleShape shapeInCyclePath(r);
    shapeInCyclePath.setOutlineColor(Color::Red);
    shapeInCyclePath.setOutlineThickness(5);
    shapeInCyclePath.setFillColor(Color(0, 0, 0, 0));
    
    CircleShape shapeVertex(r);
    shapeVertex.setOutlineColor(dark_red);
    shapeVertex.setOutlineThickness(5);
    shapeVertex.setFillColor(orange);
//////////////////////////////////////////////////////////////////////////////////////////////INTERFACE//////////////////////////////////////////////////////////////////////////////////////////////
    
    // MAIN PROGRAMM
    readFile("input.txt");
    showGraph();
    findEulerPath();
    
    
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
        
        // Edge output
        RectangleShape line;
        line.setFillColor(orange);
        
        ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setFillColor(orange);
        triangle.setOutlineColor(dark_red);
        triangle.setOutlineThickness(3);
        for (int i = 0; i < countVertex; i++)
            for (int j = 0; j < countVertex; j++)
            {
                //ConvexShape *triangle = &triangleGold;
                int a = i;
                int b = j;
                float h_ab, w_ab, long_ab, angle;
                h_ab = x[a] - x[b];
                w_ab = y[a] - y[b];
                // гипотенуза
                long_ab = sqrt(h_ab * h_ab + w_ab * w_ab);
                // угол
                angle = asin(h_ab / long_ab) / M_PI * 180;
                if(h_ab < 0 && w_ab > 0)
                    angle = 180 - angle;
                if(h_ab >= 0 && w_ab >= 0)
                    angle = 180 - angle;
                // задаем угол
                line.setRotation(angle);
                // размер линии
                line.setSize(Vector2f(1, long_ab));
                // от куда идет линия
                line.setPosition(Vector2f(x[a] + r, y[a] + r));
                // треугольник
                // определяем вершины
                int r = 30, rr = 90, rrr = 5;
                triangle.setPoint(0, Vector2f(x[b] + r, y[b] + r));
                angle = angle - 90;
                triangle.setPoint(1, Vector2f(x[b] + rr*cos((angle + rrr)*M_PI/180) +
                                               r, y[b] +
                                               rr*sin((angle + rrr) * M_PI/180) + r));
                triangle.setPoint(2, Vector2f(x[b] + rr*cos((angle - rrr)*M_PI/180) +
                                               r, y[b] +
                                               rr*sin((angle - rrr) * M_PI/180) + r));
                window.draw(line);
                window.draw(triangle);
            }
                    

        
        // Vertex output
        for (int i = 0; i < countVertex; i++)
        {
            shapeVertex.setPosition(x[i], y[i]);
            string s = to_string(i + 1);
            text.setString(s);
            text.setPosition(x[i] - 30, y[i] - 30);
            window.draw(shapeVertex);
            window.draw(text);
        }
        
        
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}

// IMPLEMENTATION OF FUNCTIONS
void readFile(string file)          // Read graph from file
{
    // Clearing the vertices
    int size = graph.size();
    for (int i = 0; i < size; i++)
        graph[i]->clear();
    graph.clear();
    
    countVertex = 0;                                   // count of vertex
    ifstream inputFile(file);
    if (!inputFile.is_open())
        cout << "Error! File is not found!" << endl;
    else
        inputFile >> countVertex;
    
    for (int i = 0; i < countVertex; i++)
    {
        graph.push_back(new vector<int>(countVertex));  // Init graph
        degree.push_back(0);                            // Init degree
    }
    
    // calculation of coordinates of vertices
    int r = 800;
    for (int i = 0; i < countVertex; i++)
    {
        int xx = 1220 - 30 + r * cos(i * 360 / countVertex * M_PI / 180);
        int yy = 1100 - 30 + r * sin(i * 360 / countVertex * M_PI / 180);
        x.push_back(xx);
        y.push_back(yy);
    }
    
    
    // Read adjacency matrix
    char vertex;
    for (int i = 0; i < countVertex; i++)
        for (int j = 0; j < countVertex; j++)
        {
            inputFile >> vertex;
            if (vertex == '1')
                (*graph[i])[j] = 1;
            else
                (*graph[i])[j] = 0;
        }
    
    // Close the file
    inputFile.close();

}

void findEulerPath()                // Find Eulerian cycle and path
{
    // read degree of graph
    for (int i = 0; i < countVertex; i++)
        for (int j = 0; j < countVertex; j++)
            degree[i] += (*graph[i])[j];
    
    int first = 0;
    while (!degree[first])
        ++first;
    
    // check degree of verteces
    int v1 = -1,  v2 = -1;                      // v1 and v2 - odd vertices
    bool bad = false;
    for (int i = 0; i < countVertex; i++)
        if (degree[i] % 2 == 1)                 // if vertices with odd degree
        {
            if (v1 == -1)                       // check v1
                v1 = i;
            else if (v2 == -1)                  // check v2
                v2 = i;
            // if graph has two vertices with odd degree,
            // graph has only Euler path
            else                                // else vertices with odd degree are more than 2,
                bad = true;                     // the graph doesn't have Euler cycle or Eulerian path
        }
        // if graph doesn't have vertices with odd degree,
        // graph has only Euler cycle
    
    // find Euler cycle
    // add sham edge
    if (v1 != -1)
    {
        ++(*graph[v1])[v2];
        ++(*graph[v2])[v1];
    }
    
    vector<int> res;                            // vector for result
    stack<int> st;                              // stack for working
    st.push (first);                            // push start vertex
    while (!st.empty())                         // while stack isn't empty
    {
        int v = st.top();                       // v - is value on top of stack
        int i;
        for (i = 0; i < countVertex; ++i)
            if ((*graph[v])[i])                 // if degree(v) = 0
                break;
        if (i == countVertex)
        {
            res.push_back(v);                   // add v to vector res
            st.pop();                           // pop v from top of stack
        }
        else                                    // find any edge from v
        {
            --(*graph[v])[i];                   // delete this edge
            --(*graph[i])[v];
            st.push (i);                        // second tail of this edge push to st
        }
    }
    
    // find Euler path
    if (v1 != -1)
        for (int i = 0; i + 1 < res.size(); i++)
            if ( (res[i] == v1 && res[i + 1] == v2) || (res[i] == v2 && res[i + 1] == v1) )
            {
                vector<int> res2;
                for (int j = i + 1; j < res.size(); j++)
                    res2.push_back (res[j]);
                for (int j = 1; j <= i; j++)
                    res2.push_back (res[j]);
                res = res2;
                break;
            }
    
    // check for graph connectivity
    for (int i = 0; i < countVertex; i++)
        for (int j = 0; j < countVertex; j++)
            if ((*graph[i])[j])
                bad = true;
    
    if (bad)
        cout << "Incoherent graph";
    else
        for (int i = 0; i < res.size(); i++)
            cout << res[i] + 1 << " ";
    
   
}

void showGraph()                    // Display graph on console
{
    cout << "Count of vertex: " << graph.size() << endl;
    for (int i = 0; i < countVertex; i++)
    {
        for (int j = 0; j < countVertex; j++)
            cout << (*graph[i])[j] << " ";
        cout << endl;
    }
}
