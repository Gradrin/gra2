#include "Multiplayer.h"



void Multiplayer::variables()
{
	this->lineEdit[IP].isClicked = false;
	this->lineEdit[PORT].isClicked = false;

	this->lineEdit[IP].x_size = 300.f;
	this->lineEdit[IP].y_size = 50.f;
	this->lineEdit[IP].x_position = gui.getWIDTH() / 2 - this->lineEdit[IP].x_size / 2;
	this->lineEdit[IP].y_position = gui.getHEIGHT()*0.5;

	this->lineEdit[PORT].x_size = 300.f;
	this->lineEdit[PORT].y_size = 50.f;
	this->lineEdit[PORT].x_position = gui.getWIDTH() / 2 - this->lineEdit[PORT].x_size / 2;
	this->lineEdit[PORT].y_position = gui.getHEIGHT()*0.6;

	this->isClicked = false;


    this->panel = false;
	this->waitingPanel = new Panels(gui);
}

void Multiplayer::addLineEdits()
{
	this->lineEdit[IP].shape.setSize(sf::Vector2f(lineEdit[IP].x_size, lineEdit[IP].y_size));
	this->lineEdit[IP].shape.setFillColor(sf::Color::Black);
	this->lineEdit[IP].shape.setPosition(lineEdit[IP].x_position, lineEdit[IP].y_position);

	this->lineEdit[IP].name = "TCP/IP:";

	this->lineEdit[IP].textName.setFont(gui.getFont());
	this->lineEdit[IP].textName.setString(lineEdit[IP].name);
	this->lineEdit[IP].textName.setCharacterSize(32);
	this->lineEdit[IP].textName.setPosition(lineEdit[IP].x_position - 100.f, lineEdit[IP].y_position);

	this->lineEdit[IP].characters = "";

	this->lineEdit[IP].text.setFont(gui.getFont());
	this->lineEdit[IP].text.setString(lineEdit[IP].characters);
	this->lineEdit[IP].text.setCharacterSize(32);
	this->lineEdit[IP].text.setPosition(lineEdit[IP].x_position, lineEdit[IP].y_position);


	this->lineEdit[PORT].shape.setSize(sf::Vector2f(lineEdit[PORT].x_size, lineEdit[PORT].y_size));
	this->lineEdit[PORT].shape.setFillColor(sf::Color::Black);
	this->lineEdit[PORT].shape.setPosition(lineEdit[PORT].x_position, lineEdit[PORT].y_position);

	this->lineEdit[PORT].name = "Port:";

	this->lineEdit[PORT].textName.setFont(gui.getFont());
	this->lineEdit[PORT].textName.setString(lineEdit[PORT].name);
	this->lineEdit[PORT].textName.setCharacterSize(32);
	this->lineEdit[PORT].textName.setPosition(lineEdit[PORT].x_position - 65.f, lineEdit[PORT].y_position);

	this->lineEdit[PORT].characters = "";

	this->lineEdit[PORT].text.setFont(gui.getFont());
	this->lineEdit[PORT].text.setString(lineEdit[PORT].characters);
	this->lineEdit[PORT].text.setCharacterSize(32);
	this->lineEdit[PORT].text.setPosition(lineEdit[PORT].x_position, lineEdit[PORT].y_position);

}

void Multiplayer::addButtons()
{
	this->button[HOST] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.2, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "HOST", 26);
	this->button[JOIN] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.35, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "JOIN", 26);
	this->button[BACK] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.8, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "BACK", 26);
}




Multiplayer::Multiplayer(Gui& gui, Online* online, Start* start)
	:gui(gui), online(online), start(start)
{
	this->variables();
	this->addLineEdits();
	this->addButtons();

}

Multiplayer::~Multiplayer()
{
	delete waitingPanel;
}

void Multiplayer::keyboardUpdate()
{
	while (this->gui.getWindow()->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->gui.getWindow()->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gui.getWindow()->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			this->gui.getGameState() = MAIN_MENU;
		}
	}
}


void Multiplayer::lineEditsUpdate()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->lineEdit[IP].shape.getGlobalBounds().contains(this->gui.getMousePos()))
			if (this->lineEdit[IP].isClicked == false)
			{
				this->lineEdit[IP].isClicked = true;
				this->lineEdit[PORT].isClicked = false;
			}
			else
				this->lineEdit[IP].isClicked = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->lineEdit[PORT].shape.getGlobalBounds().contains(this->gui.getMousePos()))
			if (this->lineEdit[PORT].isClicked == false)
			{
				this->lineEdit[PORT].isClicked = true;
				this->lineEdit[IP].isClicked = false;
			}
			else
				this->lineEdit[PORT].isClicked = false;


	if (lineEdit[IP].isClicked == true)
	{
		this->lineEdit[IP].shape.setFillColor(sf::Color::Green);
		if (ev.type == sf::Event::TextEntered)
		{
			if (ev.text.unicode == 8)
			{
				lineEdit[PORT].textInput.erase(lineEdit[PORT].textInput.getSize() - 1, 1);
				lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
				gui.getWindow()->waitEvent(ev);
			}
			else
			{
				lineEdit[PORT].textInput += ev.text.unicode;
				lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
				gui.getWindow()->waitEvent(ev);
			}
		}
	}
	else
		this->lineEdit[IP].shape.setFillColor(sf::Color::Black);

	if (lineEdit[PORT].isClicked == true)
	{
		this->lineEdit[PORT].shape.setFillColor(sf::Color::Green);
			if (ev.type == sf::Event::TextEntered)
			{
				if (ev.text.unicode == 8)
				{
					lineEdit[PORT].textInput.erase(lineEdit[PORT].textInput.getSize() - 1, 1);
					lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
					gui.getWindow()->waitEvent(ev);
				}
				else
				{
					lineEdit[PORT].textInput += ev.text.unicode;
					lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
					gui.getWindow()->waitEvent(ev);
				}
			}
	}
	else
			this->lineEdit[PORT].shape.setFillColor(sf::Color::Black);

}

void Multiplayer::createPanel()
{
	this->panel = true;
	this->panelStart = new Button(gui.getFont(), waitingPanel->getPosition_x() + (gui.getWIDTH() * waitingPanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), waitingPanel->getPosition_y() * 4.5, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "READY", 26);
	this->panelStart->setColor(panelStart->getUnableClick());
	this->panelDisconnect = new Button(gui.getFont(), waitingPanel->getPosition_x() + (gui.getWIDTH() * waitingPanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), waitingPanel->getPosition_y() * 5.5, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "DISCONNECT", 26);
	this->panelCreateText(G_TYPE, sf::Color::Red, 38, "TYPE GAME:", 1.1, 1.6);
	this->panelCreateText(G_TYPE_I, sf::Color::White, 20, "empty", 1.25, 2);
	this->panelCreateText(TIME, sf::Color::Red, 38, "     TIME:", 1.1, 2.5);
	this->panelCreateText(TIME_I, sf::Color::White, 20, "empty", 1.25, 2.9);
	this->panelCreateText(PLAYER, sf::Color::Red, 38, "   PLAYER:", 1.1, 3.4);
	this->panelCreateText(PLAYER_I, sf::Color::White, 20, "empty", 1.25, 3.8);
}

void Multiplayer::deletePanel()
{
	this->panel = false;
	delete panelStart;
	delete panelDisconnect;
}

void Multiplayer::panelCreateText(short number, sf::Color color, short sizeFont, std::string text, float size_x, float size_y)
{
	this->panelText[number] = new sf::Text;

	this->panelText[number]->setFont(gui.getFont());
	this->panelText[number]->setString(text);
	this->panelText[number]->setCharacterSize(sizeFont);
	this->panelText[number]->setFillColor(color);
	this->panelText[number]->setPosition(sf::Vector2f(waitingPanel->getPosition_x() * size_x, waitingPanel->getPosition_y() * size_y));
}

void Multiplayer::buttonPanelUpdate()
{

	if (panelStart->getCurrentColor() != panelStart->getUnableClick())
	{
		if (!panelStart->getBounds().contains(this->gui.getMousePos()))
			panelStart->setColor(panelStart->getBasic());

		if (panelStart->getBounds().contains(this->gui.getMousePos()))
			panelStart->setColor(panelStart->getIntersect());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (panelStart->getBounds().contains(this->gui.getMousePos()))
				panelStart->setColor(panelStart->getClick());
	}
	
		if (!panelDisconnect->getBounds().contains(this->gui.getMousePos()))
			panelDisconnect->setColor(panelDisconnect->getBasic());

		if (panelDisconnect->getBounds().contains(this->gui.getMousePos()))
			panelDisconnect->setColor(panelDisconnect->getIntersect());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (panelDisconnect->getBounds().contains(this->gui.getMousePos()))
				panelDisconnect->setColor(panelDisconnect->getClick());

		if ((gui.getTypeGame() != "") && (gui.getBasicVariable() > NONE) && (gui.getPlayer() > NONE))
		{
			this->panelStart->setColor(panelStart->getBasic());
		}


		if (this->panelStart->getCurrentColor() != panelStart->getUnableClick())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				if (this->panelStart->getBounds().contains(this->gui.getMousePos()))
				{
					gui.getWindow()->waitEvent(ev);
					if (ev.type == sf::Event::MouseButtonReleased)
					{
						this->deletePanel();
						this->gui.startStatus() = true;
						this->online->ClientSendPacket("START_STATUS", gui.startStatus());
					}
				}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->panelDisconnect->getBounds().contains(this->gui.getMousePos()))
		{
			gui.getWindow()->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				this->deletePanel();
				online->ClientSendPacket("CONNECT", online->getClientStatus());
				online->getLogOut() = true;
			}
		}
}

void Multiplayer::panelUpdate()
{
	if (gui.getTypeGame() != "")
		this->panelText[G_TYPE_I]->setString(gui.getTypeGame());
	if (gui.getBasicVariable() > NONE)
		this->panelText[TIME_I]->setString(std::to_string(gui.getBasicVariable() / 60) + " minuts");
	if (gui.getPlayer() == FIRST_PLAYER)
		this->panelText[PLAYER_I]->setString("First player");
	else if (gui.getPlayer() == SECOND_PLAYER)
		this->panelText[PLAYER_I]->setString("Second player");

	this->buttonPanelUpdate();

}



void Multiplayer::buttonUpdate()
{

	for (auto i : this->button)
	{
		if (!i->getBounds().contains(this->gui.getMousePos()))
			i->setColor(i->getBasic());

		if (i->getBounds().contains(this->gui.getMousePos()))
			i->setColor(i->getIntersect());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (i->getBounds().contains(this->gui.getMousePos()))
				i->setColor(i->getClick());
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button[JOIN]->getBounds().contains(this->gui.getMousePos()))
		{
			gui.getWindow()->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				online->IsConnectionVariable(true);
				online->ClientSendPacket("CONNECT", online->getClientStatus());
				this->createPanel();
			}
		}

	if (this->online->getClient() == false)
	{
		panel = false;
		delete panelStart;
		delete panelDisconnect;
		for (auto i : this->panelText)
		{
			delete i;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button[HOST]->getBounds().contains(this->gui.getMousePos()))
		{
			gui.getWindow()->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
					this->online->HostingVariable(true);
					this->gui.getGameState() = TYPE_GAME;
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button[BACK]->getBounds().contains(this->gui.getMousePos()))
		{
			gui.getWindow()->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				this->gui.getGameState() = MAIN_MENU;
			}
		}
}

void Multiplayer::update()
{
	this->gui.mousePosition();
	this->keyboardUpdate();
	if (panel == false)
	{
		this->lineEditsUpdate();
		this->buttonUpdate();
	}
	if (panel == true)
	this->panelUpdate();
	if (gui.startStatus() == true)
	this->startGame();
}

void Multiplayer::render(sf::RenderTarget* target)
{
	target->draw(gui.getBackground());
	target->draw(lineEdit[IP].shape);
	target->draw(lineEdit[IP].text);
	target->draw(lineEdit[IP].textName);
	target->draw(lineEdit[PORT].shape);
	target->draw(lineEdit[PORT].text);
	target->draw(lineEdit[PORT].textName);
	this->renderButton();
	if (panel == true)
		this->renderPanel(gui.getTarget());

}

void Multiplayer::renderPanel(sf::RenderTarget* target)
{
	this->waitingPanel->render(target);
	this->panelStart->render(target);
	this->panelDisconnect->render(target);
	for (auto i : this->panelText)
	{
		target->draw(*i);
	}
}

void Multiplayer::renderButton()
{
	for (auto i : this->button)
	{
		i->render(this->gui.getWindow());
	}
}

void Multiplayer::startGame()
{
	this->online->gameOnlineStatus(true);
	this->start = new Start(gui, online);
	while (gui.startStatus() == true)
	{
		this->gui.getWindow()->clear();
		this->start->update();
		this->start->render(gui.getWindow());
		this->gui.getWindow()->display();
	}
	if (gui.getGameState() == MULTIPLAYER)
	this->createPanel();
}
