#include "Panels.h"

Panels::Panels(Gui& gui)
	:gui(gui)
{
	if (!this->texture.loadFromFile(BACKGROUND))
	{
		throw"ERROR";
	}
	this->escapePanel.setTexture(texture);
	this->escapePanel.setScale(0.25, 0.75);
	this->escapePanel.setPosition(gui.getWIDTH()* 0.375, gui.getHEIGHT() * 0.125);
	this->escapePanel.getScale();
}

Panels::~Panels()
{

}

void Panels::update()
{

}

void Panels::render(sf::RenderTarget* target)
{
	target->draw(escapePanel);

}




float Panels::getSize_x()const
{
	return this->escapePanel.getScale().x;
}

float Panels::getSize_y() const
{
	return this->escapePanel.getScale().y;
}

short Panels::getPosition_x() const
{
	return this->escapePanel.getPosition().x;
}

short Panels::getPosition_y() const
{
	return this->escapePanel.getPosition().y;
}

