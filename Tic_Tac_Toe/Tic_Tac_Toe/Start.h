#pragma once

#include<fstream>
#include<vector>
#include<time.h>

#include"Button.h"
#include"StatsWindow.h"
#include"Resolution.h"
#include"Panels.h"
#include"GameState.h"
#include"Online.h"

const int tableSize = 484;



class Board : public sf::Drawable, public sf::Transformable
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};

class Start
{
private:

	Gui& gui;

	sf::Clock clock;
	sf::Time time;

	sf::Clock clock2;
	sf::Time time2;

	int timeVariable;
	int timeVariable2;

	//Variables for text

	enum typeText { PLAYERS, PLAYER_POINTS, PLAYER_2_POINTS, GAME_TYPE, CLOCK, FIRST_TIME, SECOND_TIME, SIZE_TEXT };
	sf::Text text[SIZE_TEXT];

	std::string player;
	std::string pointsPlayer_1;
	std::string pointsPlayer_2;


	std::string watch;
	std::string firstTime;
	std::string secondTime;

	std::fstream basicBoard;
	std::fstream actualBoard;
	sf::Event ev;

	Panels *escapePanel;


	std::fstream strim;

	sf::Texture nowa;

	int quadSize;
	int height;
	int width;

	bool escPanel;
	bool resolutionPanel;
	std::map<std::string, Button*> button;

	enum buttonsEscape { RESUME, RESOLUTION, EXIT, SIZE };

	int quad;
	short circlePoints;
	short crossPoints;
	int gameMapUpdate[tableSize];


	Board board;
	StatsWindow *statsWindow;
	Online* online;

	enum sign { EMPTY, CIRCLE, CROSS };


	void initVariables();
	void functionForText(typeText number, std::string& text, sf::Color color, double size_x, double size_y); //function is for addText();
	void addText();
	void initBoard();
	void addButton();
public:
	Start(Gui &gui, Online* online);
	~Start();

	void points(sign SIGN);


	void updateKeyboard();
	void updateButtonPanel(); //function for updateButton()
	void updateButton();
	void updateBoard();
	void updatePlayers();
	void checkingBoard();
	void checkingBoardContinued(sign SIGN,int &j, int &i,const int &width );
	void functionTime(sf::Time& time, std::string& zegar);
	void gameTime();
	void update();


	void buttonsMenuRender();
	void buttonsResolutionRender();
	void render(sf::RenderTarget* target);
	void renderEndGame();
	void buttonRender();

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
};

