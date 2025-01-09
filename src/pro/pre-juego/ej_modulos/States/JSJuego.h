#ifndef JSJUEGO_H
#define JSJUEGO_H

#include "JState.h"
#include "JSMenuJuego.h"
#include "JSTransicion.h"
#include "JSTienda.h"
#include "../PersonajePrincipal.h"
#include "../Habitacion.h"
#include "../Level.h"
#include "../pentagrama.h"
#include "../Motor/musica.h"

class JSJuego : public JState
{

private:

    static JSJuego *instance;

    Motor2D *motor2D;

    // Constructor 
    JSJuego();

    //Interfaz del estado
    MySprite *sprite, *barra_fondo, *barra_marco, *ani, *nota, *notaverde, *notaroja, *barra_vida, *barra_ritmo, *fondo_objeto1, *fondo_objeto2, *fondo_texto_objeto, *fondo_sustitucion, *fondo_objeto1_sust, *fondo_objeto2_sust, *objeto1_sust, *objeto2_sust, *boton_cont, *boton_pass, *boton_quitar1, *boton_quitar2, *fondo, *fondo2, *puntuacion, *objeto_recogido, *fondo_objeto_recogido, *fondo_quehace, *fuego1, *banner_monedas, *boton_ok_monedas, *sprite_moneda, *tutorial, *continuar;
    sf::Text textObject;
    sf::Text textSust;

    sf::Text nombreObjeto_quehace;
    sf::Text objeto_quehace;

    sf::Text cantidad_monedas;
    sf::Text cantidad_monedas_num;

    int tutorialCont = 0,num;

    sf::RectangleShape *barraProgreso, *barraProgresoFondo, *barra_armor;

    //Variables de acciones
    int contador;
    int contAct;
    char accion;
    bool iniciada;
    int lanzarFlecha;
    float deltaT;
    float velocidad;
    float bpm;
    bool necesitocargarhabitacion;
    bool reseteoLevel;
    bool batallaBien;
    bool movFlecha;
    int fondoElegido=1;
    float intervalo = 0.0f;

    bool resetear;

    bool pintahover;

    bool cogerMonedas = false;

    int monedas = 0;

    //Relojes y variables Time
    sf::Clock relojBucle;
    sf::Clock relojUpdate;
    sf::Time timeStartUpdate;
    sf::Clock clock;

    //Objetos
    float clickTimer = 0.0f;
    const float clickDuration = 0.1f;
    bool pulsado;

    std::string lastClickedButton;
    sf::Font font;
    bool generado;
    bool sustituir;
    int objetoN;
    std::string nombreObj;

    Objeto objeto1;
    Objeto objeto2;


    //Personaje principal
    std::string pathPersonaje;
    std::string pathObjetos;
    std::string pathNota;
    std::string pathNotaV;
    std::string pathNotaR;
    std::string pathFlecha;
    sf::Vector2f posPJ;
    PersonajePrincipal *personaje;


    std::vector<std::string> nombres;
    std::vector<std::string> adjetivos;

    //Habitaciones y niveles
    Level *level;
    Habitacion habitacionActual;

    //NPC para transición
    sf::String npcBatalla;

    //Musica
    Musica miMusica;

    //Pentagrama
    Pentagrama pentagrama;

    void initializeGraphics(Motor2D* motor);
    void initializeMusic();

public:
    // Variables

    static JSJuego* getInstance();
    virtual ~JSJuego();

    JSJuego(JSJuego const&) = delete;
    void operator=(JSJuego const&) = delete;

    // Funciones
    void endState();

    void cambiarBatallaBien(bool ok);
    void cambiarGeneracion(bool ok);
    void cambiarCogerMonedas(bool ok);

    sf::String getNPCBatalla();

    void comprobacionContador();

    void handleButtonClick(const std::string &buttonName);
    int generateRandomObject(int valor);
    int usarObjetoAleatorio(int cambio);
    void cogerObjeto();

    float getVida();
    void actualizarVida(float hp, float armadura);

    std::string generarNombreAleatorio();
    std::string generarAdjetivoAleatorio();

    void resetearJuego(bool reset);
    void resetearFunciones(int tipo);
    bool obtenerResetear();

    void updateKeybinds(const float &dt);
    void update(const float &dt, char& accion);
    void render(sf::RenderTarget *target = nullptr);
    void renderizadoInterfaz(sf::RenderTarget *target);

    void matoPersonaje();

    Objeto getObjeto1();
    Objeto getObjeto2();

    void gastarObjeto1();
    void gastarObjeto2();

    void establecerMonedas(int money);
    void establecerTutorial();


};

#endif // JSJUEGO_H
