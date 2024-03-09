#pragma once
#include"Button.h"
#include"Gui.h"
#include<vector>

class ComboBox
{
private:

	sf::Font font;
	sf::Text text;

	sf::Sprite sprite;
	sf::Texture spriteTexture;

	std::string str_text;


	sf::RectangleShape shape;

	std::vector<Button*>buttons;
	std::vector<std::string>buttonsNames;

	bool isOpen;
	int amount;
	float x_position;
	float y_position;
	float x_size;
	float y_size;
	float text_size;

	sf::Color basic;
	sf::Color intersects;
	sf::Color click;

public:
	ComboBox(sf::Font font, int x_position, int y_position, int x_size, int y_size, std::string  str_text, std::vector<std::string> buttonsNames, int text_size, int amount);
	~ComboBox();

	bool& Status();

	void AddButtons();
	void deleteButtons();

	const sf::FloatRect& buttonGetBounds(int & number )const;
	 sf::String buttonGetText(int& number);
	const sf::FloatRect& getBounds()const;
	 sf::String getBoxName();
	void buttonsRender(int amount, sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

	void boxSetString(const sf::String& text);

	const sf::Color& getBasicColor(int& number)const;
	const sf::Color& getIntersectColor(int& number)const;
	const sf::Color& getClickColor(int& number)const;

	void setColor(int& number, const sf::Color& color);
	const int& getSize()const;


};

