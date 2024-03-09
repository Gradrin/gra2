#include "TypeGame.h"


void TypeGame::initVariables()
{

}

void TypeGame::addBoxs()
{
	std::vector<std::string> buttonsName = { "BASIC","BEST OF THREE","BEST OF FIVE","BEST OF SEVEN" };
	std::vector<std::string> timeName = { "UNLIMITED","1","3","5","10","15","20","30"};
	std::vector<std::string> choicePlayer = { "FIRST PLAYER", "SECOND PLAYER" };

	this->box[TYPE_GAME] = new ComboBox(gui.getFont(),gui.getWIDTH() / 2 *0.1, gui.getHEIGHT() * 0.15, gui.getWIDTH() * 0.25, gui.getHEIGHT() * 0.08, "TYPE GAME", buttonsName, 26, 4);
	this->box[TIME] = new ComboBox(gui.getFont(), gui.getWIDTH() / 2*1.4, gui.getHEIGHT() * 0.15, gui.getWIDTH() * 0.25, gui.getHEIGHT() * 0.08, "TIME GAME", timeName, 26, 8);
	this->box[CHOICE_PLAYER] = new ComboBox(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.25 / 2), gui.getHEIGHT() * 0.35, gui.getWIDTH() * 0.25, gui.getHEIGHT() * 0.08, "CHOICE PLAYER", choicePlayer, 26, 2);

	this->flag[TYPE_GAME] = false;
	this->flag[TIME] = false;
	this->flag[CHOICE_PLAYER] = false;
}

void TypeGame::addButtons()
{
	this->button[START] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.7, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "START", 26);
	this->button[BACK] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.825, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "BACK", 26);

	this->button[START]->setColor(button[START]->getUnableClick());
}

TypeGame::TypeGame(Gui& gui, Online* online)
	:gui(gui), online(online)
{
	this->initVariables();
	this->addButtons();
	this->addBoxs();
}

TypeGame::~TypeGame()
{
	for (auto i : this->button)
	{
		delete i;
	}
	for (auto i : this->box)
	{
		delete i;
	}
}



void TypeGame::keyUpdate()
{

	while (this->gui.getWindow()->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->gui.getWindow()->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		for (auto i : this->box)
		{
			i->deleteButtons();
		}
		this->gui.getGameState() = MAIN_MENU;
	}
}

void TypeGame::buttonClick(int& number, int& buttonNumber, sf::String time)
{
	switch (number)
	{
	case TYPE_GAME:
	{
		this->gui.getVariable() = buttonNumber + 1;
		this->gui.getTypeGame() = box[number]->buttonGetText(buttonNumber);
		this->flag[number] = true;
		break;
	}
	case TIME:
	{
		if (buttonNumber == 0)
		{
			gui.getBasicVariable() = 0;
			break;
		}
		else
		{
			std::string strStd = time.toAnsiString();
			this->gui.getBasicVariable() = std::stoi(strStd) * 60;
			this->flag[number] = true;
			break;
		}
	}
	case CHOICE_PLAYER:
	{
		this->gui.getPlayer() = buttonNumber + 1;
		if (gui.getPlayer() == FIRST_PLAYER)
			this->gui.getSendPlayer() = SECOND_PLAYER;
		else
			this->gui.getSendPlayer() = FIRST_PLAYER;
		this->flag[number] = true;
		break;
	}
	}	
	if ((flag[TYPE_GAME] == true) && (flag[TIME] == true) && (flag[CHOICE_PLAYER] == true))
	{
		this->button[START]->setColor(button[START]->getBasic());
	}
}



void TypeGame::boxesUpdate()
{

	for (int number = 0; number < SIZE; number++)
	{
				if (box[number]->Status() == false)
			box[number]->deleteButtons();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->box[number]->getBounds().contains(this->gui.getMousePos()))
			{
				gui.getWindow()->waitEvent(ev);
				if (ev.type == sf::Event::MouseButtonReleased)
				{
					for (int i = 0; i < SIZE; i++)
					{
						if ((box[i]->Status() == true) && (i != number))
						{
							this->box[i]->Status() = false;
							this->flag[i] = false;
						}
					}
					if (box[number]->Status() == false)
					{
						this->box[number]->Status() = true;
						this->box[number]->AddButtons();
					}		
				}
			}
		}
		if (box[number]->Status() == true)
		{
			for (int buttonNumber = 0; buttonNumber < box[number]->getSize(); buttonNumber++)
			{
				if (!this->box[number]->buttonGetBounds(buttonNumber).contains(this->gui.getMousePos()))
					this->box[number]->setColor(buttonNumber, this->box[number]->getBasicColor(buttonNumber));

				if (this->box[number]->buttonGetBounds(buttonNumber).contains(this->gui.getMousePos()))
					this->box[number]->setColor(buttonNumber, this->box[number]->getIntersectColor(buttonNumber));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (this->box[number]->buttonGetBounds(buttonNumber).contains(this->gui.getMousePos()))
					{
						this->box[number]->setColor(buttonNumber, this->box[number]->getClickColor(buttonNumber));
						gui.getWindow()->waitEvent(ev);
						if (ev.type == sf::Event::MouseButtonReleased)
						{
							this->box[number]->setColor(buttonNumber, this->box[number]->getClickColor(buttonNumber));
							this->box[number]->boxSetString(box[number]->buttonGetText(buttonNumber));
							this->buttonClick(number,buttonNumber,box[number]->buttonGetText(buttonNumber));
							this->box[number]->Status() = false;
						}
					}
					else if (!this->box[number]->buttonGetBounds(buttonNumber).contains(this->gui.getMousePos()))
					{
							this->box[number]->Status() = false;
							this->flag[number] = false;
					}
				}
			}
		}
		this->box[number]->getBoxName();
	}	
}

void TypeGame::buttonFunctionUpdate(short& number)
{
	if (number == START)
	{
		if (online->getHost() == false)
		{
			this->gui.startStatus() = true;
		}
		else if (online->getHost() == true)
		{
			online->HostSendPacket("VARIABLE", gui.getVariable());
			online->HostSendPacket("GAME_TYPE" + gui.getTypeGame(), 0);
			online->HostSendPacket("BASIC_VARIABLE", gui.getBasicVariable());
			online->HostSendPacket("GET_SEND_PLAYER", gui.getSendPlayer());
		}
	}
	else
	{
		this->gui.getGameState() = MAIN_MENU;
	}
}

void TypeGame::buttonsUpdate()
{
	short number = 0;
	for (auto i : this->button)
	{
		if (i->getCurrentColor() != i->getUnableClick())
		{
			if (!i->getBounds().contains(this->gui.getMousePos()))
				i->setColor(i->getBasic());

			if (i->getBounds().contains(this->gui.getMousePos()))
				i->setColor(i->getIntersect());

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				if (i->getBounds().contains(this->gui.getMousePos()))
				{
					this->gui.getWindow()->waitEvent(ev);
					if (ev.type == sf::Event::MouseButtonReleased)
					{
						i->setColor(i->getClick());
						buttonFunctionUpdate(number);
					}
				}
		}
		number++;
	}
}

void TypeGame::update()
{
	
	this->gui.mousePosition();
	this->keyUpdate();
	this->boxesUpdate();
	this->buttonsUpdate();
	if (gui.startStatus() == true)
		this->startGame(gui.getVariable());
}

void TypeGame::startGame(short &variable)
{
	this->start[variable] = new Start(gui, online);
	while (gui.startStatus() == true)
	{
		this->gui.getWindow()->clear();
		this->start[variable]->update();
		this->start[variable]->render(gui.getWindow());
		this->gui.getWindow()->display();
	}
	this->online->gameOnlineStatus(false);
}

void TypeGame::render(sf::RenderTarget* target)
{
	target->draw(gui.getBackground());
	this->renderBoxes();
	this->renderButton();
}

void TypeGame::renderBoxes()
{
	this->box[TYPE_GAME]->render(gui.getTarget());
	this->box[TIME]->render(gui.getTarget());
	this->box[CHOICE_PLAYER]->render(gui.getTarget());

	for (auto boxNumber : this->box)
	{
		if (boxNumber->Status() == true)
		{
			boxNumber->buttonsRender(boxNumber->getSize(), gui.getWindow());
		}
	}
}

void TypeGame::renderButton()
{	
	this->button[BACK]->render(this->gui.getWindow());
	this->button[START]->render(this->gui.getWindow());
}

