#ifndef JSTIENDA_H
#define JSTIENDA_H

#include "JState.h"
#include "JSMenu.h"
#include "../third_party/tinyxml2.h"


enum EstadoTienda {
    PESTANA_OBJETOS,
    PESTANA_PERSONAJE
};


class JSTienda : public JState
{

private:
    static JSTienda *instance;

    EstadoTienda estadoActual;

    Motor2D *motor2D;
    sf::Font font;

    // Interfaz del estado
    std::vector<MySprite *> spritesObjetos;
    std::vector<MySprite *> fondoObjetos;
    std::vector<int> numObjetos;
    std::vector<sf::Text> nombreObjeto;
    std::vector<sf::Text> descripcionObjeto;
    std::vector<int> nivelObjetos;
    std::vector<sf::RectangleShape *> contadoresMejora;

    int nivelVida;
    sf::Text textoVida;
    sf::RectangleShape *rectVida;
    MySprite *mejoraVida;
    MySprite *barraMejoraVida;
    MySprite *fondoVida;
    MySprite *herrero;
    MySprite *herrero2;
    
    bool compra;


    int nivelArmadura;
    sf::Text textArmor;
    sf::RectangleShape *rectArmor;
    MySprite *mejoraArmor;
    MySprite *barraMejoraArmor;
    MySprite *fondoArmor;

    int monedas;
    sf::Text textMonedas;
    MySprite *spriteMonedas;
    int iAct;
    bool puedo;

    std::string directorio = "../../../data/ANGEL/";

    std::vector<MySprite *> barraMejoraObjetos;
    std::vector<MySprite *> botonParaMejorar;

    MySprite *fondo, *fondo_pequeno, *pestana_personaje, *pestana_objetos, *flecha_pasar, *volver, *flecha_atras, *personaje_sprite;

    std::string pathObjetos;

    float clickTimer = 0.0f;
    const float clickDuration = 0.1f;

    std::string lastClickedButton;

    int currentPage;        // Para mantener el índice de la página actual
    int objectsPerPage = 4; // Cantidad de objetos a mostrar por página

    sf::Clock relojDelta;
    sf::Clock tiempoEspera;
    float deltaT;
    int contMov;

    // Constructor
    JSTienda();

public:
    // Variables

    static JSTienda *getInstance();
    virtual ~JSTienda();

    void inizializarInterfaz();
    void subirNivelObjeto(const std::string &pathArchivo, int idObjeto, int nuevoNivel);
    void actualizarEstadistica(const std::string &pathArchivo, const std::string &estadistica, int nuevoValor);

    void renderObjects(sf::RenderTarget *target);
    void renderPersonaje(sf::RenderTarget *target);

    void nextPage();
    void previousPage();

    bool puedoSubirNivel(int nuevoNivel);
    int obtenerNivelPorID(int id);
    std::string obtenerFuncionPorID(int idObjeto);

    void mantenerBotonPulsado();

    void handleButtonClick(const std::string &buttonName);

    void idlePersonaje();

    int devolverMonedas();

    JSTienda(JSTienda const &) = delete;
    void operator=(JSTienda const &) = delete;

    // Funciones
    void endState();

    void updateKeybinds(const float &dt);
    void update(const float &dt, char &accion);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // JSTIENDA_H
