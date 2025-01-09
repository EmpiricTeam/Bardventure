#pragma once
#ifndef OBJETO_H
#define OBJETO_H

#include <vector>
#include <string>
#include "Motor/MySprite.h"
#include "Motor/Motor2D.h"

enum class ObjectType
{
    Vacio,
    Armadura,
    Armadura2,
    Vida,
    Vida2,
    Ritmo2,
    Ritmo,
    Dados,
    Daga,
    DagaInv,
    PactoSangre,
    BombaHumo,
    Tp
};

class Objeto
{
private:
    ObjectType type;
    MySprite *sprite;
    int nivel;
    bool consumible;

public:
    Objeto(const std::string &texture, int num, float x);
    int usarObjeto();
    std::string DarNombreObjeto();
    void asignarType(int tipo);
    int devolverObjeto();
    void moverX(float x);
    MySprite** getSprite();

    int obtenerNivelObjeto();
    void establecerNivel(int nivelNuevo);

    bool esConsumible();
};

#endif