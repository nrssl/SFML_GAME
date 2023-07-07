#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow& window) {
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    if (!menuTexture1.loadFromFile("images/111.png")) {
        // Handle error loading texture
    }
    if (!menuTexture2.loadFromFile("images/222.png")) {
        // Handle error loading texture
    }
    if (!menuTexture3.loadFromFile("images/333.png")) {
        // Handle error loading texture
    }
    if (!aboutTexture.loadFromFile("images/about.png")) {
        // Handle error loading texture
    }
    if (!menuBackground.loadFromFile("menu.png")) {
        // Handle error loading texture
    }
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = true;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menu3.setPosition(100, 150);
    menuBg.setPosition(345, 0);

    // Main menu loop
    while (isMenu) {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        // Check if the mouse position is within the button boundaries
        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) {
            menu1.setColor(Color::Blue);
            menuNum = 1;
        }
        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) {
            menu2.setColor(Color::Blue);
            menuNum = 2;
        }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) {
            menu3.setColor(Color::Blue);
            menuNum = 3;
        }

        // Handle menu button clicks
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (menuNum == 1) {
                isMenu = false; // If the first button is clicked, exit the menu
            }
            if (menuNum == 2) {
                window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            if (menuNum == 3) {
                window.close(); // Close the window if the third button is clicked
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.display();
    }
}
