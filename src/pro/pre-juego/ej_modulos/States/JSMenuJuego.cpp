#include "JSMenuJuego.h"

// Fuente

void JSMenuJuego::initBotones()
{
    // continuar
    botones_1["continuar"] = new MySprite(directorio + "botones/continuar_normal.png", directorio + "botones/continuar_hover.png", directorio + "botones/continuar_click.png");
    botones_1["continuar"]->centrarOrigen();
    botones_1["continuar"]->setPosition(960, 550);

    // Opciones
    botones_1["opciones"] = new MySprite(directorio + "botones/opciones_normal.png", directorio + "botones/opciones_hover.png", directorio + "botones/opciones_click.png");
    botones_1["opciones"]->centrarOrigen();
    botones_1["opciones"]->setPosition(960, 650);

    // Salir
    botones_1["salir"] = new MySprite(directorio + "botones/salir_normal.png", directorio + "botones/salir_hover.png", directorio + "botones/salir_click.png");
    botones_1["salir"]->centrarOrigen();
    botones_1["salir"]->setPosition(960, 750);

    // volver
    botones_2["volver"] = new MySprite(directorio + "botones/volver_normal.png", directorio + "botones/volver_hover.png", directorio + "botones/volver_click.png");
    botones_2["volver"]->centrarOrigen();
    botones_2["volver"]->setPosition(960, 650);

    // Barra de volumen
    barra_volumen = new MySprite(directorio + "barra_volumen.png");
    barra_volumen->centrarOrigen();
    barra_volumen->setPosition(960, 550);

    // Boton menos
    botones_2["boton_menos"] = new MySprite(directorio + "botones/boton_menos_normal.png", directorio + "botones/boton_menos_hover.png", directorio + "botones/boton_menos_click.png");
    botones_2["boton_menos"]->centrarOrigen();
    botones_2["boton_menos"]->setPosition(820, 550);

    // Boton mas
    botones_2["boton_mas"] = new MySprite(directorio + "botones/boton_mas_normal.png", directorio + "botones/boton_mas_hover.png", directorio + "botones/boton_mas_click.png");
    botones_2["boton_mas"]->centrarOrigen();
    botones_2["boton_mas"]->setPosition(1100, 550);
}

// Constructor y destructor
JSMenuJuego::JSMenuJuego() : JState(), opc(false), musica("../../../data/OCTAVIO/velocidades")
{
    initBotones();
    fondo = new MySprite(directorio + "fondos/carcel.png");
    transparente = new MySprite(directorio + "fondos/fondotransparente.png");

    titulo = new MySprite(directorio + "fondos/banner_titulo.png");
    titulo->centrarOrigen();
    titulo->setPosition(960, 270);

    subtitulo = new MySprite(directorio + "fondos/banner_subtitulo.png");
    subtitulo->centrarOrigen();
    subtitulo->setPosition(960, 350);

    motor2D = Motor2D::getInstance();

    musica.cargarCancionesPorNivel(1, 1);
    int random = musica.devolverCancionRandom();
    musica.seleccionarCancionIndice(random);
    musica.seleccionarSiguienteCancion();

    if (!font.loadFromFile(directorio + "Fonts/alagard.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    textVolumen.setFont(font);
    textVolumen.setCharacterSize(35);
    textVolumen.setFillColor(sf::Color::White);
    textVolumen.setPosition(855, 450);
    textVolumen.setOutlineColor(sf::Color::Black);
    textVolumen.setOutlineThickness(5);

    musica.crearBarraVolumen(960, 550, 198, 40);

    //musica.reproducir();

    std::cout << "Entro a reproducir desde aqui" << std::endl;

}

JSMenuJuego::~JSMenuJuego()
{
    delete fondo;
    delete transparente;
    delete barra_volumen;
    for (auto &boton : botones_1)
    {
        delete boton.second;
    }
    for (auto &boton : botones_2)
    {
        delete boton.second;
    }
}

JSMenuJuego *JSMenuJuego::instance = nullptr;

JSMenuJuego *JSMenuJuego::getInstance()
{
    if (instance == nullptr)
    {
        instance = new JSMenuJuego();
    }
    return instance;
}

// Funciones
void JSMenuJuego::endState()
{
    std::cout << "Fin del Menu"
              << "\n";
}

void JSMenuJuego::setFondo()
{
    int currentLevelType = static_cast<int>(Level::getInstance()->getLevelType());
    switch (currentLevelType)
    {
    case 0:
        fondo->cambiarSprite(directorio + "fondos/carcel.png");
        nivel = "Carcel";
        break;
    
    case 1:
        fondo->cambiarSprite(directorio + "fondos/catacumbas.png");
        nivel = "Catacumbas";
        break;
    case 2:
        fondo->cambiarSprite(directorio + "fondos/jardin.png");
        nivel = "Jardines";
        break;
    case 3:
        fondo->cambiarSprite(directorio + "fondos/comedor.png");
        nivel = "Comedor";
        break;
    case 4:
        fondo->cambiarSprite(directorio + "fondos/trono.png");
        nivel = "Trono";
        break;
    default:
        fondo->cambiarSprite(directorio + "fondos/fondotransparente.png");
        break;
    }
}

void JSMenuJuego::setFondoInfinito()
{
    fondo->cambiarSprite(directorio + "fondos/fondoInfinito.png");
}

void JSMenuJuego::updateKeybinds(const float &dt)
{
    checkForQuit();
}

void JSMenuJuego::update(const float &dt, char &accion)
{
    

    updateKeybinds(dt);

    if (musica.estaParada())
    {
        musica.reproducirDesdePausa();
    }
    musica.updateVolumen(true);

    sf::Vector2f mousePosition = motor2D->getMousePosition();

    if (clickTimer > 0)
    {
        clickTimer -= dt;
        if (clickTimer <= 0)
        {
            // Ahora que el temporizador ha finalizado, maneja la acción del botón
            handleButtonClick(lastClickedButton);
            lastClickedButton = ""; // Resetea el botón clickeado
        }
    }
    else
    {
        auto &buttons = opc ? botones_2 : botones_1; // Determina qué conjunto de botones usar
        for (auto &pair : buttons)
        {
            MySprite *boton = pair.second;
            boton->cambiaEstado(boton->getHitbox().contains(mousePosition) ? "hover" : "normal");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && boton->getHitbox().contains(mousePosition))
            {
                boton->cambiaEstado("click");
                lastClickedButton = pair.first; // Guarda el botón clickeado
                clickTimer = clickDuration;     // Reiniciar temporizador
            }
        }
    }
}

void JSMenuJuego::resetearEstadoBotones(std::map<std::string, MySprite *> &buttons)
{
    for (auto &pair : buttons)
    {
        pair.second->cambiaEstado("normal");
    }
}

void JSMenuJuego::handleButtonClick(const std::string &buttonName)
{
    if (buttonName.empty())
        return;

    if (buttonName == "continuar")
    {
        musica.pausarMusica();
        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        states.pop();
        Juego::getInstance()->actualizar(states);
        resetearEstadoBotones(botones_1);
    }

    if (buttonName == "opciones")
    {
        opc = true;
        resetearEstadoBotones(botones_1);
        volumen = musica.getVolumen();
        textVolumen.setString("Volumen: " + std::to_string(static_cast<int>(std::round(volumen))) + "%");
    }

    if (buttonName == "volver")
    {
        opc = false;
        resetearEstadoBotones(botones_2);
    }

    if (buttonName == "boton_menos" || buttonName == "boton_mas")
    {
        int change = (buttonName == "boton_mas") ? 2 : 1;
        musica.cambiarVolumen(change);
        musica.guardarVolumen(); // Guarda el nuevo volumen
        volumen = musica.getVolumen();
        textVolumen.setString("Volumen: " + std::to_string(static_cast<int>(std::round(volumen))) + "%");
    }

    if (buttonName == "salir")
    {
        musica.pausarMusica();

        JSJuego::getInstance()->resetearJuego(true);
        JSJuego::getInstance()->resetearFunciones(0);
        std::cout << "Juego resetedado" << std::endl;
        Juego::getInstance()->resetToMainMenu();
    }
}

void JSMenuJuego::renderBotones(sf::RenderTarget *target)
{
    if (opc)
    {
        target->draw(botones_2["volver"]->getSprite());
        musica.dibujarBarra(motor2D);
        target->draw(barra_volumen->getSprite());
        target->draw(textVolumen);
        target->draw(botones_2["boton_menos"]->getSprite());
        target->draw(botones_2["boton_mas"]->getSprite());

        return;
    }
    else
    {
        target->draw(botones_1["continuar"]->getSprite());
        target->draw(botones_1["opciones"]->getSprite());
        target->draw(botones_1["salir"]->getSprite());
    }
}

void JSMenuJuego::render(sf::RenderTarget *target)
{
    motor2D->clear();
    if (!target)
    {
        target = &motor2D->getVentana();
    }

    motor2D->draw(&fondo);
    motor2D->draw(&transparente);

    motor2D->draw(&titulo);
    motor2D->draw(&subtitulo);

    renderBotones(target);

    motor2D->display();
}
