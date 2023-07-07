#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow& window)
    : m_Window(window), m_SelectedIndex(0), m_MenuState(MenuState::Menu) // Initialize menu state
{
    // Load font, set title, play, and exit properties, load background texture
    // ...

    // Set background sprite properties
    // ...
}

void GameMenu::handleInput()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (m_MenuState == MenuState::Menu)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    m_SelectedIndex = (m_SelectedIndex + 1) % 2;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    m_SelectedIndex = (m_SelectedIndex + 1) % 2;
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                    if (m_SelectedIndex == 0)
                    {
                        m_MenuState = MenuState::Play; // Change menu state to "Play"
                    }
                    else if (m_SelectedIndex == 1)
                    {
                        m_Window.close(); // Close the window when "Exit" is selected
                    }
                }
            }
        }
    }
}

void GameMenu::update()
{
    // Update menu logic (if any)
}

void GameMenu::draw()
{
    m_Window.clear();

    // Draw background
    m_Window.draw(m_BackgroundSprite);

    // Draw menu items
    // ...

    m_Window.display();
}

MenuState GameMenu::getMenuState() const
{
    return m_MenuState;
}
