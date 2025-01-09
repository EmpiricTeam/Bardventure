#include "JSJuego.h"

// Constructor y destructor
JSJuego::JSJuego() : JState(), contador(0), contAct(0), accion('\0'), iniciada(false), lanzarFlecha(0), deltaT(0.0), necesitocargarhabitacion(false), batallaBien(false), generado(false), sustituir(false), pulsado(false), resetear(false), reseteoLevel(false), pintahover(false),
                     pathPersonaje("../../../data/ALE/Spritesheet/personajePrincipal.png"),
                     pathNota("../../../data/OCTAVIO/Texturas/nota.png"),
                     pathNotaV("../../../data/OCTAVIO/Texturas/nota_verde.png"),
                     pathNotaR("../../../data/OCTAVIO/Texturas/nota_rota.png"),
                     pathFlecha("../../../data/JORGE/spritesheet.png"),
                     pathObjetos("../../../data/ANGEL/sprites/items/spritesheet_objetos.png"),
                     objeto1("../../../data/ANGEL/sprites/items/spritesheet_objetos.png", 0, 0),
                     objeto2("../../../data/ANGEL/sprites/items/spritesheet_objetos.png", 0, 0),
                     posPJ(0, 0), // Inicializa la posición del personaje
                     miMusica("../../../data/OCTAVIO/velocidades")
{
    personaje = PersonajePrincipal::getInstance();
    level = Level::getInstance();
    habitacionActual = level->loadHabitacionActual();
    motor2D = Motor2D::getInstance();

    int lvl1 = JSTienda::getInstance()->obtenerNivelPorID(objeto1.devolverObjeto());
    int lvl2 = JSTienda::getInstance()->obtenerNivelPorID(objeto2.devolverObjeto());

    objeto1.establecerNivel(lvl1);
    objeto2.establecerNivel(lvl2);

    // miMusica.cargarSonido("../../../data/OCTAVIO/Sonidos/door-open.ogg");

    initializeGraphics(motor2D);
    initializeMusic();
    timeStartUpdate = relojBucle.getElapsedTime();
    miMusica.updateVolumen(false);

    nombres = {"Saqueador", "Caballero", "Prisionero", "Guardian", "Explorador", "Mercenario", "Hechicero", "Alquimista", "Cazador", "Picaro", "Shaman", "Vidente", "Berserker", "Invocador", "Templario", "Nigromante", "Druida", "Paladin", "Ladron", "Principe", "Mistico", "Centinela", "Conjurador", "Vigilante", "Errante", "Gladiador", "Profeta", "Artifice"};

    adjetivos = {
        "Valiente", "Astuto", "Misterioso", "Legendario", "Temible",
        "Sabio", "Resiliente", "Majestuoso", "Traicionero", "Implacable",
        "Agil", "Poderoso", "Antiguo", "Feroz", "Sereno",
        "Astuto", "Vigilante", "Sigiloso", "Despiadado", "Honorifico",
        "Siniestro", "Aspero", "Deslumbrante", "Noble", "Sagaz",
        "Salvaje", "Intrepido", "Vigoroso", "Luminoso", "Implacable"};
}

JSJuego::~JSJuego()
{
    delete sprite;
    delete barra_fondo;
    delete barra_vida;
    delete barra_ritmo;
    delete barra_marco;
    delete ani;
    delete nota;
    delete notaverde;
    delete notaroja;
    delete barraProgreso;
    delete barraProgresoFondo;
    delete barra_armor;
    delete fondo_texto_objeto;
    delete boton_cont;
    delete boton_pass;
    delete fondo_sustitucion;
    delete fondo_objeto1_sust;
    delete fondo_objeto2_sust;
    delete objeto1_sust;
    delete objeto2_sust;
    delete boton_quitar1;
    delete boton_quitar2;
    delete fondo_objeto1;
    delete fondo_objeto2;
    delete puntuacion;
    delete objeto_recogido;
    delete fondo_objeto_recogido;
    delete fondo_quehace;
    delete banner_monedas;
    delete boton_ok_monedas;
    delete sprite_moneda;
}

void JSJuego::initializeGraphics(Motor2D *motor2D)
{
    std::string directorio = "../../../data/ANGEL/";

    sprite = new MySprite("../../../data/JORGE/monsters.png");
    barra_fondo = new MySprite("../../../data/OCTAVIO/Texturas/barra_fondo.png");
    barra_marco = new MySprite("../../../data/OCTAVIO/Texturas/barra_marco.png");
    barra_ritmo = new MySprite("../../../data/OCTAVIO/Texturas/barra_batalla_sin_barras.png");
    barra_vida = new MySprite("../../../data/JAVIER/barra_vida.png");
    ani = new MySprite("../../../data/OCTAVIO/Texturas/anillo.png");
    nota = new MySprite("../../../data/OCTAVIO/Texturas/nota.png");
    notaverde = new MySprite("../../../data/OCTAVIO/Texturas/nota_verde.png");
    notaroja = new MySprite("../../../data/OCTAVIO/Texturas/nota_rota.png");
    fondo_texto_objeto = new MySprite("../../../data/ANGEL/fondos/banner.png");
    fondo_sustitucion = new MySprite("../../../data/ANGEL/fondos/banner.png");
    fondo_objeto1_sust = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    fondo_objeto2_sust = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    objeto1_sust = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    objeto2_sust = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    sprite_moneda = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    boton_cont = new MySprite(directorio + "botones/coger_normal.png", directorio + "botones/coger_hover.png", directorio + "botones/coger_click.png");
    boton_pass = new MySprite(directorio + "botones/dejar_normal.png", directorio + "botones/dejar_hover.png", directorio + "botones/dejar_click.png");
    boton_quitar2 = new MySprite(directorio + "botones/dejar_normal2.png", directorio + "botones/dejar_hover2.png", directorio + "botones/dejar_click2.png");
    boton_quitar1 = new MySprite(directorio + "botones/dejar_normal1.png", directorio + "botones/dejar_hover1.png", directorio + "botones/dejar_click1.png");
    fondo = new MySprite("../../../data/ALE/Spritesheet/fondo1.png");
    fondo2 = new MySprite("../../../data/ALE/Spritesheet/fondo2.png");
    fondo_objeto1 = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    fondo_objeto2 = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    fondo_objeto_recogido = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    objeto_recogido = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    puntuacion = new MySprite("../../../data/ALE/Spritesheet/numeretes.png");
    fondo_quehace = new MySprite("../../../data/ANGEL/fondos/banner.png");
    banner_monedas = new MySprite("../../../data/ANGEL/fondos/banner_monedas.png");
    boton_ok_monedas = new MySprite(directorio + "botones/coger_normal.png", directorio + "botones/coger_hover.png", directorio + "botones/coger_click.png");
    fuego1 = new MySprite("../../../data/ALE/Spritesheet/Efectos/11_fire_spritesheet.png", // Ruta a la textura
                          61,                                                              // Número de frames
                          100,
                          100,   // Tamaño de cada frame (supongamos 32x32 píxeles)
                          0.05f, // Duración de cada frame en segundos
                          8      // Número de frames por fila en la textura
    );
    if (!font.loadFromFile(directorio + "Fonts/alagard.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    objeto1.moverX((motor2D->getSize().x / 2) + 643);
    objeto2.moverX((motor2D->getSize().x / 2) + 793);

    textObject.setFont(font);
    textObject.setCharacterSize(33);
    textObject.setFillColor(sf::Color::White);
    textObject.setPosition((motor2D->getSize().x / 2) - 155, (motor2D->getSize().y / 2) - 300);
    textObject.setOutlineColor(sf::Color::Black);
    textObject.setOutlineThickness(5);

    cantidad_monedas.setFont(font);
    cantidad_monedas.setCharacterSize(30);
    cantidad_monedas.setFillColor(sf::Color::White);
    cantidad_monedas.setPosition((motor2D->getSize().x / 2) - 111, (motor2D->getSize().y / 2) - 120);
    cantidad_monedas.setOutlineColor(sf::Color::Black);
    cantidad_monedas.setOutlineThickness(5);

    cantidad_monedas_num.setFont(font);
    cantidad_monedas_num.setCharacterSize(30);
    cantidad_monedas_num.setFillColor(sf::Color::White);
    cantidad_monedas_num.setPosition((motor2D->getSize().x / 2) - 45, (motor2D->getSize().y / 2) - 76);
    cantidad_monedas_num.setOutlineColor(sf::Color::Black);
    cantidad_monedas_num.setOutlineThickness(5);

    textSust.setFont(font);
    textSust.setCharacterSize(35);
    textSust.setFillColor(sf::Color::White);
    textSust.setPosition((motor2D->getSize().x / 2) - 135, (motor2D->getSize().y / 2) - 250);
    textSust.setOutlineColor(sf::Color::Black);
    textSust.setOutlineThickness(5);
    textSust.setString("Ya tienes dos \nobjetos encima, si \nlo quieras \ndeshazte de uno");

    nombreObjeto_quehace.setFont(font);
    nombreObjeto_quehace.setCharacterSize(33);
    nombreObjeto_quehace.setFillColor(sf::Color::White);
    nombreObjeto_quehace.setPosition((motor2D->getSize().x / 2) - 155, (motor2D->getSize().y / 2) - 230);
    nombreObjeto_quehace.setOutlineColor(sf::Color::Black);
    nombreObjeto_quehace.setOutlineThickness(5);

    objeto_quehace.setFont(font);
    objeto_quehace.setCharacterSize(33);
    objeto_quehace.setFillColor(sf::Color::White);
    objeto_quehace.setPosition((motor2D->getSize().x / 2) - 155, (motor2D->getSize().y / 2) - 190);
    objeto_quehace.setOutlineColor(sf::Color::Black);
    objeto_quehace.setOutlineThickness(5);

    float escaladoBarras = 1.43f;
    float escaladoBarrasy = 0.8f;

    float escaladoBarras2 = 2.02f;
    float escaladoBarras2y = 1.0f;

    barraProgreso = new sf::RectangleShape();
    barraProgreso->setSize(sf::Vector2f(0, 30));
    barraProgreso->setFillColor(sf::Color::Blue);
    barraProgreso->setScale(escaladoBarras, escaladoBarrasy);
    // Ajustamos la posición de la barra de progreso.
    barraProgreso->setPosition((motor2D->getSize().x * 4 / 5) - 85, motor2D->getSize().y - motor2D->getSize().y + 102);

    barraProgresoFondo = new sf::RectangleShape();
    barraProgresoFondo->setSize(sf::Vector2f(200, 30));
    barraProgresoFondo->setFillColor(sf::Color::Green);
    barraProgresoFondo->setScale(escaladoBarras2, escaladoBarras2y);
    // Ajustamos la posición de la barra de progreso.
    barraProgresoFondo->setPosition((motor2D->getSize().x * 4 / 5) - 200, motor2D->getSize().y - motor2D->getSize().y + 52);

    barra_armor = new sf::RectangleShape();
    barra_armor->setSize(sf::Vector2f(200, 30));
    barra_armor->setFillColor(sf::Color(128, 128, 128));
    barra_armor->setScale(escaladoBarras2, escaladoBarras2y);
    // Ajustamos la posición de la barra de progreso.
    barra_armor->setPosition((motor2D->getSize().x * 4 / 5) - 200, motor2D->getSize().y - motor2D->getSize().y + 52);

    sprite->setOrigen(75 / 2, 75 / 2);
    sprite->setRectTextura(0 * 75, 0 * 75, 75, 75);
    sprite->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y / 2);

    sf::Vector2u numeretes_txt = puntuacion->getSprite().getTexture()->getSize();
    puntuacion->setOrigen(numeretes_txt.x / 2.0f, numeretes_txt.y / 2.0f);
    puntuacion->setPosition((motor2D->getSize().x / 2) + 1870, (motor2D->getSize().y / 2) - 20);
    puntuacion->setTileDinamico(0, 0, 160, 160);
    puntuacion->escalarSprite(1.5f);

    sf::Vector2u textureSizeFondo_objeto1 = fondo_objeto1->getSprite().getTexture()->getSize();
    fondo_objeto1->setOrigen(textureSizeFondo_objeto1.x / 2.0f, textureSizeFondo_objeto1.y / 2.0f);
    fondo_objeto1->setPosition((motor2D->getSize().x / 2) + 630, (motor2D->getSize().y / 2) + 120);
    fondo_objeto1->setTile(0, 0);
    fondo_objeto1->escalarSprite(2.5f);

    sf::Vector2u textureSizeFondo_objeto2 = fondo_objeto2->getSprite().getTexture()->getSize();
    fondo_objeto2->setOrigen(textureSizeFondo_objeto2.x / 2.0f, textureSizeFondo_objeto2.y / 2.0f);
    fondo_objeto2->setPosition((motor2D->getSize().x / 2) + 780, (motor2D->getSize().y / 2) + 120);
    fondo_objeto2->setTile(0, 0);
    fondo_objeto2->escalarSprite(2.5f);

    sf::Vector2u textureSize_objeto_cogido = objeto_recogido->getSprite().getTexture()->getSize();
    objeto_recogido->setOrigen(textureSize_objeto_cogido.x / 2.0f, textureSize_objeto_cogido.y / 2.0f);
    objeto_recogido->setPosition((motor2D->getSize().x / 2) + 40, (motor2D->getSize().y / 2) + 400);
    objeto_recogido->setTile(0, 0);
    objeto_recogido->escalarSprite(2.5f);

    sf::Vector2u textureSizeFondo_objeto_cogido = fondo_objeto_recogido->getSprite().getTexture()->getSize();
    fondo_objeto_recogido->setOrigen(textureSizeFondo_objeto_cogido.x / 2.0f, textureSizeFondo_objeto_cogido.y / 2.0f);
    fondo_objeto_recogido->setPosition((motor2D->getSize().x / 2) + 40, (motor2D->getSize().y / 2) + 400);
    fondo_objeto_recogido->setTile(0, 0);
    fondo_objeto_recogido->escalarSprite(2.5f);

    sf::Vector2u textureSizeFondo_objeto1_sust = fondo_objeto1_sust->getSprite().getTexture()->getSize();
    fondo_objeto1_sust->setOrigen(textureSizeFondo_objeto1_sust.x / 2.0f, textureSizeFondo_objeto1_sust.y / 2.0f);
    fondo_objeto1_sust->setPosition((motor2D->getSize().x / 2) + 130, (motor2D->getSize().y / 2) + 470);
    fondo_objeto1_sust->setTile(0, 0);
    fondo_objeto1_sust->escalarSprite(2.5f);

    sf::Vector2u textureSizeFondo_objeto2_sust = fondo_objeto2_sust->getSprite().getTexture()->getSize();
    fondo_objeto2_sust->setOrigen(textureSizeFondo_objeto2_sust.x / 2.0f, textureSizeFondo_objeto2_sust.y / 2.0f);
    fondo_objeto2_sust->setPosition((motor2D->getSize().x / 2) - 50, (motor2D->getSize().y / 2) + 470);
    fondo_objeto2_sust->setTile(0, 0);
    fondo_objeto2_sust->escalarSprite(2.5f);

    sf::Vector2u textureSize_objeto1_sust = objeto1_sust->getSprite().getTexture()->getSize();
    objeto1_sust->setOrigen(textureSize_objeto1_sust.x / 2.0f, textureSize_objeto1_sust.y / 2.0f);
    objeto1_sust->setPosition((motor2D->getSize().x / 2) + 130, (motor2D->getSize().y / 2) + 470);
    objeto1_sust->setTile(0, 0);
    objeto1_sust->escalarSprite(2.5f);

    sf::Vector2u textureSize_objeto2_sust = objeto2_sust->getSprite().getTexture()->getSize();
    objeto2_sust->setOrigen(textureSize_objeto2_sust.x / 2.0f, textureSize_objeto2_sust.y / 2.0f);
    objeto2_sust->setPosition((motor2D->getSize().x / 2) - 50, (motor2D->getSize().y / 2) + 470);
    objeto2_sust->setTile(0, 0);
    objeto2_sust->escalarSprite(2.5f);

    sf::Vector2u textureSize_monedas = sprite_moneda->getSprite().getTexture()->getSize();
    sprite_moneda->setOrigen(textureSize_monedas.x / 2.0f, textureSize_monedas.y / 2.0f);
    sprite_moneda->setPosition((motor2D->getSize().x / 2) + 60, (motor2D->getSize().y / 2) + 270);
    sprite_moneda->setTile(1, 0);
    sprite_moneda->escalarSprite(1.7f);

    sf::Vector2u textureSizeBarra_fondo = barra_fondo->getSprite().getTexture()->getSize();
    barra_fondo->setOrigen(textureSizeBarra_fondo.x / 2.0f, textureSizeBarra_fondo.y / 2.0f);
    barra_fondo->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y - 160);

    sf::Vector2u textureSizeFondo_objeto_texto = fondo_texto_objeto->getSprite().getTexture()->getSize();
    fondo_texto_objeto->setOrigen(textureSizeFondo_objeto_texto.x / 2.0f, textureSizeFondo_objeto_texto.y / 2.0f);
    fondo_texto_objeto->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) - 70);

    sf::Vector2u textureSizeFondo_sustitucion = fondo_sustitucion->getSprite().getTexture()->getSize();
    fondo_sustitucion->setOrigen(textureSizeFondo_sustitucion.x / 2.0f, textureSizeFondo_sustitucion.y / 2.0f);
    fondo_sustitucion->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) - 70);
    fondo_sustitucion->escalarSprite(1.0f);

    sf::Vector2u textureSizeFondo_quehace = fondo_quehace->getSprite().getTexture()->getSize();
    fondo_quehace->setOrigen(textureSizeFondo_quehace.x / 2.0f, textureSizeFondo_quehace.y / 2.0f);
    fondo_quehace->setPosition((motor2D->getSize().x / 2) + 50, (motor2D->getSize().y / 2) - 190);
    fondo_quehace->escalarSpritePorValor(1.4f, 0.2f);

    sf::Vector2u textureSizeFondo_monedas = banner_monedas->getSprite().getTexture()->getSize();
    banner_monedas->setOrigen(textureSizeFondo_monedas.x / 2.0f, textureSizeFondo_monedas.y / 2.0f);
    banner_monedas->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) - 70);
    banner_monedas->escalarSprite(1.0f);

    boton_ok_monedas->centrarOrigen();
    boton_ok_monedas->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) + 30);
    boton_ok_monedas->escalarSprite(0.7);

    boton_cont->centrarOrigen();
    boton_cont->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) + 30);
    boton_cont->escalarSprite(0.7);
    // Salir
    boton_pass->centrarOrigen();
    boton_pass->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) + 100);
    boton_pass->escalarSprite(0.7);

    boton_quitar1->centrarOrigen();
    boton_quitar1->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) - 40);
    boton_quitar1->escalarSprite(0.7);
    // Salir
    boton_quitar2->centrarOrigen();
    boton_quitar2->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) + 30);
    boton_quitar2->escalarSprite(0.7);

    sf::Vector2u textureSizeBarra_marco = barra_marco->getSprite().getTexture()->getSize();
    barra_marco->setOrigen(textureSizeBarra_marco.x / 2.0f, textureSizeBarra_marco.y / 2.0f);
    barra_marco->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y - 160);

    sf::Vector2u textureSizeBarra_vida = barra_vida->getSprite().getTexture()->getSize();
    barra_vida->setOrigen(textureSizeBarra_vida.x / 2.0f, textureSizeBarra_vida.y / 2.0f);
    barra_vida->setPosition(motor2D->getSize().x * 4 / 5, motor2D->getSize().y - motor2D->getSize().y + 70);
    barra_vida->escalarSprite(0.7);

    sf::Vector2u textureSizeBarra_ritmo = barra_ritmo->getSprite().getTexture()->getSize();
    barra_ritmo->setOrigen(textureSizeBarra_ritmo.x / 2.0f, textureSizeBarra_ritmo.y / 2.0f);
    barra_ritmo->setPosition((motor2D->getSize().x * 4 / 5) + 57, motor2D->getSize().y - motor2D->getSize().y + 115);
    barra_ritmo->escalarSprite(0.5);

    sf::Vector2u textureSizeAnillo = ani->getSprite().getTexture()->getSize();
    ani->setOrigen(textureSizeAnillo.x / 2.0f, textureSizeAnillo.y / 2.0f);
    ani->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y - 160);

    sf::Vector2u textureSizeNota = nota->getSprite().getTexture()->getSize();
    nota->setOrigen(textureSizeNota.x / 2.0f, textureSizeNota.y / 2.0f);
    nota->setPosition(1210, motor2D->getSize().y - 163);

    sf::Vector2u textureSizeNotaVerde = notaverde->getSprite().getTexture()->getSize();
    notaverde->setOrigen(textureSizeNotaVerde.x / 2.0f, textureSizeNotaVerde.y / 2.0f);
    notaverde->setPosition(1210, motor2D->getSize().y - 163);

    sf::Vector2u textureSizeNotaRoja = notaroja->getSprite().getTexture()->getSize();
    notaroja->setOrigen(textureSizeNotaRoja.x / 2.0f, textureSizeNotaRoja.y / 2.0f);
    notaroja->setPosition(1210, motor2D->getSize().y - 163);

    tutorial = new MySprite("../../../data/ANGEL/fondos/tuto_1.png");
    tutorial->centrarOrigen();
    tutorial->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y / 2);
    continuar = new MySprite(directorio + "botones/continuar_normal.png", directorio + "botones/continuar_hover.png", directorio + "botones/continuar_click.png");
    continuar->centrarOrigen();
    continuar->setPosition(motor2D->getSize().x / 2, (motor2D->getSize().y / 2) + 300);
}

void JSJuego::initializeMusic()
{

    int dificultad = JSMenu::getInstance()->getDificultad();

    miMusica.cargarCancionesPorNivel(1, dificultad);
    int random = miMusica.devolverCancionRandom();
    miMusica.seleccionarCancionIndice(random);
    miMusica.seleccionarSiguienteCancion();

    // miMusica.seleccionarCancionNombre("Pump-It.ogg");
    // std::cout << "Reproduciendo a " << miMusica.obtenerBPM() << " BPM." << std::endl;

    bpm = miMusica.obtenerBPM();

    velocidad = (miMusica.obtenerBPM() * 2.13) / 110;
}

JSJuego *JSJuego::instance = nullptr;

JSJuego *JSJuego::getInstance()
{
    if (instance == nullptr)
    {
        instance = new JSJuego();
    }
    return instance;
}

// Funciones

void JSJuego::endState()
{
    std::cout << "Fin del Juego"
              << "\n";
}

void JSJuego::cambiarBatallaBien(bool ok)
{
    batallaBien = ok;
}

void JSJuego::cambiarGeneracion(bool ok)
{
    generado = ok;
}

float JSJuego::getVida()
{
    return personaje->devolverVida();
}

void JSJuego::actualizarVida(float hp, float armadura)
{
    personaje->quitarVida(hp, armadura);
}

void JSJuego::establecerTutorial()
{
    std::string pathCompleto = "../../../data/ANGEL/txt/";
    std::ifstream file(pathCompleto + "tutorial.txt", std::ios::in); // Abre el archivo para lectura
    if (file.is_open())
    {
        file >> num;  // Lee el volumen desde el archivo
        file.close(); // Cierra el archivo
        if (num && num != 0)
        {
            tutorialCont = num;
            std::cout << "El tutorial es:" << tutorialCont << std::endl;
            std::ofstream outFile(pathCompleto + "tutorial.txt", std::ios::out | std::ios::trunc);
            if (outFile.is_open())
            {
                outFile << 0;    // Escribe 0 en el archivo
                outFile.close(); // Cierra el archivo después de escribir
            }
        }
        else
        {
            tutorialCont = 0;
        }
    }
}

void JSJuego::cogerObjeto()
{
    // std::cout << "Entro a coger objetos" << std::endl;
    if (objeto1.DarNombreObjeto() == "")
    {
        objeto1.asignarType(objetoN);
        int lvl1 = JSTienda::getInstance()->obtenerNivelPorID(objeto1.devolverObjeto());

        objeto1.establecerNivel(lvl1);

        objeto2_sust->setTile(0, objetoN);

        // std::cout << "Objeto cogido con int: " << objeto1.devolverObjeto() << std::endl;
    }
    else if (objeto2.DarNombreObjeto() == "")
    {
        objeto2.asignarType(objetoN);
        int lvl2 = JSTienda::getInstance()->obtenerNivelPorID(objeto2.devolverObjeto());

        objeto2.establecerNivel(lvl2);
        objeto1_sust->setTile(0, objetoN);
    }
    else
    {
        // std::cout << "no queda hueco para objetos" << std::endl;
        sustituir = true;
    }
}

void JSJuego::handleButtonClick(const std::string &buttonName)
{

    // std::cout << "He puslado el boton, con este nombre " << buttonName << std::endl;

    if (buttonName.empty())
        return;

    if (buttonName == "cont")
    {
        batallaBien = false;
        cogerObjeto();
    }

    if (buttonName == "contM")
    {
        cogerMonedas = false;
        JSTienda::getInstance()->actualizarEstadistica("../../../data/OCTAVIO/tienda.xml", "monedas", JSTienda::getInstance()->devolverMonedas() + monedas);
    }

    if (buttonName == "pass")
    {
        batallaBien = false;
        sustituir = false;
    }

    if (buttonName == "quit1")
    {
        batallaBien = false;
        sustituir = false;
        objeto1.asignarType(objetoN);
        int lvl1 = JSTienda::getInstance()->obtenerNivelPorID(objeto1.devolverObjeto());

        objeto1.establecerNivel(lvl1);

        objeto2_sust->setTile(0, objetoN);
    }

    if (buttonName == "quit2")
    {
        batallaBien = false;
        sustituir = false;
        objeto2.asignarType(objetoN);
        int lvl2 = JSTienda::getInstance()->obtenerNivelPorID(objeto2.devolverObjeto());

        objeto2.establecerNivel(lvl2);
        objeto1_sust->setTile(0, objetoN);
    }

    if (buttonName == "continuar")
    {
        if (tutorialCont > 0)
        {
            std::cout << "El tutorial antes es:" << tutorialCont << std::endl;
            if (tutorialCont == 1)
            {
                tutorial->cambiarSprite("../../../data/ANGEL/fondos/tuto_2.png");
                std::cout << "He entrado en el primer if:" << tutorialCont << std::endl;
                tutorialCont++;
            }
            else if (tutorialCont == 2)
            {
                tutorial->cambiarSprite("../../../data/ANGEL/fondos/tuto_3.png");
                std::cout << "He entrado en el segundo if:" << tutorialCont << std::endl;
                tutorialCont++;
            }
            else if (tutorialCont == 3)
            {
                tutorialCont = 0;
            }
            std::cout << "El tutorial despues es:" << tutorialCont << std::endl;
            batallaBien = false;
            sustituir = false;
        }
    }
}

void JSJuego::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void JSJuego::update(const float &dt, char &accion)
{
    // std::cout << "update" << std::endl;
    movFlecha = false;
    if (miMusica.estaParada())
    {
        miMusica.updateVolumen(false);
        miMusica.reproducirDesdePausa();
    }

    sf::Event event;

    this->updateKeybinds(dt);

    if (batallaBien || sustituir || tutorialCont != 0 || cogerMonedas)
    {
        sf::Vector2f mousePosition = this->motor2D->getMousePosition();

        if (clickTimer > 0)
        {
            clickTimer -= dt;
            if (clickTimer <= 0)
            {
                // Ahora que el temporizador ha finalizado, maneja la acción del botón
                handleButtonClick(lastClickedButton);
                lastClickedButton = ""; // Resetea el botón clickeado
                pulsado = false;
            }
        }
        else
        {
            if (fondo_objeto_recogido->getHitbox().contains(mousePosition))
            {
                pintahover = true;
            }
            else
            {
                pintahover = false;
            }

            if (!cogerMonedas)
            {
                boton_cont->cambiaEstado(boton_cont->getHitbox().contains(mousePosition) ? "hover" : "normal");
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && boton_cont->getHitbox().contains(mousePosition) && pulsado == false && sustituir == false)
                {
                    boton_cont->cambiaEstado("click");
                    lastClickedButton = "cont"; // Guarda el botón clickeado
                    clickTimer = clickDuration; // Reiniciar temporizador
                    pulsado = true;
                }
            }

            boton_ok_monedas->cambiaEstado(boton_ok_monedas->getHitbox().contains(mousePosition) ? "hover" : "normal");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && boton_ok_monedas->getHitbox().contains(mousePosition) && pulsado == false && sustituir == false)
            {
                boton_ok_monedas->cambiaEstado("click");
                lastClickedButton = "contM"; // Guarda el botón clickeado
                clickTimer = clickDuration;  // Reiniciar temporizador
                pulsado = true;
            }

            continuar->cambiaEstado(continuar->getHitbox().contains(mousePosition) ? "hover" : "normal");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continuar->getHitbox().contains(mousePosition) && pulsado == false)
            {
                continuar->cambiaEstado("click");
                lastClickedButton = "continuar"; // Guarda el botón clickeado
                clickTimer = clickDuration;      // Reiniciar temporizador
                pulsado = true;
            }

            boton_pass->cambiaEstado(boton_pass->getHitbox().contains(mousePosition) ? "hover" : "normal");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && boton_pass->getHitbox().contains(mousePosition) && pulsado == false)
            {
                boton_pass->cambiaEstado("click");
                lastClickedButton = "pass"; // Guarda el botón clickeado
                clickTimer = clickDuration; // Reiniciar temporizador
                pulsado = true;
            }

            // boton_quitar1->cambiaEstado(boton_quitar1->getHitbox().contains(mousePosition) ? "hover" : "normal");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fondo_objeto2_sust->getHitbox().contains(mousePosition) && pulsado == false)
            {
                // boton_quitar1->cambiaEstado("click");
                lastClickedButton = "quit1"; // Guarda el botón clickeado
                clickTimer = clickDuration;  // Reiniciar temporizador
                pulsado = true;
            }

            // boton_quitar2->cambiaEstado(boton_quitar2->getHitbox().contains(mousePosition) ? "hover" : "normal");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fondo_objeto1_sust->getHitbox().contains(mousePosition) && pulsado == false)
            {
                // boton_quitar2->cambiaEstado("click");
                lastClickedButton = "quit2"; // Guarda el botón clickeado
                clickTimer = clickDuration;  // Reiniciar temporizador
                pulsado = true;
            }
        }
    }

    // std::cout << "Tengo los objetos: " << objeto1.DarNombreObjeto() << " y " << objeto2.DarNombreObjeto() << std::endl;

    this->relojUpdate.restart();

    sf::Vector2f posAntigua = personaje->getPosicion();
    int tileX = posAntigua.x / 32;
    int tileY = posAntigua.y / 32;

    // std::cout << accion << std::endl;

    std::stack<JState *> states = Juego::getInstance()->devolverStates();

    auto NPCbatalla = habitacionActual.checkNPCbatalla(tileX, tileY);
    if (NPCbatalla != nullptr)
    {

        // Se encontró un NPC, puedes proceder con las operaciones de batalla o lo que necesites hacer
        miMusica.pausarMusica();

        pentagrama.borrarTodas();

        std::cout << "Se encontró un NPC, preparando para la batalla." << std::endl;

        std::unique_ptr<Boss> boss = nullptr;

        if (NPCbatalla->getTipo() == "JEFE")
        {
            switch (static_cast<int>(level->getLevelType()))
            {
            case 0:
            {

                boss = BossFactory::createBoss(NPCbatalla->getPathSprite(), BossType::PRISION);
                boss->asignarTipoNivel(static_cast<int>(level->getLevelType()));
                std::cout << "Se ha creado a Hector. VIDA ALCACHOFA: " << boss->getVida() << std::endl;
                break;
            }
            case 1:
            {
                boss = BossFactory::createBoss(NPCbatalla->getPathSprite(), BossType::CATACUMBAS);
                boss->asignarTipoNivel(static_cast<int>(level->getLevelType()));
                std::cout << "Se ha creado a Hector. VIDA HECTOR: " << boss->getVida() << std::endl;

                break;
            }
            case 2:
            {

                boss = BossFactory::createBoss(NPCbatalla->getPathSprite(), BossType::JARDINES);
                boss->asignarTipoNivel(static_cast<int>(level->getLevelType()));
                std::cout << "Se ha creado a Hector. VIDA JARDIN: " << boss->getVida() << std::endl;
                break;
            }
            case 3:
            {
                boss = BossFactory::createBoss(NPCbatalla->getPathSprite(), BossType::COMEDOR);
                boss->asignarTipoNivel(static_cast<int>(level->getLevelType()));
                std::cout << "Se ha creado a Hector. VIDA COCINERO: " << boss->getVida() << std::endl;

                break;
            }
            case 4:
            {
                boss = BossFactory::createBoss(NPCbatalla->getPathSprite(), BossType::REY);
                boss->asignarTipoNivel(static_cast<int>(level->getLevelType()));
                std::cout << "Se ha creado a Hector. VIDA REY: " << boss->getVida() << std::endl;

                break;
            }
            default:
                std::cout << "ERROR BOSS" << std::endl;
                exit;
                break;
            }
        }
        else
        {
            boss = BossFactory::createBoss(NPCbatalla->getPathSprite(), BossType::NPC);
            boss->asignarTipoNivel(static_cast<int>(level->getLevelType()));
            boss->cambiarVidaNPC(NPCbatalla->getHp());
        }

        miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/thunder-sound-effect.ogg");

        std::cout << "LEVEL EN JUEGO: " << static_cast<int>(level->getLevelType()) << std::endl;
        if (boss->getTipo() == BossType::NPC)
        {
            std::string nombre = generarNombreAleatorio();
            std::string apellido = generarAdjetivoAleatorio();

            boss->asignarNombreNPC(nombre + " " + apellido);
        }
        Batalla::getInstance()->asignarTipoNivel(static_cast<int>(level->getLevelType()));
        // std::cout << "Vida NPC: " << NPCbatalla->hp <<std::endl;
        npcBatalla = NPCbatalla->getPathSprite() + "," + NPCbatalla->getTipo();
        Batalla::getInstance()->reiniciar();

        JSTransicion::getInstance()->setTipo("batalla");
        JSTransicion::getInstance()->resetState();

        boss->asignarSprite(JSTransicion::getInstance()->getEnemigo());

        Batalla::getInstance()->asignarBoss(move(boss));
        Batalla::getInstance()->asignarBonificacionDano(contador);
        Batalla::getInstance()->cambiarAInfinito(false);

        Batalla::getInstance()->pasarObjetos(objeto1.devolverObjeto(), 1, objeto2.devolverObjeto(), 1);

        states.push(JSTransicion::getInstance());
        Juego::getInstance()->actualizar(states);
        // Lo elimino sin comprobar porque o te mata o lo matas, no lo vas a ver
        habitacionActual.eliminarNPC(NPCbatalla);
    }

    switch (accion)
    {
    case 'Q':
        miMusica.pausarMusica();

        pentagrama.borrarTodas();
        JSMenuJuego::getInstance()->setFondo();
        states.push(JSMenuJuego::getInstance());

        Juego::getInstance()->actualizar(states);

        break;
    case 'W':
    case 'S':
    case 'A':
    case 'D':
    {

        if (!batallaBien && !sustituir && tutorialCont == 0)
        {
            int direccion = (accion == 'W') ? 1 : (accion == 'S') ? 2
                                              : (accion == 'A')   ? 3
                                                                  : 4;
            int puedoMover = level->checkNextTile(habitacionActual, necesitocargarhabitacion, tileX, tileY, direccion);
            if (puedoMover == 1)
            {
                personaje->update(direccion);
            }
            else if (puedoMover == 2)
            {
                personaje->update(direccion);
                miMusica.pausarMusica();
                JSTransicion::getInstance()->setTipo("final1");
                JSTransicion::getInstance()->resetState();
                states.push(JSTransicion::getInstance());
                Juego::getInstance()->actualizar(states);
            }
            else if (puedoMover == 3)
            {
                miMusica.pausarMusica();
                personaje->update(direccion);
                JSTransicion::getInstance()->setTipo("final2");
                JSTransicion::getInstance()->resetState();
                states.push(JSTransicion::getInstance());
                Juego::getInstance()->actualizar(states);
            }
            for (int i = 0; i < habitacionActual.getNpcs().size(); ++i)
            {
                auto &npc = habitacionActual.getNpcs()[i];
                if (npc->getTipo() == "ARQUERO" && npc->getContadorFlecha() == 0)
                {
                    npc->cargarFlechas(pathFlecha, npc->getPosicion(), personaje->getPosicion());
                }
                if (npc->getTipo() == "ARQUERO")
                {
                    npc->aumContador();
                }

                auto nuevapos = npc->nuevaPos(personaje->getPosicion());
                bool puedemover = habitacionActual.checkMoveEntidad(i, nuevapos.x, nuevapos.y);

                int maxIntentos = 10;
                int intentos = 0;
                while (!puedemover && intentos < maxIntentos)
                {
                    nuevapos = npc->nuevaPos(personaje->getPosicion());
                    puedemover = habitacionActual.checkMoveEntidad(i, nuevapos.x, nuevapos.y);
                    intentos++;
                }
                if (intentos == 10)
                {
                    nuevapos.x = npc->getX();
                    nuevapos.y = npc->getY();
                }
                npc->updateNpc(nuevapos);
            }

            pentagrama.comprobacionGolpeo(motor2D, pathNotaV, pathNotaR, contador);
            // ESTABA AQUI
        }
        movFlecha = true;
        break;
    }
    case 's':
        // pentagrama.agregarNotaInicial(pathNota, motor2D);
        // pentagrama.comprobacionGolpeo(motor2D, pathNotaV, pathNotaR, contador);

        break;

    case 'O':
        if (objeto1.esConsumible() == false)
        {
            // std::cout << "Se ha pulsado k y el objeto es: " << objeto1.esConsumible() << std::endl;
        }

        if (objeto1.esConsumible() == true)
        {
            int n = objeto1.usarObjeto();

            float suma = 0.0f;

            // std::cout << "El numero que tiene que aplicar es: " << n << std::endl;

            int c = 0;

            switch (n)
            {
            case 0:
                suma = 20 + (20 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->DarArmadura(suma);
                // std::cout << "Ahora su armadura es de: " << suma << std::endl;
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 1:
                suma = 50 + (50 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->DarArmadura(suma);
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 2:
                suma = 20 + (20 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->sumarVida(suma);
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 3:
                suma = 50 + (50 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->sumarVida(suma);
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 4:
                suma = 20 + (20 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                if (contador + suma >= 200)
                {
                    contador = 200;
                }
                else
                {
                    contador += suma;
                }
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/acoustic-guitar-c-major-chord-sound-effect_mod.ogg");
                break;
            case 5:
                suma = 50 + (50 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                if (contador + suma >= 200)
                {
                    contador = 200;
                }
                else
                {
                    contador += suma;
                }
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/acoustic-guitar-c-major-chord-sound-effect_mod.ogg");
                break;

            case 6:
                c = usarObjetoAleatorio(1);
                usarObjetoAleatorio(c);
                matoPersonaje();

                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/dados.ogg");
                objeto1.asignarType(0);
                break;
            case 7:
                suma = 40 + (40 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->sumarVida(-20);
                matoPersonaje();
                contador = contador + 40;
                if (contador > 200)
                {
                    contador = 200;
                }
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/sword-draw-sound-effect.ogg");
                break;
            case 8:
                if (contador - 30 <= 0)
                {
                    contador = 0;
                    personaje->sumarVida(30 - (30 - contador));
                }
                else
                {
                    suma = 50 + (50 * ((objeto1.obtenerNivelObjeto() - 1) / 2.0f));
                    personaje->sumarVida(50);
                    contador = contador - 30;
                }
                objeto1.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/sword-draw-sound-effect.ogg");
                break;
            case 11:
                if (level->getCurrentRoomName() != "C_B.tmx" && level->getCurrentRoomName() != "D_B.tmx" && level->getCurrentRoomName() != "J_B.tmx" && level->getCurrentRoomName() != "P_B.tmx" && level->getCurrentRoomName() != "T_B.tmx")
                {
                    necesitocargarhabitacion = true;
                    objeto1.asignarType(0);
                }

                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/tp.ogg");
                break;
            default:
                break;
            }
        }
        break;

    case 'P':
        if (objeto2.esConsumible() == true)
        {
            int n = objeto2.usarObjeto();

            float suma = 0.0f;

            int c = 0;

            switch (n)
            {

            case 0:
                suma = 20 + (20 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->DarArmadura(suma);
                // std::cout << "Ahora su armadura es de: " << suma << std::endl;
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 1:
                suma = 50 + (50 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->DarArmadura(suma);
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 2:
                suma = 20 + (20 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->sumarVida(suma);
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 3:
                suma = 50 + (50 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->sumarVida(suma);
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pocion.ogg");
                break;
            case 4:
                suma = 20 + (20 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                if (contador + suma >= 200)
                {
                    contador = 200;
                }
                else
                {
                    contador += suma;
                }
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/acoustic-guitar-c-major-chord-sound-effect_mod.ogg");
                break;
            case 5:
                suma = 50 + (50 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                if (contador + suma >= 200)
                {
                    contador = 200;
                }
                else
                {
                    contador += suma;
                }
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/acoustic-guitar-c-major-chord-sound-effect_mod.ogg");
                break;

            case 6:
                c = usarObjetoAleatorio(1);
                usarObjetoAleatorio(c);

                matoPersonaje();

                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/dados.ogg");
                objeto2.asignarType(0);
                break;
            case 7:
                suma = 40 + (40 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                personaje->sumarVida(-20);
                matoPersonaje();
                contador = contador + 40;
                if (contador > 200)
                {
                    contador = 200;
                }

                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/sword-draw-sound-effect.ogg");
                break;
            case 8:
                if (contador - 30 <= 0)
                {
                    contador = 0;
                    personaje->sumarVida(30 - (30 - contador));
                }
                else
                {
                    suma = 50 + (50 * ((objeto2.obtenerNivelObjeto() - 1) / 2.0f));
                    personaje->sumarVida(50);
                    contador = contador - 30;
                }
                objeto2.asignarType(0);
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/sword-draw-sound-effect.ogg");
                break;
            case 11:
                if (level->getCurrentRoomName() != "C_B.tmx" && level->getCurrentRoomName() != "D_B.tmx" && level->getCurrentRoomName() != "J_B.tmx" && level->getCurrentRoomName() != "P_B.tmx" && level->getCurrentRoomName() != "T_B.tmx")
                {
                    necesitocargarhabitacion = true;
                    objeto2.asignarType(0);
                }
                miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/tp.ogg");
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    velocidad = (miMusica.obtenerBPM() * 2.13) / 110;
}

sf::String JSJuego::getNPCBatalla()
{
    return npcBatalla;
}

void JSJuego::matoPersonaje()
{
    if (personaje->devolverVida() <= 0)
    {
        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        miMusica.pausarMusica();

        pentagrama.borrarTodas();
        JSTransicion::getInstance()->setTipo("muerte");

        JSTransicion::getInstance()->resetState();
        states.push(JSTransicion::getInstance());

        Juego::getInstance()->actualizar(states);
    }
}

int JSJuego::usarObjetoAleatorio(int cambio)
{
    int random = generateRandomObject(9);

    // std::cout << "Random: " << random << std::endl;

    int random2 = (random + 1) * cambio;

    random2 = (random2 % 8);

    random2 += 1;

    // std::cout << "Cambio es: " << cambio << std::endl;
    // std::cout << "Random2 es: " << random2 << std::endl;

    // std::cout << "-----------------------------------" << std::endl;

    switch (random2)
    {
    case 1:
        personaje->sumarVida(20);
        break;
    case 2:
        personaje->sumarVida(50);
        break;
    case 3:
        if (contador + 20 >= 200)
        {
            contador = 200;
        }
        else
        {
            contador += 20;
        }
        break;
    case 4:
        if (contador + 50 >= 200)
        {
            contador = 200;
        }
        else
        {
            contador += 20;
        }
        break;
    case 5:
        personaje->sumarVida(-20);
        contador = contador + 40;
        if (contador > 200)
        {
            contador = 200;
        }
        break;
    case 6:
        if (contador - 30 <= 0)
        {
            contador = 0;
            personaje->sumarVida(30 - (30 - contador));
        }
        else
        {
            personaje->sumarVida(50);
            contador = contador - 30;
        }
        break;
    case 7:
        personaje->DarArmadura(20);
        break;
    case 8:
        personaje->DarArmadura(50);
        break;
    }

    return random2;
}

void JSJuego::renderizadoInterfaz(sf::RenderTarget *target)
{
    int maxContador = 200;
    int maxVida = PersonajePrincipal::getInstance()->getVidaMax();
    int maxArmor = PersonajePrincipal::getInstance()->getArmorMax();

    // std::cout << "Vida maxima: " << maxVida << std::endl;
    sf::RenderStates states;

    this->motor2D->clear();

    if (fondoElegido == 0)
    {
        this->motor2D->draw(&this->fondo);
    }
    else if (fondoElegido == 1)
    {
        this->motor2D->draw(&this->fondo2);
    }

    sf::View vistaMapa = this->motor2D->getVentana().getDefaultView();
    sf::View vistaUI = this->motor2D->getVentana().getDefaultView();
    vistaMapa.move(-470.0f, -200.0f);
    vistaMapa.zoom(0.7f);
    this->motor2D->getVentana().setView(vistaMapa);

    // Dibujo de la habitación actual y otros elementos
    habitacionActual.draw(this->motor2D->getVentana(), states);

    // Dibuja al personaje principal
    this->motor2D->draw(personaje->getSprite());

    // Dibuja los NPCs y posibles flechas
    for (auto &npc : habitacionActual.getNpcs())
    {
        npc->moveNPC(deltaT);
        this->motor2D->draw(npc->getSprite());
        for (const auto &flecha : npc->getCarcaj())
        {
            if (npc->getTipo() == "ARQUERO")
            {
                flecha->moverFlecha(deltaT);
                this->motor2D->draw(flecha->devolverSprite());
            }
        }
    }

    habitacionActual.drawRest(this->motor2D->getVentana(), states);
    this->motor2D->getVentana().setView(vistaUI);

    this->motor2D->draw(&barra_fondo);
    pentagrama.render(this->motor2D);

    float porcentaje = static_cast<float>(contador) / maxContador;
    barraProgreso->setSize(sf::Vector2f(200 * porcentaje, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

    float porcentaje2 = static_cast<float>(personaje->devolverVida()) / maxVida;
    // std::cout << "Vida actual: " << personaje->devolverVida() << " y el porcentaje de vida es: " << porcentaje2 << std::endl;
    barraProgresoFondo->setSize(sf::Vector2f(200 * porcentaje2, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

    float porcentaje3 = static_cast<float>(personaje->devolverArmor()) / maxArmor;
    // std::cout << "Armadura PJ: " << PersonajePrincipal::getInstance()->devolverArmor() << std::endl;
    //  std::cout << "Vida actual: " << personaje->devolverVida() << " y el porcentaje de vida es: " << porcentaje2 << std::endl;
    barra_armor->setSize(sf::Vector2f(200 * porcentaje3, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

    this->motor2D->draw(&barra_marco);
    this->motor2D->draw(&ani);
    this->motor2D->drawRectangle(*barraProgresoFondo);
    this->motor2D->drawRectangle(*barra_armor);

    this->motor2D->draw(&barra_vida);

    this->motor2D->draw(&fondo_objeto1);
    this->motor2D->draw(&fondo_objeto2);

    comprobacionContador();

    if ((contador > 35 && contador < 73))
    {

        this->motor2D->draw(&fuego1);
        fuego1->setPosition((motor2D->getSize().x / 2) + 750, (motor2D->getSize().y / 2) - 20);
        fuego1->escalarSpritePorValor(4.0, 2.0);
        fuego1->updateAnimacion();
    }
    else if ((contador > 74 && contador < 125))
    {
        this->motor2D->draw(&fuego1);
        fuego1->setPosition((motor2D->getSize().x / 2) + 730, (motor2D->getSize().y / 2) - 40);
        fuego1->escalarSpritePorValor(6.0, 4.0);
        fuego1->updateAnimacion();
    }
    else if (contador > 124)
    {
        this->motor2D->draw(&fuego1);
        fuego1->setPosition((motor2D->getSize().x / 2) + 650, (motor2D->getSize().y / 2) - 100);
        fuego1->escalarSpritePorValor(12.0, 6.0);
        fuego1->updateAnimacion();
    }
    this->motor2D->draw(&puntuacion);

    if (objeto1.devolverObjeto() != 0)
    {
        // std::cout << "Lo pinto porque tiene id: " << objeto1.devolverObjeto() << std::endl;
        this->motor2D->draw(objeto1.getSprite());
    }

    if (objeto2.devolverObjeto() != 0)
    {
        this->motor2D->draw(objeto2.getSprite());
    }

    if (cogerMonedas)
    {
        this->motor2D->draw(&banner_monedas);
        this->motor2D->draw(&boton_ok_monedas);
        this->motor2D->draw(&sprite_moneda);
        cantidad_monedas.setString("Has encontrado: ");
        cantidad_monedas_num.setString(std::to_string(monedas));
        target->draw(cantidad_monedas);
        target->draw(cantidad_monedas_num);
    }
    else
    {
        if (batallaBien)
        {
            if (!generado)
            {
                int random = generateRandomObject(12);
                objetoN = random;
                Objeto obj = Objeto(pathObjetos, objetoN, 0);

                nombreObj = obj.DarNombreObjeto();

                std::string funcion = JSTienda::getInstance()->obtenerFuncionPorID(objetoN);

                // std::cout << "Entra a coger el nombre " << nombreObj << ". Su numero random es: " << random << std::endl;

                textObject.setString("Ohhh. Parece que el\n enemigo ha soltado\n un objeto. \nTu decides si cogerlo\n o dejarlo en el suelo");
                nombreObjeto_quehace.setString(nombreObj);
                objeto_quehace.setString(funcion);

                generado = true;

                objeto_recogido->setTile(0, objetoN);
            }

            this->motor2D->draw(&fondo_texto_objeto);
            this->motor2D->draw(&fondo_objeto_recogido);
            this->motor2D->draw(&objeto_recogido);
            this->motor2D->draw(&boton_cont);
            this->motor2D->draw(&boton_pass);
            target->draw(textObject);

            if (pintahover == true)
            {
                this->motor2D->draw(&fondo_quehace);
                target->draw(nombreObjeto_quehace);
                target->draw(objeto_quehace);
            }
        }
    }

    if (sustituir)
    {
        this->motor2D->draw(&fondo_sustitucion);
        // this->motor2D->draw(&boton_quitar1);
        // this->motor2D->draw(&boton_quitar2);
        this->motor2D->draw(&boton_pass);
        this->motor2D->draw(&fondo_objeto1_sust);
        this->motor2D->draw(&fondo_objeto2_sust);
        this->motor2D->draw(&objeto1_sust);
        this->motor2D->draw(&objeto2_sust);
        target->draw(textSust);
    }

    if (tutorialCont > 0 && tutorialCont < 4)
    {
        this->motor2D->draw(&tutorial);
        this->motor2D->draw(&continuar);
    }

    this->motor2D->display();
}

void JSJuego::comprobacionContador()
{
    if (contador >= 200)
    {
        if (contAct != 10)
        {
            contAct = 10;
            puntuacion->setTileDinamico(contAct, 0, 160, 160);
        }
    }
    else
    {
        int newTileIndex = contador / 18; // Calcula el índice del tile basado en el contador
        if (newTileIndex != contAct)
        { // Solo actualiza si el nuevo índice es diferente del actual
            contAct = newTileIndex;
            puntuacion->setTileDinamico(contAct, 0, 160, 160);
        }
    }
}

int JSJuego::generateRandomObject(int valor)
{

    // motor de números aleatorios basado en Mersenne Twister
    std::srand(static_cast<unsigned>(std::time(0)));

    int random = 0;

    random = (std::rand() % valor);

    return random + 1;
}

std::string JSJuego::generarNombreAleatorio()
{

    // motor de números aleatorios basado en Mersenne Twister
    std::srand(static_cast<unsigned>(std::time(0)));

    int random = 0;

    random = (std::rand() % nombres.size());

    return nombres[random];
}

std::string JSJuego::generarAdjetivoAleatorio()
{

    // motor de números aleatorios basado en Mersenne Twister
    std::srand(static_cast<unsigned>(std::time(0)));

    int random = 0;

    random = (std::rand() % adjetivos.size());

    return adjetivos[random];
}

void JSJuego::render(sf::RenderTarget *target)
{
    // std::cout << "render" << std::endl;

    if (!target)
    {
        target = &this->motor2D->getVentana();
    }

    intervalo = 60.0f / miMusica.obtenerBPM(); // Convertir BPM a segundos por beat

    float reloj = relojUpdate.getElapsedTime().asMilliseconds() / 66.6;
    reloj += 0.25;
    deltaT = std::min(1.f, reloj);
    deltaT = std::round(deltaT * 100) / 100.0;

    // std::cout << deltaT << std::endl;
    if (movFlecha == true)
    {
        sf::FloatRect hitboxPj = personaje->getHitbox();
        for (int i = 0; i < habitacionActual.getNpcs().size(); ++i)
        {
            auto &npc = habitacionActual.getNpcs()[i];
            if (npc->getTipo() == "ARQUERO")
            {
                sf::FloatRect hitboxFlecha = npc->getFlecha();

                sf::FloatRect interseccion;
                if (hitboxPj.intersects(hitboxFlecha, interseccion))
                {

                    float areaInterseccion = interseccion.width * interseccion.height;
                    float areaFlecha = hitboxFlecha.width * hitboxFlecha.height;

                    if (areaInterseccion >= 0.8 * areaFlecha)
                    {
                        personaje->quitarVidaFlecha();
                        if (objeto1.usarObjeto() == 9 && personaje->devolverVida() <= 0)
                        {
                            personaje->sumarVida(20);
                            objeto1.asignarType(0);
                            miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pacto.ogg");
                        }
                        else if (objeto2.usarObjeto() == 9 && personaje->devolverVida() <= 0)
                        {
                            personaje->sumarVida(20);
                            objeto2.asignarType(0);
                            miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/pacto.ogg");
                        }

                        matoPersonaje();

                        npc->cargarFlechas(pathFlecha, npc->getPosicion(), personaje->getPosicion());
                    }
                }
            }
        }
    }

    personaje->movePj(deltaT);

    if (!batallaBien && !sustituir && tutorialCont == 0)
    {
        pentagrama.update(motor2D, velocidad, pathNotaR, contador, deltaT);
    }

    if (!iniciada)
    {
        miMusica.reproducir();
        iniciada = true;
    }

    miMusica.sePuedeSiguienteCancion();

    // CONTROL DEL RELOJ PARA LANZAR LAS NOTAS
    // Asumimos que `clock` y `intervalo` son miembros adecuadamente inicializados de JSJuego
    if (clock.getElapsedTime().asSeconds() >= intervalo)
    {
        if (!batallaBien && !sustituir && tutorialCont == 0)
        {
            pentagrama.agregarNotaInicial(pathNota, motor2D); // Asumiendo que motor2D es accesible
        }

        switch (fondoElegido)
        {
        case 0:
            fondoElegido = 1;
            break;

        case 1:
            fondoElegido = 0;
            break;

        default:
            break;
        }

        clock.restart(); // Restablecer el reloj
    }

    if (necesitocargarhabitacion)
    {
        if (reseteoLevel)
        {
            // std::cout << "La habitacion actual es: " << level->getCurrentRoomName() << std::endl;
            habitacionActual = level->loadHabitacionActual();
            this->motor2D->clear(); // Limpiar la ventana después de cargar con éxito la nueva habitación
            necesitocargarhabitacion = false;
            reseteoLevel = false;
        }
        else
        {
            level->nextRoom();
            // miMusica.reproducirSonido();
            miMusica.reproducirSonido("../../../data/OCTAVIO/Sonidos/door-open.ogg");

            if (level->getCurrentRoomIndex() == 0)
            {
                level->changeLevel();

                int dificultad = JSMenu::getInstance()->getDificultad();

                miMusica.pararMusica();

                miMusica.cargarCancionesPorNivel(static_cast<int>(level->getLevelType()), dificultad);
                int random = miMusica.devolverCancionRandom();
                miMusica.seleccionarCancionIndice(random);
                miMusica.seleccionarSiguienteCancion();

                iniciada = false;
            }

            habitacionActual = level->loadHabitacionActual();
            this->motor2D->clear(); // Limpiar la ventana después de cargar con éxito la nueva habitación
            necesitocargarhabitacion = false;
        }
    }

    this->renderizadoInterfaz(target);
}

void JSJuego::resetearJuego(bool reset)
{
    if (reset)
    {
        necesitocargarhabitacion = true;
    }
    resetear = reset;
}

void JSJuego::resetearFunciones(int tipo)
{
    miMusica.pararMusica();

    contador = 0;

    iniciada = false;

    initializeMusic();

    Level::getInstance()->generateRandomRooms(LevelType::Carcel);
    Level::getInstance()->setCurrentRoomIndex(0);
    Level::getInstance()->setLevelType(LevelType::Carcel);
    reseteoLevel = true;

    PersonajePrincipal::getInstance()->quitarVida(PersonajePrincipal::getInstance()->getVidaMax(), 0);

    objeto1.asignarType(0);
    objeto2.asignarType(0);

    // std::cout << "Acabo de ser reseteado" << std::endl;
}

bool JSJuego::obtenerResetear()
{
    return resetear;
}

Objeto JSJuego::getObjeto1()
{
    return objeto1;
}

Objeto JSJuego::getObjeto2()
{
    return objeto2;
}

void JSJuego::gastarObjeto1()
{
    objeto1.asignarType(0);
    // std::cout << "He gastado el objeto 1: " << objeto1.devolverObjeto() << std::endl;
}

void JSJuego::gastarObjeto2()
{
    objeto2.asignarType(0);
}

void JSJuego::cambiarCogerMonedas(bool ok)
{
    cogerMonedas = ok;
}

void JSJuego::establecerMonedas(int money)
{
    monedas = money;
}
