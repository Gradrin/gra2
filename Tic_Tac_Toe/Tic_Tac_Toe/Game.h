#pragma once


#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <thread>
#include<string.h>
#include<fstream>
#include"Button.h"
#include"GameState.h"
#include"Introduction.h"
#include"Start.h"
#include"TypeGame.h"
#include"Multiplayer.h"
#include "resources.h"
#include"Resolution.h"
#include"GameState.h"
#include"Gui.h"

class Game 
{
private:

	sf::Event ev;
	Gui gui;

	enum buttonSize { SIZE = 5 };

	Button *button[SIZE];

	TypeGame *gameType;
	Multiplayer* multiplayer;
	Resolution* resolution;
	Introduction* introduction;

	Start* start;

	bool isConnected;

	Online* online;


	//Constructor's functions
	void addButtons();

public:
	Game();
	virtual ~Game();

	//update functions

	void keyboardUpdate();
	void buttonsClick(short& number); //button Click() is for buttonUpdate();
	void buttonsUpdate();
	void update();
	
	//render functions
	void buttonsRender();
	template<typename T>
	void statusRenderFunction(GameState _gameState,T* status); // function for StatusRender();
	void statusRender();
	void render();

	void run();

};

