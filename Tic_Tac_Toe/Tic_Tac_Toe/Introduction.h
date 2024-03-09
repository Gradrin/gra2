#pragma once
#include"Button.h"
#include"GameState.h"
#include"Gui.h"

class Introduction
{
private:
	Gui& gui;

	sf::Event ev;
	sf::Text text;
	std::string std_text;

	Button *button;


	//Constructor's functions
	void initText();
	void addButton();
public:
	Introduction(Gui& gui);
	~Introduction();

	//introduction update
	void keyboardUpdate();
	void buttonUpdate();
	void update();


	//introduction render
	void render(sf::RenderTarget *target);
	void renderButton();
};

