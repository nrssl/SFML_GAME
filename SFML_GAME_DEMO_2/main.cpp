#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window;
sf::Texture texture;
sf::Sprite sprite;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Texture wallTexture;
sf::Sprite wallSprite;
sf::Texture wallTexture1;
sf::Sprite wallSprite1;
sf::Texture wallTexture2;
sf::Sprite wallSprite2;
sf::Texture wallTexture3;
sf::Sprite wallSprite3;
sf::Texture wallTexture4;
sf::Sprite wallSprite4;
sf::Texture wallTexture5;
sf::Sprite wallSprite5;
float speed = 0.5;
void board(float time);
float CurrentFrame = 0;
int CharDirection;

int main()
{
    window.create(sf::VideoMode(720, 720), "SFML Game!");
    window.setFramerateLimit(60);

    texture.loadFromFile("image.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(200, 200);

    backgroundTexture.loadFromFile("background.png");
    backgroundSprite.setTexture(backgroundTexture);

    wallTexture.loadFromFile("wall.png");
    wallSprite.setTexture(wallTexture);
    wallSprite.setPosition(0, 0);

    wallTexture1.loadFromFile("wall1.png");
    wallSprite1.setTexture(wallTexture1);
    wallSprite1.setPosition(264,336);

    wallTexture2.loadFromFile("wall2.png");
    wallSprite2.setTexture(wallTexture2);
    wallSprite2.setPosition(648,264);

    wallTexture3.loadFromFile("wall3.png");
    wallSprite3.setTexture(wallTexture3);
    wallSprite3.setPosition(312,624);

    wallTexture4.loadFromFile("wall4.png");
    wallSprite4.setTexture(wallTexture4);
    wallSprite4.setPosition(0,576);

    wallTexture5.loadFromFile("wall5.png");
    wallSprite5.setTexture(wallTexture5);
    wallSprite5.setPosition(0,264);

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

        // Collision
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        sf::FloatRect wallBounds = wallSprite.getGlobalBounds();
        sf::FloatRect wallBounds1 = wallSprite1.getGlobalBounds();
        sf::FloatRect wallBounds2 = wallSprite2.getGlobalBounds();
        sf::FloatRect wallBounds3 = wallSprite3.getGlobalBounds();
        sf::FloatRect wallBounds4 = wallSprite4.getGlobalBounds();
        sf::FloatRect wallBounds5 = wallSprite5.getGlobalBounds();

        if (spriteBounds.intersects(wallBounds) || spriteBounds.intersects(wallBounds1) ||
            spriteBounds.intersects(wallBounds2) || spriteBounds.intersects(wallBounds3) ||
            spriteBounds.intersects(wallBounds4) || spriteBounds.intersects(wallBounds5))
        {
            if (CharDirection == 0)
                sprite.move(speed * time, 0);
            if (CharDirection == 1)
                sprite.move(-speed * time, 0);
            if (CharDirection == 2)
                sprite.move(0, speed * time);
            if (CharDirection == 3)
                sprite.move(0, -speed * time);
        }

        board(time);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(sprite);
        window.draw(wallSprite);
        window.draw(wallSprite1);
        window.draw(wallSprite2);
        window.draw(wallSprite3);
        window.draw(wallSprite4);
        window.draw(wallSprite5);
        window.display();
    }

    return 0;
}

// Keyboard
void board(float time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        CharDirection = 0;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 64, 64, 64));
        sprite.move(-speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        CharDirection = 1;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 128, 64, 64));
        sprite.move(speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        CharDirection = 2;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 192, 64, 64));
        sprite.move(0, -speed * time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        CharDirection = 3;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 64, 0, 64, 64));
        sprite.move(0, speed * time);
    }
}