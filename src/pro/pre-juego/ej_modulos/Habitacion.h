#pragma once
#ifndef HABITACION_H
#define HABITACION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Motor/Motor2D.h"
#include "PersonajePrincipal.h"
#include "factoryNpc.h"
#include "npc.h"
#include "Motor/Tilemap.h"

class Habitacion : public sf::Drawable, public sf::Transformable {
public:
    bool cargaHabitacion(const std::string& archivoMapa);
    bool spawnEntidades(int tipo);
    bool checkMoveEntidad(int iterador, int x, int y);
    void crearYAgregarNPC(std::string& tex, NPCType tipo, int x ,int y);
    Npc* checkNPCbatalla(int tileX,int tileY);
    std::vector<std::vector<int>> getTilemapHitbox();
    std::vector<std::vector<int>> getTilemapMovimientos();
    const std::vector<std::unique_ptr<Npc>>& getNpcs() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawRest(sf::RenderTarget& target, sf::RenderStates states) const;
    void eliminarNPC(Npc* npcActual);

private:
    std::vector<std::string> split(const std::string& str, char delim);
    int _width, _heigth, _tilewidth, _tileheigth, _numlayers;
    sf::Vector2u tilesetSize;
    std::vector<Tilemap> tilemaps;
    int* tilemapSpawn = nullptr;

    std::vector<std::unique_ptr<Npc>> npcs;
    std::vector<std::unique_ptr<MySprite>> vfx;
    std::vector<std::vector<int>> tilemapHitbox;
    std::vector<std::vector<int>> tilemapMovimientos;    
};
#endif