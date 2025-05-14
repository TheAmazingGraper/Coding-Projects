// Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Due Date May 14.

using namespace std;

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>


class PuzzlePiece : public sf::Drawable, public sf::Transformable {
public:


    static const std::vector<sf::Vector2i> L;
    static const std::vector<sf::Vector2i> T;
    static const std::vector<sf::Vector2i> plus;
    static const std::vector<sf::Vector2i> minus;

    PuzzlePiece(int num, float blockSize, sf::Color color = sf::Color::Blue)
        : blockSize(blockSize), color(color), shape(getShape(num)) {
       
        // build shape
        for (const auto& coord : *shape) {
            sf::RectangleShape block(sf::Vector2f(blockSize, blockSize)); // building block (small sqaure)
            block.setFillColor(color);
            block.setOrigin(sf::Vector2f(blockSize / 2.f, blockSize / 2.f));
            block.setPosition(sf::Vector2f(static_cast<float>(coord.x) * blockSize, static_cast<float>(coord.y) * blockSize)); // uses our vector notation to offset blocks
            blocks.push_back(block); // adds the block to our vector of rectangle shapes "blocks"
        }
    }

    // allows .setFillColor()
    void setFillColor(const sf::Color& newColor) {
        color = newColor;
        for (auto& block : blocks) {
            block.setFillColor(color); // fills each building block of the shape the new color
        }
    }

    //allows .getGlobalBounds()
    sf::FloatRect getGlobalBounds() const {
        if (blocks.empty()) return {};

        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        float maxY = std::numeric_limits<float>::lowest(); 

        for (const auto& block : blocks) {
            sf::Transform totalTransform = getTransform() * block.getTransform(); 
            sf::FloatRect rect = totalTransform.transformRect(block.getLocalBounds());

            minX = std::min<float>(minX, rect.position.x);
            minY = std::min<float>(minY, rect.position.y);
            maxX = std::max<float>(maxX, rect.position.x + rect.size.x);
            maxY = std::max<float>(maxY, rect.position.y + rect.size.y);
        }

        return sf::FloatRect(sf::Vector2f(minX, minY), sf::Vector2f(maxX - minX, maxY - minY));
    }

    float getBlockSize() const {
        return blockSize;
    }

private:
    std::vector<sf::RectangleShape> blocks;
    float blockSize;                        // set by constructor
    sf::Color color;                        // |
    const std::vector<sf::Vector2i>* shape; // |

    // method to choose puzzle piece
    static const std::vector<sf::Vector2i>* getShape(int num) { 
        switch (num) {
        case 0: return &L;
        case 1: return &T;
        case 2: return &plus;
        case 3: return &minus;
        default: return &L;
        } // needs implementation without switch
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        for (const auto& block : blocks) {
            target.draw(block, states); // draw each block in blocks
        }
    }
};


const std::vector<sf::Vector2i> PuzzlePiece::L = { {0,0}, {1,0}, {1,1} }; // shape 0
const std::vector<sf::Vector2i> PuzzlePiece::T = { {0,0}, {1,0}, {2,0}, {1,1} }; // shape 1
const std::vector<sf::Vector2i> PuzzlePiece::plus = { {0,1}, {1,0}, {1,1}, {2,1}, {1,2} }; // shape 2
const std::vector<sf::Vector2i> PuzzlePiece::minus = { {0,0}, {1,0} }; // shape 3

class Background : public sf::Texture{


    sf::Texture bgTextures[4];
    sf::Texture currentTexture;

public:
    Background() {
        bgTextures[0].loadFromFile("background1.png");
        bgTextures[1].loadFromFile("background2.png");
        bgTextures[2].loadFromFile("background3.png");
        bgTextures[3].loadFromFile("background4.png");

        setBackground(0); // default
    }

    void setBackground(int num) {
		currentTexture = bgTextures[num];
    }

    sf::Texture getBackground() {
       return currentTexture;
    }
};


int main() {

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Writing the real code for the project here.
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Opens a window the size of (800, 600).
    sf::RenderWindow Game(sf::VideoMode({ 800, 600 }), "Main Menu");


    //------------------------------------------------------------------------------------------------------------------------------------------
    // Backgrounds
    //------------------------------------------------------------------------------------------------------------------------------------------
    Background bg;
	bool renderFlag = true; // flag to check if the background needs to be redrawn

    auto backgroundHelper = [&Game, &bg, &renderFlag]() { // lambda function to draw the background
        sf::Texture current = bg.getBackground();
        sf::Sprite bgSprite(current);

        if (renderFlag) { // prevents calc unless screen size has changed
            bgSprite.setScale(sf::Vector2f(float(Game.getSize().x) / current.getSize().x, float(Game.getSize().y) / current.getSize().y));
            renderFlag = false;
        }
        Game.draw(bgSprite);
    };


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
    WindowModeDown.setOrigin({ WindowModeDown.getRadius(),WindowModeDown.getRadius() });
    WindowModeDown.rotate(sf::degrees(180));


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
    // Puzzle Pieces
    //------------------------------------------------------------------------------------------------------------------------------------------
    
    //need to create a piece crafter class
    // craft a puzzle piece: (shape, length of side, color)
    //PuzzlePiece piece(1, (Game.getSize().x/20), sf::Color::Blue); // Shape 1 = T
    //piece.setPosition({ 300, 400 });
    //piece.setRotation(NorthAngle);
    //piece.setOrigin({ piece.getGlobalBounds().size.x/3.f, piece.getGlobalBounds().size.y/2.f});

    //PuzzlePiece piece2(2, (Game.getSize().x / 20), sf::Color::Blue); // Shape 1 = Plus
    //piece2.setPosition({ 400, 400 });
    //piece2.setRotation(NorthAngle);
    //piece2.setOrigin({ piece2.getGlobalBounds().size.x / 2.f, piece2.getGlobalBounds().size.y / 2.f });

    // shape 0 = L
    // shape 1 = T
    // shape 2 = plus
    // shape 3 = minus
    
    std::vector<PuzzlePiece> pieces;
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> xDist(100, 200);
    std::uniform_int_distribution<int> yDist(100, Game.getSize().y);
    std::uniform_int_distribution<int> angleDist(0, 3);

    auto pieceMaker = [&](const std::vector<int>& shapeIds) {
        float blockSize = 30;
        sf::Color color = sf::Color::Blue;

        for (int shapeId : shapeIds) {
            pieces.emplace_back(shapeId, blockSize, color);
            PuzzlePiece& piece = pieces.back();

            piece.setPosition({
                static_cast<float>(xDist(rng)),
                static_cast<float>(yDist(rng))
                });

            sf::FloatRect bounds = piece.getGlobalBounds();
            switch (shapeId) {
            case 0: // L-shape
                piece.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 8.f });
                break;
            case 1: // T-shape // -
                piece.setOrigin({ bounds.size.x / 2.666f, bounds.size.y / 3.f });
                break;
            case 2: // Plus-shape
                piece.setOrigin({ bounds.size.x / 2.6667f, bounds.size.y / 2.6667f });
                break;
            case 3: // minus-shape
                piece.setOrigin({ bounds.size.x / 4.f, bounds.size.y / 8.f});
                break;
            }

            switch (angleDist(rng)) {
            case 0: piece.setRotation(NorthAngle); break;
            case 1: piece.setRotation(EastAngle); break;
            case 2: piece.setRotation(SouthAngle); break;
            case 3: piece.setRotation(WestAngle); break;
            }
        }
        };

    auto drawPieces = [&Game, &pieces]() { // lambda function to draw the background
        for (const auto& piece : pieces) {
            Game.draw(piece);
        }
        };

    pieceMaker({ 0, 1, 2, 3, 0, 1, 2, 3 });


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
            for (auto& piece : pieces) {
                if (piece.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) && isPlay) {
                    piece.setFillColor(sf::Color::Red);

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        piece.setPosition({ (float)localPosition.x, (float)localPosition.y });

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                            piece.setRotation(WestAngle);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                            piece.setRotation(NorthAngle);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                            piece.setRotation(SouthAngle);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                            piece.setRotation(EastAngle);
                        }
                    }
                }
                else {
                    piece.setFillColor(sf::Color::Blue);
                }
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

            // Test800x600Button Changes to red when mouse hover.
            if (Text800x600Button.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true && ResolutionModes % 4 == 0) {
                Text800x600Button.setFillColor(sf::Color::Red);

                // Left click to activate 800x600.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode({ 800, 600 }), "Options", sf::State::Windowed);
					renderFlag = true; // set the flag to true to redraw the background to the correct size
                }
            }
            else {
                Text800x600Button.setFillColor(sf::Color::Blue);
            }

            // Text1280x720Button Changes to red when mouse hover.
            if (Text1280x720Button.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true && ResolutionModes % 4 == 1) {
                Text1280x720Button.setFillColor(sf::Color::Red);

                // Left click to activate Text1280x720Button.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode({ 1280, 720 }), "Options", sf::State::Windowed);
                    renderFlag = true; // set the flag to true to redraw the background to the correct size

                }
            }
            else {
                Text1280x720Button.setFillColor(sf::Color::Blue);
            }

            // Text1920x1080Button Changes to red when mouse hover.
            if (Text1920x1080Button.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true && ResolutionModes % 4 == 2) {
                Text1920x1080Button.setFillColor(sf::Color::Red);

                // Left click to activate Text1920x1080Button.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode({ 1920, 1080 }), "Options", sf::State::Windowed);
                    renderFlag = true; // set the flag to true to redraw the background to the correct size

                }
            }
            else {
                Text1920x1080Button.setFillColor(sf::Color::Blue);
            }

            // FullScreenButton Changes to red when mouse hover.
            if (FullScreenButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true && ResolutionModes % 4 == 3) {
                FullScreenButton.setFillColor(sf::Color::Red);

                // Left click to activate FullScreenMode.
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Game.create(sf::VideoMode::getFullscreenModes()[0], "Options", sf::Style::None, sf::State::Fullscreen);
                    renderFlag = true; // set the flag to true to redraw the background to the correct size
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

            // WindowModeButton is not a button.
            if (ResolutionModeButton.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
                //Empty
            }
            else {
                ResolutionModeButton.setFillColor(sf::Color::Blue);
            }

            // WindowModeUp Button Changes to red when mouse hover.
            if (WindowModeUp.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
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
            if (WindowModeDown.getGlobalBounds().contains({ (float)localPosition.x, (float)localPosition.y }) == true) {
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
        // Position of puzzle pieces
        //PuzzleText.setPosition(piece.getPosition());
        //PuzzleText.setRotation(piece.getRotation());
        //PuzzleText.setOrigin(piece.getOrigin());

        MainMenuText.setPosition({ 0, 0 });
        MainMenuButton.setPosition(MainMenuText.getPosition());

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
        VolumeText.setPosition({ SoundBar.getPosition().x, SoundBar.getPosition().y - 50 });
        Speaker.setPosition({ CenterX - 200, CenterY });

        // Positions of MusicBar and Volume
        MusicVolumeText.setPosition({ MusicBar.getPosition().x, MusicBar.getPosition().y - 50 });
        MusicSymbol.setPosition({ Speaker.getPosition().x, Speaker.getPosition().y - 100 });

        //Convert Volume and MusicVolume into string.
        string VolumeString = to_string(Volume);
        VolumeText.setString(VolumeString);

        string MusicVolumeString = to_string(MusicVolume);
        MusicVolumeText.setString(MusicVolumeString);

        // Positions of the TestSound is left at default (top left).

        ResolutionModeText.setPosition({ MusicSymbol.getPosition().x, MusicSymbol.getPosition().y - 100 });
        ResolutionModeButton.setPosition(ResolutionModeText.getPosition());

        WindowModeUp.setPosition({ ResolutionModeText.getPosition().x + 325, ResolutionModeText.getPosition().y });
        WindowModeDown.setPosition({ ResolutionModeText.getPosition().x + 325, ResolutionModeText.getPosition().y + 40 });

        //------------------------------------------------------------------------------------------------------------------------------------------
        // Other windows that share buttons.
        //------------------------------------------------------------------------------------------------------------------------------------------

        if (isOptions) {
            ReturnText.setPosition({ CenterX, CenterY + 100 });
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

        //Order matters when drawing objects.
        Game.clear();




        if (isMainMenu) {
            backgroundHelper();
            Game.draw(QuitButton);
            Game.draw(QuitText);
            Game.draw(OptionsButton);
            Game.draw(OptionsText);
            Game.draw(PlayButton);
            Game.draw(PlayText);
            //Game.draw(Grape);
        }

        if (isOptions) {
            backgroundHelper(); 
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
            backgroundHelper();
            drawPieces();
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

