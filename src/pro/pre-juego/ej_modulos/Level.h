#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include "Habitacion.h"

enum class LevelType {
    Carcel,
    Catacumbas,
    Jardines,
    Comedor,
    Trono
};

class Level {
public:
    static Level* getInstance();
    virtual ~Level();

    Level(Level const&) = delete;
    void operator=(Level const&) = delete;
    LevelType getLevelType();
    int getCurrentRoomIndex();
    Habitacion loadHabitacionActual();
    void generateRandomRooms(LevelType type);
    void nextRoom();
    void changeLevel();
    int checkNextTile(Habitacion& habitacion, bool& cargar, int x, int y, int movimiento);
    std::string getCurrentRoomName() const;

    void setCurrentRoomIndex(int i);
    void setLevelType(LevelType newType);
private:
    std::vector<std::string> rooms;
    Level();
    static Level *instance;
    LevelType type;
    int currentRoomIndex;
};



#endif