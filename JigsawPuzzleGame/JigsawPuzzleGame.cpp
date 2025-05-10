// Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Due Date May 14.

using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(){


    //-------------------------------------------------
    // New Window with a green circle
    //-------------------------------------------------

    
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }


    //-------------------------------------------------
    // Manipulating Angles
    //-------------------------------------------------
    sf::Angle angle1 = sf::degrees(10);
    angle1 *= 2.f; // 20 degrees
    sf::Angle angle2 = angle1 + sf::radians(0.5f); // 48.6 degrees
    angle2 = -angle2; // -48.6 degrees
    angle2 /= 3.f; // -16.2 degrees

    bool equal = (angle1 == angle2); // false
    bool inequal = (angle1 != angle2); // true

    cout << "Manipulating Angles" << endl;

    cout << "Angle1: " << angle1.asDegrees() << " degrees" << endl;
    cout << "Angle1: " << angle1.asRadians() << " radians" << endl;

    cout << "Angle2: " << angle2.asDegrees() << " degrees" << endl;
    cout << "Angle2: " << angle2.asRadians() << " radians" << endl;

    cout << "Is Angle1 = Angle2 : " << equal << endl;
    cout << "Is Angle1 = Angle2 : " << inequal << endl;

    //-------------------------------------------------
    // Clock and Time
    //-------------------------------------------------
    
    cout << "\nClock and Time" << endl;

    sf::Time t1 = sf::microseconds(10000);
    sf::Time t2 = sf::milliseconds(10);
    sf::Time t3 = sf::seconds(0.01f);

    cout << "t1: " << t1.asMicroseconds() << " microseconds" << endl;
    cout << "t2: " << t2.asMilliseconds() << " milliseconds" << endl;
    cout << "t3: " << t3.asSeconds() << " seconds" << endl;

    sf::Clock clock; // starts the clock
    
    //Time is constant, so we need to update it.
    sf::Time elapsed1 = clock.getElapsedTime(); 
    cout << "elapsed1: " << elapsed1.asMicroseconds() << " microseconds" << endl;
    clock.restart();

    elapsed1 = clock.getElapsedTime();
    sf::Time elapsed2 = clock.getElapsedTime();
    cout << "elapsed2: " << elapsed2.asMilliseconds() << " milliseconds" << endl;
    clock.restart();
    
    elapsed1 = clock.getElapsedTime();
    sf::Time elapsed3 = clock.getElapsedTime();
    std::cout << "elapsed3: " << elapsed3.asSeconds() << " seconds" << endl;

    clock.stop(); // stops the clock
    cout << "Is the clock running: " << boolalpha << clock.isRunning() << endl; // boolalpha transform the bool into "true / false" instead of "1 / 0"
    clock.reset(); // resets elapsed time to zero, and also stop running the clock.

    clock.start(); // starts the clock
    sf::Time elapsed4 = clock.getElapsedTime();
    cout << "elapsed4: " << elapsed4.asSeconds() << " seconds" << endl;

    /*
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        updateGame(elapsed);
        ...
    }*/

    //-------------------------------------------------
    // User Streams (input and output)
    //-------------------------------------------------


    //Using an input stream

    sf::FileInputStream stream("Grapes.png"); // I'm using this for a test texture. Maybe...
    sf::Texture texture(stream);

    //-------------------------------------------------
    // Attempting to open another window with the Grapes.png
    //-------------------------------------------------

    sf::Texture texture2("Grapes.png");
    sf::Sprite sprite(texture);

    sf::Font font("Roboto-Regular.tff");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    text.setString("Hello world");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


        // inside the main loop, between window.clear() and window.display()
        


    cout << "\nOpening a new window" << endl;
    cout << "When 2 seconds has pass the window will change." << endl;

    sf::RenderWindow window2(sf::VideoMode({ 800, 600 }), "Orignal window");
   
    clock.restart();
    sf::Time elapsed5 = clock.getElapsedTime();

    // run the program as long as the window is open
    while (window2.isOpen()){

        window2.clear();
        window2.draw(sprite);
        window2.draw(text);
        window2.display();

        elapsed5 = clock.getElapsedTime();

        if (elapsed5.asSeconds() > 2) {
            // change the position of the window (relatively to the desktop)
            window2.setPosition({ 10, 50 });

            // change the size of the window
            window2.setSize({ 640, 480 });

            // change the title of the window
            window2.setTitle("New SFML window");

            // get the size of the window
            sf::Vector2u size = window2.getSize();
            auto [width, height] = size;

            // check whether the window has the focus
            bool focus = window.hasFocus();

            //sprite.setTextureRect(sf::IntRect({ 10, 10 }, { 32, 32 })); //Changes the rectangle of the texture.
            sprite.setColor(sf::Color(0, 255, 0)); // green
            sprite.setColor(sf::Color(255, 255, 255, 128)); // half transparent
            // position
            //sprite.setPosition({ 10.f, 50.f }); // absolute position
            sprite.move({ 10.f, 10.f }); // offset relative to the current position

            // rotation
            sprite.setRotation(sf::degrees(90)); // absolute angle
            //sprite.rotate(sf::degrees(14)); // offset relative to the current angle

            // scale
            sprite.setScale({ 2.5f, 2.f }); // absolute scale factor
            sprite.scale({ 1.5f, 1.25f }); // factor relative to the current scale
            //sprite.setOrigin({ 25.f, 25.f });
        }

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window2.pollEvent()){
        
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window2.close();

            // Whenever a key is press trigger this event.
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << static_cast<int>(keyPressed->scancode) << std::endl;
                    std::cout << "code: " << static_cast<int>(keyPressed->code) << std::endl;
                    std::cout << "control: " << keyPressed->control << std::endl;
                    std::cout << "alt: " << keyPressed->alt << std::endl;
                    std::cout << "shift: " << keyPressed->shift << std::endl;
                    std::cout << "system: " << keyPressed->system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString() << std::endl;
                    std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed->scancode)) << std::endl;
                    std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed->code)) << std::endl;
                }
            }
        }
        
    }
    



}


/*
using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>

void loopFunction(int y);


class button {

public:
    bool pressable;

};


int main()
{
    cout << "Press q to quit!\n" << endl;

    bool quit = false;


    string input;
    int loop = 0;

    button a;
    a.pressable = true;

    cout << a.pressable << endl;

    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }



    // Main while loop where game jigsaw will play.
    while (!quit) {

        cin >> input;

        if (input == "q")
            quit = true;

        if (quit)
            cout << "Quit: True." << endl;
        else
            cout << "Quit: False." << endl;

        loop++;
        cout << "Loop: " << loop << endl;

        loopFunction(loop);

    }


    cout << "Exiting program." << endl;
}


void loopFunction(int y) {

    int x = 0;

    for (int i = 0; i < y; i++) {
        cout << "Loop: " << x << endl;
        x++;
    }

    cout << "Loop terminated" << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

*/