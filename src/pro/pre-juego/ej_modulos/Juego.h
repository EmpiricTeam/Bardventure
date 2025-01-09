#ifndef JUEGO_H
#define JUEGO_H
#define kUpdateTimePS 1000/15

#include "States/JSMenu.h"
#include "States/JSBatalla.h"

class Juego
{
private:
    //Variables
    sf::Event sfEvent;
    char accion;

    sf::Clock dtClock;
    sf::Clock relojBucle;
    sf::Time tiempoBucle = relojBucle.getElapsedTime();
    float dt;

    std::stack<JState*> states;

    static Juego *instance;

    //Inicializacion 
    void initWindow();
    void initStates();

    Juego();
    
public:

    static Juego* getInstance();
    //Constructor y destructor
    virtual ~Juego();

    //Funciones
    void resetToMainMenu();
    //Regular
    void endApplication();

    //Update
    void updateDt();    
    void updateSFMLEvents();
    void update();

    std::stack<JState*> devolverStates();
    void actualizar(std::stack<JState*> state);

    //Render
    void render();

    //Core
    void run();
};


#endif // JUEGO_H