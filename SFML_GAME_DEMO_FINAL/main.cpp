#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void menu(RenderWindow& window);

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
sf::Texture enemyTexture;
std::vector<sf::Sprite> enemies;
std::vector<sf::Sprite> bullets;
sf::Clock bulletTimer;

float speed = 0.5;
void board(float time);
float CurrentFrame = 0;
int CharDirection;
float enemySpeed = 0.1f;
int enemyDirection = 0;
float enemyTimer = 0.0f;
float enemyDelay = 3000.0f;
const int numEnemyFrames = 4;
int currentEnemyFrame = 0;
float enemyAnimationTimer = 0.0f;
float enemyAnimationDelay = 0.2f;

// Enemy adding
void spawnEnemy(float x, float y)
{
    sf::Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);
    enemySprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
    enemySprite.setPosition(x, y);

    enemies.push_back(enemySprite);
}

// Enemy Animation
void enemyAnimation(float deltaTime)
{
    enemyAnimationTimer += deltaTime;

    if (enemyAnimationTimer >= enemyAnimationDelay)
    {
        currentEnemyFrame = (currentEnemyFrame + 1) % numEnemyFrames;
        enemyAnimationTimer = 0.0f;
    }
}

// Enemy Moving
void moveEnemies(float deltaTime)
{
    enemyTimer += deltaTime;

    sf::Vector2f playerPosition = sprite.getPosition();

    for (auto& enemy : enemies)
    {
        sf::Vector2f enemyPosition = enemy.getPosition();
        sf::Vector2f direction = playerPosition - enemyPosition;
        sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

        enemy.move(normalizedDirection * enemySpeed * deltaTime);

        // Enemy moving
        if (normalizedDirection.x < 0) // Moving left
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 48, 32, 48));
        }
        else if (normalizedDirection.x > 0) // Moving right
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 96, 32, 48));
        }
        else if (normalizedDirection.y < 0) // Moving up
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 144, 32, 48));
        }
        else if (normalizedDirection.y > 0) // Moving down
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 0, 32, 48));
        }

        enemy.move(normalizedDirection * enemySpeed * deltaTime);
    }

    if (enemyTimer >= enemyDelay)
    {
        sf::Vector2f spritePosition = sprite.getPosition();

        for (auto& enemy : enemies)
        {
            sf::Vector2f enemyPosition = enemy.getPosition();
            sf::Vector2f direction = spritePosition - enemyPosition;
            sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }

        enemyTimer = 0.0f;
    }
}

void menu(RenderWindow& window) {
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;

    if (!menuTexture1.loadFromFile("111.jpg")) {
    }
    if (!menuTexture2.loadFromFile("222.png")) {
    }
    if (!menuTexture3.loadFromFile("333.png")) {
    }
    if (!aboutTexture.loadFromFile("about.png")) {
    }
    if (!menuBackground.loadFromFile("menu.png")) {
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
        window.clear(Color(0, 0, 0));

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

int main()
{
    window.create(sf::VideoMode(720, 720), "Resident Survivor");
    window.setFramerateLimit(60);
    window.setActive(false); // Deactivate the window initially

    sf::RenderWindow window_game(sf::VideoMode(700, 700), "Game Window");

    texture.loadFromFile("image.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 31, 31));
    sprite.setPosition(200, 300);

    backgroundTexture.loadFromFile("background.png");
    backgroundSprite.setTexture(backgroundTexture);

    wallTexture.loadFromFile("wall.png");
    wallSprite.setTexture(wallTexture);
    wallSprite.setPosition(0, 0);

    wallTexture1.loadFromFile("wall1.png");
    wallSprite1.setTexture(wallTexture1);
    wallSprite1.setPosition(264, 336);

    wallTexture2.loadFromFile("wall2.png");
    wallSprite2.setTexture(wallTexture2);
    wallSprite2.setPosition(648, 264);

    wallTexture3.loadFromFile("wall3.png");
    wallSprite3.setTexture(wallTexture3);
    wallSprite3.setPosition(312, 624);

    wallTexture4.loadFromFile("wall4.png");
    wallSprite4.setTexture(wallTexture4);
    wallSprite4.setPosition(0, 576);

    wallTexture5.loadFromFile("wall5.png");
    wallSprite5.setTexture(wallTexture5);
    wallSprite5.setPosition(0, 264);

    enemyTexture.loadFromFile("enemy.png");

    // Enemy spawner
    spawnEnemy(200, 400);
    spawnEnemy(400, 200);
    spawnEnemy(600, 500);

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.restart().asMicroseconds() / 800.0f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Activate the game window when the play button is clicked
                    window.setActive(true);
                    menu(window_game);
                }
            }
        }


        if (window.isOpen())
        {
            board(time);
            moveEnemies(time);

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
                if (CharDirection == 0) // Moving left
                    sprite.move(speed * time, 0);
                else if (CharDirection == 2) // Moving right
                    sprite.move(-speed * time, 0);
                else if (CharDirection == 2) // Moving up
                    sprite.move(0, speed * time);
                else if (CharDirection == 3) // Moving down
                    sprite.move(0, -speed * time);
            }

            window_game.clear();
                window_game.draw(backgroundSprite);
            window_game.draw(sprite);
            window_game.draw(wallSprite);
            window_game.draw(wallSprite1);
            window_game.draw(wallSprite2);
            window_game.draw(wallSprite3);
            window_game.draw(wallSprite4);
            window_game.draw(wallSprite5);
            for (const auto& enemy : enemies)
            {
                window_game.draw(enemy);
            }
            window_game.display();
        }

        window.clear();
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
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(CurrentFrame) * 31, 94, 31, 31));
        sprite.move(-speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        CharDirection = 1;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(CurrentFrame) * 31, 31, 31, 31));
        sprite.move(speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        CharDirection = 2;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(CurrentFrame) * 31, 63, 31, 31));
        sprite.move(0, -speed * time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        CharDirection = 3;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(CurrentFrame) * 31, 0, 31, 31));
        sprite.move(0, speed * time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        CharDirection = 0;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 63, 316.66, 63, 63.34));
        sprite.move(0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        CharDirection = 1;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 63, 189.98, 63, 63.34));
        sprite.move(0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
    {
        CharDirection = 2;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 63, 253.32, 63, 63.34));
        sprite.move(0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
    {
        CharDirection = 3;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 63, 126.64, 63, 63.34));
        sprite.move(0, 0);
    }
}


