// Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Due Date May 14.

using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main(){

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Writing the real code for the project here.
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Opens a window the size of (800, 600).
    sf::RenderWindow Game(sf::VideoMode({ 800, 600 }), "Main Menu");
    

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Fonts
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::Font font("AGENCYR.ttf");
    sf::Font font2("AGENCYB.ttf");


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Text Objects
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::Text QuitText(font2);
    QuitText.setString("Quit");

    sf::Text FullScreenText(font);
    FullScreenText.setString("Full Screen");

    sf::Text VolumeText(font); 

    sf::Text TestSoundText(font);
    TestSoundText.setString("TestSound");

    sf::Text MusicVolumeText(font);

    sf::Text PuzzleText(font);
    PuzzleText.setString("Puzzle Piece");

    sf::Text OptionsText(font);
    OptionsText.setString("Options");

    sf::Text PlayText(font);
    PlayText.setString("Play");

    sf::Text ReturnText(font);
    ReturnText.setString("Return");

    sf::Text MainMenuText(font);
    MainMenuText.setString("Main Menu");

    sf::Text WindowModeText(font);
    WindowModeText.setString("Window Mode:");
    
    sf::Text WindowText(font);
    WindowText.setString("Window");

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Sprite Objects
    //------------------------------------------------------------------------------------------------------------------------------------------
    //sf::Texture GrapeTexture("Grapes.png");
    //sf::Sprite Grape(GrapeTexture);
    //Grape.setColor(sf::Color::Blue);

    // Sprite and texture.
    sf::Texture SpeakerTexture("Speaker.png");
    sf::Sprite Speaker(SpeakerTexture);
    Speaker.setColor(sf::Color::White);
    Speaker.setScale({ 0.25, 0.25 });

    // Music Sprite and texture.
    sf::Texture MusicTexture("TrebleClefBlack.png");
    sf::Sprite MusicSymbol(MusicTexture);
    MusicSymbol.setColor(sf::Color::White);
    MusicSymbol.setScale({ 0.25, 0.25 });

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Buttons
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::RectangleShape QuitButton(QuitText.getGlobalBounds().size); // Quit button
    sf::RectangleShape FullScreenButton(FullScreenText.getGlobalBounds().size); //Fullscreen
    sf::RectangleShape SoundBar({ 300, 20 }); //SoundBar is 300 pixel long.
    sf::RectangleShape SoundBar2({ 300, 20 });
    sf::RectangleShape TestSoundButton(TestSoundText.getGlobalBounds().size);
    sf::RectangleShape MusicBar({ 300,20 });
    sf::RectangleShape MusicBar2(MusicBar.getSize());
    sf::RectangleShape OptionsButton(OptionsText.getGlobalBounds().size);
    sf::RectangleShape PlayButton(PlayText.getGlobalBounds().size);
    sf::RectangleShape ReturnButton(ReturnText.getGlobalBounds().size);
    sf::RectangleShape MainMenuButton(MainMenuText.getGlobalBounds().size);
    sf::RectangleShape WindowModeButton(WindowModeText.getGlobalBounds().size);
    sf::CircleShape TriangleUp(20.f, 3);
    sf::CircleShape TriangleDown(20.f, 3);
    
    TriangleDown.setOrigin({TriangleDown.getRadius(),TriangleDown.getRadius()});
    TriangleDown.rotate(sf::degrees(180));


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Puzzle Piece
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::RectangleShape Puzzle(PuzzleText.getGlobalBounds().size);
    Puzzle.setOrigin({ Puzzle.getSize().x / 2, Puzzle.getSize().y / 2 });
    Puzzle.setPosition({ 300, 400 });


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Sound bars and shapes
    //------------------------------------------------------------------------------------------------------------------------------------------
    //SoundBar
    SoundBar.setFillColor(sf::Color::Green);
    SoundBar2.setFillColor(sf::Color::White);

    //MusicBar
    MusicBar.setFillColor(sf::Color::Green);
    MusicBar2.setFillColor(sf::Color::White);

    sf::CircleShape SoundCircle(10, 20); //SoundBar cursor
    sf::CircleShape SoundCircle2(10, 20); //MusicBar cursor


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Sounds
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::SoundBuffer buffer("Windows Background.wav");
    sf::Sound sound(buffer);
    

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Music
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Music by <a href="https://pixabay.com/users/kimurasukuru-25042105/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=336601">kimurasukuru</a> from <a href="https://pixabay.com/music//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=336601">Pixabay</a>
    sf::Music music("city-bgm-336601.mp3");
    music.play();
    music.setLooping(true);


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Angles
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::Angle NorthAngle = sf::degrees(0);
    sf::Angle EastAngle = sf::degrees(90);
    sf::Angle SouthAngle = sf::degrees(180);
    sf::Angle WestAngle = sf::degrees(270);


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Windows types and screens
    //------------------------------------------------------------------------------------------------------------------------------------------    
    bool isMainMenu = true; // Screen = 0
    bool isOptions = false; // Screen = 1
    bool isPlay = false; // Screen = 2

    int Screen = 0;

    // Get the Previous screen value for the returnButton.
    int PreviousScreen = Screen;

    sf::Text PreviousText(font);

    // Run the program as long as the game window is open.
    while (Game.isOpen()) {
        // Volumes of both sound and music. (also convert the float into int)
        int Volume = (int)SoundBar.getSize().x / 3;
        int MusicVolume = (int)MusicBar.getSize().x / 3;

        // Finding the Game window size.
        sf::Vector2u WindowSize = Game.getSize();
        int WindowX = WindowSize.x;
        int WindowY = WindowSize.y;

        // Finding the center of the Game window.
        float CenterX = WindowX / 2;
        float CenterY = WindowY / 2;

        // Get the local mouse position (relative to the Game window).
        sf::Vector2i localPosition = sf::Mouse::getPosition(Game);

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Press button only when it is the Main Menu.
        //------------------------------------------------------------------------------------------------------------------------------------------ 
        if (isMainMenu) {
            Screen = 0;

            // PlayButton Changes to red when mouse hover.
            if (PlayButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                PlayButton.setFillColor(sf::Color::Red);

                // Left click to change window to Play window.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    isMainMenu = false;
                    isOptions = false;
                    isPlay = true;
                    Game.create(sf::VideoMode(Game.getSize()), "Play");
                    PreviousScreen = Screen;
                }
            }
            else {
                PlayButton.setFillColor(sf::Color::Blue);
            }

            // OptionsButton Changes to red when mouse hover.
            if (OptionsButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                OptionsButton.setFillColor(sf::Color::Red);

                // Left click changes window to Options window.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    isMainMenu = false;
                    isOptions = true;
                    isPlay = false;
                    Game.create(sf::VideoMode(Game.getSize()), "Options");
                    PreviousScreen = Screen;
                }
            }
            else {
                OptionsButton.setFillColor(sf::Color::Blue);
            }

            // Quit Button Changes to red when mouse hover.
            if (QuitButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                QuitButton.setFillColor(sf::Color::Red);

                // Left click to quit Game window.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                    // Add GameSave code here...

                    Game.close();
                }
            }
            else {
                QuitButton.setFillColor(sf::Color::Blue);
            }
        }

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Press button only when it is Play.
        //------------------------------------------------------------------------------------------------------------------------------------------ 
        if (isPlay) {
            Screen = 2;

            // Puzzle Changes to red when mouse hover.
            if (Puzzle.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true && isPlay) {
                Puzzle.setFillColor(sf::Color::Red);

                // Left click and move to drag the puzzle piece.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                   
                    Puzzle.setPosition({ (float)localPosition.x , (float)localPosition.y });

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

                // Left click changes window to Options window.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    isMainMenu = false;
                    isOptions = true;
                    isPlay = false;
                    Game.create(sf::VideoMode(Game.getSize()), "Options");
                    PreviousScreen = Screen;
                }
            }
            else {
                OptionsButton.setFillColor(sf::Color::Blue);
            }

            // ReturnButton Button Changes to red when mouse hover.
            if (ReturnButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                ReturnButton.setFillColor(sf::Color::Red);

                // Left click to activate ReturnButton.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (PreviousScreen == 0) {
                        Game.create(sf::VideoMode(Game.getSize()), "Main Menu");
                        isMainMenu = true;
                        isOptions = false;
                        isPlay = false;
                        PreviousScreen = Screen;
                    }

                    if (PreviousScreen == 2) {
                        Game.create(sf::VideoMode(Game.getSize()), "Play");
                        isMainMenu = false;
                        isOptions = false;
                        isPlay = true;
                        PreviousScreen = Screen;
                    }
                }
            }
            else {
                ReturnButton.setFillColor(sf::Color::Blue);
            }

            // MainMenuButton Changes to red when mouse hover.
            if (MainMenuButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                MainMenuButton.setFillColor(sf::Color::Red);

                // Left click to play test sound.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        Game.create(sf::VideoMode(Game.getSize()), "Main Menu");
                        isMainMenu = true;
                        isOptions = false;
                        isPlay = false;
                }
            }
            else {
                MainMenuButton.setFillColor(sf::Color::Blue);
            }

        }

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Press button only when it is the Options.
        //------------------------------------------------------------------------------------------------------------------------------------------ 
        if (isOptions) {
            Screen = 1;

            // FullScreen Button Changes to red when mouse hover.
            if (FullScreenButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                FullScreenButton.setFillColor(sf::Color::Red);

                // Left click to activate FullScreenMode.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode::getFullscreenModes()[0], "Main Menu", sf::Style::None, sf::State::Fullscreen);
                }
            }
            else {
                FullScreenButton.setFillColor(sf::Color::Blue);
            }

            //I have to use the SoundBar2 for the global bounds, since SoundBar changes.
            if (SoundBar2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                SoundCircle.setPosition({ (float)localPosition.x - 10, SoundBar.getPosition().y });
                SoundCircle.setFillColor(sf::Color::White);
                Game.draw(SoundCircle);

                // Left click to adjust volume.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                    // Stop sound circle from going below the SoundBar position x.
                    if (SoundCircle.getPosition().x < SoundBar.getPosition().x)
                        SoundCircle.setPosition(SoundBar.getPosition());

                    // Changes the SoundBar based on the position of the Mouse.
                    SoundBar.setSize({ (localPosition.x - SoundBar.getPosition().x), SoundBar.getSize().y });

                    // Set the volume of sound.
                    sound.setVolume(Volume);
                }
            }
            else {
                SoundBar.setFillColor(sf::Color::Green);
                SoundCircle.setFillColor(sf::Color::Green);
            }

            // TestSound Button Changes to red when mouse hover.
            if (TestSoundButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                TestSoundButton.setFillColor(sf::Color::Red);

                // Left click to play test sound.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sound.play();
                }
            }
            else {
                TestSoundButton.setFillColor(sf::Color::Blue);
            }

            // MusicBar (Same thing as the SoundBar, but this one control the volume of the music).
            if (MusicBar2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                SoundCircle2.setPosition({ (float)localPosition.x - 10, MusicBar2.getPosition().y });
                SoundCircle2.setFillColor(sf::Color::White);
                Game.draw(SoundCircle2);

                // Left click to adjust volume.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                    //Stop sound circle from going below the SoundBar position x.
                    if (SoundCircle2.getPosition().x < MusicBar.getPosition().x)
                        SoundCircle2.setPosition(MusicBar.getPosition());

                    // Changes the MusicBar based on the position of the Mouse. 
                    MusicBar.setSize({ (localPosition.x - MusicBar.getPosition().x), MusicBar.getSize().y });

                    // Set the volume of music.
                    music.setVolume(MusicVolume);
                }

            }
            else {
                MusicBar.setFillColor(sf::Color::Green);
                SoundCircle2.setFillColor(sf::Color::Green);
            }

            // ReturnButton Button Changes to red when mouse hover.
            if (ReturnButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                ReturnButton.setFillColor(sf::Color::Red);

                // Left click to activate ReturnButton.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (PreviousScreen == 0) {
                        Game.create(sf::VideoMode(Game.getSize()), "Main Menu");
                        isMainMenu = true;
                        isOptions = false;
                        isPlay = false;
                        PreviousScreen = Screen;
                    }

                    if (PreviousScreen == 2) {
                        Game.create(sf::VideoMode(Game.getSize()), "Play");
                        isMainMenu = false;
                        isOptions = false;
                        isPlay = true;
                        PreviousScreen = Screen;
                    }
                }
            }
            else {
                ReturnButton.setFillColor(sf::Color::Blue);
            }

            // WindowModeButton Changes to red when mouse hover.
            if (WindowModeButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                WindowModeButton.setFillColor(sf::Color::Red);

                // Left click to activate FullScreenMode.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    //Game.create(sf::VideoMode::getFullscreenModes()[0], "Main Menu", sf::Style::None, sf::State::Fullscreen);
                }
            }
            else {
                WindowModeButton.setFillColor(sf::Color::Blue);
            }
        }


        // Check all the window's events that were triggered since the last iteration of the loop.
        while (const std::optional event = Game.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {

                // Add GameSave code here...

                Game.close();
            }
        }

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Positions of Main menu objects.
        //------------------------------------------------------------------------------------------------------------------------------------------
        PlayButton.setPosition({ OptionsButton.getPosition().x, OptionsButton.getPosition().y - 50 });
        PlayText.setPosition(PlayButton.getPosition());

        OptionsButton.setPosition({ QuitButton.getPosition().x, QuitButton.getPosition().y - 50 });
        OptionsText.setPosition(OptionsButton.getPosition());

        QuitButton.setPosition({ CenterX, CenterY });
        QuitText.setPosition({ CenterX, CenterY });


        //------------------------------------------------------------------------------------------------------------------------------------------
        // Positions of Play objects.
        //------------------------------------------------------------------------------------------------------------------------------------------ 
        // Position of puzzle pieces
        PuzzleText.setPosition(Puzzle.getPosition());
        PuzzleText.setRotation(Puzzle.getRotation());
        PuzzleText.setOrigin(Puzzle.getOrigin());

        MainMenuText.setPosition({ 0, 0 });
        MainMenuButton.setPosition(MainMenuText.getPosition());

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Positions of Options objects.
        //------------------------------------------------------------------------------------------------------------------------------------------
        // Transform change the position of Object2 relative to Object1
        sf::Transform transform = Speaker.getTransform();
        sf::Transform transform2 = MusicSymbol.getTransform();
        sf::Transform transform3 = WindowModeButton.getTransform();

        // Relative position of the objects. From Object1 to Object2.
        sf::Vector2f relativePosition(300, 90);
        sf::Vector2f relativePosition2(150, 0);

        // Apply the transformation to the relative position.
        sf::Vector2f transformedPosition = transform.transformPoint(relativePosition);
        sf::Vector2f transformedPosition2 = transform2.transformPoint(relativePosition);
        sf::Vector2f transformedPosition3 = transform3.transformPoint(relativePosition2);

        // Move Object2 relative to Object1.
        SoundBar2.setPosition(transformedPosition);
        SoundBar.setPosition(transformedPosition);
        MusicBar.setPosition(transformedPosition2);
        MusicBar2.setPosition(transformedPosition2);
        WindowText.setPosition(transformedPosition3);

        // Positions of SoundBar and Volume
        VolumeText.setPosition({ SoundBar.getPosition().x, SoundBar.getPosition().y - 50 });
        Speaker.setPosition({ CenterX - 200, CenterY - 100 });

        // Positions of MusicBar and Volume
        MusicVolumeText.setPosition({ MusicBar.getPosition().x, MusicBar.getPosition().y - 50 });
        MusicSymbol.setPosition({ Speaker.getPosition().x, Speaker.getPosition().y - 100 });

        //Convert Volume and MusicVolume into string.
        string VolumeString = to_string(Volume);
        VolumeText.setString(VolumeString);

        string MusicVolumeString = to_string(MusicVolume);
        MusicVolumeText.setString(MusicVolumeString);

        //FullScreen does not have a position, because it is position to the origin (top left) by default.

        // Positions of the TestSound.
        TestSoundText.setPosition({ FullScreenText.getPosition().x, FullScreenText.getPosition().y + 50 });
        TestSoundButton.setPosition(TestSoundText.getPosition());

        WindowModeText.setPosition({ 100,300 });
        WindowModeButton.setPosition(WindowModeText.getPosition());
        
        if (isOptions) {
            ReturnText.setPosition({ CenterX, CenterY + 30});
            ReturnButton.setPosition(ReturnText.getPosition());
        }
        
        if (isPlay) {
            ReturnText.setPosition({ 0,0 });
            ReturnButton.setPosition(ReturnText.getPosition());

            OptionsText.setPosition({ 0, 50 });
            OptionsButton.setPosition(OptionsText.getPosition());
        }

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Drawing/Displaying the objects onto the Game Window.
        //------------------------------------------------------------------------------------------------------------------------------------------
        PlayButton.setPosition({ OptionsButton.getPosition().x, OptionsButton.getPosition().y - 50 });
        PlayText.setPosition(PlayButton.getPosition());

        if (isMainMenu) {
            OptionsButton.setPosition({ QuitButton.getPosition().x, QuitButton.getPosition().y - 50 });
            OptionsText.setPosition(OptionsButton.getPosition());
        }

        QuitButton.setPosition({ CenterX, CenterY });
        QuitText.setPosition({ CenterX, CenterY });
        
        //PreviousText.setString(to_string(PreviousScreen));
        //PreviousText.setPosition({ 300, 300 });

        TriangleUp.setPosition({ 100, CenterY });
        TriangleDown.setPosition({ 100, CenterY + 50 });

        //Order matters when drawing objects.
        Game.clear();

        Game.draw(TriangleUp);
        Game.draw(TriangleDown);

        if (isMainMenu) {
            Game.draw(QuitButton);
            Game.draw(QuitText);
            Game.draw(OptionsButton);
            Game.draw(OptionsText);
            Game.draw(PlayButton);
            Game.draw(PlayText);
            //Game.draw(Grape);
        }

        if (isOptions) {
            Game.draw(FullScreenButton);
            Game.draw(FullScreenText);
            Game.draw(Speaker);
            Game.draw(SoundBar2);
            Game.draw(SoundBar);
            Game.draw(VolumeText);
            Game.draw(SoundCircle);
            Game.draw(TestSoundButton);
            Game.draw(TestSoundText);
            Game.draw(MusicSymbol);
            Game.draw(MusicBar2);
            Game.draw(MusicBar);
            Game.draw(MusicVolumeText);
            Game.draw(SoundCircle2);
            Game.draw(ReturnButton);
            Game.draw(ReturnText);
            Game.draw(WindowModeButton);
            Game.draw(WindowModeText);
            Game.draw(WindowText);
        }

        if (isPlay) {
            Game.draw(Puzzle);
            Game.draw(PuzzleText);
            Game.draw(OptionsButton);
            Game.draw(OptionsText);
            Game.draw(MainMenuButton);
            Game.draw(MainMenuText);
        }
        Game.display();  
    }
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

