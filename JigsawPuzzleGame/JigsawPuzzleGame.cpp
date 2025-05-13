// Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Due Date May 14.

using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main(){

    /*

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

    
    //sf::Clock clock;
    //while (window.isOpen())
    //{
    //    sf::Time elapsed = clock.restart();
    //    updateGame(elapsed);
    //    ...
    //}

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
    sf::Sprite sprite(texture2);

    sf::Font font("AGENCYR.ttf");
    //sf::Font font;
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
            sprite.setPosition({ 500.f, 50.f }); // absolute position
            //sprite.move({ 10.f, 10.f }); // offset relative to the current position

            // rotation
            sprite.setRotation(sf::degrees(90)); // absolute angle
            //sprite.rotate(sf::degrees(14)); // offset relative to the current angle

            // scale
            sprite.setScale({ 2.5f, 2.f }); // absolute scale factor
            sprite.scale({ 1.5f, 1.25f }); // factor relative to the current scale
            //sprite.setOrigin({ 30.f, 30.f });
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
    
    */

    //-------------------------------------------------
    // Writing the real code for the project here.
    //-------------------------------------------------


    //Opens a window the size of (1000, 600).
    //sf::RenderWindow MainMenu(sf::VideoMode::getFullscreenModes()[0], "Main Menu", sf::Style::None, sf::State::Fullscreen);
    sf::RenderWindow MainMenu(sf::VideoMode({ 1000, 600 }), "Main Menu");
    
    //Fonts
    sf::Font font("AGENCYR.ttf");
    sf::Font font2("AGENCYB.ttf");

    //Texts
    sf::Text QuitText(font2);
    QuitText.setString("Quit");

    sf::Text FullScreenText(font);
    FullScreenText.setString("Full Screen");

    sf::Text VolumeText(font); // The setString is in the window.

    sf::Text TestSoundText(font);
    TestSoundText.setString("TestSound");

    sf::Text MusicVolumeText(font);

    sf::Text PuzzleText(font);
    PuzzleText.setString("Puzzle Piece");

    sf::Text OptionsText(font);
    OptionsText.setString("Options");

    //sf::Texture GrapeTexture("Grapes.png");
    //sf::Sprite Grape(GrapeTexture);
    //Grape.setColor(sf::Color::Blue);

    //Speaker Sprite and texture.
    sf::Texture SpeakerTexture("Speaker.png");
    sf::Sprite Speaker(SpeakerTexture);
    Speaker.setColor(sf::Color::White);
    Speaker.setScale({ 0.25, 0.25 });

    //Music Sprite and texture.
    sf::Texture MusicTexture("TrebleClefBlack.png");
    sf::Sprite Music(MusicTexture);
    Music.setColor(sf::Color::White);
    Music.setScale({ 0.25, 0.25 });


    //Buttons
    //sf::RectangleShape QuitButton({ 45.f,35.f }); // Quit button
    sf::RectangleShape QuitButton(QuitText.getGlobalBounds().size); // Quit button
    sf::RectangleShape FullScreenButton(FullScreenText.getGlobalBounds().size); //Fullscreen
    sf::RectangleShape SoundBar({ 300, 20 }); //SoundBar is 300 pixel long.
    sf::RectangleShape SoundBar2({ 300, 20 });
    sf::RectangleShape TestSoundButton(TestSoundText.getGlobalBounds().size);
    sf::RectangleShape MusicBar({ 300,20 });
    sf::RectangleShape MusicBar2(MusicBar.getSize());
    sf::RectangleShape OptionsButton(OptionsText.getGlobalBounds().size);

    //Puzzle Piece
    sf::RectangleShape Puzzle(PuzzleText.getGlobalBounds().size);
    Puzzle.setPosition({ 300, 400 });

    //SoundBar
    SoundBar.setFillColor(sf::Color::Green);
    SoundBar2.setFillColor(sf::Color::White);

    //MusicBar
    MusicBar.setFillColor(sf::Color::Green);
    MusicBar2.setFillColor(sf::Color::White);

    sf::CircleShape SoundCircle(10, 20); //SoundBar cursor
    sf::CircleShape SoundCircle2(10, 20); //MusicBar cursor

    //Sounds
    sf::SoundBuffer buffer("Windows Background.wav");
    sf::Sound sound(buffer);
    
    //Musics
    //Music by <a href="https://pixabay.com/users/kimurasukuru-25042105/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=336601">kimurasukuru</a> from <a href="https://pixabay.com/music//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=336601">Pixabay</a>
    sf::Music music("city-bgm-336601.mp3");
    music.play();
    music.setLooping(true);

    //Creating the 4 default angles
    sf::Angle NorthAngle = sf::degrees(0);
    sf::Angle EastAngle = sf::degrees(90);
    sf::Angle SouthAngle = sf::degrees(180);
    sf::Angle WestAngle = sf::degrees(270);

        // run the program as long as the window is open
    while (MainMenu.isOpen()) {

        

        sf::Vector2u WindowSize = MainMenu.getSize();
        int WindowX = WindowSize.x;
        int WindowY = WindowSize.y;

        float CenterX = WindowX / 2;
        float CenterY = WindowY / 2;


        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(MainMenu); // window is a sf::Window


        // Quit Button Changes to red when mouse hover.
        if (QuitButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
            QuitButton.setFillColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                // left mouse button is pressed on top of quit button then close menu.
                MainMenu.close();
            }
        }
        else {
            QuitButton.setFillColor(sf::Color::Blue);
        }



        // Puzzle Changes to red when mouse hover.
        if (Puzzle.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
            Puzzle.setFillColor(sf::Color::Red);

            // left mouse button is pressed drag the puzzle piece
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                //Pick up the center piece of the puzzle, and drag them to a new position
                if (Puzzle.getRotation() == NorthAngle) {
                    Puzzle.setPosition({ (float)localPosition.x - Puzzle.getSize().x / 2, (float)localPosition.y - Puzzle.getSize().y / 2 });
                }

                if (Puzzle.getRotation() == WestAngle) {
                    Puzzle.setPosition({ (float)localPosition.x - Puzzle.getSize().y / 2, (float)localPosition.y + Puzzle.getSize().x / 2 });
                }

                if (Puzzle.getRotation() == SouthAngle) {
                    Puzzle.setPosition({ (float)localPosition.x + Puzzle.getSize().x / 2, (float)localPosition.y + Puzzle.getSize().y / 2 });
                }

                if (Puzzle.getRotation() == EastAngle) {
                    Puzzle.setPosition({ (float)localPosition.x + Puzzle.getSize().y / 2, (float)localPosition.y - Puzzle.getSize().x / 2 });
                }


                //Change the rotation of the Puzzle piece.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                   Puzzle.setRotation(WestAngle);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    Puzzle.setRotation(NorthAngle);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                    Puzzle.setRotation(SouthAngle);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    Puzzle.setRotation(EastAngle);
                }


            }
        }
        else {
            Puzzle.setFillColor(sf::Color::Blue);
        }

        // OptionsButton Changes to red when mouse hover.
        if (OptionsButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
            OptionsButton.setFillColor(sf::Color::Red);

            // left mouse button is pressed on top of FullScreen button then close menu.
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                
                //MainMenu.close();
                //MainMenu.create(sf::VideoMode(MainMenu.getSize()), "Options");


                sf::RenderWindow Options(sf::VideoMode({800, 600}), "Options");

                while (Options.isOpen()) {
                    
                    int Volume = (int)SoundBar.getSize().x / 3; // Convert the float into an int, then that int into a string.
                    int MusicVolume = (int)MusicBar.getSize().x / 3;

                    sf::Vector2i localPosition = sf::Mouse::getPosition(Options); // window is a sf::Window

                    // check all the window's events that were triggered since the last iteration of the loop
                    while (const std::optional event = Options.pollEvent()) {
                        // "close requested" event: we close the window
                        if (event->is<sf::Event::Closed>())
                            Options.close();
                    }

                    // FullScreen Button Changes to red when mouse hover.
                    if (FullScreenButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                        FullScreenButton.setFillColor(sf::Color::Red);

                        // left mouse button is pressed on top of FullScreen button then close menu.
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            MainMenu.create(sf::VideoMode::getFullscreenModes()[0], "Main Menu", sf::Style::None, sf::State::Fullscreen);
                        }
                    }
                    else {
                        FullScreenButton.setFillColor(sf::Color::Blue);
                    }

                    // SoundBar  Changes to red when mouse hover ove the global bounds of SoundBar2.
                    //I have to use the SoundBar2 for the global bounds, since SoundBar changes.
                    if (SoundBar2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                        //SoundBar.setFillColor(sf::Color::Red);
                        SoundCircle.setPosition({ (float)localPosition.x - 10, SoundBar.getPosition().y });
                        SoundCircle.setFillColor(sf::Color::White);
                        MainMenu.draw(SoundCircle);

                        // left mouse button is pressed on SoundCircle to adjust volume.
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                            //Stop sound circle from going below the SoundBar position x.
                            if (SoundCircle.getPosition().x < SoundBar.getPosition().x)
                                SoundCircle.setPosition(SoundBar.getPosition());
                            SoundBar.setSize({ (localPosition.x - SoundBar.getPosition().x), SoundBar.getSize().y });
                        }

                    }
                    else {
                        SoundBar.setFillColor(sf::Color::Green);
                        SoundCircle.setFillColor(sf::Color::Green);
                    }

                    // TestSound Button Changes to red when mouse hover.
                    if (TestSoundButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                        TestSoundButton.setFillColor(sf::Color::Red);

                        // left mouse button is pressed on top of FullScreen button then close menu.
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            sound.setVolume(Volume);
                            sound.play();
                        }
                    }
                    else {
                        TestSoundButton.setFillColor(sf::Color::Blue);
                    }

                    // MusicBar (Same thing as the SoundBar, but this one control the volume of the music).
                    if (MusicBar2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                        //MusicBar.setFillColor(sf::Color::Red);
                        SoundCircle2.setPosition({ (float)localPosition.x - 10, MusicBar2.getPosition().y });
                        SoundCircle2.setFillColor(sf::Color::White);
                        MainMenu.draw(SoundCircle2);

                        // left mouse button is pressed on SoundCircle2 to adjust volume.
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                            //Stop sound circle from going below the SoundBar position x.
                            if (SoundCircle2.getPosition().x < MusicBar.getPosition().x)
                                SoundCircle2.setPosition(MusicBar.getPosition());

                            MusicBar.setSize({ (localPosition.x - MusicBar.getPosition().x), MusicBar.getSize().y });
                            music.setVolume(MusicVolume);
                        }

                    }
                    else {
                        MusicBar.setFillColor(sf::Color::Green);
                        SoundCircle2.setFillColor(sf::Color::Green);
                    }


                    //Position of the Text,Buttons, and Sprites.
                    sf::Transform transform = Speaker.getTransform();
                    sf::Transform transform2 = Music.getTransform();


                    // 2. Define the relative position
                    sf::Vector2f relativePosition(300, 90);
                    sf::Vector2f relativePosition2(0, 0);

                    // 3. Apply the transformation to the relative position
                    sf::Vector2f transformedPosition = transform.transformPoint(relativePosition);
                    sf::Vector2f transformedPosition2 = transform2.transformPoint(relativePosition);

                    // 4. Move sprite1 to the transformed position
                    SoundBar2.setPosition(transformedPosition);
                    SoundBar.setPosition(transformedPosition);

                    VolumeText.setPosition({ SoundBar.getPosition().x, SoundBar.getPosition().y - 50 });
                    Speaker.setPosition({ CenterX - 200, CenterY - 100 });



                    TestSoundText.setPosition({ FullScreenText.getPosition().x, FullScreenText.getPosition().y + 50 });
                    TestSoundButton.setPosition(TestSoundText.getPosition());

                    string VolumeString = to_string(Volume);
                    VolumeText.setString(VolumeString);

                    MusicVolumeText.setPosition({ MusicBar.getPosition().x, MusicBar.getPosition().y - 50 });
                    Music.setPosition({ Speaker.getPosition().x, Speaker.getPosition().y - 100 });
                    MusicBar.setPosition(transformedPosition2);
                    MusicBar2.setPosition(MusicBar.getPosition());

                    string MusicVolumeString = to_string(MusicVolume);
                    MusicVolumeText.setString(MusicVolumeString);

                    Options.clear();
                    Options.draw(FullScreenButton);
                    Options.draw(FullScreenText);
                    Options.draw(Speaker);
                    Options.draw(SoundBar2);
                    Options.draw(SoundBar);
                    Options.draw(VolumeText);
                    Options.draw(SoundCircle);
                    Options.draw(TestSoundButton);
                    Options.draw(TestSoundText);
                    Options.draw(Music);
                    Options.draw(MusicBar2);
                    Options.draw(MusicBar);
                    Options.draw(MusicVolumeText);
                    Options.draw(SoundCircle2);
                    Options.display();
                }

            }
        }
        else {
            OptionsButton.setFillColor(sf::Color::Blue);
        }

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = MainMenu.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                MainMenu.close();
        }





        PuzzleText.setPosition(Puzzle.getPosition());
        PuzzleText.setRotation(Puzzle.getRotation());


        QuitButton.setPosition({ CenterX, CenterY });
        QuitText.setPosition({ CenterX, CenterY });
        
        OptionsButton.setPosition({ QuitButton.getPosition().x, QuitButton.getPosition().y - 50 });
        OptionsText.setPosition(OptionsButton.getPosition());


        //Order matters when drawing objects.
        MainMenu.clear();
        MainMenu.draw(QuitButton);
        MainMenu.draw(QuitText);
        MainMenu.draw(Puzzle);
        MainMenu.draw(PuzzleText);
        MainMenu.draw(OptionsButton);
        MainMenu.draw(OptionsText);
        //MainMenu.draw(Grape);
        MainMenu.display();

        
    }
    music.stop();


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

