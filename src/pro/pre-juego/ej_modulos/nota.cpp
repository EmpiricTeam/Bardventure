#include "nota.h"


sf::Vector2f Nota::obtenerPuntoInicial(Motor2D &motor){
    sf::Vector2f puntoInicial(0, 0);

    puntoInicial.x = (motor.getSize().x / 2) - 245;
    puntoInicial.y = motor.getSize().y - 163;

    return puntoInicial;
}


sf::Vector2f Nota::obtenerPuntoFinal(Motor2D &motor){
  sf::Vector2f puntoFinal(0, 0);

  puntoFinal.x = 1210;
  puntoFinal.y = motor.getSize().y - 163;

  return puntoFinal;
}

Nota::Nota(const std::string& tex, Motor2D *motor) : sprite(new MySprite(tex))
{
    puntoInicial = obtenerPuntoInicial(*motor);
    puntoFinal = obtenerPuntoFinal(*motor);

    sprite->setPosition(puntoInicial.x, puntoInicial.y);
    sprite->setOrigen(sprite->getHitbox().width / 2, sprite->getHitbox().height / 2);

}

Nota::Nota(const std::string& tex, const sf::Vector2f& inicial, Motor2D *motor): sprite(new MySprite(tex))
{
    puntoInicial = inicial;
    puntoFinal = obtenerPuntoFinal(*motor);

    sprite->setPosition(puntoInicial.x,puntoInicial.y);
    sprite->setOrigen(sprite->getHitbox().width / 2, sprite->getHitbox().height / 2);

}

MySprite** Nota::devolverSprite(){
    return &sprite;
}

sf::Vector2f* Nota::devolverInicial(){
    return &puntoInicial;
}

sf::Vector2f* Nota::devolverFinal(){
    return &puntoFinal;
}

MySprite* Nota::devolverSpriteSinPunt(){
    return sprite;
}