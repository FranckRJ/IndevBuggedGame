#include "editLevelState.hpp"
#include "blockManager.hpp"
#include "global.hpp"

editLevelStateClass::editLevelStateClass(std::string levelName)
{
    view.setSize(WIDTH_SCREEN, HEIGHT_SCREEN);
    view.setCenter(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

    currentLevelName = levelName;
    levelManagerClass::loadBasicLevelFromFile(infoForLevel, levelName);
    playerSprite.setSize(sf::Vector2f(40, 80));
    playerSprite.setFillColor(sf::Color::Blue);
    playerSprite.setPosition(infoForLevel.playerStartPosition.x, infoForLevel.playerStartPosition.y);

    idCurrentBlock = 0;
    newIdForCurrentBlock();
    currentBlock.sprite.setPosition(-SIZE_BLOCK * 2, -SIZE_BLOCK * 2);
}

void editLevelStateClass::update(sf::RenderWindow& window)
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Subtract)
            {
                ++idCurrentBlock;
                newIdForCurrentBlock();
            }
            else if(event.key.code == sf::Keyboard::Add)
            {
                --idCurrentBlock;
                newIdForCurrentBlock();
            }
            else if(event.key.code == sf::Keyboard::S)
            {
                levelManagerClass::saveBasicLevel(infoForLevel, currentLevelName);
            }
            else if(event.key.code == sf::Keyboard::L)
            {
                infoForLevel.mapOfGame.clear();
                levelManagerClass::loadBasicLevelFromFile(infoForLevel, currentLevelName);
                playerSprite.setPosition(infoForLevel.playerStartPosition.x, infoForLevel.playerStartPosition.y);
            }
        }
    }

    mouseMoveHere(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        leftClickHere(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        rightClickHere(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        moveView(-10, 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        moveView(10, 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        moveView(0, -10);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        moveView(0, 10);
    }
}

void editLevelStateClass::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(200, 200, 200));
    window.setView(view);
    window.draw(playerSprite);

    for(int x = (view.getCenter().x - (WIDTH_SCREEN / 2)) / SIZE_BLOCK; x < (view.getCenter().x + (WIDTH_SCREEN / 2)) / SIZE_BLOCK; ++x)
    {
        for(int y = (view.getCenter().y - (HEIGHT_SCREEN / 2)) / SIZE_BLOCK; y < (view.getCenter().y + (HEIGHT_SCREEN / 2)) / SIZE_BLOCK; ++y)
        {
            auto block = infoForLevel.mapOfGame.find(point(x, y));
            if(block != infoForLevel.mapOfGame.end())
            {
                window.draw(block->second.sprite);
            }
        }
    }

    window.draw(currentBlock.sprite);
}

void editLevelStateClass::leftClickHere(int x, int y)
{
    if(x >= 0 && y >= 0 && x < WIDTH_SCREEN && y < HEIGHT_SCREEN)
    {
        x = (currentBlock.sprite.getPosition().x / SIZE_BLOCK);
        y = (currentBlock.sprite.getPosition().y / SIZE_BLOCK);

        infoForLevel.mapOfGame[point(x, y)] = currentBlock;
    }
}

void editLevelStateClass::rightClickHere(int x, int y)
{
    if(x >= 0 && y >= 0 && x < WIDTH_SCREEN && y < HEIGHT_SCREEN)
    {
        x += view.getCenter().x - (WIDTH_SCREEN / 2);
        y += view.getCenter().y - (HEIGHT_SCREEN / 2);
        infoForLevel.mapOfGame.erase(point(x / SIZE_BLOCK, y / SIZE_BLOCK));
    }
}

void editLevelStateClass::mouseMoveHere(int x, int y)
{
    x += view.getCenter().x - (WIDTH_SCREEN / 2);
    y += view.getCenter().y - (HEIGHT_SCREEN / 2);
    x /= SIZE_BLOCK;
    y /= SIZE_BLOCK;

    currentBlock.sprite.setPosition(SIZE_BLOCK * x, SIZE_BLOCK * y);
}

void editLevelStateClass::newIdForCurrentBlock()
{
    if(idCurrentBlock < 0)
    {
        idCurrentBlock = blockManagerClass::getNumberOfBlock() - 1;
    }
    else if(idCurrentBlock >= blockManagerClass::getNumberOfBlock())
    {
        idCurrentBlock = 0;
    }

    currentBlock = blockManagerClass::getBasicBlockForBlockNumber(idCurrentBlock);
}

void editLevelStateClass::moveView(int x, int y)
{
    view.move(x, y);

    if(view.getCenter().x < infoForLevel.limitOfGame.left + (WIDTH_SCREEN / 2))
    {
        view.setCenter(infoForLevel.limitOfGame.left + (WIDTH_SCREEN / 2), view.getCenter().y);
    }
    else if(view.getCenter().x > infoForLevel.limitOfGame.left + infoForLevel.limitOfGame.width - (WIDTH_SCREEN / 2))
    {
        view.setCenter(infoForLevel.limitOfGame.left + infoForLevel.limitOfGame.width - (WIDTH_SCREEN / 2), view.getCenter().y);
    }

    if(view.getCenter().y < infoForLevel.limitOfGame.top + (HEIGHT_SCREEN / 2))
    {
        view.setCenter(view.getCenter().x, infoForLevel.limitOfGame.top + (HEIGHT_SCREEN / 2));
    }
    else if(view.getCenter().y > infoForLevel.limitOfGame.top + infoForLevel.limitOfGame.height - (HEIGHT_SCREEN / 2))
    {
        view.setCenter(view.getCenter().x, infoForLevel.limitOfGame.top + infoForLevel.limitOfGame.height - (HEIGHT_SCREEN / 2));
    }
}
