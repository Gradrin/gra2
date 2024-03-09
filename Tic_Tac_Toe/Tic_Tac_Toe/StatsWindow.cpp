#include "StatsWindow.h"

void StatsWindow::initText()
{
	if (online->GameOnline() == false)
	{
		this->std_text = "THIS GAME WON PLAYER PLAYED AS:";
		if (this->circlePoints == this->gui.getVariable())
		{
			if (!this->sign.loadFromFile(CIRCLE_WIN))
			{
				throw"ERROR";
			}
			this->backgroundSign = new sf::Sprite;
			this->backgroundSign->setTexture(sign);

		}
		else
		{
			if (!this->sign.loadFromFile(CROSS_WIN))
			{
				throw"ERROR";
			}
			this->backgroundSign = new sf::Sprite;
			this->backgroundSign->setTexture(sign);

		}
	}
	else
	{
		if (online->getHost() == true)
		{
			if (online->getTurn() == CLIENT)
			{
				this->std_text = "WINNER IS:\n      YOU";
				if (circlePoints > crossPoints)
					this->std_text2 = "RESULT MATCH:\n             YOU = " + 
					std::to_string(circlePoints) + " Points\nOPONNENT = " + 
					std::to_string(crossPoints) + " Points";
				else
					this->std_text2 = "RESULT MATCH:\n             YOU = " +
					std::to_string(crossPoints) + " Points\nOPONNENT = " +
					std::to_string(circlePoints) + " Points";
			}
			else
			{
				this->std_text = "WINNER IS:\nOPONNENT";
				if (circlePoints > crossPoints)
					this->std_text2 = "RESULT MATCH:\n             YOU = " +
					std::to_string(crossPoints) + " Points\nOPONNENT = " +
					std::to_string(circlePoints) + " Points";
				else
					this->std_text2 = "RESULT MATCH:\n             YOU = " +
					std::to_string(circlePoints) + " Points\nOPONNENT = " +
					std::to_string(crossPoints) + " Points";
			}
		}
		else if ((online->getClient() == true))
		{
			if (online->getTurn() == HOST)
			{
				this->std_text = "WINNER IS:\n      YOU";
				if (circlePoints > crossPoints)
					this->std_text2 = "RESULT MATCH:\n             YOU = " +
					std::to_string(circlePoints) + " Points\nOPONNENT = " +
					std::to_string(crossPoints) + " Points";
				else
					this->std_text2 = "RESULT MATCH:\n             YOU = " +
					std::to_string(crossPoints) + " Points\nOPONNENT = " +
					std::to_string(circlePoints) + " Points";
			}
			else
			{
				this->std_text = "WINNER IS:\nOPONNENT";
				if (circlePoints > crossPoints)
					this->std_text2 = "RESULT:\n             YOU = " +
					std::to_string(crossPoints) + " Points\nOPONNENT = " +
					std::to_string(circlePoints) + " Points";
				else
					this->std_text2 = "RESULT:\n             YOU = " +
					std::to_string(circlePoints) + " Points\nOPONNENT = " +
					std::to_string(crossPoints) + " Points";
			}
		}
		this->backgroundSign = new sf::Sprite;
		this->backgroundSign->setTexture(gui.getTexture());
	}

	this->text.setFont(gui.getFont());
	this->text.setString(std_text);
	this->text.setCharacterSize(34);
	if (online->GameOnline() == false)
		this->text.setPosition(sf::Vector2f(gui.getWIDTH() / 2 - gui.getWIDTH() * 0.24, gui.getHEIGHT() / 6));
	else
		this->text.setPosition(sf::Vector2f(gui.getWIDTH() / 2 - gui.getWIDTH() * 0.05, gui.getHEIGHT() / 6));

	this->text2.setFont(gui.getFont());
	this->text2.setString(std_text2);
	this->text2.setCharacterSize(34);
	this->text2.setPosition(sf::Vector2f(gui.getWIDTH() / 2 - gui.getWIDTH() * 0.1, gui.getHEIGHT() / 2.5));


}

void StatsWindow::addButtons()
{
	this->button[PLAY_AGAIN] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.65, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "PLAY AGAIN", 26);
	if (online->GameOnline() == false)
		this->button[BACK] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.8, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "BACK", 26);
	else
		this->button[BACK] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.8, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "DISCONNECT", 26);
}

StatsWindow::StatsWindow(Online* online, Gui& gui, short& circlePoints, short& crossPoints)
	:online(online), gui(gui), circlePoints(circlePoints), crossPoints(crossPoints)
{
	this->initText();
	this->addButtons();
}

StatsWindow::~StatsWindow()
{
	for (auto i : this->button)
	{
		delete i;
	}
	delete this->backgroundSign;

}

void StatsWindow::updateKeyboard()
{
	while (this->gui.getWindow()->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->gui.getWindow()->close();
	}
}

void StatsWindow::buttonsClick(short& number)
{
	if (online->GameOnline() == false)
	{
		if (number == PLAY_AGAIN)
		{
			this->gui.getGameState() = TYPE_GAME;
			circlePoints = 0;
			crossPoints = 0;
		}
		else
		{
			this->gui.getGameState() = MAIN_MENU;
			this->gui.startStatus() = false;
		}
	}
	else
	{
		if (number == PLAY_AGAIN)
		{
			if (online->getHost() == true)
			{
				this->gui.getGameState() = TYPE_GAME;
				this->gui.startStatus() = false;
			}
			else
			{
				this->gui.getGameState() = MULTIPLAYER;
				this->gui.startStatus() = false;
			}
		}
		else
		{
			this->gui.getGameState() = MAIN_MENU;
		}
	}
}

void StatsWindow::buttonsUpdate()
{
	short number = 0;
	for (auto i : this->button)
	{
		if (!i->getBounds().contains(this->gui.getMousePos()))
			i->setColor(i->getBasic());

		if (i->getBounds().contains(this->gui.getMousePos()))
			i->setColor(i->getIntersect());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (i->getBounds().contains(this->gui.getMousePos()))
			{
				i->setColor(i->getClick());
				this->gui.getWindow()->waitEvent(ev);
				if (ev.type == sf::Event::MouseButtonReleased)
				{
					buttonsClick(number);
				}
			}
		number++;
	}
}

void StatsWindow::update()
{
	this->updateKeyboard();
	this->gui.mousePosition();
	this->buttonsUpdate();
}

void StatsWindow::render(sf::RenderTarget* target)
{
	target->draw(*backgroundSign);
	target->draw(text);
	target->draw(text2);
	this->buttonsRender();

}

void StatsWindow::buttonsRender()
{
	for (auto i : this->button)
	{
		i->render(gui.getWindow());
	}
}
