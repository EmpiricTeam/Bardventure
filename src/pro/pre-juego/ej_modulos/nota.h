#pragma once
#ifndef NOTA_H
#define NOTA_H

#include <SFML/Graphics.hpp>
#include "Motor/MySprite.h"
#include "Motor/Motor2D.h"

class Nota {
private:
    MySprite* sprite;
    sf::Vector2f puntoInicial;
    sf::Vector2f puntoFinal;

public:

    Nota(const std::string& tex, Motor2D *motor);
    Nota(const std::string& tex, const sf::Vector2f& inicial, Motor2D *motor);
    sf::Vector2f obtenerPuntoInicial(Motor2D &motor);
    sf::Vector2f obtenerPuntoFinal(Motor2D &motor);

    MySprite** devolverSprite();
    MySprite* devolverSpriteSinPunt();
    sf::Vector2f* devolverInicial();
    sf::Vector2f* devolverFinal();

};

#endif