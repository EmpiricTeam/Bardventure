#include "JSMenu.h"

// Fuente

void JSMenu::initBotones()
{
    // Jugar
    botones_1["jugar"] = new MySprite(directorio + "botones/jugar_normal.png", directorio + "botones/jugar_hover.png", directorio + "botones/jugar_click.png");
    botones_1["jugar"]->centrarOrigen();
    botones_1["jugar"]->setPosition(460, 550);

    // Opciones
    botones_1["opciones"] = new MySprite(directorio + "botones/opciones_normal.png", directorio + "botones/opciones_hover.png", directorio + "botones/opciones_click.png");
    botones_1["opciones"]->centrarOrigen();
    botones_1["opciones"]->setPosition(460, 750);

    // Salir
    botones_1["salir"] = new MySprite(directorio + "botones/salir_normal.png", directorio + "botones/salir_hover.png", directorio + "botones/salir_click.png");
    botones_1["salir"]->centrarOrigen();
    botones_1["salir"]->setPosition(460, 850);

    // Dificil
    botones_1["dificil"] = new MySprite(directorio + "botones/dificil_normal.png", directorio + "botones/dificil_hover.png", directorio + "botones/dificil_click.png");
    botones_1["dificil"]->centrarOrigen();
    botones_1["dificil"]->setPosition(560, 450);

    // Facil
    botones_1["facil"] = new MySprite(directorio + "botones/facil_normal.png", directorio + "botones/facil_hover.png", directorio + "botones/facil_click.png");
    botones_1["facil"]->centrarOrigen();
    botones_1["facil"]->setPosition(360, 450);

    // Medio
    botones_1["medio"] = new MySprite(directorio + "botones/medio_normal.png", directorio + "botones/medio_hover.png", directorio + "botones/medio_click.png");
    botones_1["medio"]->centrarOrigen();
    botones_1["medio"]->setPosition(460, 450);

    // volver
    botones_2["volver"] = new MySprite(directorio + "botones/volver_normal.png", directorio + "botones/volver_hover.png", directorio + "botones/volver_click.png");
    botones_2["volver"]->centrarOrigen();
    botones_2["volver"]->setPosition(460, 650);

    // infinito
    botones_1["infinito"] = new MySprite(directorio + "botones/infinito_normal.png", directorio + "botones/infinito_hover.png", directorio + "botones/infinito_click.png");
    botones_1["infinito"]->centrarOrigen();
    botones_1["infinito"]->setPosition(370, 650);

    // mejora
    botones_1["mejora"] = new MySprite(directorio + "botones/mejora_normal.png", directorio + "botones/mejora_hover.png", directorio + "botones/mejora_click.png");
    botones_1["mejora"]->centrarOrigen();
    botones_1["mejora"]->setPosition(550, 650);

    // Barra de volumen
    barra_volumen = new MySprite(directorio + "barra_volumen.png");
    barra_volumen->centrarOrigen();
    barra_volumen->setPosition(460, 550);

    // Boton menos
    botones_2["boton_menos"] = new MySprite(directorio + "botones/boton_menos_normal.png", directorio + "botones/boton_menos_hover.png", directorio + "botones/boton_menos_click.png");
    botones_2["boton_menos"]->centrarOrigen();
    botones_2["boton_menos"]->setPosition(320, 550);

    // Boton mas
    botones_2["boton_mas"] = new MySprite(directorio + "botones/boton_mas_normal.png", directorio + "botones/boton_mas_hover.png", directorio + "botones/boton_mas_click.png");
    botones_2["boton_mas"]->centrarOrigen();
    botones_2["boton_mas"]->setPosition(600, 550);
}

// Constructor y destructor
JSMenu::JSMenu() : JState(), opc(false), musica("../../../data/OCTAVIO/velocidades"), dificultad(1)
{
    this->initBotones();
    this->fondo = new MySprite(directorio + "fondos/main.png");

    this->titulo = new MySprite(directorio + "fondos/banner_titulo.png");
    this->titulo->centrarOrigen();
    this->titulo->setPosition(460, 270);

    this->subtitulo = new MySprite(directorio + "fondos/banner_subtitulo.png");
    this->subtitulo->centrarOrigen();
    this->subtitulo->setPosition(460, 350);

    this->banner = new MySprite(directorio + "fondos/banner.png");
    this->banner->centrarOrigen();
    this->banner->setPosition(460, 627);

    this->banner_facil = new MySprite(directorio + "fondos/banner_facil.png");
    this->banner_facil->centrarOrigen();
    this->banner_facil->setPosition(775, 600);

    this->banner_medio = new MySprite(directorio + "fondos/banner_medio.png");
    this->banner_medio->centrarOrigen();
    this->banner_medio->setPosition(775, 600);

    this->banner_dificil = new MySprite(directorio + "fondos/banner_dificil.png");
    this->banner_dificil->centrarOrigen();
    this->banner_dificil->setPosition(775, 600);

    motor2D = Motor2D::getInstance();

    if (!font.loadFromFile(directorio + "Fonts/alagard.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    textVolumen.setFont(font);
    textVolumen.setCharacterSize(35);
    textVolumen.setFillColor(sf::Color::White);
    textVolumen.setPosition(355, 450);
    textVolumen.setOutlineColor(sf::Color::Black);
    textVolumen.setOutlineThickness(5);

    textDificultad.setFont(font);
    textDificultad.setCharacterSize(31);
    textDificultad.setFillColor(sf::Color::White);
    textDificultad.setPosition(655, 460);
    textDificultad.setOutlineColor(sf::Color::Black);
    textDificultad.setOutlineThickness(5);
    updateDificultadTexto();

    // musica.cargarVolumen();
    musica.reproducirPorNombre("gotmain.ogg");
    musica.crearBarraVolumen(460, 550, 198, 40);
}

JSMenu::~JSMenu()
{
    delete fondo;
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

JSMenu *JSMenu::instance = nullptr;

JSMenu *JSMenu::getInstance()
{
    if (instance == nullptr)
    {
        instance = new JSMenu();
    }
    return instance;
}

// Funciones
void JSMenu::endState()
{
    std::cout << "Fin del Menu"
              << "\n";
}

int JSMenu::getDificultad() const
{
    return dificultad;
}

void JSMenu::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void JSMenu::updateDificultadTexto()
{

    if (dificultad == 1)
    {
        textDificultad.setFillColor(sf::Color::Green);
        std::string dificultadStr = "Dificultad facil";
        textDificultad.setString(dificultadStr);
        botones_1["facil"]->cambiaEstado("click");
    }
    else if (dificultad == 2)
    {
        textDificultad.setFillColor(sf::Color::Yellow);
        std::string dificultadStr = "Dificultad media";
        textDificultad.setString(dificultadStr);
        botones_1["medio"]->cambiaEstado("click");
    }
    else
    {
        textDificultad.setFillColor(sf::Color::Red);
        std::string dificultadStr = "Dificultad dificil";
        textDificultad.setString(dificultadStr);
        botones_1["dificil"]->cambiaEstado("click");
    }
}

void JSMenu::update(const float &dt, char &accion)
{
    this->updateKeybinds(dt);

    if (musica.estaStop())
    {
        musica.reproducirDesdeParada();
    }
    musica.updateVolumen(true);

    sf::Vector2f mousePosition = this->motor2D->getMousePosition();

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
            updateDificultadTexto();
        }
    }
}

void JSMenu::resetearEstadoBotones(std::map<std::string, MySprite *> &buttons)
{
    for (auto &pair : buttons)
    {
        pair.second->cambiaEstado("normal");
    }
}

void JSMenu::handleButtonClick(const std::string &buttonName)
{
    if (buttonName.empty())
        return;

    if (buttonName == "jugar")
    {
        musica.pararMusica();

        if (JSJuego::getInstance()->obtenerResetear() == true)
        {
            std::cout << "Entro a resetear" << std::endl;
            JSJuego::getInstance()->resetearFunciones(1);
            JSJuego::getInstance()->resetearJuego(false);
        }
        JSJuego::getInstance()->establecerTutorial();

        JSMenuJuego::getInstance()->setFondo();
        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        states.push(JSJuego::getInstance());
        Juego::getInstance()->actualizar(states);
        resetearEstadoBotones(botones_1);
        std::cout << "Jugar" << std::endl;
    }

    if (buttonName == "infinito")
    {      
        musica.pararMusica();
        JSJuego::getInstance()->resetearFunciones(0);
        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        Batalla::getInstance()->asignarTipoNivel(static_cast<int>(0));
        Batalla::getInstance()->cambiarAInfinito(true);
        Batalla::getInstance()->reiniciar();
        Batalla::getInstance()->inicializar();
        // std::cout << "Vida NPC: " << NPCbatalla->hp <<std::endl;

        JSTransicion::getInstance()->setTipo("infinito");
        JSTransicion::getInstance()->resetState();
        

        states.push(JSTransicion::getInstance());
        Juego::getInstance()->actualizar(states);
    }

    if (buttonName == "mejora")
    {      
        musica.pararMusica();
        std::stack<JState *> states = Juego::getInstance()->devolverStates();

        states.push(JSTienda::getInstance());
        Juego::getInstance()->actualizar(states);
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

    if (buttonName == "facil")
    {
        dificultad = 1;
    }

    if (buttonName == "medio")
    {
        dificultad = 2;
    }

    if (buttonName == "dificil")
    {
        dificultad = 3;
    }

    if (buttonName == "salir")
    {
        this->quit = true;
    }
}

void JSMenu::renderBotones(sf::RenderTarget *target)
{
    if (opc)
    {
        target->draw(this->botones_2["volver"]->getSprite());
        musica.dibujarBarra(motor2D);
        target->draw(this->barra_volumen->getSprite());
        target->draw(this->botones_2["boton_menos"]->getSprite());
        target->draw(this->botones_2["boton_mas"]->getSprite());
        target->draw(textVolumen);

        return;
    }
    else
    {
        target->draw(this->botones_1["jugar"]->getSprite());
        target->draw(this->botones_1["opciones"]->getSprite());
        target->draw(this->botones_1["salir"]->getSprite());
        target->draw(this->botones_1["facil"]->getSprite());
        target->draw(this->botones_1["medio"]->getSprite());
        target->draw(this->botones_1["dificil"]->getSprite());
        target->draw(this->botones_1["infinito"]->getSprite());
        target->draw(this->botones_1["mejora"]->getSprite());
    }
}

void JSMenu::render(sf::RenderTarget *target)
{
    this->motor2D->clear();
    if (!target)
    {
        target = &this->motor2D->getVentana();
    }

    this->motor2D->draw(&this->fondo);

    if (dificultad == 1)
    {
        this->motor2D->draw(&this->banner_facil);
    }
    else if (dificultad == 2)
    {
        this->motor2D->draw(&this->banner_medio);
    }
    else
    {
        this->motor2D->draw(&this->banner_dificil);
    }
    this->motor2D->draw(&this->banner);
    this->motor2D->draw(&this->titulo);
    this->motor2D->draw(&this->subtitulo);
    this->renderBotones(target);

    target->draw(textDificultad);

    this->motor2D->display();
}
