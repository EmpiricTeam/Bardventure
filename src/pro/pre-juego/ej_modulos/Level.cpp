#include "Level.h"
#include <iostream>
#include <random>
#include <set>

// Constructor de Level
Level::Level() : type(LevelType::Carcel), currentRoomIndex(0) {
    generateRandomRooms(type); 
}

Level *Level::instance = nullptr;

Level *Level::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Level();
    }
    return instance;
}

Level::~Level()
{

}

void Level::generateRandomRooms(LevelType type) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dOrden(1, 3);
    std::uniform_int_distribution<> dHabitacion(1, 3);

    bool finalLevel = false;
    std::string tipoNivel = "NULL";
    std::string archivo = ".tmx";
    std::string tipoHabitacion = "NULL";
    std::vector<std::string> newRooms ={"null","null","null"};

    switch (type)
            {
            case LevelType::Carcel:
                tipoNivel="P_";
                break;
            case LevelType::Catacumbas:
                tipoNivel="C_";
                break;
            case LevelType::Jardines:
                tipoNivel="J_";
                break;
            case LevelType::Comedor:
                tipoNivel="D_";
                break;
            case LevelType::Trono:
                tipoNivel="T_";
                finalLevel=true;
                break;
            default:
                break;
            }
    if(finalLevel){
        rooms={tipoNivel+"I"+archivo,tipoNivel+"B"+archivo,tipoNivel+"F"+archivo,tipoNivel+"X"+archivo};
    }else{
        rooms = {tipoNivel+"I"+archivo,"1","2","3",tipoNivel+"B"+archivo,tipoNivel+"F"+archivo};
        std::set<int> numerosUsados;
        for(int i=0;i<3;i++){
            if(i==1||i==2){
                numerosUsados.clear();
            }
            std::string habitacionNueva = "NULL";
            if(i==0){
                tipoHabitacion="P_";
            }else if(i==1){
                tipoHabitacion="M_";
            }else if (i==2){
                tipoHabitacion="G_";
            }
            
            int numeroHabitacion;
            do {
                numeroHabitacion = dHabitacion(gen); 
            } while(!numerosUsados.insert(numeroHabitacion).second);

            std::string numero = std::to_string(numeroHabitacion);

            habitacionNueva = tipoNivel+tipoHabitacion+numero+archivo;
            newRooms[i]=habitacionNueva;
        }
        numerosUsados.clear();
        for(int j=0;j<3;j++){
            int numeroHabitacion;
            
            do {
                numeroHabitacion = dOrden(gen)- 1; 
            } while(!numerosUsados.insert(numeroHabitacion).second);

            rooms[j+1]=newRooms[numeroHabitacion];
        }
    }
    
    
    
    std::cout << "Habitaciones generadas:" << std::endl;
    for(const auto& room : rooms) {
        std::cout << room << std::endl;
    }

}

void Level::nextRoom() {
    if (currentRoomIndex + 1 < rooms.size()) {
        currentRoomIndex++;
    }else{
        currentRoomIndex=0;
    }
}

std::string Level::getCurrentRoomName() const {
    if (currentRoomIndex >= 0 && currentRoomIndex < rooms.size()) {
        return rooms[currentRoomIndex];
    }
    return ""; 
}

Habitacion Level::loadHabitacionActual(){
    std::string nombreHabitacion = getCurrentRoomName();
    Habitacion habitacion;
    habitacion.cargaHabitacion("../../../data/ALE/"+ nombreHabitacion);
    habitacion.spawnEntidades(static_cast<int>(type));

    return habitacion;
}

int Level::checkNextTile(Habitacion& habitacion,bool& cargar, int x, int y, int movimiento) {
    int xFuturo = x;
    int yFuturo = y;

    cargar=false;
    
    switch (movimiento) {
    case 1: yFuturo--; break;
    case 2: yFuturo++; break;
    case 3: xFuturo--; break;
    case 4: xFuturo++; break;
    }

    // Verificación de colisión
    if (!(habitacion.getTilemapHitbox().empty()) && (habitacion.getTilemapHitbox()[yFuturo][xFuturo] != 0)) {
        return 0; // No es posible moverse debido a una colisión
    }

    if (!(habitacion.getTilemapMovimientos().empty())) {
        // Verificar tiles de movimiento especial
        int tileMovimiento = habitacion.getTilemapMovimientos()[yFuturo][xFuturo];
        if (tileMovimiento != 0) {
            switch (tileMovimiento) {
                case 793:  // Puerta que requiere que la habitación esté completada.
                        std::cout << "Cambio de habitación" << std::endl;
                        cargar = true;
                        return 1; // Indica que es posible moverse (cambio de habitación activado)
                    break;

                case 792:  // Cambio de nivel.
                    std::cout << "Cambio de nivel" << std::endl;
                    cargar=true;
                    currentRoomIndex=-1;
                    return 1; // Indica que es posible moverse (cambio de nivel activado)
                    break;
                
                case 841:
                    std::cout << "Fin del juego" << std::endl;
                    if(getCurrentRoomName()=="T_F.tmx"){
                        return 2;
                    }else{
                        return 3;
                    }
                    break;

                default:
                    // Otros tiles que requieren acciones específicas podrían ser manejados aquí
                    break;
            }
        }
    }


    return 1; // Movimiento posible sin acciones especiales
}


void Level::changeLevel() {
    std::cout << "Cambiando de nivel. Nivel actual (tipo): " << static_cast<int>(type) << std::endl;
    this->rooms.clear();
    LevelType newType = static_cast<LevelType>((static_cast<int>(type) + 1) % 5);
    std::cout << "Nivel nuevo (tipo): " << static_cast<int>(newType) << std::endl;
    type = newType;
    this->generateRandomRooms(newType);
    std::cout << "Cambio completado. Nivel actual (tipo): " << static_cast<int>(type) << std::endl;   
}

LevelType Level::getLevelType(){
    return type;
}

int Level::getCurrentRoomIndex(){
    return currentRoomIndex;
}

void Level::setCurrentRoomIndex(int i){
    currentRoomIndex=i;
}

void Level::setLevelType(LevelType newType){
    type=newType;
}