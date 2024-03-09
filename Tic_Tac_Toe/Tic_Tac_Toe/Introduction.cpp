#include "Introduction.h"

void Introduction::initText()
{
	this->std_text = "\nWelcome in Gomoku game.\n The game's rules are very simple. In game is two players:\n - First player play as O,\n - Second player as X.\n Everyone has self round and can put only his one sign on empty\n place in board. You have to put five sign in one line to win.\n If no one does this and the board will be full then is draw. ";
	
	this->text.setFont(gui.getFont());
	this->text.setString(std_text);
	this->text.setCharacterSize(34);
	this->text.setPosition(sf::Vector2f(gui.getWIDTH() * 0.1, gui.getHEIGHT() * 0.1));
}

void Introduction::addButton()
{
	this->button = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.7, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "BACK", 26);
}


Introduction::Introduction(Gui& gui)
: gui(gui)
{
	this->initText();
	this->addButton();
}

Introduction::~Introduction()
{

}


void Introduction::keyboardUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gui.getWindow()->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			this->gui.getGameState() = MAIN_MENU;
		}
	}
}

void Introduction::buttonUpdate()
{
	if (!button->getBounds().contains(this->gui.getMousePos()))
		button->setColor(button->getBasic());

	if (button->getBounds().contains(this->gui.getMousePos()))
		button->setColor(button->getIntersect());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (button->getBounds().contains(this->gui.getMousePos()))
			button->setColor(button->getClick());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button->getBounds().contains(this->gui.getMousePos()))
			this->gui.getGameState() = MAIN_MENU;

	while (this->gui.getWindow()->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->gui.getWindow()->close();
	}
}

void Introduction::update()
{
	this->gui.mousePosition();
	this->keyboardUpdate();
	this->buttonUpdate();
}

void Introduction::render(sf::RenderTarget* target)
{
	target->draw(gui.getBackground());
	target->draw(text);
	this->renderButton();
}

void Introduction::renderButton()
{

	this->button->render(this->gui.getWindow());
}
