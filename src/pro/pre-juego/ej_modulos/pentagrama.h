#pragma once
#ifndef PENTAGRAMA_H
#define PENTAGRAMA_H

#include <SFML/Graphics.hpp>
#include "nota.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

#include "Motor/Motor2D.h"

class Pentagrama {
private:
    std::vector<std::unique_ptr<Nota>> notasIniciales;
    std::vector<std::unique_ptr<Nota>> notasFinales;

public:
    
    void comprobacionGolpeo(Motor2D* motor, std::string &prueba2, std::string &prueba3, int &contador);
    void cambioPentagrama();
    void agregarNotaInicial(const std::string& tex, Motor2D *motor);
    void agregarNotaFinal(const std::string& tex, const sf::Vector2f& inicial, Motor2D *motor);
    void borrarTodas();
    void update(Motor2D *motor, float velocidad, std::string& prueba3, int& contador, float deltaT);
    void render(Motor2D *motor);
    std::vector<std::unique_ptr<Nota>>& devolverNotasIni();
    std::vector<std::unique_ptr<Nota>>& devolverNotasFin();
};

#endif