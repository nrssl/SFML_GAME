#pragma once

#include <SFML/Graphics.hpp>

enum class MenuState
{
    Menu,
    Play
};

class GameMenu
{
public:
    GameMenu(sf::RenderWindow& window);
    void handleInput();
    void update();
    void draw();
    MenuState getMenuState() const; // Added

private:
    sf::RenderWindow& m_Window;
    sf::Font m_Font;
    sf::Text m_Title;
    sf::Text m_PlayText;
    sf::Text m_ExitText;
    sf::Texture m_BackgroundTexture;
    sf::Sprite m_BackgroundSprite;
    int m_SelectedIndex;
    MenuState m_MenuState; // Added
};

