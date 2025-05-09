// Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>

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

    cout << "Angle1: " << angle1.asDegrees() << endl;
    cout << "Angle1: " << angle1.asRadians() << endl;

    cout << "Angle2: " << angle2.asDegrees() << endl;
    cout << "Angle2: " << angle2.asRadians() << endl;

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

    sf::FileInputStream stream("Grapes.png");
    sf::Texture texture(stream);

    //-------------------------------------------------
    // Attempting to open another window with the Grapes.png
    //-------------------------------------------------

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