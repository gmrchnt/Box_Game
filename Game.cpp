#include "Game.h"

//Initializers
void Game::initVariables()
{
	this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->points = 0;
    this->enemySpawnTimerMax = 50.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health = 10;
}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	this->window = new RenderWindow(this->videomode, "Fifth Game", Style::Titlebar | Style::Close | Style::Resize);
    this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
    this->enemy.setPosition(10.f,  10.f);
    this->enemy.setSize(Vector2f(100.f, 100.f));
    this->enemy.setFillColor(Color::Black);
    this->enemy.setOutlineColor(Color(249, 105, 14,255));
    this->enemy.setOutlineThickness(8.f);
    this->enemy.setScale(0.5f, 0.5f);
}

void Game::initFonts()
{
    font.loadFromFile("Fonts/TT Rounds Neue Trial Condensed ExtraBold.ttf");
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(32);

    //Set color of text using RGBA
    this->uiText.setFillColor(Color(193, 57, 7, 255));
    this->uiText.setPosition(250.f, 0.f);
    this->uiText.setString("Points: 0");
}

//Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemy();
}

//Destructor
Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.f
    );

    //Randomize enemy type
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        this->enemy.setSize(Vector2f(100.f, 100.f));
        this->enemy.setFillColor(Color(0x990011FF));//Cherry red & off-white
        this->enemy.setOutlineColor(Color(0xFCF6F5FF));
        this->enemy.setOutlineThickness(8.f);
        break;
    case 1:
        this->enemy.setSize(Vector2f(95.f, 95.f));
        this->enemy.setFillColor(Color(0x2F3C7EFF));//Blue & pastel pink
        this->enemy.setOutlineColor(Color(0xFBEAEBFF));
        this->enemy.setOutlineThickness(4.f);
        break;
    case 2:
        this->enemy.setSize(Vector2f(90.f, 90.f));
        this->enemy.setFillColor(Color(0x101820FF));//Dark charcoal & bright yellow
        this->enemy.setOutlineColor(Color(0xFEE715FF));
        this->enemy.setOutlineThickness(4.f);
        break;
    case 3:
        this->enemy.setSize(Vector2f(85.f, 85.f));
        this->enemy.setFillColor(Color(0xF96167FF));//Light red & yellow
        this->enemy.setOutlineColor(Color(0xF9E795FF));
        this->enemy.setOutlineThickness(4.f);
        break;
    case 4:
        this->enemy.setSize(Vector2f(80.f, 80.f));
        this->enemy.setFillColor(Color(0x8AAAE5FF));//Baby blue & white
        this->enemy.setOutlineColor(Color(0xFFFFFFFF));
        this->enemy.setOutlineThickness(4.f);
        break;

    default:
        this->enemy.setSize(Vector2f(75.f, 75.f));
        this->enemy.setFillColor(Color(0x735DA5FF));//Salmon pink & soft peach
        this->enemy.setOutlineColor(Color(0xFFF2D7FF));
        this->enemy.setOutlineThickness(4.f);
        break;
    }


    //Spawn the enemy
    this->enemies.push_back(this->enemy);

    //
}
void Game::updateMousePositions()
{
    /*
        Updates mouse position:
        - Relatice to the window(Vector2i)
    */
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if (this->ev.key.code == Keyboard::Escape)
            {
                this->window->close();
            }
            else if (this->ev.key.code == Keyboard::Enter && this->health <= 0) {
                this->endGame = true;
            }
            break;
        }
    }
}

void Game::updateText()
{
    stringstream ss;

    ss << "Points: " << this->points << " Health: " << this->health;

    this->uiText.setString(ss.str());
}

void Game::renderText(RenderWindow& target)
{
    target.draw(uiText);
}

void Game::updateEnemies()
{
    
    //Updating the timer for enemy
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Moving and updating the enemies
    for (int i=0;i<this->enemies.size();i++)  //auto& e : this->enemies -iterator method
    {
        bool toDelete = false;
        this->enemies[i].move(0.f, 3.f);

        //Check if clicked upon
        if (Mouse::isButtonPressed(Mouse::Left) && !mouseHeld)
        {
            if (enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                toDelete = true;

                //Points gain
                if (this->enemies[i].getFillColor() == Color(0x990011FF))
                    points += 1;
                else if (this->enemies[i].getFillColor() == Color(0x2F3C7EFF))
                    points += 2;
                else if (this->enemies[i].getFillColor() == Color(0x101820FF))
                    points += 3;
                else if (this->enemies[i].getFillColor() == Color(0xF96167FF))
                    points += 4;
                else if (this->enemies[i].getFillColor() == Color(0x8AAAE5FF))
                    points += 5;
                else if (this->enemies[i].getFillColor() == Color(0x735DA5FF))
                    points += 6;

                mouseHeld = true;

            }
        }

        //If the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            toDelete = true;

            //Health Lost
            this->health -= 1;
        }

        if (toDelete)
        {
            this->enemies.erase(this->enemies.begin() + i);
        }

        //mouseHeld variable is reset only when the left mouse button is not pressed
        if (Mouse::isButtonPressed(Mouse::Left) == false && mouseHeld)
        {
            mouseHeld = false;
        }
    }
}

void Game::renderEnemies(RenderWindow& target)
{

    //Rendering all enemies
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::renderEndScreen(RenderWindow& target)
{
    this->window->clear(Color(255, 194, 193, 255));
    stringstream ss;

    ss << "Game Over!\n Points:" << this->points << "\n\npress ENTER to quit";

    this->uiText.setString(ss.str());
    this->uiText.setPosition(250.f, 200.f);
    target.draw(uiText);
    target.display();
}

void Game::update()
{
    this->pollEvents();
    if (this->endGame == false)
    {
        this->updateMousePositions();
        this->updateEnemies();
        this->updateText();
    }

}

void Game::render()
{
    if (this->health <= 0) 
    {
        this->renderEndScreen(*this->window);
    }
    else
    {
        this->window->clear(Color(255, 194, 193, 255));

        // Draw game objects
        this->renderEnemies(*this->window);
        this->renderText(*this->window);

        this->window->display();

    }
}