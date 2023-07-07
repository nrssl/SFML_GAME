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
sf::Texture enemyTexture;
std::vector<sf::Sprite> enemies;

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


//Enemy adding,atnimation and move
void spawnEnemy(float x, float y)
{
    sf::Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);
    enemySprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
    enemySprite.setPosition(x, y);

    enemies.push_back(enemySprite);
}


void EnemyAnimation(float deltaTime)
{
    enemyAnimationTimer += deltaTime;

    if (enemyAnimationTimer >= enemyAnimationDelay)
    {
        currentEnemyFrame = (currentEnemyFrame + 1) % numEnemyFrames;
        enemyAnimationTimer = 0.0f;
    }
}

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

        //Enemy moving
        if (normalizedDirection.x < 0) // Moving left
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 48, 32, 48));
            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }
        else if (normalizedDirection.x > 0) // Moving right
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 96, 32, 48));
            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }
        else if (normalizedDirection.y < 0) // Moving up
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 144, 32, 48));
            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }
        else if (normalizedDirection.y > 0) // Moving down
        {
            enemy.setTextureRect(sf::IntRect(currentEnemyFrame * 32, 0, 32, 48));
            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }
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

int main()
{
    window.create(sf::VideoMode(720, 720), "Resident Survivor");
    window.setFramerateLimit(60);

    texture.loadFromFile("image.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 31.66, 31.66));
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

    //Enemy spawner
    spawnEnemy(200, 400);
    spawnEnemy(400, 200);
    spawnEnemy(600, 500); 

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.restart().asMicroseconds() / 800.0f;
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

        moveEnemies(time); // Move the enemies
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

        
for (const auto& enemy : enemies)
        {
            window.draw(enemy);
        }

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
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 31.66, 94.99, 31.66, 31.66));
        sprite.move(-speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        CharDirection = 1;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 31.66, 31.66, 31.66, 31.66));
        sprite.move(speed * time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        CharDirection = 2;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 31.66, 63.33, 31.66, 31.66));
        sprite.move(0, -speed * time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        CharDirection = 3;
        CurrentFrame += 0.005 * time;
        std::cout << CurrentFrame << std::endl;
        if (CurrentFrame > 4)
            CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 31.66, 0, 31.66, 31.66));
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
