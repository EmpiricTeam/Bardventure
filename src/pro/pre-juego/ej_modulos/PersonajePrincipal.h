#pragma once
#ifndef PERSONAJEPRINCIPAL_H
#define PERSONAJEPRINCIPAL_H

#include <SFML/Graphics.hpp>

#include "PosicionInterpolada.h"
#include "Objeto.h"
#include "Motor/MySprite.h"

class PersonajePrincipal {
public:
    static PersonajePrincipal* getInstance();
    virtual ~PersonajePrincipal();
    
    void update(int movimiento);
    void movePj(float deltaT);
    void setPosicion(int x, int y);
    float devolverVida();
    float devolverArmor();
    void DarArmadura(float armadura);
    void sumarVida(int suma);
    void quitarVidaFlecha();
    void quitarVida(int vida);
    void subirVidaMax(float vM);

    float getVidaMax();

    void subirArmorMax(float vM);

    float getArmorMax();
    sf::Vector2f getPosicion();

    void quitarVida(float hp, float armadura);
    sf::FloatRect getHitbox();
    MySprite** getSprite();

    


    // Eliminamos la capacidad de copiar y asignar
    PersonajePrincipal(PersonajePrincipal const&) = delete;
    void operator=(PersonajePrincipal const&) = delete;

    private:
        //PersonajePrincipal(const std::string &texture, sf::Vector2f &inicial);
        PersonajePrincipal();

        static PersonajePrincipal *instance;
        
        int dirMove;
        int contMove;
        float armor;
        float vida;

        float vidaMax;

        MySprite *sprite;

        sf::Vector2f movimiento;
        sf::FloatRect hitbox;
        PosicionInterpolada posicionInterpolada;
        sf::Clock tiempoEspera;
};

#endif
