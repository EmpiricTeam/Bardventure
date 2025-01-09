#include "JSTransicion.h"

// Fuente

// Constructor y destructor
JSTransicion::JSTransicion() : JState(), musica("../../../data/OCTAVIO/velocidades")
{
    JSJuego *juego = JSJuego::getInstance();

    fondo = new MySprite(directorio + "fondos/fondotransparente.png");
    fondoFinal = new MySprite(directorio + "fondos/final1.png");
    creditos = new MySprite(directorio + "fondos/creditos.png");
    creditos->setOrigen(960, 0);
    creditos->setPosition(960, 0);

    enemigo = new MySprite(directorio + "sprites/orco.png");
    enemigo->centrarOrigen();

    bardo = new MySprite(directorio + "sprites/bardo.png");
    bardo->centrarOrigen();
    bardo->escalarSprite(0.8);

    banda_texto2 = new MySprite(directorio + "fondos/muertobatalla.png");
    banda_texto2->centrarOrigen();

    versus = new MySprite("../../../data/ALE/Spritesheet/VS.png", // Ruta a la textura
                          90,                                     // Número de frames
                          64,
                          128,  // Tamaño de cada frame (supongamos 32x32 píxeles)
                          0.1f, // Duración de cada frame en segundos
                          10    // Número de frames por fila en la textura
    );
    versus->escalarSprite(4);
    versus->centrarOrigen();
    versus->setPosition(960, 340);

    motor2D = Motor2D::getInstance();

    if (!font.loadFromFile(directorio + "Fonts/InfoStory.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    textNivel.setFont(font);
    textNivel.setCharacterSize(35);
    textNivel.setFillColor(sf::Color::White);
    textNivel.setPosition(380, 450);

    // Iniciar el reloj al crear el estado
    startTime = std::chrono::steady_clock::now();

    actionTriggered = false;
    positionX = (0.0f);
    bandapostionX = (1900.0f);
    isMoving = true;
    tipo = "infinito";
}

JSTransicion::~JSTransicion()
{
    delete fondo;
    delete enemigo;
    delete bardo;
    delete banda_texto2;
    delete versus;
    delete creditos;
    delete fondoFinal;
}

JSTransicion *JSTransicion::instance = nullptr;

JSTransicion *JSTransicion::getInstance()
{
    if (instance == nullptr)
    {
        instance = new JSTransicion();
    }
    return instance;
}

void JSTransicion::endState()
{
    std::cout << "Fin del Menu"
              << "\n";
}

void JSTransicion::setTipo(std::string t)
{
    tipo = t;
}

void JSTransicion::setEnemigo()
{

    JSJuego *juego = JSJuego::getInstance();
    enemigoInfo = juego->getNPCBatalla();

    size_t pos = enemigoInfo.find(',');

    enemigoPath = enemigoInfo.substr(0, pos);
    enemigoTipo = enemigoInfo.substr(pos + 1);

    enemigo->cambiarSprite(enemigoPath);

    // Peon,alfil,reina,arquero

    if (enemigoTipo == "PEON")
    {
        enemigo->cambiarSprite(directorio + "sprites/orco.png");
        enemigo->escalarSprite(0.6);
    }
    else if (enemigoTipo == "ALFIL")
    {
        enemigo->cambiarSprite(directorio + "sprites/orco_casco.png");
        enemigo->escalarSprite(0.6);
    }
    else if (enemigoTipo == "REINA")
    {
        enemigo->cambiarSprite(directorio + "sprites/caballero.png");
        enemigo->escalarSprite(0.6);
    }
    else if (enemigoTipo == "ARQUERO")
    {
        enemigo->cambiarSprite(directorio + "sprites/arquero.png");
        enemigo->escalarSprite(0.6);
    }
    else if (enemigoTipo == "JEFE")
    {
        int currentLevelType = static_cast<int>(Level::getInstance()->getLevelType());
        switch (currentLevelType)
        {
        case 0:
            enemigo->cambiarSprite(directorio + "sprites/alcachofa.png");
            break;

        case 1:
            enemigo->cambiarSprite(directorio + "sprites/tortuga.png");
            break;
        case 2:
            enemigo->cambiarSprite(directorio + "sprites/garbanzo.png");
            break;
        case 3:
            enemigo->cambiarSprite(directorio + "sprites/motzarela.png");
            break;
        case 4:
            enemigo->cambiarSprite(directorio + "sprites/limon.png");
            enemigo->escalarSprite(0.6);
            break;
        default:
            fondo->cambiarSprite(directorio + "fondos/fondotransparente.png");
            break;
        }
    }
}

void JSTransicion::resetState()
{
    startTime = std::chrono::steady_clock::now(); // Reinicia el reloj
    actionTriggered = false;                      // Restablece la bandera para permitir la transición
    positionX = (0.0f);
    bandapostionX = (1920.0f);
    endPositionX = 960; 
    creditos->setPosition(960, 0);
    
    isMoving = true;
    versus->setFrameOne();

    if (tipo != "infinito" && tipo != "muerte" && tipo != "final1" && tipo != "final2" && tipo != "creditos")
    {

        setEnemigo();

        int currentLevelType = static_cast<int>(Level::getInstance()->getLevelType());
        if (currentLevelType == 0)
        {
            fondo->cambiarSprite(directorio + "fondos/carcel.png");
            nivel = "Carcel";
        }
        else if (currentLevelType == 1)
        {
            fondo->cambiarSprite(directorio + "fondos/catacumbas.png");
            nivel = "Catacumbas";
        }
        else if (currentLevelType == 2)
        {
            fondo->cambiarSprite(directorio + "fondos/jardin.png");
            nivel = "Jardines";
        }
        else if (currentLevelType == 3)
        {
            fondo->cambiarSprite(directorio + "fondos/comedor.png");
            nivel = "Comedor";
        }
        else if (currentLevelType == 4)
        {
            fondo->cambiarSprite(directorio + "fondos/trono.png");
            nivel = "Trono";
        }
    }
    else if (tipo == "muerte")
    {
        fondo->cambiarSprite(directorio + "fondos/fondoMuerte.png");
    }
    else if (tipo == "infinito")
    {
        fondo->cambiarSprite(directorio + "fondos/fondoInfinito.png");
        enemigo->cambiarSprite(directorio + "fondos/infinito.png");
        enemigo->escalarSprite(0.4);
    }
    else if (tipo == "final1")
    {
        fondoFinal->cambiarSprite(directorio + "fondos/final1.png");
    }
    else if (tipo == "final2")
    {
        fondoFinal->cambiarSprite(directorio + "fondos/final2.png");
    }
}

void JSTransicion::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void JSTransicion::update(const float &dt, char &accion)
{
    currentTime = std::chrono::steady_clock::now();
    auto totalElapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    this->relojUpdate.restart();
    if (tipo == "batalla")
    {
        if (totalElapsed >= 2.5)
        {
            Batalla::getInstance()->inicializar();
            std::stack<JState *> states = Juego::getInstance()->devolverStates();
            states.pop();
            states.push(Batalla::getInstance());
            Juego::getInstance()->actualizar(states);
        }
    }
    else if (tipo == "muerte")
    {
        if (totalElapsed >= 5)
        {
            JSJuego::getInstance()->resetearJuego(true);
            Juego::getInstance()->resetToMainMenu();
        }
    }
    else if (tipo == "infinito")
    {
        if (totalElapsed >= 3)
        {
            Batalla::getInstance()->inicializar();
            std::stack<JState *> states = Juego::getInstance()->devolverStates();
            states.pop();
            states.push(Batalla::getInstance());
            Juego::getInstance()->actualizar(states);
        }
    }
    else if (tipo == "final1" || tipo == "final2")
    {
        if (totalElapsed >= 5)
        {
            tipo = "creditos";
            resetState();
        }
    }
    else if (tipo == "creditos")
    {

        if (totalElapsed >= 50)
        {
            this->relojUpdate.restart();
            this->relojRender.restart();
            JSJuego::getInstance()->resetearJuego(true);
            Juego::getInstance()->resetToMainMenu();
        }
    }
}

void JSTransicion::renderizadoTransicion()
{
    float reloj = relojUpdate.getElapsedTime().asMilliseconds() / 66.6;
    reloj += 0.25;
    deltaT = std::min(1.f, reloj);
    deltaT = std::round(deltaT * 100) / 100.0;

    if (tipo == "batalla" || tipo == "infinito")
    {
        if (isMoving)
        {
            float moveStep = speed * deltaT;

            // Actualizar posición horizontal
            // Asegurarse de que los personajes se muevan hacia el centro
            if (positionX < endPositionX)
            {
                positionX += moveStep;
                enemigo->setPosition(positionX, 320);      // Asegúrate de que el '170' es la altura vertical deseada
                bardo->setPosition(1920 - positionX, 950); // Si 1920 es el ancho de la pantalla, ajusta según necesites
            }
            else
            {
                // Detener el movimiento cuando ambos personajes alcanzan el centro
                isMoving = false;
            }
        }

        this->motor2D->draw(&fondo);
        this->motor2D->draw(&enemigo);

        versus->updateAnimacion();
        this->motor2D->draw(&versus);

        this->motor2D->draw(&bardo);
    }
    else if (tipo == "muerte")
    {
        // Actualizar posición de la banda y texto
        if (isMoving)
        {
            float moveStep = speed * deltaT;

            // Actualizar posición de la banda y texto
            if (bandapostionX > endBandapostionX)
            {
                bandapostionX -= moveStep;
                banda_texto2->setPosition(bandapostionX + 1000, 630);
            }

            // Verificar si los movimientos han terminado
            if (bandapostionX <= endBandapostionX)
            {
                isMoving = false;
            }
        }
        this->motor2D->draw(&fondo);
        this->motor2D->draw(&banda_texto2);
    }
    else if (tipo == "final1" || tipo == "final2")
    {
        this->motor2D->draw(&fondoFinal);
    }
    else if (tipo == "creditos")
    {
        currentTimeRender = std::chrono::steady_clock::now();
        auto totalElapsedRender = std::chrono::duration_cast<std::chrono::seconds>(currentTimeRender - startTime).count();
        this->relojRender.restart();

        this->motor2D->draw(&creditos);

        if (totalElapsedRender >= 3)
        {
            if (isMoving)
            {
                float moveStep = speedCreditos * deltaT;

                // Actualizar posición horizontal
                // Asegurarse de que los personajes se muevan hacia el centro
                if (positionX > endPositionY)
                {
                    positionX -= moveStep;
                    creditos->setPosition(960, positionX);
                }
                else
                {
                    // Detener el movimiento cuando ambos personajes alcanzan el centro
                    isMoving = false;
                }
            }
        }

        
    }
}

void JSTransicion::render(sf::RenderTarget *target)
{
    this->motor2D->clear();
    if (!target)
    {
        target = &this->motor2D->getVentana();
    }

    renderizadoTransicion();

    this->motor2D->display();
}

MySprite *JSTransicion::getEnemigo()
{
    return enemigo;
}
