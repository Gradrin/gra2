#include "Start.h"


//-----------CLASS BOARD------------------//

bool Board::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the gameMap size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}




//-----------CLASS START------------------//



void Start::initVariables()
{

    this->quadSize = 32;
    this->height = 22;
    this->width = 22;

    escPanel = false;
    resolutionPanel = false;

    this->timeVariable = gui.getBasicVariable();
    this->timeVariable2 = gui.getBasicVariable();

    if (gui.getBasicVariable() > 0)
    {
        time = sf::seconds(timeVariable);
        time2 = sf::seconds(timeVariable2);
    }
}

void Start::functionForText(typeText number,std::string &text,sf::Color color,double size_x,double size_y)
{
    this->text[number].setFont(gui.getFont());
    this->text[number].setString(text);
    this->text[number].setCharacterSize(38);
    this->text[number].setFillColor(color);
    this->text[number].setPosition(sf::Vector2f(gui.getWIDTH() * size_x, gui.getHEIGHT() * size_y));
}



void Start::addText()
{
    if (online->GameOnline() == false)
        this->player = "   POINTS\nPlayer 1 = \nPlayer 2 =\n ";
    else if (online->GameOnline() == true)
        this->player = "   POINTS\n      You = \nEnemy =\n ";

    this->pointsPlayer_1 = std::to_string(circlePoints);
    this->pointsPlayer_2 = std::to_string(circlePoints);
    this->watch = "TIME";
    this->firstTime = "";
    this->secondTime = "";

 
    this->functionForText(PLAYERS, player, sf::Color::Blue, 0.76, 0.6);
    this->functionForText(PLAYER_POINTS, pointsPlayer_1, sf::Color::Green, 0.91, 0.66);
    this->functionForText(PLAYER_2_POINTS, pointsPlayer_2, sf::Color::Red, 0.91, 0.73);
    if (gui.getTypeGame() == "BASIC")
        this->functionForText(GAME_TYPE, gui.getTypeGame(), sf::Color::Red, 0.8, 0.1);
    else
        this->functionForText(GAME_TYPE, gui.getTypeGame(), sf::Color::Red, 0.73, 0.1);
    this->functionForText(CLOCK, watch, sf::Color::White, 0.80, 0.3);
    if (gui.getBasicVariable() == 0)
    {
        this->functionForText(FIRST_TIME, firstTime, sf::Color::White, 0.76, 0.35);
        this->functionForText(SECOND_TIME, secondTime, sf::Color::White, 0.76, 0.4);
    }
    else if (gui.getBasicVariable() > 0)
    {
        this->functionForText(FIRST_TIME, firstTime, sf::Color::White, 0.80, 0.35);
        this->functionForText(SECOND_TIME, secondTime, sf::Color::White, 0.80, 0.4);
    }
}

void Start::initBoard()
{

    if (online->GameOnline() == true)
    {
     
        if (gui.getPlayer() == FIRST_PLAYER)
        {
            if (online->getHost() == true)
                online->changePlayer(HOST);
            else
                online->changePlayer(CLIENT);
        }
        else if (gui.getPlayer() == SECOND_PLAYER)
        {
            if (online->getHost() == true)
                online->changePlayer(CLIENT);
            else
                online->changePlayer(HOST);
        }
    }
    else
        this->quad = gui.getPlayer();

    int gameMap[tableSize];
    int i = 0;
    std::string linia;
    this->basicBoard.open(BOARD);
    while (getline(basicBoard, linia))
    {
        gameMap[i] = EMPTY;
        i++;
    }
    this->basicBoard.close();
    this->board.setPosition((float)quadSize, (float)quadSize);
}

void Start::addButton()
{
    if (online->GameOnline() == false)
        this->button["LEAVE"] = new Button(gui.getFont(), gui.getWIDTH() * 0.74, gui.getHEIGHT() * 0.85, gui.getWIDTH() * 0.2, gui.getHEIGHT() * 0.1, "EXIT", 26);
    else if (online->GameOnline() == true)
        this->button["DISCONNECT"] = new Button(gui.getFont(), gui.getWIDTH() * 0.74, gui.getHEIGHT() * 0.85, gui.getWIDTH() * 0.2, gui.getHEIGHT() * 0.1, "DISCONNECT", 26);
}

Start::Start(Gui& gui, Online* online)
    :gui(gui),online(online)
{
    this->initVariables();
    this->addText();
    this->initBoard();
    this->addButton();
    escapePanel = new Panels(gui);
}

Start::~Start()
{
    delete this->escapePanel;
    if (online->GameOnline() == false)
        this->button.erase("LEAVE");
    else
        this->button.erase("DISCONNECT");
}

void Start::points(sign SIGN)
{
    if (online->GameOnline() == false)
    {
        if (SIGN == CIRCLE)
            this->circlePoints++;
        else if (SIGN == CROSS)
            this->crossPoints++;
    }
    else
    {
        if ((SIGN == CIRCLE) && (gui.getPlayer() == FIRST_PLAYER))
            this->circlePoints++;
        else if ((SIGN == CROSS) && (gui.getPlayer() == FIRST_PLAYER))
            this->crossPoints++;
        else if ((SIGN == CIRCLE) && (gui.getPlayer() == SECOND_PLAYER))
            this->crossPoints++;
        else if ((SIGN == CROSS) && (gui.getPlayer() == SECOND_PLAYER))
            this->circlePoints++;
    }

    if (gui.getPlayer() == CIRCLE)
    {
        this->gui.getPlayer() = CROSS;
        this->quad = gui.getPlayer();
    }
    else
    {
        this->gui.getPlayer() = CIRCLE;
        this->quad = gui.getPlayer();
    }

    for (int i = 0; i < tableSize; ++i)
    {
        gameMapUpdate[i] = EMPTY;
    }
    if ((circlePoints == gui.getVariable()) && (gui.getVariable() > BASIC))
        this->gui.getGameState() = GAMESTATS;
    else if ((crossPoints == gui.getVariable()) && (gui.getVariable() > BASIC))
        this->gui.getGameState() = GAMESTATS;
}


void Start::updateKeyboard()
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
                if (escPanel == false)
                {
                    this->button["RESUME"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 2, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "RESUME", 26);
                    this->button["RESOLUTION"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 3.6, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "RESOLUTION", 26);
                    this->button["EXIT"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 5.25, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "EXIT", 26);
                    escPanel = true;
                }
                else
                {
                    this->updateButtonPanel();
                    escPanel = false;
                }
            }
        }
     
}

void Start::updateButtonPanel()
{
    this->button.erase("RESUME");
    this->button.erase("RESOLUTION");
    this->button.erase("EXIT");
        escPanel = false;
}

void Start::updateButton()
{
    std::cout<<online->GameOnline()<<std::endl;
    for (auto i : this->button)
    {
        if (!i.second->getBounds().contains(this->gui.getMousePos()))
            i.second->setColor(i.second->getBasic());

        if (i.second->getBounds().contains(this->gui.getMousePos()))
            i.second->setColor(i.second->getIntersect());

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if (i.second->getBounds().contains(this->gui.getMousePos()))
            {
                i.second->setColor(i.second->getClick());
            }
    }

    if (escPanel == true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->button["RESUME"]->getBounds().contains(this->gui.getMousePos()))
            {
                gui.getWindow()->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    updateButtonPanel();
                    gui.getWindow()->waitEvent(ev);
                }

            }
            else if (this->button["EXIT"]->getBounds().contains(this->gui.getMousePos()))
            {
                gui.getWindow()->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    this->updateButtonPanel();
                    this->gui.startStatus() = false;
                }
            }
            else if (this->button["RESOLUTION"]->getBounds().contains(this->gui.getMousePos()))
            {
                gui.getWindow()->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    updateButtonPanel();
                    this->button["3840 x 2160"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 1.5, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.08, "3840 x 2160", 26);
                    this->button["2560 x 1440"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 2.4, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.08, "2560 x 1440", 26);
                    this->button["1920 x 1080"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 3.3, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.08, "1920 x 1080", 26);
                    this->button["1024 x 768"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 4.2, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.08, "1024 x 768", 26);
                    this->button["800 x 600"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 5.1, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.08, "800 x 600", 26);
                    this->button["BACK"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 6.0, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.08, "BACK", 26);
                    this->resolutionPanel = true;
                }
            }
        }
    }

    if (resolutionPanel == true)
    {
        Resolution resolution(gui);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->button["3840 x 2160"]->getBounds().contains(this->gui.getMousePos()))
            {
                resolution.buttonFunction(2560, 1440);
            }
            if (this->button["2560 x 1440"]->getBounds().contains(this->gui.getMousePos()))
            {
                resolution.buttonFunction(2560, 1440);
            }
            if (this->button["1920 x 1080"]->getBounds().contains(this->gui.getMousePos()))
            {
                resolution.buttonFunction(1920, 1080);
            }
            if (this->button["1024 x 768"]->getBounds().contains(this->gui.getMousePos()))
            {
                resolution.buttonFunction(1024, 1080);
            }
            if (this->button["800 x 600"]->getBounds().contains(this->gui.getMousePos()))
            {
                resolution.buttonFunction(800, 600);
            }
            if (this->button["BACK"]->getBounds().contains(this->gui.getMousePos()))
            {
                gui.getWindow()->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    resolutionPanel = false;
                    escPanel = true;
                    this->button.erase("3840 x 2160");
                    this->button.erase("2560 x 1440");
                    this->button.erase("1920 x 1080");
                    this->button.erase("1024 x 768");
                    this->button.erase("800 x 600");
                    this->button.erase("BACK");
                    this->button["RESUME"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 2, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "RESUME", 26);
                    this->button["RESOLUTION"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 3.6, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "RESOLUTION", 26);
                    this->button["EXIT"] = new Button(gui.getFont(), escapePanel->getPosition_x() + (gui.getWIDTH() * escapePanel->getSize_x() * 0.5 - (gui.getWIDTH() * 0.15 * 0.5)), escapePanel->getPosition_y() * 5.25, gui.getWIDTH() * 0.15, gui.getHEIGHT() * 0.1, "EXIT", 26);
                }
            }
        }
    }

    if (online->GameOnline() == false)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if (this->button["LEAVE"]->getBounds().contains(this->gui.getMousePos()))
            {
                gui.getWindow()->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    this->gui.startStatus() = false;

                }
            }
    }
    else
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if (this->button["DISCONNECT"]->getBounds().contains(this->gui.getMousePos()))
            {
                gui.getWindow()->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    this->gui.getVariable() = 0;
                    gui.getGameState() = TYPE_GAME;
                    if (online->getHost() == true)
                        online->hostDisconnet();
                    else if (online->getClient() == true)
                        online->getLogOut() = true;

                }
            }
          
}

void Start::updateBoard()
{

    int gameMap[tableSize];
    int x = 0;

    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
        {
            gameMap[x] = gameMapUpdate[x];

       

            if (online->GameOnline() == true)
            {
                if (quad != online->getSign())
                {
                    this->quad = online->getSign();
                    gameMapUpdate[online->getNumberTable()] = quad;
                    if (online->getHost() == true)
                        quad = gui.getPlayer();
                    else if (online->getClient() == true)
                        quad = gui.getPlayer();

                }
            }

            if (online->getTurn() == CLIENT)
            {
                timeVariable = time.asSeconds();
                clock.restart();
            }
            
            if ((this->gui.getMousePos().x >= (i * quadSize + quadSize) &&
                this->gui.getMousePos().x <= ((i + 1) * quadSize + quadSize)) &&
                (this->gui.getMousePos().y >= (j * quadSize + quadSize) &&
                    this->gui.getMousePos().y <= ((j + 1) * quadSize + quadSize)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    gui.getWindow()->waitEvent(ev);
                    if (ev.type == sf::Event::MouseButtonReleased)
                    {
                        if ((this->gameMapUpdate[x] != CROSS) && (this->gameMapUpdate[x] != CIRCLE) && (online->GameOnline() == false))
                        {
 
                            this->gameMapUpdate[x] = this->quad;
                            if (this->quad == CROSS)
                            {
                                timeVariable = time.asSeconds();
                                this->quad = CIRCLE;
                                clock.restart();
                            }
                            else if (this->quad == CIRCLE)
                            {
                                timeVariable2 = time2.asSeconds();
                                this->quad = CROSS;
                                clock2.restart();
                            }
                        }
                        else if ((this->gameMapUpdate[x] != CROSS) && (this->gameMapUpdate[x] != CIRCLE) && (online->getTurn() == HOST) && (online->getHost() == true))
                        {
                            this->quad = gui.getPlayer();
                            this->gameMapUpdate[x] = this->quad;
                            this->online->HostSendPacket("GET_PLAYER", gui.getPlayer());
                            this->online->HostSendPacket("CLIENT", CLIENT);
                            this->online->HostSendPacket("NR_TABLE", x);
                            online->changePlayer(CLIENT);                        
                            timeVariable = time.asSeconds();
                        }
                        else if ((this->gameMapUpdate[x] != CROSS) && (this->gameMapUpdate[x] != CIRCLE) && (online->getTurn() == CLIENT) && (online->getClient() == true))
                        {
                            this->quad = gui.getPlayer();
                            this->gameMapUpdate[x] = this->quad;
                            this->online->ClientSendPacket("GET_PLAYER", gui.getPlayer());
                            this->online->ClientSendPacket("HOST", HOST);
                            this->online->ClientSendPacket("NR_TABLE", x);
                            online->changePlayer(HOST);
                            timeVariable2 = time2.asSeconds();
                        }
                    }
                }
            }
            x++;
        }
    
    if (!board.load(ICONS, sf::Vector2u(quadSize, quadSize), gameMap, width, height))
        std::cout << "ERROR" << "\n";

    
    basicBoard.open(BOARD);
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        basicBoard << gameMapUpdate[i] << "\n";
    }
    basicBoard.close();
}

void Start::updatePlayers()
{
    this->pointsPlayer_1 = std::to_string(circlePoints);
    this->text[PLAYER_POINTS].setString(pointsPlayer_1);

    this->pointsPlayer_2 = std::to_string(crossPoints);
    this->text[PLAYER_2_POINTS].setString(pointsPlayer_2);
}

void Start::functionTime(sf::Time& time, std::string& watch)
{
    if (gui.getBasicVariable() == 0)
    {
        watch = "UNLIMITED";
    }
    else if (time.asSeconds() < 3600)
    {
        float czas = (int)time.asSeconds();
        int minuts = czas / 60;
        int seconds = czas - (int)(minuts) * 60;
        watch = std::to_string(minuts) + " : " + std::to_string(seconds);

    }
    else if (time.asSeconds() < 60)
    {
        watch = "0 : " + std::to_string((int)time.asSeconds());
    }
}

void Start::gameTime()
{
    if (gui.getBasicVariable() > 0)
    {
        if (online->GameOnline() == false)
        {
            if (quad == CROSS)
            {
                time2 = sf::seconds(timeVariable2) - clock2.getElapsedTime();
                time = time;
            }
            else
            {
                time = sf::seconds(timeVariable) - clock.getElapsedTime();
                time2 = time2;
            }
            this->text[FIRST_TIME].setString(secondTime);
            this->text[SECOND_TIME].setString(firstTime);
        }
        else
        {
            if (online->getHost() == true)
            {
                if (online->getTurn() == HOST)
                {
                    time = sf::seconds(timeVariable) - clock.getElapsedTime();
                    timeVariable2 = time2.asSeconds();
                    time2 = time2;
                    clock2.restart();
                }
                else
                {
                    time2 = sf::seconds(timeVariable2) - clock2.getElapsedTime();
                    time = time;
                    clock.restart();
                }
                this->text[FIRST_TIME].setString(firstTime);
                this->text[SECOND_TIME].setString(secondTime);
            }
            else if (online->getClient() == true)
            {
                if (online->getTurn() == CLIENT)
                {
                    time2 = sf::seconds(timeVariable2) - clock2.getElapsedTime();
                    timeVariable = time.asSeconds();
                    time = time;
                    clock.restart();
                }
                else
                {
                    time = sf::seconds(timeVariable) - clock.getElapsedTime();
                    time2 = time2;
                    clock2.restart();
                }
                this->text[FIRST_TIME].setString(secondTime);
                this->text[SECOND_TIME].setString(firstTime);
            }
        }
        this->functionTime(time, firstTime);
        this->functionTime(time2, secondTime);


        if (firstTime == "0 : 0")
        {
            this->points(CROSS);
            this->timeVariable = gui.getBasicVariable();
            this->timeVariable2 = gui.getBasicVariable();
            this->clock.restart();
            this->clock2.restart();
        }

        if (secondTime == "0 : 0")
        {
            this->points(CROSS);
            this->timeVariable = gui.getBasicVariable();
            this->timeVariable2 = gui.getBasicVariable();
            this->clock.restart();
            this->clock2.restart();
        }
    }
    else
    {
        this->text[FIRST_TIME].setString(firstTime);
        this->text[SECOND_TIME].setString(secondTime);
        this->functionTime(time, firstTime);
        this->functionTime(time2, secondTime);
    }
    
}

void Start::update()
{
    this->gameTime();
    this->updateKeyboard();
    this->updateButton();
    this->gui.mousePosition();
    if (escPanel == false)
    this->updateBoard();
    this->checkingBoard();
    this->updatePlayers();
     if (this->gui.getGameState() == GAMESTATS)
        this->renderEndGame();

}

void Start::render(sf::RenderTarget* target)
{
	target->draw(gui.getBackground());
    for (auto i : this->text)
    {
        target->draw(i);
    }
    target->draw(board);
    this->buttonRender();
    if (escPanel == true) 
    {
        buttonsMenuRender();
    }
    if (resolutionPanel == true)
    {
        buttonsResolutionRender();
    }
}

void Start::checkingBoard()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //POINTS FOR X AND O FOR VERTICALL AND HORIZONTALL
            if (gameMapUpdate[j + (i * width)] == CROSS)
            {
                checkingBoardContinued(CROSS, j, i, width);
            }
            else if (gameMapUpdate[j + (i * width)] == CIRCLE)
            {
                checkingBoardContinued(CIRCLE, j, i, width);
            }
        }
    }
}
 
void Start::checkingBoardContinued(sign SIGN, int& j, int& i, const int& width)
    {
    if ((gameMapUpdate[(j + 1) + ((i + 1) * width)] == SIGN)
        && (gameMapUpdate[(j + 2) + ((i + 2) * width)] == SIGN)
        && (gameMapUpdate[(j + 3) + ((i + 3) * width)] == SIGN)
        && (gameMapUpdate[(j + 4) + ((i + 4) * width)] == SIGN))
    {
        this->points(SIGN);
    }
    if ((gameMapUpdate[(j - 1) + ((i + 1) * width)] == SIGN)
        && (gameMapUpdate[(j - 2) + ((i + 2) * width)] == SIGN)
        && (gameMapUpdate[(j - 3) + ((i + 3) * width)] == SIGN)
        && (gameMapUpdate[(j - 4) + ((i + 4) * width)] == SIGN))
    {
        this->points(SIGN);
    }
    if ((gameMapUpdate[(j + 1) + (i * width)] == SIGN)
        && (gameMapUpdate[(j + 2) + (i * width)] == SIGN)
        && (gameMapUpdate[(j + 3) + (i * width)] == SIGN)
        && (gameMapUpdate[(j + 4) + (i * width)] == SIGN))
    {
        this->points(SIGN);
    }
    if ((gameMapUpdate[j + ((i + 1) * width)] == SIGN)
        && (gameMapUpdate[j + ((i + 2) * width)] == SIGN)
        && (gameMapUpdate[j + ((i + 3) * width)] == SIGN)
        && (gameMapUpdate[j + ((i + 4) * width)] == SIGN))
    {
        this->points(SIGN);
    }
}

void Start::renderEndGame()
{
    this->statsWindow = new StatsWindow(online, gui, circlePoints, crossPoints);
    while (this->gui.getGameState() == GAMESTATS)
    {
        this->gui.getWindow()->clear();
        this->statsWindow->update();
        this->statsWindow->render(gui.getWindow());
        this->gui.getWindow()->display();
    }
}

void Start::buttonRender()
{
    if (online->GameOnline() == false)
        button["LEAVE"]->render(gui.getWindow());
    else
        button["DISCONNECT"]->render(gui.getWindow());
}

void Start::buttonsMenuRender()
{
    escapePanel->render(gui.getWindow());
    button["RESUME"]->render(gui.getWindow());
    button["RESOLUTION"]->render(gui.getWindow());
    button["EXIT"]->render(gui.getWindow());
}

void Start::buttonsResolutionRender()
{
    escapePanel->render(gui.getWindow());
    button["3840 x 2160"]->render(gui.getWindow());
    button["2560 x 1440"]->render(gui.getWindow());
    button["1920 x 1080"]->render(gui.getWindow());
    button["1024 x 768"]->render(gui.getWindow());
    button["800 x 600"]->render(gui.getWindow());
    button["BACK"]->render(gui.getWindow());
}

sf::View Start::getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;
}

