// Flecha.cpp
#include "Flecha.h"

// Constructor de Flecha
Flecha::Flecha(const std::string &textura, const sf::Vector2f &dir, const sf::Vector2f &ini)
: direccion(dir), inicial(ini), posicionInterpolada(ini.x,ini.y), sprite(new MySprite(textura)) {
    if(direccion.x==32)
    {
        sprite->setTile(1,4);
    }else if(direccion.x==-32){
        sprite->setTile(0,4);
    }else if(direccion.y==32){
        sprite->setTile(3,4);
    }else{
        sprite->setTile(2,4);
    }
    sprite->setPosition(ini.x,ini.y);
    //sprite->setOrigin(sprite->getHitbox().width / 2, sprite->getHitbox().height / 2);

}


void Flecha::moverFlecha(float deltaT){
    if(posicionInterpolada.getPosicionX() == sprite->getPosicion().x && posicionInterpolada.getPosicionY() == sprite->getPosicion().y){
        posicionInterpolada.actualizarPosicion(posicionInterpolada.getPosicionX(),posicionInterpolada.getPosicionY());
    }else{
        posicionInterpolada.setPercentTic(deltaT);

        float nuevaX = posicionInterpolada.getPosicionInterpoladaX();
        float nuevaY = posicionInterpolada.getPosicionInterpoladaY();

        sprite->setPosition(nuevaX,nuevaY); 
    }
    hitboxflecha = sprite->getHitbox();
}

sf::FloatRect Flecha::getHitbox()
{
    return hitboxflecha;
}

PosicionInterpolada* Flecha::getPosicionInterpolada(){
    return &posicionInterpolada;
}

sf::Vector2f* Flecha::getdireccion(){
    return &direccion;
}

void Flecha::actualizarHitbox(sf::FloatRect hitbox){
    hitboxflecha = hitbox;        
}

MySprite** Flecha::devolverSprite(){
    return &sprite;
}
