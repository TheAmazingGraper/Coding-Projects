// Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <SFML/Graphics.hpp>

int main()
{
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