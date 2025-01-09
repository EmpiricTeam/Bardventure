#ifndef JSBATALLA_H
#define JSBATALLA_H

#include "JState.h"
#include "Juego.h"
#include "JSMenuJuego.h"

#include "../Proyectil.h"
#include "../Boss.h"
#include "../BossFactory.h"
#include "../Motor/musica.h"
#include "../Motor/EfectoTexto.h"


#include "../Objeto.h"

enum ResultadoTecla { Ninguno, Perfect, Good, Bad};

class Batalla : public JState
{

private:
    static Batalla* instance;
    MySprite* fondo;
    MySprite* carril;
    std::vector<std::unique_ptr<Proyectil>> proyectilesPunteros;
    std::vector<std::unique_ptr<Proyectil>> ataques;
    std::unique_ptr<Boss> bossBatalla;

    //sf::Sprite sprite;
    MySprite* sprite;
    sf::Texture tex;

    Motor2D *motor2D;

    sf::Clock temporizadorProyectiles;
    
    
    int contador;
    static const int maxContador = 600;

    //Atributos para la Barra de ataque
    //sf::Sprite barra_ataque;
    MySprite* barra_ataque;
    sf::Texture barra_ataque_tex;
    sf::RectangleShape barraProgreso;
    sf::Vector2f posicionBarraProgreso;
    float escaladoBarras;
    float anguloBarraProgreso;
    float longitudBarraProgreso;
    float alturaBarraProgreso;

    //BARRA DE VIDA DEL BOSS
    MySprite *barra_vida_boss;
    sf::Texture barra_vida_boss_tex;
    sf::RectangleShape barraVidaBoss;
    int valorVidaBoss; // NO HABRÍA QUE USARLO SINO COGER LA VIDA DEL BOSS
    int maxValorVidaBoss; // COGER LA QUE TE PASAN

    //BARRA DE VIDA
    MySprite *barra_vida;
    sf::Texture barra_vida_tex;
    sf::RectangleShape barraVida;
    sf::RectangleShape barraArmor;

    int valorVida; //Esto iría en la clase del personaje creo

    float BPM;
    MySprite *proyectil;

    sf::Clock relojUpdate;

    Musica *musica;

    int bonificacionDano;
    sf::Clock blinkTimer;  // Temporizador para el parpadeo
    bool isYellow = true;

    sf::Font fuente;
    sf::Text bossNameText;

    int tipoNivel;
    bool esInfinita = false;
    int contadorInfinito;
    sf::Text contadorInfinitoText;

    MySprite *mensajes;
    ResultadoTecla resultadoTecla = ResultadoTecla::Ninguno;
    sf::Clock resultadoTimer;  // Temporizador para mostrar el sprite de resultado
    float resultadoMostrarDuracion = 0.625f;

    MySprite *fondo_objeto1;
    MySprite *fondo_objeto2;
    
    std::unique_ptr<Objeto> objeto1;
    std::unique_ptr<Objeto> objeto2;

    std::vector<EfectoTexto> efectosTexto;

    sf::RectangleShape hitboxShape;

    bool bossCatacumbasCreado = false;
    bool bossJardinesCreado = false;
    bool bossComedorCreado = false;
    bool bossReyCreado = false;


    //Batalla();
    Batalla();
    

public:
    static Batalla* getInstance();

    virtual ~Batalla();

    Batalla(Batalla const&) = delete;
    void operator=(Batalla const&) = delete;

    static void initialize(const std::vector<std::unique_ptr<Proyectil>>& vectorProyectiles, const sf::Texture& tex);
    void asignarBoss(std::unique_ptr<Boss> boss);
    void generarProyectil(bool ataque);
    std::unique_ptr<Proyectil> crearProyectilNuevo( sf::Vector2f puntoInicial, sf::Vector2f puntoFinal, int carril, float velocidad, tipoProyectil tipoP, bool ataque);
    sf::Vector2f obtenerPuntoInicial(int carril);
    sf::Vector2f obtenerPuntoFinal(int carril);

    void setTexture();
    void setTextureBarraBatalla();
    void addProyectil(std::unique_ptr<Proyectil> proyectil);
    void addAtaque(std::unique_ptr<Proyectil> proyectil);
    void eliminarPrimerProyectil();
    void eliminarPrimerAtaque();
    std::vector<std::unique_ptr<Proyectil>>::iterator eliminarProyectil(std::vector<std::unique_ptr<Proyectil>>::iterator it);
    void cambiarPosicionSinInterpolacion(sf::Vector2f pos);
    void setScaleSprite(sf::Vector2f rot);
    int getContador();
    int getMaxContador();
    std::vector<std::unique_ptr<Proyectil>>& getProyectiles();
    std::vector<std::unique_ptr<Proyectil>>& getAtaques();
    MySprite* getSprite();

    void inicializarBarra();
    void actualizarContador(int incremento);
    void actualizarBarraProgreso();

    void inicializarBarraVidaBoss();
    void actualizarVidaBoss(int decremento);

    void inicializarBarraVida();
    void inicializarBarraArmor();
    void actualizarBarraVida(int decremento);
    void actualizarBarraArmor();


    int generateRandomObject();

    void update(float delta, sf::RenderWindow& window, sf::Sprite** proyectil);
    void dibujar(sf::RenderWindow& window, float factorInterpolacion);
    //void update(float delta, sf::RenderWindow& window);

    void cambiarCarrilProyectil(std::unique_ptr<Proyectil>& proyectil);

    void actualizarVelocidadLanzamiento(float bpm);

    sf::FloatRect getAdjustedHitbox(MySprite* sprite);

    char getInput();
    void controlTeclas(char accion);
    sf::Vector2f obtenerPuntoInicialAtaque(int carril);


    Boss& getBoss();


    void endState();

    void updateKeybinds(const float& dt);
    void update(const float& dt, char& accion);
    void render(sf::RenderTarget* target = nullptr);

    void asignarBonificacionDano(int x);
    int obtenerDano();
    void asignarTipoNivel(int tipo);
    void cambiarAInfinito(bool bol);
    void cambiarBossInfinito();

    void inicializarSpritesObjetos();
    void pasarObjetos(int o1, int x1, int o2, int x2);

    void inicializar();
    void reiniciar();


};

#endif