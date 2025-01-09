#pragma once
#ifndef POSICIONINTERPOLADA_H
#define POSICIONINTERPOLADA_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#include "nota.h"


class PosicionInterpolada {

private:
    float posXActual, posYActual; // Posiciones actuales
    float posXAnterior, posYAnterior; // Posiciones anteriores
    float percentTic; // Porcentaje del avance entre frames

public:
    PosicionInterpolada(float iniX, float iniY);

    void actualizarPosicion(float nuevaX, float nuevaY);

    void setPercentTic(float percent);

    float getPosicionInterpoladaX();

    float getPosicionInterpoladaY();

    float getPosicionX();

    float getPosicionY();
};



#endif