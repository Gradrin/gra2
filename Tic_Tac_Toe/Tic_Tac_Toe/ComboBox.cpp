#include "ComboBox.h"


ComboBox::ComboBox(sf::Font font, int x_position, int y_position, int x_size, int y_size, std::string  str_text, std::vector<std::string> buttonsNames, int text_size, int amount)
	:font(font), x_position(x_position), y_position(y_position), x_size(x_size), y_size(y_size), str_text(str_text), buttonsNames(buttonsNames), text_size(text_size), amount(amount)
{
	this->isOpen = false;

	this->shape.setPosition(x_position, y_position);
	this->shape.setSize(sf::Vector2f(x_size, y_size));
	this->shape.setFillColor(sf::Color(70, 70, 70, 200));
	this->shape.getGlobalBounds();

	this->font = font;
	this->text.setFont(this->font);
	this->text.setString(str_text);

	this->text.setPosition(this->shape.getPosition().x
		+ (this->shape.getGlobalBounds().width / 2.f)
		- this->text.getGlobalBounds().width / 2.f, this->shape.getPosition().y
		+ (this->shape.getGlobalBounds().height / 2.f)
		- this->text.getGlobalBounds().height / 2.f);

	this->text.setCharacterSize(text_size);
	this->text.setFillColor(sf::Color::Red);


	if (!this->spriteTexture.loadFromFile(BOX))
	{
		throw"ERROR";
	}

	this->sprite.setTexture(this->spriteTexture);
	this->sprite.setPosition(shape.getPosition().x + shape.getSize().x / 2, shape.getPosition().y - shape.getSize().y*0.775 );
	this->sprite.setScale(0.2, 0.2);

}

ComboBox::~ComboBox()
{
	buttons.clear();
	for (auto i : this->buttons)
	{
		delete i;
	}
}

bool& ComboBox::Status()
{
	return this->isOpen;
}

void ComboBox::AddButtons()
{
	for (int i = 0; i < amount; i++)
	{
		this->buttons.push_back(new Button(font, x_position, i * y_size + y_position + y_size, x_size, y_size, buttonsNames[i], 26));
	}
}

void ComboBox::deleteButtons()
{
	buttons.clear();
	for (auto i : this->buttons) 
	{
		delete i;
	}
}


void ComboBox::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
	if (Status() == false)
		target->draw(sprite);
}



void ComboBox::boxSetString(const sf::String& text)
{
	this->text.setString(text);
}

const sf::Color& ComboBox::getBasicColor(int& number) const
{
	return this->buttons[number]->getBasic();
}

const sf::Color& ComboBox::getIntersectColor(int& number) const
{
	return this->buttons[number]->getIntersect();
}

const sf::Color& ComboBox::getClickColor(int& number) const
{
	return this->buttons[number]->getClick();
}

void ComboBox::setColor(int& number, const sf::Color& color)
{
		this->buttons[number]->setColor(color);
}

const int& ComboBox::getSize() const
{
	return this->amount;
}


const sf::FloatRect& ComboBox::buttonGetBounds(int& number) const
{
	return this->buttons[number]->getBounds();
}

 sf::String ComboBox::buttonGetText(int& number)
{
	return this->buttons[number]->getText();
}



const sf::FloatRect& ComboBox::getBounds() const
{
	return this->shape.getGlobalBounds();
}

sf::String ComboBox::getBoxName()
{
	return this->text.getString();
}

void ComboBox::buttonsRender(int amount, sf::RenderTarget* target)
{
	for (int i = 0; i < amount; i++)
	{
		this->buttons[i]->render(target);
	}
}
