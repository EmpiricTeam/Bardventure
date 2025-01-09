#ifndef JSTransicion_H
#define JSTransicion_H

#include "JSJuego.h"
#include "JSBatalla.h"
#include "../Level.h"
#include <memory>
#include <chrono>

class JSTransicion : public JState
{
private:

    static JSTransicion *instance;

    Musica musica;
    MySprite* fondo;
    MySprite* creditos;
    MySprite* fondoFinal;

    MySprite* enemigo;
    MySprite* bardo;
    MySprite* banda_texto2;
    MySprite* versus;

    Motor2D* motor2D;

    float positionX;
    float bandapostionX;
    float endPositionX = 960;  
    float endBandapostionX = 0;  
    float endPositionY = -2648;

    float speed = 40.0f;  // Velocidad de movimiento en píxeles por segundo
    float speedCreditos = 2.0f;  // Velocidad de movimiento en píxeles por segundo
    bool isMoving = true;

    std::string directorio = "../../../data/ANGEL/";
    std::string nivel;
    std::string enemigoInfo;
    std::string enemigoPath;
    std::string enemigoTipo;

    sf::Font font;
    sf::Text textNivel;

    // Variables de tiempo
    //Relojes y variables Time
    sf::Clock relojBucle;
    sf::Clock relojUpdate;
    sf::Clock relojRender;
    sf::Time timeStartUpdate;
    sf::Time timeStartRender;

    sf::Clock clock;
    float deltaT;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point currentTime;
    std::chrono::steady_clock::time_point currentTimeRender;
    bool actionTriggered = false;
    std::string tipo;

    JSTransicion();
    void endState();

public:
    static JSTransicion* getInstance();
    virtual ~JSTransicion();

    JSTransicion(JSTransicion const&) = delete;
    void operator=(JSTransicion const&) = delete;

    void setTipo(std::string t);
    void setEnemigo();
    void updateKeybinds(const float& dt);
    void resetState();
    void update(const float& dt, char& accion);
    void renderizadoTransicion();
    void render(sf::RenderTarget* target = nullptr);

    MySprite* getEnemigo(); 
};


#endif // JSTransicion_H
