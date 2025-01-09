#pragma once
#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include "Motor/MySprite.h"
#include "Motor/Motor2D.h"



enum BossType {
    NPC,
    PRISION, //BASE
    CATACUMBAS, //ESQUIVAR
    JARDINES, //ALGUNAS NOTAS DARLES Y OTRAS ESQUIVAR
    COMEDOR,  //CAMBIE DE CARRIL
    REY //POPURRI DE TODOS
};


class Boss {
    private:
        MySprite* sprite;
        BossType tipo;
        int level;
        int vida;
        int maxValorVidaBoss;
        sf::String nombre;


    public:
        Boss(const std::string& texture, BossType type);
        BossType getTipo();
        void actualizarVida(int cantidad);
        int getVida();
        int getVidaMax();
        void cambiarVidaNPC(float vidaNPC);
        void asignarTipoNivel(int level1);
        sf::String getNombre();
        void asignarNombreNPC(sf::String nombreNuevo);
        void asignarSprite(MySprite* spriteB);
        MySprite** getSprite();

};

#endif