#include "Game.h"

// Private functions
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("textures/bullet.png");
}

void Game::initGUI()
{
    // Load font
    if (!this->font.loadFromFile("Fonts/jetbrain.ttf"))
    {
        std::cout << "ERROR::GAME::INITGUI::Failed to load font!"
                  << "\n";
    }

    // Init point text
    this->pointText.setPosition(sf::Vector2f(700.f, 25.f));
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(20);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("Test");

    // Game over text
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(sf::Vector2f(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
                                                this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f));

                    

    //Health bar GUI
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    // this->playerHpBar.getOutlineColor(sf::Color::Green);
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
    // this->playerHpBarBack.setPosition(this->playerHpBar.getPosition().x, this->playerHpBar.getPosition().y);
    // this->playerHpBarBack.getOutlineColor(sf::Color::Green);
}

void Game::initWorld()
{
    if (!this->worldBackgroundTexture.loadFromFile("textures/2.jpg"))
    {
        std::cout << "ERROR::GAME::INITWORLD::Failed to load world background texture!"
                  << "\n";
    }

    this->worldBackground.setTexture(this->worldBackgroundTexture);
}

void Game::initSystems()
{

    this->points = 0;
}

void Game::initPlayer()
{

    this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
}

// Constructors / Destructors
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initGUI();
    this->initWorld();
    this->initSystems();
    this->initPlayer();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    // Delete textures (loop for deletting map of textures)
    for (auto &i : this->textures)
    {
        delete i.second;
    }

    // Delete bullets
    for (auto *i : this->bullets)
    {
        delete i;
    }

    // Delete enemies
    for (auto *i : this->enemies)
    {
        delete i;
    }
}

// Functions
void Game::run()
{

    while (this->window->isOpen())
    {
        this->updatePollEvents();
        if(this->player->getHp() > 0)
        this->update();
        this->render();
    }
}

void Game::updatePollEvents()
{

    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();

        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();
    }
}

void Game::updateInput()
{

    // Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 2.f,
                       this->player->getPos().y, 0.f, -1.f, 5.f));
    }
}

void Game::updateGUI()
{
    std::stringstream ss;

    ss << "Points: " << this->points;
    this->pointText.setString(ss.str());

    // Update player GUI
    
    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f * static_cast<float>(this->player->getHp()) / this->player->getHpMax(), 25.f));

    
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
    // can only have 1 collison at a time due to sides of screen being far away from each other

    // Left world collision
    if (this->player->getBounds().left < 0.f)
    {
    this->player->setPosition(0.f, this->player->getBounds().top);
    }

    // Right world collision
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
    this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    // Bottom world collision
    if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
    this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }

    // Top world collision
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }
}

void Game::updateBullets()
{

    unsigned counter = 0;
    for (auto *bullet : this->bullets)
    {
        bullet->update();

        // Bullet culling (top of screen)
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            // Delete bullet
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
            
        }
        ++counter;
    }
}

void Game::updateEnemies()
{
    // Spawning
    this->spawnTimer += 0.1f;

    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));

        // Update
        unsigned counter = 0;

        for (auto *enemy : this->enemies)
        {
            enemy->update();

            // Enemy culling (bottom of screen)
            if (enemy->getBounds().top > this->window->getSize().y)
            {
                // Delete enemy
                delete this->enemies.at(counter);
                this->enemies.erase(this->enemies.begin() + counter);
                // making vector one size smaller
               
            }

            // Enemy player collision
            else if (enemy->getBounds().intersects(this->player->getBounds()))
            {
                // Delete enemy
                this->player->loseHp(this->enemies[counter]->getDamage());
                delete this->enemies.at(counter);
                this->enemies.erase(this->enemies.begin() + counter);
                // making vector one size smaller
                
                
            }

            ++counter;
        }
    }
}

void Game::updateCombat()
{
    for (int i = 0; i < this->enemies.size(); i++)
    {

        bool enemy_deleted = false;
        for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {

                this->points += this->enemies[i]->getPoints();

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                enemy_deleted = true;
            }
        }
    }
}



void Game::update()
{

    
    this->updateInput();
    this->player->update();
    this->updateCollision();
    this->updateBullets();
    this->updateEnemies();
    this->updateCombat();
    this->updateGUI();
    this->updateWorld();
}

void Game::renderGUI()
{
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{

    this->window->draw(this->worldBackground);
}

void Game::render()
{

    // Draw world background
    this->renderWorld();

    // Draw game objects
    this->player->render(*this->window);

    for (auto *bullet : this->bullets)
    {
        bullet->render(this->window);
    }

    for (auto *enemy : this->enemies)
    {
        enemy->render(this->window);
    }

    this->renderGUI();

    // Game over screen
    if (this->player->getHp() <= 0)
    {
        this->window->draw(this->gameOverText);
    }

    this->window->display();
}
