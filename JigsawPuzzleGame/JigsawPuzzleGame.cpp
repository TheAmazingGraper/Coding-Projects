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

    sf::Text ResolutionModeText(font);
    ResolutionModeText.setString("Resolution Modes:");

    sf::Text Text800x600(font);
    Text800x600.setString("800x600");

    sf::Text Text1280x720(font);
    Text1280x720.setString("1280x720");

    sf::Text Text1920x1080(font);
    Text1920x1080.setString("1920x1080");

    sf::Text FullScreenText(font);
    FullScreenText.setString("Full Screen");

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
    sf::RectangleShape ResolutionModeButton(ResolutionModeText.getGlobalBounds().size);
    sf::CircleShape WindowModeUp(20.f, 3);
    sf::CircleShape WindowModeDown(20.f, 3);
    sf::RectangleShape Text800x600Button(Text800x600.getGlobalBounds().size);
    sf::RectangleShape Text1280x720Button(Text1280x720.getGlobalBounds().size);
    sf::RectangleShape Text1920x1080Button(Text1920x1080.getGlobalBounds().size);

    WindowModeUp.setOrigin({ WindowModeUp.getRadius(), WindowModeUp.getRadius() });
    WindowModeDown.setOrigin({ WindowModeDown.getRadius(),WindowModeDown.getRadius()});
    WindowModeDown.rotate(sf::degrees(180));

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Puzzle Piece
    //------------------------------------------------------------------------------------------------------------------------------------------
    sf::RectangleShape Puzzle(PuzzleText.getGlobalBounds().size);
    Puzzle.setOrigin({ Puzzle.getSize().x / 2, Puzzle.getSize().y / 2 });
    Puzzle.setPosition({ 300, 400 });

    sf::CircleShape Puzzle2(20.f, 3);
    Puzzle2.setOrigin({ Puzzle2.getRadius(), Puzzle2.getRadius() });
    Puzzle2.setPosition({ 200, 200 });
    
    //sf::RectangleShape Puzzle2Button(Puzzle2.getGlobalBounds().size);
    sf::CircleShape Puzzle2Button(Puzzle2);

    sf::CircleShape Puzzle3(15.f);
    Puzzle3.setOrigin({ Puzzle3.getRadius(), Puzzle3.getRadius() });
    Puzzle3.setPosition({ 300, 300 });

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
    bool isFullScreen = false;

    int Screen = 0;

    int ResolutionModes = 0;
    //800x600:       ResolutionModes = 0
    //1280x720:      ResolutionModes = 1
    //1920x1080:     ResolutionModes = 2
    //FullScreen:    ResolutionModes = 3
    
    // Get the Previous screen value for the returnButton.
    int PreviousScreen = Screen;

    // Single Mouse click
    bool click = true;

    // Holding a puzzle piece 
    bool HoldingPuzzle = false;
    bool HoldingPuzzle2 = false;
    bool HoldingPuzzle3 = false;
    int HoldingPuzzlesPieces = 0;

    sf::Text HoldingPuzzleText(font);
    sf::Text HoldingPuzzleText2(font);
    sf::Text HoldingPuzzleText3(font);



    // Run the program as long as the game window is open.
    while (Game.isOpen()) {

        HoldingPuzzlesPieces = HoldingPuzzle + HoldingPuzzle2 + HoldingPuzzle3;



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
    ;

            // PlayButton Changes to red when mouse hover.
            if (PlayButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (OptionsButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (QuitButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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

            HoldingPuzzle = false;
            HoldingPuzzle2 = false;
            HoldingPuzzle3 = false;



         /*
            if (Puzzle.getPosition().y > 600)
                Puzzle.setPosition({ Puzzle.getPosition().x, 0 });

            if (Puzzle.getGlobalBounds().contains(Puzzle2.getGlobalBounds().position)) {
                
                while (Puzzle.getGlobalBounds().contains(Puzzle2.getGlobalBounds().position)) {
                    Puzzle.move({ 0,1 });
                }
            }else{
               // Puzzle.move({ 0,1 });
            }*/

            // Puzzle Changes to red when mouse hover.
            if (Puzzle.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
                Puzzle.setFillColor(sf::Color::Red);
        
                // Left click and move to drag the puzzle piece.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && click) {
                   

                    HoldingPuzzle = true;

          

                    //if(HoldingPuzzle && !HoldingPuzzle2 && !HoldingPuzzle3)
                    //if(HoldingPuzzle && !HoldingPuzzle2)
                        //if(HoldingPuzzle && !HoldingPuzzle3)
                    //if(HoldingPuzzle && !HoldingPuzzle2 && !HoldingPuzzle3)
                    while (HoldingPuzzle) {

                        if (click) {
                            HoldingPuzzle = false;
                        }
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
            }
            else {
                Puzzle.setFillColor(sf::Color::Blue);
            }

            // Puzzle2 Changes to red when mouse hover.
            if (Puzzle2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
                Puzzle2.setFillColor(sf::Color::Red);

                // Left click and move to drag the puzzle piece.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                    HoldingPuzzle2 = true;



                    //if (HoldingPuzzlesPieces <= 1 )
                    //if(HoldingPuzzle2 && !HoldingPuzzle && !HoldingPuzzle3)
                    //if (HoldingPuzzle2 && !HoldingPuzzle)
                        //if (HoldingPuzzle2 && !HoldingPuzzle3)

                    while(HoldingPuzzle2) {
                        if (click) {
                            HoldingPuzzle2 = false;
                        }
                    Puzzle2.setPosition({ (float)localPosition.x , (float)localPosition.y });

                    //Change the rotation of the Puzzle2 piece.
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                        Puzzle2.setRotation(WestAngle);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                        Puzzle2.setRotation(NorthAngle);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                        Puzzle2.setRotation(SouthAngle);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                        Puzzle2.setRotation(EastAngle);
                    }
                }
                }
            }
            else {
                Puzzle2.setFillColor(sf::Color::Blue);
            }

            // Puzzle3 Changes to red when mouse hover.
            if (Puzzle3.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
                Puzzle3.setFillColor(sf::Color::Red);

                // Left click and move to drag the puzzle piece.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                    HoldingPuzzle3 = true;

                  


                    //if (HoldingPuzzlesPieces == 1)
                    //if (HoldingPuzzle3 && !HoldingPuzzle && !HoldingPuzzle2)
                        if (HoldingPuzzle3 && !HoldingPuzzle)
                            if (HoldingPuzzle3 && !HoldingPuzzle2)
                        Puzzle3.setPosition({ (float)localPosition.x , (float)localPosition.y });

                    //Change the rotation of the Puzzle2 piece.
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                        Puzzle3.setRotation(WestAngle);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                        Puzzle3.setRotation(NorthAngle);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                        Puzzle3.setRotation(SouthAngle);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                        Puzzle3.setRotation(EastAngle);
                    }
                }
            }
            else {
                Puzzle3.setFillColor(sf::Color::Blue);
            }

            // OptionsButton Changes to red when mouse hover.
            if (OptionsButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (ReturnButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (MainMenuButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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

            // Test800x600Button Changes to red when mouse hover.
            if (Text800x600Button.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) && ResolutionModes % 4 == 0) {
                Text800x600Button.setFillColor(sf::Color::Red);

                // Left click to activate 800x600.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode({800, 600}), "Options", sf::State::Windowed);
                }
            }
            else {
                Text800x600Button.setFillColor(sf::Color::Blue);
            }

            // Text1280x720Button Changes to red when mouse hover.
            if (Text1280x720Button.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) && ResolutionModes % 4 == 1) {
                Text1280x720Button.setFillColor(sf::Color::Red);

                // Left click to activate Text1280x720Button.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode({ 1280, 720 }), "Options", sf::State::Windowed);
                }
            }
            else {
                Text1280x720Button.setFillColor(sf::Color::Blue);
            }

            // Text1920x1080Button Changes to red when mouse hover.
            if (Text1920x1080Button.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })  && ResolutionModes % 4 == 2) {
                Text1920x1080Button.setFillColor(sf::Color::Red);

                // Left click to activate Text1920x1080Button.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode({ 1920, 1080 }), "Options", sf::State::Windowed);
                }
            }
            else {
                Text1920x1080Button.setFillColor(sf::Color::Blue);
            }

            // FullScreenButton Changes to red when mouse hover.
            if (FullScreenButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })  && ResolutionModes % 4 == 3) {
                FullScreenButton.setFillColor(sf::Color::Red);

                // Left click to activate FullScreenMode.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode::getFullscreenModes()[0], "Options", sf::Style::None, sf::State::Fullscreen);
                }
            }
            else {
                FullScreenButton.setFillColor(sf::Color::Blue);
            }

            //I have to use the SoundBar2 for the global bounds, since SoundBar changes.
            if (SoundBar2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (TestSoundButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (MusicBar2.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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
            if (ReturnButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
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

            // WindowModeButton is not a button.
            if (ResolutionModeButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
                //Empty
            }
            else {
                ResolutionModeButton.setFillColor(sf::Color::Blue);
            }

            // WindowModeUp Button Changes to red when mouse hover.
            if (WindowModeUp.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
                WindowModeUp.setFillColor(sf::Color::Red);

                // Left click to activate WindowModeUp.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && click) {
                    ResolutionModes += 1;
                    click = false;
                }
                
            }
            else {
                WindowModeUp.setFillColor(sf::Color::Blue);
            }

            // WindowModeDown Button Changes to red when mouse hover.
            if (WindowModeDown.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y })) {
                WindowModeDown.setFillColor(sf::Color::Red);

                // Left click to activate WindowModeDown.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && click) {
                    ResolutionModes -= 1;
                    click = false;
                }
                
            }
            else {
                WindowModeDown.setFillColor(sf::Color::Blue);
            }
        }


        // Check all the window's events that were triggered since the last iteration of the loop.
        while (const std::optional event = Game.pollEvent()) {

            if (event->is < sf::Event::MouseButtonReleased>()) {
                click = true;
                HoldingPuzzle = false;
                HoldingPuzzle2 = false;
                HoldingPuzzle3 = false;
            }



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

        MainMenuText.setPosition({ 0, 0 });
        MainMenuButton.setPosition(MainMenuText.getPosition());

        // Position of puzzle pieces
        PuzzleText.setPosition(Puzzle.getPosition());
        PuzzleText.setRotation(Puzzle.getRotation());
        PuzzleText.setOrigin(Puzzle.getOrigin());

        Puzzle2Button.setPosition(Puzzle2.getPosition());
        Puzzle2Button.setOrigin(Puzzle2.getOrigin());
        //Puzzle2Button.setRotation(Puzzle2.getRotation());

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Positions of Options objects.
        //------------------------------------------------------------------------------------------------------------------------------------------
        // Transform change the position of Object2 relative to Object1
        sf::Transform transform = Speaker.getTransform();
        sf::Transform transform2 = MusicSymbol.getTransform();
        sf::Transform transform3 = ResolutionModeButton.getTransform();

        // Relative position of the objects. From Object1 to Object2.
        sf::Vector2f relativePosition(300, 90);
        sf::Vector2f relativePosition2(200, 0);

        // Apply the transformation to the relative position.
        sf::Vector2f transformedPosition = transform.transformPoint(relativePosition);
        sf::Vector2f transformedPosition2 = transform2.transformPoint(relativePosition);
        sf::Vector2f transformedPosition3 = transform3.transformPoint(relativePosition2);

        // Move Object2 relative to Object1.
        SoundBar2.setPosition(transformedPosition);
        SoundBar.setPosition(transformedPosition);
        MusicBar.setPosition(transformedPosition2);
        MusicBar2.setPosition(transformedPosition2);
        Text800x600.setPosition(transformedPosition3);
        Text800x600Button.setPosition(transformedPosition3);
        Text1280x720.setPosition(transformedPosition3);
        Text1280x720Button.setPosition(transformedPosition3);
        Text1920x1080.setPosition(transformedPosition3);
        Text1920x1080Button.setPosition(transformedPosition3);
        FullScreenText.setPosition(transformedPosition3);
        FullScreenButton.setPosition(transformedPosition3);

        // Positions of SoundBar and Volume
        // Positions of SoundBar and Volume
        VolumeText.setPosition({ SoundBar.getPosition().x, SoundBar.getPosition().y - 50 });
        Speaker.setPosition({ CenterX - 200, CenterY  });

        // Positions of MusicBar and Volume
        MusicVolumeText.setPosition({ MusicBar.getPosition().x, MusicBar.getPosition().y - 50 });
        MusicSymbol.setPosition({ Speaker.getPosition().x, Speaker.getPosition().y - 100 });

        //Convert Volume and MusicVolume into string.
        string VolumeString = to_string(Volume);
        VolumeText.setString(VolumeString);

        string MusicVolumeString = to_string(MusicVolume);
        MusicVolumeText.setString(MusicVolumeString);

        // Positions of the TestSound is left at default (top left).

        ResolutionModeText.setPosition({ MusicSymbol.getPosition().x, MusicSymbol.getPosition().y - 100});
        ResolutionModeButton.setPosition(ResolutionModeText.getPosition());

        WindowModeUp.setPosition({ ResolutionModeText.getPosition().x + 325, ResolutionModeText.getPosition().y });
        WindowModeDown.setPosition({ ResolutionModeText.getPosition().x + 325, ResolutionModeText.getPosition().y + 40 });
        
        //------------------------------------------------------------------------------------------------------------------------------------------
        // Other windows that share buttons.
        //------------------------------------------------------------------------------------------------------------------------------------------

        if (isOptions) {
            ReturnText.setPosition({ CenterX, CenterY + 100});
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
        HoldingPuzzleText.setString(to_string(HoldingPuzzle));
        HoldingPuzzleText.setPosition({ 0, 100 });

        HoldingPuzzleText2.setString(to_string(HoldingPuzzle2));
        HoldingPuzzleText2.setPosition({ 0, 200 });

        HoldingPuzzleText3.setString(to_string(HoldingPuzzle3));
        HoldingPuzzleText3.setPosition({ 0, 300 });
        //Order matters when drawing objects.
        Game.clear();
        Game.draw(HoldingPuzzleText);
        Game.draw(HoldingPuzzleText2);
        Game.draw(HoldingPuzzleText3);
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
            Game.draw(ResolutionModeButton);
            Game.draw(ResolutionModeText);
            Game.draw(WindowModeUp);
            Game.draw(WindowModeDown);

            if (ResolutionModes % 4 == 0) {
                Game.draw(Text800x600Button);
                Game.draw(Text800x600);
            }

            if (ResolutionModes % 4 == 1) {
                Game.draw(Text1280x720Button);
                Game.draw(Text1280x720);
            }

            if (ResolutionModes % 4 == 2) {
                Game.draw(Text1920x1080Button);
                Game.draw(Text1920x1080);
            }

            if (ResolutionModes % 4 == 3) {
                Game.draw(FullScreenButton);
                Game.draw(FullScreenText);
            }
        }

        if (isPlay) {
            Game.draw(OptionsButton);
            Game.draw(OptionsText);
            Game.draw(MainMenuButton);
            Game.draw(MainMenuText);
            Game.draw(Puzzle);
            Game.draw(PuzzleText);
            Game.draw(Puzzle2Button);
            Game.draw(Puzzle2);
            Game.draw(Puzzle3);
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

