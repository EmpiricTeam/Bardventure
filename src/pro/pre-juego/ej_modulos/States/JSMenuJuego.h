#ifndef JSMenuJuego_JUEGO_H
#define JSMenuJuego_JUEGO_H

#include "JSJuego.h"
#include "JSMenuJuego.h"
#include "../Juego.h"
#include "../Motor/musica.h"  
#include <memory>

class JSMenuJuego : public JState
{

private:
    static JSMenuJuego *instance;
    std::map<std::string, MySprite*> botones_1;
    std::map<std::string, MySprite*> botones_2;
    
    sf::Text textVolumen;
    sf::Font font;
    float volumen;

    float clickTimer = 0.0f;
    const float clickDuration = 0.1f;

    std::string lastClickedButton;
    std::string nivel;

    MySprite* fondo;
    MySprite* transparente;
    MySprite* titulo;
    MySprite* subtitulo;
    MySprite* barra_volumen;

    Motor2D* motor2D;

    Musica musica;
    std::string directorio = "../../../data/ANGEL/";

    bool opc;

    //Funciones 
    void initBotones();

    JSMenuJuego();

public:
    static JSMenuJuego* getInstance();
    virtual ~JSMenuJuego();

    //Funciones
    void endState();
    
    JSMenuJuego(JSMenuJuego const&) = delete;
    void operator=(JSMenuJuego const&) = delete;

    void resetearEstadoBotones(std::map<std::string, MySprite*> &buttons);

    void updateDificultadTexto();
    void updateSFMLEvents();
    void updateKeybinds(const float& dt);
    void update(const float& dt, char& accion);

    void handleButtonClick(const std::string& buttonName);
    void setFondo();
    void setFondoInfinito();
    
    void renderBotones(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // JSMenuJuegoJUEGO_H
