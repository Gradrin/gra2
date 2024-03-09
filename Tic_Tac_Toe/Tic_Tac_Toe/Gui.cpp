#include "Gui.h"


void Gui::initVariables()
{
	this->stream.open(WINDOW);
	if (this->stream.is_open())
	{

		stream >> name;
		stream >> frame;
		stream >> vsync;
	}
	this->stream.close();

	WIDTH = 1024;
	HEIGHT = 768;

	this->gameState = MAIN_MENU;
	this->variable = AMOUNT;
	this->typeGame = "";
	this->basicVariable = NONE;
	this->player = NONE;
	this->sendPlayer = 0;
	this->start = false;
}

void Gui::addBackground()
{
	if (!this->texture.loadFromFile(BACKGROUND))
	{
		throw"ERROR";
	}
	this->background.setTexture(texture);

}

void Gui::initFonts()
{

	if (!this->font.loadFromFile(FONT))
	{
		std::cout << "FAILD" << "\n";
	}
}

void Gui::addWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), name);
	this->window->setFramerateLimit(frame);
	this->window->setVerticalSyncEnabled(vsync);
}


Gui::Gui()
{
	this->initVariables();
	this->addBackground();
	this->initFonts();
	this->addWindow();
}

Gui::~Gui()
{
}




void Gui::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Gui::renderBackground(sf::RenderTarget* target)
{
	target->draw(background);
}


const sf::Vector2f& Gui::getMousePos() const
{
	return this->mousePosView;
}

 sf::RenderWindow* Gui::getWindow() 
{
	return this->window;
}

 sf::RenderTarget* Gui::getTarget()
 {
	 return this->window;
 }

const sf::Font& Gui::getFont() const
{
	return this->font;
}

 GameState& Gui::getGameState() 
{
	return this->gameState;
}

 const sf::Sprite& Gui::getBackground() const
 {
	 return this->background;
 }

 const sf::Texture& Gui::getTexture() const
 {
	 return this->texture;
 }

const short& Gui::getHEIGHT() const
{
	return this->HEIGHT;
}

const short& Gui::getWIDTH() const
{
	return this->WIDTH;
}

 short& Gui::getVariable() 
{
	return this->variable;
}

 int& Gui::getBasicVariable()
 {
	 return this->basicVariable;
 }

 short& Gui::getPlayer()
 {
	 return this->player;
 }

 short& Gui::getSendPlayer()
 {
	 return this->sendPlayer;
 }

 bool& Gui::startStatus()
 {
	 return this->start;
 }

 std::string& Gui::getTypeGame()
 {
	 return this->typeGame;
 }
 