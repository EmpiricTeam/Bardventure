#ifndef FLECHA_H
#define FLECHA_H

#include <SFML/Graphics.hpp>
#include "PosicionInterpolada.h"
#include "Motor/MySprite.h"

class Flecha {

private:
    MySprite *sprite;
    sf::Vector2f inicial;
    sf::Vector2f direccion;
    sf::FloatRect hitboxflecha;
    PosicionInterpolada posicionInterpolada;

public:
    
    sf::FloatRect getHitbox();

    Flecha(const std::string &textura, const sf::Vector2f &dir, const sf::Vector2f &ini);

    void moverFlecha(float deltaT);

    PosicionInterpolada *getPosicionInterpolada();

    sf::Vector2f *getdireccion();

    void actualizarHitbox(sf::FloatRect hitbox);

    MySprite** devolverSprite();




};

#endif