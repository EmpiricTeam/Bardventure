#ifndef JSMENU_H
#define JSMENU_H

#include "JSJuego.h"
#include "JSBatalla.h"
#include "JSTienda.h"
#include "../Motor/musica.h"
#include <memory>

class JSMenu : public JState
{

private:
    static JSMenu *instance;
    std::map<std::string, MySprite*> botones_1;
    std::map<std::string, MySprite*> botones_2;
    Musica musica;

    float clickTimer = 0.0f;
    const float clickDuration = 0.1f;

    std::string lastClickedButton;
    sf::Font font;

    sf::Text textDificultad;
    sf::Text textVolumen;
    int dificultad;
    float volumen;

    MySprite* fondo;
    MySprite* titulo;
    MySprite* subtitulo;
    MySprite* banner;
    MySprite* banner_facil;
    MySprite* banner_medio;
    MySprite* banner_dificil;
    MySprite* barra_volumen;

    Motor2D* motor2D;

    
    std::string directorio = "../../../data/ANGEL/";
    sf::String npcBatalla;

    bool opc;
    bool tienda;

    //Funciones 
    void initBotones();

    JSMenu();

public:
    static JSMenu* getInstance();
    virtual ~JSMenu();

    //Funciones
    void endState();
    
    JSMenu(JSMenu const&) = delete;
    void operator=(JSMenu const&) = delete;

    void resetearEstadoBotones(std::map<std::string, MySprite*> &buttons);

    void updateDificultadTexto();
    void updateSFMLEvents();
    void updateKeybinds(const float& dt);
    void update(const float& dt, char& accion);

    void handleButtonClick(const std::string& buttonName);
    
    void renderBotones(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);

    int getDificultad() const;
};

#endif // JSMENU_H
