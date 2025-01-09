#include "Proyectil.h"

Proyectil::Proyectil( const sf::Vector2f& inicial, const sf::Vector2f& final, int elCarril, double laVelocidad, tipoProyectil tipoP, bool ataque)
    : puntoInicial(inicial), puntoFinal(final), carril(elCarril), escala(0.42f, 0.42f), velocidad(laVelocidad), posicionAnterior(inicial), posicionActual(inicial), tipo(tipoP), isAtaque(ataque)
{
        //sprite = new MySprite("../../../data/ALE/Spritesheet/Efectos/16_sunburn_spritesheet.png", 61, 100, 0.2, 8);
        

    if(isAtaque){
        sprite = new MySprite("../../../data/ALE/Spritesheet/Efectos/18_midnight_spritesheet.png", 64, 100,100, 0.03, 8);
        sprite->setPosition(inicial.x, inicial.y);
        sprite->setOrigen(sprite->getHitbox().width / 2, sprite->getHitbox().height / 2);
        sprite->escalarSprite(2);

        float hitboxScale = 0.3f; // El tamaño de la hitbox será el 50% del tamaño del sprite
        sf::FloatRect smallerHitbox;
        smallerHitbox.width = sprite->getHitbox().width * hitboxScale;
        smallerHitbox.height = sprite->getHitbox().height * hitboxScale;
        smallerHitbox.left = sprite->getPosition().x - (smallerHitbox.width / 2);
        smallerHitbox.top = sprite->getPosition().y - (smallerHitbox.height / 2);

        sprite->setHitboxPersonalizada(smallerHitbox);

    }else {
        sprite = new MySprite("../../../data/ALE/Spritesheet/Efectos/16_sunburn_spritesheet.png", 61, 100,100, 0.05, 8);
        sprite->setPosition(inicial.x, inicial.y);
        sprite->setOrigen(sprite->getHitbox().width / 2, sprite->getHitbox().height / 2);
        sprite->escalarSprite(1);
        
        float hitboxScale = 0.5f; // El tamaño de la hitbox será el 50% del tamaño del sprite
        sf::FloatRect smallerHitbox;
        smallerHitbox.width = sprite->getHitbox().width * hitboxScale;
        smallerHitbox.height = sprite->getHitbox().height * hitboxScale;
        smallerHitbox.left = sprite->getPosition().x - (smallerHitbox.width / 2);
        smallerHitbox.top = sprite->getPosition().y - (smallerHitbox.height / 2);

        sprite->setHitboxPersonalizada(smallerHitbox);
    }

    
    /*sprite->setPosition(inicial.x, inicial.y);
    sprite->setOrigen(sprite->getHitbox().width / 2, sprite->getHitbox().height / 2);*/

    sf::Vector2f direccionNueva = puntoFinal - puntoInicial;
    float magnitud = std::sqrt(direccionNueva.x * direccionNueva.x + direccionNueva.y * direccionNueva.y);
    if (magnitud > 0.0f) {
        direccionNueva /= magnitud;
    }

    direccion = direccionNueva;
    cambiado = false;

    motor2D = Motor2D::getInstance();

    frameActual = 0;
}

void Proyectil::actualizarPoscionSinInterpolacion(float x, float y){
    sprite->setPosition(x, y);
}


sf::Vector2f Proyectil::getPosicionSprite(){
    return sprite->getPosicion();
}

void Proyectil::renderizar(sf::RenderWindow& window, float interpolacion){
    sf::Vector2f posicionInterpolada = posicionAnterior + (posicionActual - posicionAnterior) * interpolacion;
    
    // Actualiza la posición del sprite para el renderizado
    sprite->setPosition(posicionInterpolada.x, posicionInterpolada.y);
    motor2D->draw(&sprite);
}

void Proyectil::cambiarDireccion(sf::Vector2f direccionNueva){
    direccion = direccionNueva;
}

sf::Vector2f Proyectil::getDireccion(){
    return direccion;
}

void Proyectil::actualizarPuntoFinal(sf::Vector2f punto){
    puntoFinal = punto;
}

void Proyectil::actualizarPuntoInicial(sf::Vector2f punto){
    puntoInicial = punto;
}

sf::Vector2f Proyectil::getPuntoInicial(){
    return puntoInicial;
}

sf::Vector2f Proyectil::getPuntoFinal(){
    return puntoFinal;
}

int Proyectil::getCarril(){
    return carril;
}

tipoProyectil Proyectil::getTipo(){
    return tipo;
}

void Proyectil::dibujar(){
    motor2D->draw(&sprite);
}

MySprite* Proyectil::getSprite(){
    return sprite;
}

void Proyectil::escalar(float escala){
    sprite->escalarSprite(escala);
}

sf::Vector2f Proyectil::getPosicionAnterior(){
    return posicionAnterior;
}

sf::Vector2f Proyectil::getPosicionActual(){
    return posicionActual;
}

void Proyectil::actualizarPosicionAnterior(sf::Vector2f anterior){
    posicionAnterior = anterior;
}

void Proyectil::actualizarPosicionActual(sf::Vector2f actual){
    posicionActual = actual;
}

void Proyectil::cambiar(bool b){
    cambiado = true;
}

bool Proyectil::getCambiado(){
    return cambiado;
}

void Proyectil::actualizarCarril(int carrilNuevo){
    carril = carrilNuevo;
}