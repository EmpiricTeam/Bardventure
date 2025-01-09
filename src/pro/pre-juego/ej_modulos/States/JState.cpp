#include "JState.h"

//Constructor y destructor
JState::JState()
{
    this->quit = false;
}

JState::~JState()
{

}

//Funciones

const bool &JState::getQuit() const
{
    return this->quit;
}

void JState::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        this->quit = true;
    }
}

void JState::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(Motor2D::getInstance()->getVentana());
    this->mousePosView = Motor2D::getInstance()->getVentana().mapPixelToCoords(sf::Mouse::getPosition(Motor2D::getInstance()->getVentana()));
}

