#pragma once

#include<map>
#include"Online.h"
#include"Button.h"
#include"resources.h"
#include"Gui.h"

class StatsWindow
{
private:

	Gui& gui;
	Online* online;
	sf::Sprite *backgroundSign;
	sf::Texture sign;
	sf::Text text;
	sf::Text text2;

	std::string std_text;
	std::string std_text2;


	sf::Event ev;

	enum buttons :short { BACK, PLAY_AGAIN, SIZE };

	Button *button[SIZE];

	short &circlePoints;
	short &crossPoints;

	//Constructor's functions
	void initText();
	void addButtons();

public:
	StatsWindow(Online* online, Gui& gui, short& circlePoints, short& crossPoints);
	~StatsWindow();

	//update functions
	void updateKeyboard();
	void buttonsClick(short& number);
	void buttonsUpdate();
	void update();

	//render functions
	void render(sf::RenderTarget* target);
	void buttonsRender();
};

