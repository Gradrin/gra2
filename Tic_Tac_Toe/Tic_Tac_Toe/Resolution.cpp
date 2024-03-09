#include "Resolution.h"


void Resolution::addButtons()
{
	this->button[R_3840x2160] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.075, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "3840 x 2160", 26);
	this->button[R_2560x1440] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.225, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "2560 x 1440", 26);
	this->button[R_1920x1080] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.375, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "1920 x 1080", 26);
	this->button[R_1024x768] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.525, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "1024 x 768", 26);
	this->button[R_800x600] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.675, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "800 x 600", 26);
	this->button[BACK] = new Button(gui.getFont(), (gui.getWIDTH() / 2) - (gui.getWIDTH() * 0.3 / 2), gui.getHEIGHT() * 0.825, gui.getWIDTH() * 0.3, gui.getHEIGHT() * 0.1, "BACK", 26);
}

Resolution::Resolution(Gui& gui)
	:gui(gui)
{
	addButtons();
}


Resolution::~Resolution()
{
	for (auto i : this->button)
	{
		delete i;
	}
}



void Resolution::keyboardUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gui.getWindow()->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			this->gui.getGameState() = MAIN_MENU;
		}
	}

	while (this->gui.getWindow()->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->gui.getWindow()->close();
	}
}

void Resolution::buttonFunction(const int& width, const int& height)
{
		gui.getWindow()->waitEvent(ev);
		if (ev.type == sf::Event::MouseButtonReleased)
		{
			this->strim.open(WINDOW);

			strim << "Tic_Tac_Toe\n";
			strim << 30 << "\n";
			strim << 0 << "\n";

			this->strim.close();
			gui.getWindow()->setSize(sf::Vector2u(width, height));
		}
}

void Resolution::buttonUpdate()
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
		if (this->button[R_3840x2160]->getBounds().contains(this->gui.getMousePos()))
		{
			buttonFunction(3840, 2160);
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button[R_2560x1440]->getBounds().contains(this->gui.getMousePos()))
		{
			buttonFunction(2560, 1440);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button[R_1920x1080]->getBounds().contains(this->gui.getMousePos()))
		{
			buttonFunction(1920, 1080);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button[R_1024x768]->getBounds().contains(this->gui.getMousePos()))
		{
			buttonFunction(1024, 768);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button[R_800x600]->getBounds().contains(this->gui.getMousePos()))
		{
			buttonFunction(800, 600);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button[BACK]->getBounds().contains(this->gui.getMousePos()))
			this->gui.getGameState() = MAIN_MENU;
}

void Resolution::update()
{
	gui.mousePosition();
	this->keyboardUpdate();
	this->buttonUpdate();
}

void Resolution::render(sf::RenderTarget* target)
{
	target->draw(gui.getBackground());
	this->renderButton();
}

void Resolution::renderButton()
{
	for (auto i : this->button)
	{
		i->render(this->gui.getWindow());
	}
}
