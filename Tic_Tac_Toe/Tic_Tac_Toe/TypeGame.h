#pragma once

#include<map>
#include<vector>
#include <string>
#include"Button.h"
#include"ComboBox.h"
#include"Start.h"
#include"Online.h"
#include"Gui.h"

class TypeGame
{
private:

	Gui& gui;
	Online* online;

	sf::Event ev;

	enum typeBox { TYPE_GAME, TIME, CHOICE_PLAYER,SIZE };
	enum typeButton { START, BACK, SIZE_BUTTON };

	bool flag[SIZE];

	ComboBox* box[SIZE];
	Button* button[SIZE_BUTTON];
	std::map<int, Start*> start;

	

	//Constructor's functions
	void initVariables();
	void addBoxs();
	void addButtons();

public:
	TypeGame(Gui& gui, Online* online);
	virtual ~TypeGame();

	//update functions
	void keyUpdate();
	void buttonClick(int& number, int& buttonNumber, sf::String time); //buttonClick() is for boxesUpdate();
	void boxesUpdate();
	void buttonFunctionUpdate(short& number);//buttonFunctionUpdate() is for buttonUpdate();
	void buttonsUpdate();
	void startGame(short& variable);
	void update();

	//render functions
	void render(sf::RenderTarget *target);
	void renderBoxes();
	void renderButton();



};

