#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

/* 
	Class that acts as the game engine
	Wrapper class.
*/

class Game
{
private:

	//Variables
	//Window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;

	//Mouse position
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Resources
	Font font;

	//Text
	Text uiText;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	vector<RectangleShape>enemies;
	RectangleShape enemy;

	//Private Functions
	void initVariables();
	void initWindow();
	void initEnemy();
	void initFonts();
	void initText();

public:
	
	//Contructos / Destructors
	Game();
	virtual ~Game();

	//Accecssors
	const bool getWindowIsOpen() const;
	const bool getEndGame() const;
	
	//Functions
	void spawnEnemy();
	void updateMousePositions();
	void pollEvents();
	void update();
	void updateText();
	void updateEnemies();
	void render();
	void renderText(RenderWindow& target);
	void renderEnemies(RenderWindow& target);
	void renderEndScreen(RenderWindow& target);
};

