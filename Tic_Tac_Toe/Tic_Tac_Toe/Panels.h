#pragma once

#include"Button.h"
#include "resources.h"
#include"Gui.h"

class Panels
{
private:

	Gui& gui;

	sf::Sprite escapePanel;
	sf::Texture texture;

public:
	Panels(Gui& gui);
	~Panels();

	void update();
	void render(sf::RenderTarget* target);


	float getSize_x()const;
	float getSize_y()const;

	short getPosition_x()const;
	short getPosition_y()const;
};
					