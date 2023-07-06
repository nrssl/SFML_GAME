#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window;
sf::RectangleShape rectangle(sf::Vector2f(150, 70));
sf::Texture texture;
sf::Sprite sprite;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
float speed = 0.5;
void board(float time);
float CurrentFrame = 0;

int main()
{
    window.create(sf::VideoMode(720, 720), "SFML Game!");
    window.setFramerateLimit(60);

    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setPosition(200,200);

    texture.loadFromFile("image.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

    backgroundTexture.loadFromFile("background.png");
    backgroundSprite.setTexture(backgroundTexture);

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        std::cout << time << std::endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        board(time);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(sprite);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}

// Keyboard
void board(float time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 64, 64, 64));
        sprite.move(-speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 128, 64, 64));
        sprite.move(speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 192, 64, 64));
        sprite.move(0, -speed * time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 0, 64, 64));
        sprite.move(0, speed * time);
    }
}
