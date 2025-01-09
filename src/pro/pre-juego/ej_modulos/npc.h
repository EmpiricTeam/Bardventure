#pragma once
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cstdlib> 
#include <cmath>   
#include <random>
#include <chrono>
#include "Motor/MySprite.h"
#include "Flecha.h"
#include "PosicionInterpolada.h"

enum NPCType {
    PEON,
    ALFIL,
    REINA,
    ARQUERO,
    JEFE
};

class Npc {
public:
    Npc(const std::string& texture, NPCType type, int x, int y);
    void updateNpc(sf::Vector2i playerPosition);
    //funciones arquero
    void cargarFlechas(const std::string &texturaFlecha, sf::Vector2f posicionInicial, sf::Vector2f posicionPj);
    void avanzaFlecha();
    void moveNPC(float deltaT);
    void aumContador();
    int getContadorFlecha();
    sf::String getTipo(); 
    sf::Vector2f ataqueArquero(sf::Vector2f posicionPj, sf::Vector2f posicionEn);
    sf::Vector2i nuevaPos(sf::Vector2f playerPosition);
    int getX();
    int getY();
    sf::FloatRect getFlecha();
    void setRecarga();
    MySprite **getSprite();
    std::string getPathSprite();
    int getHp();
    sf::Vector2f getPosicion();
    std::vector<std::unique_ptr<Flecha>>& getCarcaj();

private:
    int dirMove;
    int contMove;
    int contadorFlecha;
    sf::Clock tiempoEspera;
    bool recarga;
    MySprite *sprite;
    NPCType type;
    float hp;
    sf::Vector2f movement;
    std::vector<std::unique_ptr<Flecha>> carcaj; 
    PosicionInterpolada posicionInterpolada;
};
#endif