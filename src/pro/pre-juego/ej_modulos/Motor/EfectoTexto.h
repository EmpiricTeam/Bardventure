#pragma once
#ifndef EFECTOTEXTO_H
#define EFECTOTEXTO_H

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Motor/Motor2D.h";

class EfectoTexto
{
    public:
        EfectoTexto(const std::string& contenido, sf::Font& fuente, sf::Vector2f posicionInicial, sf::Color color, float duracionMs, float escala = 1.5f);

        bool update();
        void draw(float factorInterpolacion);
        

    private:
        sf::Text texto;
        sf::Vector2f velocidad;
        sf::Clock duracion;
        float duracionMs;

        sf::Vector2f posicionAnterior;
        sf::Vector2f posicionActual;
};


#endif