#ifndef JSTATE_H
#define JSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <fstream>
#include <sstream>
#include <random>
#include <cstdlib> // Para std::rand() y std::srand()
#include <ctime>   // Para std::time()
#include <iostream>
#include <chrono>
#include <string>
#include "../Motor/MySprite.h"
#include "../Motor/Motor2D.h"
#include <vector>
#include <stack>
#include <map>

class JState
{
private:
    

protected:
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::vector<sf::Texture> textures;

public:
    JState();
    virtual ~JState();

    const bool& getQuit() const;

    //Funciones 
    virtual void checkForQuit();

    virtual void endState() = 0;
    virtual void updateMousePositions();
    virtual void updateKeybinds(const float& dt) = 0;
    virtual void update(const float& dt, char& accion) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif // JSTATE_H
