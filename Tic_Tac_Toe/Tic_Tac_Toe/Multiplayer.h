#pragma once
#include"Button.h"
#include"Online.h"
#include"GameState.h"
#include"Start.h"
#include"Panels.h"

class Multiplayer
{
private:

	
	enum LineEdit { IP, PORT };

	struct
	{
		bool isClicked;
		float x_position;
		float y_position;
		float x_size;
		float y_size;
		sf::Text text;
		sf::Text textName;
		std::string characters;
		std::string name;
		sf::String textInput;
		sf::RectangleShape shape;
	}lineEdit[2];

	enum panelInformation { G_TYPE, G_TYPE_I, TIME, TIME_I, PLAYER, PLAYER_I, SIZE_TEXT };

	sf::Text *panelText[SIZE_TEXT];

	sf::Event ev;

	Gui& gui;
	Online* online;
	Start* start;
	Panels* waitingPanel;

	bool isClicked;
	bool panel;

	enum buttons : short { HOST, JOIN, BACK,SIZE };

	Button* button[SIZE];
	Button* panelStart;
	Button* panelDisconnect;

	//Constructor's functions
	void variables();
	void addLineEdits();
	void addButtons();

public:
	Multiplayer(Gui& gui, Online* online, Start* start);
	~Multiplayer();

	//update functions
	void keyboardUpdate();
	void buttonUpdate();
	void lineEditsUpdate();

	//panel's functions
	void createPanel();
	void deletePanel();

	void panelCreateText(short number, sf::Color color, short sizeFont, std::string text, float size_x, float size_y); //Create panel after click button[JOIN]
	void buttonPanelUpdate();
	void panelUpdate();

	void update();

	//render functions
	void render(sf::RenderTarget* target);
	void renderPanel(sf::RenderTarget* target);
	void renderButton();


	//Function after receive packet from host
	void startGame();

};

