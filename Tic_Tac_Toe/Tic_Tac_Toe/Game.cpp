#include "Game.h"



void Game::addButtons()
{

	this->button[TYPE_GAME] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT()*0.15, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "SINGLE PLAYER", 26);
	this->button[MULTIPLAYER] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.3, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "MULTIPLAYER", 26);
	this->button[RESOLUTION] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.45, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "RESOLUTION", 26);
	this->button[INTRODUCTION] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.6, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "INTRODUCTION", 26);
	this->button[EXIT] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.75, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "EXIT", 26);
}

Game::Game()
{

	this->addButtons();
	this->online = new Online(gui);

}

Game::~Game()
{
	for (auto i : this->button)
	{
		delete i;
	}
	delete gui.getWindow();
}

void Game::keyboardUpdate()
{
	while (this->gui.getWindow()->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->gui.getWindow()->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->gui.getWindow()->close();
}

void Game::buttonsClick(short& number)
{
	this->gui.getGameState() = static_cast<GameState>(number);
}


void Game::buttonsUpdate()
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

void Game::update()
{
	this->gui.mousePosition();
	this->keyboardUpdate();
	this->buttonsUpdate();
}

void Game::buttonsRender()
{
	for (auto i : this->button)
	{
		i->render(gui.getWindow());
	}
}

template<typename T>
void Game::statusRenderFunction(GameState _gameState, T* status)
{
	while (gui.getGameState() == _gameState)
	{
		this->gui.getWindow()->clear();
		status->update();
		status->render(gui.getWindow());
		this->gui.getWindow()->display();
	}

}

void Game::statusRender()
{

	switch (gui.getGameState())
	{
	case TYPE_GAME:
	{
		this->gameType = new TypeGame(gui, online);
		statusRenderFunction(gui.getGameState(), gameType);
		break; 
	}
	case MULTIPLAYER: 
	{
		this->multiplayer = new Multiplayer(gui, online, start);
		statusRenderFunction(gui.getGameState(), multiplayer);
		break;
	}
	case RESOLUTION: 
	{
		this->resolution = new Resolution(gui);
		statusRenderFunction(gui.getGameState(), resolution);
		break;
	}
	case INTRODUCTION: 
	{
		this->introduction = new Introduction(gui);
		statusRenderFunction(gui.getGameState(), introduction);
		break;
	}
	case EXIT:
	{
		this->gui.getWindow()->close();
		break;
	}
	}
}

void Game::render()
{
	this->gui.getWindow()->clear();
	this->gui.renderBackground(gui.getTarget());
	this->buttonsRender();
	if (gui.getGameState() != MAIN_MENU)
	this->statusRender();
	this->gui.getWindow()->display();
}

void Game::run()
{
	
	std::thread connectionThread(&Online::ConnectClients, online);
	std::thread forPacked(&Online::packetSystem, online);

	while (this->gui.getWindow()->isOpen())
	{
		this->update();
		this->render();
	}
	connectionThread.join();
	forPacked.join();
}


