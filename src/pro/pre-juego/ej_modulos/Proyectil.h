#pragma once
#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Motor/Motor2D.h"

enum class tipoProyectil {
    Romper,
    Esquivar
};

class Proyectil {
private:
    Motor2D* motor2D;
    MySprite* sprite;
    int frameActual;
    sf::Vector2f puntoInicial;
    sf::Vector2f puntoFinal;
    sf::Vector2f escala;
    int carril;
    double velocidad;
    sf::Vector2f direccion;
    bool cambiado;
    tipoProyectil tipo;

    sf::Vector2f posicionAnterior;
    sf::Vector2f posicionActual;

    bool isAtaque;

public:
    
    Proyectil( const sf::Vector2f& inicial, const sf::Vector2f& final, int carril, double velocidad, tipoProyectil tipoP, bool ataque);
    void actualizarPoscionSinInterpolacion(float x, float y);
    sf::Vector2f getPosicionSprite();
    void renderizar(sf::RenderWindow& window, float interpolacion);
    int getCarril();
    void cambiarDireccion(sf::Vector2f direccion);
    sf::Vector2f getDireccion();
    void actualizarPuntoFinal(sf::Vector2f punto);
    void actualizarPuntoInicial(sf::Vector2f punto);
    sf::Vector2f getPuntoInicial();
    sf::Vector2f getPuntoFinal();
    tipoProyectil getTipo();

    MySprite* getSprite();

    void escalar(float escala);
    void dibujar();


    sf::Vector2f getPosicionAnterior();
    sf::Vector2f getPosicionActual();
    void actualizarPosicionAnterior(sf::Vector2f anterior);
    void actualizarPosicionActual(sf::Vector2f actual);
    void cambiar(bool b);
    bool getCambiado();
    void actualizarCarril(int carril);

};

#endif