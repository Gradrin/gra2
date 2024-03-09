#pragma once
#include<fstream>
#include"Button.h"
#include"GameState.h"
#include"resources.h"
#include"Gui.h"

extern enum buttons;

class Resolution
{
private:
	Gui& gui;
	sf::Text text;
	sf::Event ev;

	std::fstream strim;

	enum resolutionButton :short { R_3840x2160, R_2560x1440, R_1920x1080, R_1024x768, R_800x600, BACK, SIZE };

	Button *button[SIZE];


	void addButtons();

public:
	Resolution(Gui& gui);
	~Resolution();

	//update functions
	void keyboardUpdate();
	void buttonFunction(const int& width, const int& height);
	void buttonUpdate();
	void update();


	//render functions
	void render(sf::RenderTarget* target);
	void renderButton();

};

