#include "JSBatalla.h"

Batalla::Batalla() : JState()
{
    motor2D = Motor2D::getInstance();
    // Acceder a Juego para obtener el stack de estados

    valorVida = JSJuego::getInstance()->getVida();

    // std::cout << "Vida del personaje: " << valorVida << std::endl;

    std::srand(std::time(0));

    contador = 0;
    escaladoBarras = 0.7f;
    longitudBarraProgreso = 600.0f;
    alturaBarraProgreso = 30.0f;
    valorVidaBoss = 595;
    // valorVida = 600;
    bossBatalla = nullptr;
    BPM = 0.0f;

    // proyectil = new MySprite("../javier/batalla_base/resources/barra_batalla.png");
    // proyectil = new MySprite("../../../data/OCTAVIO/Texturas/nota.png");

    sf::Vector2f pos(motor2D->getSize().x / 2, motor2D->getSize().y - 60);
    setTexture();
    sprite->setPosition(pos.x, pos.y);
    sf::Vector2f rot(2.4, 2.4);
    // setScaleSprite(rot);

    // auto boss = BossFactory::createBoss("", BossType::REY);
    // asignarBoss(move(boss));

    int dificultad = JSMenu::getInstance()->getDificultad();

    musica = new Musica("../../../data/OCTAVIO/velocidades"); // Asumiendo que este es el path correcto
    musica->cargarCancionesPorNivel(1, dificultad);
    // std::cout << musica->cancionesDeNivel.size() << std::endl;

    int random = musica->devolverCancionRandom();
    musica->seleccionarCancionIndice(random);
    musica->seleccionarSiguienteCancion();

    float bpm = musica->obtenerBPM();
    actualizarVelocidadLanzamiento(bpm);
    musica->updateVolumen(false);

    musica->reproducir();

    inicializar();

    fondo = new MySprite("../../../data/JAVIER/catacumbasRealistas.jpg");
    fondo->setOrigen(0, 0);

    asignarBonificacionDano(0);

    if (!fuente.loadFromFile("../../../data/ANGEL/Fonts/alagard.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    esInfinita = false;
    contadorInfinito = 0;
    mensajes = new MySprite("../../../data/JAVIER/mensajes.png");

    carril = new MySprite("../../../data/JAVIER/carriles.png");
    carril->setOrigen(carril->getHitbox().width / 2, carril->getHitbox().height);
    carril->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y);

    objeto1 = std::make_unique<Objeto>("../../../data/ANGEL/sprites/items/spritesheet_objetos.png", JSJuego::getInstance()->getObjeto1().devolverObjeto(), 1);
    objeto2 = std::make_unique<Objeto>("../../../data/ANGEL/sprites/items/spritesheet_objetos.png", JSJuego::getInstance()->getObjeto2().devolverObjeto(), 1);

    inicializarSpritesObjetos();
}

Batalla::~Batalla()
{
    delete fondo;
    delete carril;
    delete sprite;
    delete barra_ataque;
    delete barra_vida_boss;
    delete barra_vida;
    delete proyectil;
    delete musica;
    delete mensajes;
}

Batalla *Batalla::instance = nullptr;

Batalla *Batalla::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Batalla();
    }
    return instance;
}

void Batalla::asignarBoss(std::unique_ptr<Boss> boss)
{
    std::cout << "Estoy en batalla. Vida:" << boss->getVida() << std::endl;
    bossBatalla = move(boss);
    maxValorVidaBoss = bossBatalla->getVida();
    std::cout << "Se ha asignado el boss. Vida:" << bossBatalla->getVida() << std::endl;

    bossNameText.setString(bossBatalla->getNombre());
    bossNameText.setCharacterSize(33);
    bossNameText.setOutlineColor(sf::Color::Black);
    bossNameText.setOutlineThickness(5);
}

void Batalla::setTexture()
{

    // sprite = new MySprite("../javier/batalla_base/resources/sprites.png");
    // sprite = new MySprite("../../../data/JAVIER/sprites.png");
    sprite = new MySprite("../../../data/ANGEL/sprites/bardo.png");
    sprite->centrar();
    sprite->escalarSprite(0.42);

    float hitboxScale = 0.3f; // El tamaño de la hitbox será el 50% del tamaño del sprite
    sf::FloatRect smallerHitbox;
    smallerHitbox.width = sprite->getHitbox().width * hitboxScale;
    smallerHitbox.height = sprite->getHitbox().height * hitboxScale;
    smallerHitbox.left = sprite->getPosition().x - (smallerHitbox.width / 2);
    smallerHitbox.top = sprite->getPosition().y - (smallerHitbox.height / 2);

    sf::FloatRect hitboxPersonaje = sprite->getHitboxPersonalizada();

    sprite->setHitboxPersonalizada(smallerHitbox);

    // sprite->setRectTextura(0 * 75, 3 * 75, 75, 75);
    // sprite->setOrigen(75 / 2, 75 / 2);
    //  sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
    //  sprite.setOrigin(75 / 2, 75 / 2);
}

void Batalla::setTextureBarraBatalla()
{
    float anadir = ((motor2D->getSize().x / 2) - (motor2D->getSize().x / 3)) / 2;
    sf::Vector2f pos(1395, motor2D->getSize().y - 215);
    sf::Vector2f puntoA(motor2D->getSize().x / 2, 0);
    sf::Vector2f puntoB((motor2D->getSize().x * 2 / 3) + anadir, motor2D->getSize().y);
    float deltaX = puntoB.x - puntoA.x;
    float deltaY = puntoB.y - puntoA.y;
    float radianes = atan2(deltaY, deltaX);
    float angulos = radianes * 180 / 3.14;

    float escaladoBarras = 0.7f;

    // barra_ataque = new MySprite("../javier/batalla_base/resources/barra_batalla.png");
    barra_ataque = new MySprite("../../../data/JAVIER/barra_batalla.png");

    barra_ataque->setOrigen(0, barra_ataque->tamText().y / 2);

    barra_ataque->setPosition(1395, motor2D->getSize().y - 215);
    // barra_ataque.setPosition(pos);
    barra_ataque->rotarSprite(angulos + 180);
    // barra_ataque.setRotation(angulos);
    anguloBarraProgreso = angulos;
    barra_ataque->escalarSprite(escaladoBarras);
}

void Batalla::setScaleSprite(sf::Vector2f rot)
{
    sprite->escalarSprite(rot.x);
}

void Batalla::addProyectil(std::unique_ptr<Proyectil> proyectilPasado)
{
    proyectilesPunteros.push_back(std::move(proyectilPasado));
}

void Batalla::addAtaque(std::unique_ptr<Proyectil> proyectilPasado)
{
    ataques.push_back(std::move(proyectilPasado));
}

void Batalla::eliminarPrimerProyectil()
{
    if (!proyectilesPunteros.empty())
    {
        proyectilesPunteros.erase(proyectilesPunteros.begin());
    }
}

std::vector<std::unique_ptr<Proyectil>>::iterator Batalla::eliminarProyectil(std::vector<std::unique_ptr<Proyectil>>::iterator it)
{
    return proyectilesPunteros.erase(it);
}

void Batalla::eliminarPrimerAtaque()
{
    if (!ataques.empty())
    {
        ataques.erase(ataques.begin());
    }
}

void Batalla::cambiarPosicionSinInterpolacion(sf::Vector2f pos)
{
    // sprite.setPosition(pos);
    sprite->setPosition(pos.x, pos.y);
}

int Batalla::getContador()
{
    return contador;
}

int Batalla::generateRandomObject()
{

    std::srand(static_cast<unsigned>(std::time(0)));

    int random = 0;

    random = (std::rand() % 10);

    return random;
}

int Batalla::getMaxContador()
{
    return maxContador;
}

std::vector<std::unique_ptr<Proyectil>> &Batalla::getProyectiles()
{
    return proyectilesPunteros;
}

std::vector<std::unique_ptr<Proyectil>> &Batalla::getAtaques()
{
    return ataques;
}

MySprite *Batalla::getSprite()
{
    return sprite;
}

void Batalla::actualizarContador(int incremento)
{
    contador += incremento;
    if (contador > maxContador)
    {
        contador = maxContador;
    }
    else if (contador < 0)
    {
        contador = 0;
    }

    actualizarBarraProgreso();
}

void Batalla::inicializarBarra()
{
    /*float borde = 20.0f * escaladoBarras;
    float anadir = ((motor2D->getSize().x /2) - (motor2D->getSize().x/3)) / 2;
    sf::Vector2f puntoA(motor2D->getSize().x/2, 0);
    sf::Vector2f puntoB((motor2D->getSize().x *2 / 3) + anadir, motor2D->getSize().y);
    float deltaX = puntoB.x - puntoA.x;
    float deltaY = puntoB.y - puntoA.y;
    float radianes = atan2(deltaY, deltaX);
    float angulos = radianes * 180/ 3.14;

    sf::Vector2f posicionEsquina = sf::Vector2f(barra_ataque->getPosition().x , barra_ataque->getPosition().y);

    sf::Vector2f nuevo1 = sf::Vector2f(
        posicionEsquina.x + sin(radianes) * borde,
        posicionEsquina.y - cos(radianes) * borde
    );*/

    barraProgreso.setSize(sf::Vector2f(0, 30));
    barraProgreso.setFillColor(sf::Color::Blue);
    barraProgreso.setPosition(1395, motor2D->getSize().y - 215);
    barraProgreso.setOrigin(0, barraProgreso.getSize().y / 2);

    barraProgreso.setRotation(anguloBarraProgreso + 180);
    barraProgreso.setScale(escaladoBarras, escaladoBarras);
}

void Batalla::actualizarBarraProgreso()
{
    float porcentaje = static_cast<float>(contador) / maxContador;
    barraProgreso.setSize(sf::Vector2f(longitudBarraProgreso * porcentaje, alturaBarraProgreso));
}

void Batalla::endState()
{
    // std::cout << "Fin del Juego" << "\n";
}

void Batalla::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void Batalla::update(const float &dt, char &accion)
{
    // std::cout << "Vida Boss" << bossBatalla->getVida() << std::endl;
    this->updateKeybinds(dt);

    if (musica->estaParada())
    {
        musica->updateVolumen(false);
        musica->reproducirDesdePausa();
    }

    if (contador >= maxContador - 10)
    {
        // Revisa si han pasado al menos 500 milisegundos
        if (blinkTimer.getElapsedTime().asMilliseconds() >= 200)
        {
            // Resetea el reloj para el siguiente intervalo
            blinkTimer.restart();

            // Alternar el color
            if (isYellow)
            {
                barraProgreso.setFillColor(sf::Color::Blue);
                isYellow = false;
            }
            else
            {
                sf::Color goldColor(255, 215, 0); // RGB para dorado
                barraProgreso.setFillColor(goldColor);
                isYellow = true;
            }
        }
    }
    else
    {
        // Si el contador es menor, asegúrate de que el color sea azul y reinicia el estado
        if (isYellow)
        {
            barraProgreso.setFillColor(sf::Color::Blue);
            isYellow = true; // Restablece el color a azul
        }
        blinkTimer.restart(); // También reinicia el temporizador si sales del modo parpadeo
    }

    if (valorVida <= 0)
    {
        musica->pararMusica();
        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        reiniciar();
        JSTransicion::getInstance()->setTipo("muerte");
        JSTransicion::getInstance()->resetState();
        states.push(JSTransicion::getInstance());
        Juego::getInstance()->actualizar(states);
    }

    if (bossBatalla->getVida() <= 0)
    {
        // std::cout << "Vida Boss:" << bossBatalla->getVida() << std::endl;
        // std::cout << "Armadura PJ: " << PersonajePrincipal::getInstance()->devolverArmor() << std::endl;
        musica->pararMusica();

        int random = generateRandomObject();

        // std::cout << "El numero random es: " << random << std::endl;

        if (random > 4)
        {
            JSJuego::getInstance()->cambiarGeneracion(true);
            JSJuego::getInstance()->cambiarBatallaBien(false);
            JSJuego::getInstance()->cambiarCogerMonedas(true);
            int num = JSJuego::getInstance()->generateRandomObject(3);
            JSJuego::getInstance()->establecerMonedas(num);
        }
        else
        {
            JSJuego::getInstance()->cambiarGeneracion(false);
            JSJuego::getInstance()->cambiarBatallaBien(true);
            JSJuego::getInstance()->cambiarCogerMonedas(true);
            int num = JSJuego::getInstance()->generateRandomObject(3);
            JSJuego::getInstance()->establecerMonedas(num);
        }

        JSJuego::getInstance()->actualizarVida(valorVida, PersonajePrincipal::getInstance()->devolverArmor());

        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        states.pop();
        Juego::getInstance()->actualizar(states);
        reiniciar();
    }

    if (temporizadorProyectiles.getElapsedTime().asSeconds() >= (60.0f / BPM))
    {
        generarProyectil(false);           // Genera un nuevo proyectil
        temporizadorProyectiles.restart(); // Reinicia el temporizador
    }

    for (int i = 0; i < proyectilesPunteros.size(); i++)
    {
        auto &proyectil = proyectilesPunteros[i];

        if (proyectil->getPosicionSprite().y > motor2D->getSize().y)
        {
            // Manejo de proyectiles fuera de la pantalla
        }
        else
        {
            proyectil->actualizarPosicionAnterior(proyectil->getPosicionActual());
            // proyectil->posicionAnterior = proyectil->posicionActual;
            //  sf::Vector2f movimiento = sf::Vector2f(direccion.x * proyectil->velocidad * delta, direccion.y * proyectil->velocidad * delta);
            sf::Vector2f movimiento = sf::Vector2f(proyectil->getDireccion().x * 12, proyectil->getDireccion().y * 12);
            proyectil->actualizarPosicionActual(proyectil->getPosicionActual() + movimiento);
            // proyectil->posicionActual = proyectil->posicionActual + movimiento;
            //  proyectil->sprite.setPosition(proyectil->posicionActual);

            if (proyectil->getPosicionActual().y > motor2D->getSize().y / 2 - 200 && proyectil->getPosicionActual().y < motor2D->getSize().y - 400)
            {
                if ((bossBatalla->getTipo() == BossType::JARDINES || bossBatalla->getTipo() == BossType::REY) && !proyectil->getCambiado())
                {
                    if (rand() % 100 < 2)
                    { // Genera un número entre 0 y 99
                        cambiarCarrilProyectil(proyectil);
                        // std::cout << "Cambio de carril en: " << proyectil->posicionActual.y <<  std::endl;
                        proyectil->cambiar(true);
                        // proyectil->cambiado = true;
                    }
                }
            }
            float currentScale = proyectil->getSprite()->obtenerEscala().x;
            // std::cout << "Escala Proyectil: " << proyectil->getSprite()->obtenerEscala().x << std::endl;
            proyectil->escalar(currentScale * 1.01);

            // La actualización de la posición del sprite para la renderización con interpolación se hará en otro lugar
        }
    }

    for (int i = 0; i < ataques.size(); i++)
    {
        auto &ataque = ataques[i];

        if (ataque->getPosicionSprite().y > motor2D->getSize().y)
        {
            // Manejo de proyectiles fuera de la pantalla
        }
        else
        {
            ataque->actualizarPosicionAnterior(ataque->getPosicionActual());
            // ataque->posicionAnterior = ataque->posicionActual;
            //  sf::Vector2f movimiento = sf::Vector2f(direccion.x * proyectil->velocidad * delta, direccion.y * proyectil->velocidad * delta);
            sf::Vector2f movimiento = sf::Vector2f(ataque->getDireccion().x * 24, ataque->getDireccion().y * 24);
            ataque->actualizarPosicionActual(ataque->getPosicionActual() + movimiento);
            // ataque->posicionActual = ataque->posicionActual + movimiento;
            float currentScale = ataque->getSprite()->obtenerEscala().x;
            // std::cout << "Escala Proyectil: " << ataque->getSprite()->obtenerEscala().x << std::endl;
            ataque->escalar(currentScale * 0.98);
        }
    }

    if (!proyectilesPunteros.empty() && (proyectilesPunteros[0]->getSprite()->getPosicion().y) > motor2D->getSize().y)
    // if (!proyectilesPunteros.empty() && proyectilesPunteros[0]->sprite->getPosicion().y > motor2D->getSize().y )
    {
        if (bossBatalla->getTipo() == BossType::CATACUMBAS)
        {
            // Que le quite un 5 por ciento de la vida máxima
            // actualizarVidaBoss(-static_cast<int>((5.0 / 100.0) * bossBatalla->getVidaMax()));
            std::cout << "VIDA HECTOR: " << bossBatalla->getVida() << std::endl;
            actualizarVidaBoss(-(obtenerDano()));
        }
        else
        {
            if (proyectilesPunteros[0]->getTipo() == tipoProyectil::Esquivar)
            {
                PersonajePrincipal::getInstance()->quitarVida(-10);
                actualizarBarraVida(+10);
                actualizarBarraArmor();
            }
            else
            {
                PersonajePrincipal::getInstance()->quitarVida(20);
                actualizarBarraVida(-20);
                actualizarBarraArmor();
            }
        }
        eliminarPrimerProyectil();

        // valorVida -= 100;
    }

    if (!ataques.empty() && ataques[0]->getSprite()->getPosicion().y < (motor2D->getSize().y / 2) / 2)
    {
        // Depende de lo cargada que este la barra del mapa hacer más daño o menos
        // int quitar = -static_cast<int>((2.5 / 100.0) * bossBatalla->getVidaMax());

        efectosTexto.push_back(EfectoTexto("-" + std::to_string(obtenerDano()), fuente, ataques[0]->getPosicionSprite(), sf::Color::Red, 3000));

        eliminarPrimerAtaque();
        // std::cout << "Vida boss: " << bossBatalla->getVida() << std::endl;
        //  Quitar un 5% de la vida máxima
        std::cout << "VIDA BOSS: " << bossBatalla->getVida() << std::endl;

        actualizarVidaBoss(-(obtenerDano()));
    }

    // ROMPER PROYECTILES CON ATAQUES -------------------------------
    for (auto ataque_it = ataques.begin(); ataque_it != ataques.end(); ++ataque_it)
    {
        for (auto proyectil_it = proyectilesPunteros.begin(); proyectil_it != proyectilesPunteros.end();)
        {
            // Asegúrate de que ambos tienen carriles definidos y que coinciden

            if ((*ataque_it)->getSprite()->getHitbox().intersects((*proyectil_it)->getSprite()->getHitboxPersonalizada()))
            {
                // cambiarColorAleatorio((*ataque_it)->sprite);
                proyectil_it = eliminarProyectil(proyectil_it); // Elimina el proyectil y avanza el iterador
                continue;                                       // Continúa con el próximo proyectil
            }
            ++proyectil_it; // Solo avanza el iterador si no se elimina nada o no coinciden los carriles
        }
    }
    //----------------------------------------------------------------

    for (auto proyectil = proyectilesPunteros.begin(); proyectil != proyectilesPunteros.end();)
    {
        if ((*proyectil)->getTipo() == tipoProyectil::Esquivar || bossBatalla->getTipo() == CATACUMBAS)
        {
            sf::FloatRect hitboxProyectil = (*proyectil)->getSprite()->getHitboxPersonalizada();

            sf::FloatRect hitboxPersonaje = sprite->getHitboxPersonalizada();

            if (hitboxProyectil.intersects(hitboxPersonaje))
            {
                proyectil = proyectilesPunteros.erase(proyectil);
                actualizarBarraVida(-20);
                PersonajePrincipal::getInstance()->quitarVida(20);
            }
            else
            {
                ++proyectil; // Solo incrementamos si no se eliminó el elemento
            }
        }
        else
        {
            ++proyectil; // Siempre incrementamos si no entramos en la condición de arriba
        }
    }

    auto it = efectosTexto.begin();
    while (it != efectosTexto.end())
    {
        if (!it->update())
        {
            it = efectosTexto.erase(it); // Correcto: actualiza el iterador después de borrar
        }
        else
        {
            ++it;
        }
    }

    if (valorVida <= 0)
    {
    }

    if (esInfinita)
    {
        cambiarBossInfinito();
    }

    controlTeclas(accion);
    relojUpdate.restart().asSeconds();
}

int Batalla::obtenerDano()
{
    /*const float base = 2.5f;
    const float factorReductor = 0.05f;
    float porcentaje = base;

    for(int i= 10; i<std::min(x, 100); i+=10){
        porcentaje += (base- (i/100.0f) * factorReductor);
    }
    return std::min(porcentaje, 25.0f);*/

    int danoBase = 15;
    float bonificacion = bonificacionDano / 200.0f;

    int danoFinal = danoBase + static_cast<int>(danoBase * bonificacion);
    std::cout << "DAÑO" << danoFinal << std::endl;

    return danoFinal;
}

void Batalla::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = &this->motor2D->getVentana();
    }
    motor2D->draw(&fondo);
    motor2D->draw(bossBatalla->getSprite());
    motor2D->draw(&carril);

    // motor2D->draw(&fondo);
    sf::Vector2f ptoInicial(motor2D->getSize().x / 2, 0);
    float anadir = ((motor2D->getSize().x / 2) - (motor2D->getSize().x / 3)) / 2;

    sf::VertexArray linea(sf::Lines, 2);
    linea[0].position = ptoInicial;
    linea[0].color = sf::Color::Red;
    linea[1].position = sf::Vector2f((motor2D->getSize().x / 3) - anadir, motor2D->getSize().y);
    linea[1].color = sf::Color::Blue;

    sf::VertexArray lineaGuia(sf::Lines, 2);
    lineaGuia[0].position = ptoInicial;
    lineaGuia[0].color = sf::Color::Red;
    lineaGuia[1].position = sf::Vector2f((motor2D->getSize().x / 3), motor2D->getSize().y);
    lineaGuia[1].color = sf::Color::Blue;

    sf::VertexArray linea2(sf::Lines, 2);
    linea2[0].position = ptoInicial;
    linea2[0].color = sf::Color::Red;
    linea2[1].position = sf::Vector2f((motor2D->getSize().x / 3) + anadir, motor2D->getSize().y);
    linea2[1].color = sf::Color::Blue;

    sf::VertexArray linea3(sf::Lines, 2);
    linea3[0].position = ptoInicial;
    linea3[0].color = sf::Color::Red;
    linea3[1].position = sf::Vector2f((motor2D->getSize().x / 2) + anadir, motor2D->getSize().y);
    linea3[1].color = sf::Color::Blue;

    sf::VertexArray linea4(sf::Lines, 2);
    linea4[0].position = ptoInicial;
    linea4[0].color = sf::Color::Red;
    linea4[1].position = sf::Vector2f((motor2D->getSize().x * 2 / 3) + anadir, motor2D->getSize().y);
    linea4[1].color = sf::Color::Blue;

    sf::VertexArray linea5(sf::Lines, 2);
    linea5[0].position = ptoInicial;
    linea5[0].color = sf::Color::Red;
    linea5[1].position = sf::Vector2f((motor2D->getSize().x / 2), motor2D->getSize().y);
    linea5[1].color = sf::Color::Blue;

    sf::VertexArray linea6(sf::Lines, 2);
    linea6[0].position = sf::Vector2f((0), (motor2D->getSize().y / 2) / 2);
    linea6[0].color = sf::Color::Red;
    linea6[1].position = sf::Vector2f((motor2D->getSize().x), (motor2D->getSize().y / 2) / 2);
    linea6[1].color = sf::Color::Blue;

    sf::VertexArray linea7(sf::Lines, 2);
    linea7[0].position = sf::Vector2f((0), motor2D->getSize().y - 150);
    linea7[0].color = sf::Color::Red;
    linea7[1].position = sf::Vector2f((motor2D->getSize().x), motor2D->getSize().y - 150);
    linea7[1].color = sf::Color::Blue;

    sf::VertexArray linea8(sf::Lines, 2);
    linea8[0].position = sf::Vector2f((0), (motor2D->getSize().y / 2) / 2);
    linea8[0].color = sf::Color::Red;
    linea8[1].position = sf::Vector2f((motor2D->getSize().x), (motor2D->getSize().y / 2) / 2);
    linea8[1].color = sf::Color::Blue;
    //-----------------------------------------------------------------------------------------

    /*motor2D->drawLinea(linea);
    motor2D->drawLinea(lineaGuia);
    motor2D->drawLinea(linea2);
    motor2D->drawLinea(linea3);
    motor2D->drawLinea(linea4);
    motor2D->drawLinea(linea5);
    motor2D->drawLinea(linea6);
    motor2D->drawLinea(linea7);*/

    if (!(bossBatalla->getTipo() == BossType::CATACUMBAS) && !(esInfinita))
    {
        motor2D->drawRectangle(barraProgreso);
        motor2D->draw(&barra_ataque);
    }

    if (!esInfinita)
    {
        motor2D->drawRectangle(barraVidaBoss);
        motor2D->draw(&barra_vida_boss);
        motor2D->drawText(bossNameText);
    }
    else
    {
        motor2D->drawText(contadorInfinitoText);
    }

    motor2D->drawRectangle(barraVida);
    motor2D->drawRectangle(barraArmor);

    motor2D->draw(&barra_vida);

    float factorInterpolacion = 0.0f;
    float reloj = relojUpdate.getElapsedTime().asMilliseconds() / 66.6;
    reloj += 0.25;
    factorInterpolacion = std::min(1.f, reloj);
    factorInterpolacion = std::round(factorInterpolacion * 100) / 100.0;

    for (auto &proyectil : proyectilesPunteros)
    {
        // Interpolación lineal de la posición para el renderizado suave.
        sf::Vector2f posicionInterpolada = proyectil->getPosicionAnterior() * (1 - factorInterpolacion) + proyectil->getPosicionActual() * factorInterpolacion;
        // sf::Vector2f posicionInterpolada = proyectil->posicionAnterior * (1 - factorInterpolacion) + proyectil->posicionActual * factorInterpolacion;
        proyectil->getSprite()->setPosition(posicionInterpolada.x, posicionInterpolada.y);

        if (proyectil->getTipo() == tipoProyectil::Esquivar)
        {
            proyectil->getSprite()->cambiarColor(sf::Color::Green);
        }
        /*sf::RectangleShape hitboxShape;
        hitboxShape.setSize(sf::Vector2f(proyectil->sprite->getHitboxPersonalizada().width, proyectil->sprite->getHitboxPersonalizada().height)); // Establece el tamaño de la hitbox
        hitboxShape.setFillColor(sf::Color::Transparent); // Hacer el interior transparente
        hitboxShape.setOutlineColor(sf::Color::Red); // Color del borde rojo para visibilidad
        hitboxShape.setOutlineThickness(2);
        hitboxShape.setPosition(proyectil->sprite->getPosicion().x - proyectil->sprite->getHitboxPersonalizada().width / 2, proyectil->sprite->getPosicion().y - proyectil->sprite->getHitboxPersonalizada().height / 2);
        motor2D->drawRectangle(hitboxShape);*/

        proyectil->dibujar();
    }

    for (auto &ataque : ataques)
    {
        sf::Vector2f posInterpolada = ataque->getPosicionAnterior() * (1 - factorInterpolacion) + ataque->getPosicionActual() * factorInterpolacion;
        // sf::Vector2f posInterpolada = ataque->posicionAnterior * (1 - factorInterpolacion) + ataque->posicionActual * factorInterpolacion;
        ataque->getSprite()->setPosition(posInterpolada.x, posInterpolada.y);
        /*sf::RectangleShape hitboxShape2;
        hitboxShape2.setSize(sf::Vector2f(ataque->sprite->getHitboxPersonalizada().width, ataque->sprite->getHitboxPersonalizada().height)); // Establece el tamaño de la hitbox
        hitboxShape2.setFillColor(sf::Color::Transparent); // Hacer el interior transparente
        hitboxShape2.setOutlineColor(sf::Color::Green); // Color del borde rojo para visibilidad
        hitboxShape2.setOutlineThickness(2);
        hitboxShape2.setPosition(ataque->sprite->getPosicion().x - ataque->sprite->getHitboxPersonalizada().width / 2, ataque->sprite->getPosicion().y - ataque->sprite->getHitboxPersonalizada().height / 2);
        motor2D->drawRectangle(hitboxShape2);*/
        ataque->dibujar();
    }

    motor2D->draw(&sprite);

    if (resultadoTimer.getElapsedTime().asSeconds() < resultadoMostrarDuracion)
    {
        switch (resultadoTecla)
        {
        case ResultadoTecla::Perfect:
            mensajes->setRectTextura(0, 0, 1024, 1024 / 3); // Asumiendo que tienes estas texturas definidas
            mensajes->escalarSprite(0.7);

            break;
        case ResultadoTecla::Good:
            mensajes->setRectTextura(0, 1024 / 3, 1024, 1024 / 3); // Asumiendo que tienes estas texturas definidas
            mensajes->escalarSprite(0.7);

            break;
        case ResultadoTecla::Bad:
            mensajes->setRectTextura(0, (1024 / 3) * 2, 1024, 1024 / 3); // Asumiendo que tienes estas texturas definidas
            mensajes->escalarSprite(0.7);

            break;
        default:
            break;
        }
        mensajes->setPosition(0, 0); // Asumiendo que quieres que aparezca cerca del sprite del jugador
        motor2D->draw(&mensajes);
    }

    for (int i = 0; i < proyectilesPunteros.size(); i++)
    {
        auto &proyectil = proyectilesPunteros[i];

        if (proyectil->getSprite()->isAnimated == true)
        {
            proyectil->getSprite()->updateAnimacion();
        }
    }

    for (int i = 0; i < ataques.size(); i++)
    {
        auto &ataque = ataques[i];

        if (ataque->getSprite()->isAnimated == true)
        {
            ataque->getSprite()->updateAnimacion();
        }
    }

    musica->sePuedeSiguienteCancion();

    // OBJETOS
    if (!esInfinita)
    {
        motor2D->draw(&fondo_objeto1);
        motor2D->draw(&fondo_objeto2);
    }

    if (JSJuego::getInstance()->getObjeto1().devolverObjeto() != 0 && !esInfinita)
    {
        // std::cout << "Lo pinto porque tiene id: " << objeto1.devolverObjeto() << std::endl;
        this->motor2D->draw(objeto1->getSprite());
    }

    if (JSJuego::getInstance()->getObjeto2().devolverObjeto() != 0 && !esInfinita)
    {
        // std::cout << "Lo pinto porque tiene id: " << objeto1.devolverObjeto() << std::endl;
        this->motor2D->draw(objeto2->getSprite());
    }

    /*for (auto it = efectosTexto.begin(); it != efectosTexto.end();) {
        (*it).draw();
    }*/

    for (auto &efecto : efectosTexto)
    {
        efecto.draw(factorInterpolacion);
    }

    sf::FloatRect hitboxPersonaje = sprite->getHitboxPersonalizada();

    // Crear un objeto sf::RectangleShape para dibujar la hitbox
    /*sf::RectangleShape hitboxShape;
    hitboxShape.setPosition(sf::Vector2f(hitboxPersonaje.left, hitboxPersonaje.top));
    hitboxShape.setSize(sf::Vector2f(hitboxPersonaje.width, hitboxPersonaje.height));
    hitboxShape.setFillColor(sf::Color::Transparent);  // Hacer el interior transparente
    hitboxShape.setOutlineColor(sf::Color::Red);      // Color rojo para el contorno
    hitboxShape.setOutlineThickness(1.0f);            // Grosor del contorno

    // En tu función de renderizado
    motor2D->drawRectangle(hitboxShape);  // Dibuja la hitbox sobre el sprite*/
}

void Batalla::controlTeclas(char accion)
{
    float ancho = motor2D->getSize().x;
    float anadir = ((motor2D->getSize().x / 2) - (motor2D->getSize().x / 3)) / 2;
    sf::Vector2f puntoFinalAtaque(motor2D->getSize().x / 2, 0);
    float velocidadAtaque = 6.5f;
    int actual = 0;

    switch (accion)
    {
    case 'Q':
    {
        std::stack<JState *> states = Juego::getInstance()->devolverStates();
        musica->pausarMusica();
        if (esInfinita)
        {
            JSMenuJuego::getInstance()->setFondoInfinito();
        }
        else
        {
            JSMenuJuego::getInstance()->setFondo();
        }

        states.push(JSMenuJuego::getInstance());
        Juego::getInstance()->actualizar(states);
    }

    case 'D':
    {
        // Escala por defecto
        sf::Vector2f pos((motor2D->getSize().x * 2 / 3), motor2D->getSize().y - 60);
        cambiarPosicionSinInterpolacion(pos);
        sf::Vector2f rot(0.3, 0.3);
        // setScaleSprite(rot);
        break;
    }

    case 'A':
    {
        sf::Vector2f rot(-2.4, 2.4);
        // setScaleSprite(rot);
        sf::Vector2f pos((motor2D->getSize().x / 3), motor2D->getSize().y - 60);

        cambiarPosicionSinInterpolacion(pos);
        break;
    }

    case 'W':
    case 'S':
    {
        sf::Vector2f rot(2.4, 2.4);
        // setScaleSprite(rot);
        sf::Vector2f pos(motor2D->getSize().x / 2, motor2D->getSize().y - 60);
        cambiarPosicionSinInterpolacion(pos);
        break;
    }

    case 'L':
    {
        if (!(bossBatalla->getTipo() == BossType::CATACUMBAS) && !(esInfinita))
        {

            int carrilAtaque = 0;
            sf::Vector2f puntoInicialAtaque(0.0, 0.0);
            if (sprite->getPosicion().x == motor2D->getSize().x * 2 / 3)
            {
                carrilAtaque = 3;
                puntoInicialAtaque = obtenerPuntoInicialAtaque(carrilAtaque);
            }
            else if ((sprite)->getPosicion().x == motor2D->getSize().x / 3)
            {
                carrilAtaque = 1;
                puntoInicialAtaque = obtenerPuntoInicialAtaque(carrilAtaque);
            }
            else
            {
                carrilAtaque = 2;
                puntoInicialAtaque = obtenerPuntoInicialAtaque(carrilAtaque);
            }

            if (contador >= maxContador - 10)
            {
                sf::Vector2f puntoInicialAtaque1 = obtenerPuntoInicialAtaque(1);
                sf::Vector2f puntoInicialAtaque2 = obtenerPuntoInicialAtaque(2);
                sf::Vector2f puntoInicialAtaque3 = obtenerPuntoInicialAtaque(3);
                tipoProyectil tipoP = tipoProyectil::Romper;
                addAtaque(crearProyectilNuevo(puntoInicialAtaque1, puntoFinalAtaque, carrilAtaque, velocidadAtaque, tipoP, true));
                addAtaque(crearProyectilNuevo(puntoInicialAtaque2, puntoFinalAtaque, carrilAtaque, velocidadAtaque, tipoP, true));
                addAtaque(crearProyectilNuevo(puntoInicialAtaque3, puntoFinalAtaque, carrilAtaque, velocidadAtaque, tipoP, true));

                actualizarContador(-getMaxContador());
                // valorVidaBoss = valorVidaBoss - 150;
            }
            else if (getContador() >= 200)
            {
                addAtaque(crearProyectilNuevo(puntoInicialAtaque, puntoFinalAtaque, carrilAtaque, velocidadAtaque, tipoProyectil::Romper, true));
                actualizarContador(-200);
                // valorVidaBoss = valorVidaBoss - 75;
            }
        }
        break;
    }

    case 'C':
    {
        actualizarContador(+600);
        actualizarVidaBoss(-600);
        break;
    }

    case 'K':
    {
        if (!(proyectilesPunteros.empty()))
        {

            sf::FloatRect hitboxPersonaje = sprite->getHitbox();
            // std::cout << sprite->getPosicion().x << std::endl;

            float limiteInferior = motor2D->getSize().y;
            float limiteSuperior = limiteInferior - 150;

            int carril = 0;

            if (sprite->getPosicion().x == 960)
            {
                carril = 2;
                // std::cout << "Carril 2" << std::endl;
            }
            else if (sprite->getPosicion().x == motor2D->getSize().x * 2 / 3)
            {
                carril = 3;
                // std::cout << "Carril 3" << std::endl;
            }
            else
            {
                carril = 1;
                // std::cout << "Carril 1" << std::endl;
            }

            sf::FloatRect hitboxCora;

            bool proyectilEncontrado = false;

            for (auto it = proyectilesPunteros.begin(); it != proyectilesPunteros.end(); ++it)
            {
                if ((*it)->getCarril() == carril)
                {
                    sf::FloatRect hitboxCora = (*it)->getSprite()->getHitboxPersonalizada();
                    proyectilEncontrado = true;

                    if (hitboxCora.top >= limiteSuperior && hitboxCora.top + hitboxCora.height <= limiteInferior)
                    {
                        // std::cout << "PERFECT MÁQUINA" << std::endl;
                        resultadoTecla = ResultadoTecla::Perfect;
                        resultadoTimer.restart();

                        actualizarContador(+40);
                        actual = 1;
                        it = eliminarProyectil(it);
                        contadorInfinito += 1000;
                        break;
                    }
                    else if (hitboxCora.top + hitboxCora.height > limiteSuperior && hitboxCora.top < limiteInferior)
                    {
                        // std::cout << "DENTRO" << std::endl;
                        resultadoTecla = ResultadoTecla::Good;
                        resultadoTimer.restart();

                        actualizarContador(+20);
                        actual = 2;
                        it = eliminarProyectil(it);
                        contadorInfinito += 10;
                        break;
                    }
                    else
                    {
                        // std::cout << "MAL" << std::endl;
                        resultadoTecla = ResultadoTecla::Bad;
                        resultadoTimer.restart();

                        actual = 3;
                        actualizarContador(-30);
                        contadorInfinito -= 20;
                        // Aquí no eliminamos el proyectil, así que no necesitamos modificar el iterador
                    }
                }
            }
            if (!proyectilEncontrado)
            {
                actualizarContador(-20); // Restar puntos
                resultadoTecla = ResultadoTecla::Bad;
                resultadoTimer.restart();

                contadorInfinito -= 20;
                actual = -1;
            }
        }
        contadorInfinitoText.setString("Contador: " + std::to_string(contadorInfinito));

        break;
    }

    case 'J':
    {

        int nuevoCarril = std::rand() % 3 + 1;
        // std::cout << "Carril: " << nuevoCarril<< std::endl;
        sf::Vector2f nuevoPuntoInicial = obtenerPuntoInicial(nuevoCarril);
        sf::Vector2f nuevoPuntoFinal = obtenerPuntoFinal(nuevoCarril);
        // std::cout << "Punto Inicial y: " << nuevoPuntoInicial.y << std::endl;
        // std::cout << "Punto Final y: " << nuevoPuntoFinal.y << std::endl;
        // crearProyectil(*srpiteProyectil, nuevoPuntoInicial, nuevoPuntoFinal, proyectilesPunteros, nuevoCarril, velocidad);
        addProyectil(crearProyectilNuevo(nuevoPuntoInicial, nuevoPuntoFinal, nuevoCarril, 100, tipoProyectil::Romper, false));

        break;
    }
    case 'O':
        if (objeto1->esConsumible() == false)
        {
            // std::cout << "Se ha pulsado k y el objeto es: " << objeto1->esConsumible() << std::endl;
        }

        if (objeto1->esConsumible() == true)
        {
            int n = objeto1->usarObjeto();

            int nivel = JSTienda::getInstance()->obtenerNivelPorID(n + 1);

            float suma = 0.0f;

            // std::cout << "El numero que tiene que aplicar es: " << n << std::endl;

            int c = 0;

            switch (n)
            {
            case 0:
                suma = 20 + (20 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->DarArmadura(suma);
                // std::cout << "Ahora su armadura es de: " << suma << std::endl;
                objeto1->asignarType(0);
                actualizarBarraArmor();
                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 1:
                suma = 50 + (50 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->DarArmadura(suma);
                objeto1->asignarType(0);
                actualizarBarraArmor();
                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 2:
                suma = 20 + (20 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->sumarVida(suma);
                objeto1->asignarType(0);
                actualizarBarraVida(0);
                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 3:
                suma = 50 + (50 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->sumarVida(suma);
                objeto1->asignarType(0);
                actualizarBarraVida(0);
                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 4:
                /*
                    suma = 20 + (20 * ((nivel - 1) / 2.0f));
                    if (contador + suma >= 200)
                    {
                        contador = 200;
                    }
                    else
                    {
                        contador += suma;
                    }
                    JSJuego::getInstance()->gastarObjeto1();
                */
                break;
            case 5:
                /*
                    suma = 50 + (50 * ((nivel - 1) / 2.0f));
                    if (contador + suma >= 200)
                    {
                        contador = 200;
                    }
                    else
                    {
                        contador += suma;
                    }
                    JSJuego::getInstance()->gastarObjeto1();
                */
                break;

            case 6:
                c = JSJuego::getInstance()->usarObjetoAleatorio(1);
                JSJuego::getInstance()->usarObjetoAleatorio(c);

                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 7:
                suma = 40 + (40 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->sumarVida(-20);
                /*contador = contador + 40;
                if (contador > 200)
                {
                    contador = 200;
                }*/
                bonificacionDano = bonificacionDano + 40;
                if (bonificacionDano > 200)
                {
                    bonificacionDano = 200;
                }
                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 8:
                if (contador - 30 <= 0)
                {
                    contador = 0;
                    PersonajePrincipal::getInstance()->sumarVida(30 - (30 - contador));
                }
                else
                {
                    suma = 50 + (50 * ((nivel - 1) / 2.0f));
                    PersonajePrincipal::getInstance()->sumarVida(50);
                    contador = contador - 30;
                }
                JSJuego::getInstance()->gastarObjeto1();

                break;
            case 10:
                if (bossBatalla->getTipo() == BossType::NPC)
                {
                    actualizarVidaBoss(-600);
                    objeto1->asignarType(0);

                    JSJuego::getInstance()->gastarObjeto1();
                }

                break;

            default:
                break;
            }
        }
        break;

    case 'P':
        if (objeto2->esConsumible() == false)
        {
            // std::cout << "Se ha pulsado k y el objeto es: " << objeto1->esConsumible() << std::endl;
        }

        if (objeto2->esConsumible() == true)
        {
            int n = objeto2->usarObjeto();

            int nivel = JSTienda::getInstance()->obtenerNivelPorID(n + 1);

            float suma = 0.0f;

            // std::cout << "El numero que tiene que aplicar es: " << n << std::endl;

            int c = 0;

            switch (n)
            {
            case 0:
                suma = 20 + (20 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->DarArmadura(suma);
                // std::cout << "Ahora su armadura es de: " << suma << std::endl;
                objeto2->asignarType(0);
                actualizarBarraArmor();
                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 1:
                suma = 50 + (50 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->DarArmadura(suma);
                objeto2->asignarType(0);
                actualizarBarraArmor();
                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 2:
                suma = 20 + (20 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->sumarVida(suma);
                objeto2->asignarType(0);
                actualizarBarraVida(0);
                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 3:
                suma = 50 + (50 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->sumarVida(suma);
                objeto2->asignarType(0);
                actualizarBarraVida(0);
                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 4:
                /*
                    suma = 20 + (20 * ((nivel - 1) / 2.0f));
                    if (contador + suma >= 200)
                    {
                        contador = 200;
                    }
                    else
                    {
                        contador += suma;
                    }
                    JSJuego::getInstance()->gastarObjeto1();
                */
                break;
            case 5:
                /*
                    suma = 50 + (50 * ((nivel - 1) / 2.0f));
                    if (contador + suma >= 200)
                    {
                        contador = 200;
                    }
                    else
                    {
                        contador += suma;
                    }
                    JSJuego::getInstance()->gastarObjeto1();
                */
                break;

            case 6:
                c = JSJuego::getInstance()->usarObjetoAleatorio(1);
                JSJuego::getInstance()->usarObjetoAleatorio(c);
                objeto2->asignarType(0);

                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 7:
                suma = 40 + (40 * ((nivel - 1) / 2.0f));
                PersonajePrincipal::getInstance()->sumarVida(-20);
                /*contador = contador + 40;
                if (contador > 200)
                {
                    contador = 200;
                }*/
                bonificacionDano = bonificacionDano + 40;
                if (bonificacionDano > 200)
                {
                    bonificacionDano = 200;
                }
                objeto2->asignarType(0);
                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 8:
                if (contador - 30 <= 0)
                {
                    contador = 0;
                    PersonajePrincipal::getInstance()->sumarVida(30 - (30 - contador));
                }
                else
                {
                    suma = 50 + (50 * ((nivel - 1) / 2.0f));
                    PersonajePrincipal::getInstance()->sumarVida(50);
                    contador = contador - 30;
                }
                objeto2->asignarType(0);
                JSJuego::getInstance()->gastarObjeto2();

                break;
            case 10:

                if (bossBatalla->getTipo() == BossType::NPC)
                {
                    actualizarVidaBoss(-600);

                    objeto2->asignarType(0);

                    JSJuego::getInstance()->gastarObjeto2();
                }
                break;

            default:
                break;
            }
        }
        break;
    }

    // update(delta, *motor2D, srpiteProyectil);
}

void Batalla::inicializarBarraVidaBoss()
{
    sf::Vector2f pos(motor2D->getSize().x / 2, 200);
    // barra_vida_boss_tex = text;
    // barra_vida_boss = new MySprite("../javier/batalla_base/resources/barra_vida.png");
    barra_vida_boss = new MySprite("../../../data/JAVIER/barra_vida_enemigo.png");

    // barra_vida_boss->setOrigen(barra_vida_boss_tex.getSize().x/2, barra_vida_boss_tex.getSize().y/2);
    barra_vida_boss->setOrigen(barra_vida_boss->tamText().x / 2, barra_vida_boss->tamText().y / 2);

    barra_vida_boss->setPosition(pos.x + 500, pos.y);
    barra_vida_boss->escalarSprite(escaladoBarras);

    barraVidaBoss.setSize(sf::Vector2f(595, 34));
    barraVidaBoss.setFillColor(sf::Color::Red);
    barraVidaBoss.setOrigin(barra_vida_boss->tamText().x / 2, barra_vida_boss->tamText().y / 2);
    barraVidaBoss.setPosition(pos.x + 500, pos.y + 15);
    barraVidaBoss.setScale(escaladoBarras, escaladoBarras);
}

void Batalla::actualizarVidaBoss(int decremento)
{
    bossBatalla->actualizarVida(decremento);

    float porcentajeVidaBoss = static_cast<float>(bossBatalla->getVida()) / bossBatalla->getVidaMax();
    barraVidaBoss.setSize(sf::Vector2f(595.0f * porcentajeVidaBoss, 34));
}

void Batalla::inicializarBarraVida()
{
    sf::Vector2f posVida = sf::Vector2f(525, motor2D->getSize().y - 215);
    float anadir = ((motor2D->getSize().x / 2) - (motor2D->getSize().x / 3)) / 2;

    sf::Vector2f puntoAVida = sf::Vector2f(motor2D->getSize().x / 2, 0);
    sf::Vector2f puntoBVida = sf::Vector2f((motor2D->getSize().x / 3) - anadir, motor2D->getSize().y);

    float deltaXVida = puntoBVida.x - puntoAVida.x;
    float deltaYVida = puntoBVida.y - puntoAVida.y;

    float radianesVida = atan2(deltaYVida, deltaXVida);
    float angulosVida = radianesVida * 180 / 3.14;

    // barra_vida = new MySprite("../javier/batalla_base/resources/barra_vida.png");
    barra_vida = new MySprite("../../../data/JAVIER/barra_vida.png");

    // barra_vida->setOrigen(barra_vida_tex.getSize().x, 0);
    // std::cout << barra_vida->tamText().x << "," << angulosVida << std::endl;
    barra_vida->setOrigen(barra_vida->tamText().x, 0);

    barra_vida->setPosition(525, motor2D->getSize().y - 215);
    barra_vida->rotarSprite(angulosVida);
    barra_vida->escalarSprite(escaladoBarras);

    sf::Vector2f posicionEsquinaVida = sf::Vector2f(barra_vida->getPosicion().x, barra_vida->getPosicion().y);

    float interiorMasBorde = 52.0f * escaladoBarras;
    sf::Vector2f nuevo = sf::Vector2f(
        posicionEsquinaVida.x - sin(radianesVida) * interiorMasBorde,
        posicionEsquinaVida.y + cos(radianesVida) * interiorMasBorde);

    float porcentajeVida = static_cast<float>(valorVida) / PersonajePrincipal::getInstance()->getVidaMax();
    barraVida.setSize(sf::Vector2f(600 * porcentajeVida, 30));
    barraVida.setFillColor(sf::Color::Green);

    // Ajustamos la posición de la barra de vida.
    barraVida.setPosition(nuevo.x, nuevo.y);

    // Rotamos la barra de progreso para que coincida con la rotación del sprite de borde.
    barraVida.setRotation(angulosVida + 180);

    barraVida.setScale(escaladoBarras, escaladoBarras);
}

void Batalla::inicializarBarraArmor()
{
    sf::Vector2f posVida = sf::Vector2f(525, motor2D->getSize().y - 215);
    float anadir = ((motor2D->getSize().x / 2) - (motor2D->getSize().x / 3)) / 2;

    sf::Vector2f puntoAVida = sf::Vector2f(motor2D->getSize().x / 2, 0);
    sf::Vector2f puntoBVida = sf::Vector2f((motor2D->getSize().x / 3) - anadir, motor2D->getSize().y);

    float deltaXVida = puntoBVida.x - puntoAVida.x;
    float deltaYVida = puntoBVida.y - puntoAVida.y;

    float radianesVida = atan2(deltaYVida, deltaXVida);
    float angulosVida = radianesVida * 180 / 3.14;

    sf::Vector2f posicionEsquinaVida = sf::Vector2f(barra_vida->getPosicion().x, barra_vida->getPosicion().y);

    float interiorMasBorde = 52.0f * escaladoBarras;
    sf::Vector2f nuevo = sf::Vector2f(
        posicionEsquinaVida.x - sin(radianesVida) * interiorMasBorde,
        posicionEsquinaVida.y + cos(radianesVida) * interiorMasBorde);

    float porcentajeArmadura = static_cast<float>(PersonajePrincipal::getInstance()->devolverArmor()) / PersonajePrincipal::getInstance()->getVidaMax();
    barraArmor.setSize(sf::Vector2f(600 * porcentajeArmadura, 30));
    barraArmor.setFillColor(sf::Color(128, 128, 128));

    // Ajustamos la posición de la barra de vida.
    barraArmor.setPosition(nuevo.x, nuevo.y);

    // Rotamos la barra de progreso para que coincida con la rotación del sprite de borde.
    barraArmor.setRotation(angulosVida + 180);

    barraArmor.setScale(escaladoBarras, escaladoBarras);
}

void Batalla::actualizarBarraVida(int decremento)
{
    valorVida = PersonajePrincipal::getInstance()->devolverVida();
    // valorVida += decremento;
    if (valorVida > PersonajePrincipal::getInstance()->getVidaMax())
    {
        valorVida = PersonajePrincipal::getInstance()->getVidaMax();
    }
    else if (valorVida < 0)
    {
        valorVida = 0;
    }

    // std::cout << "La vida del personaje es de: " << valorVida << std::endl;

    float porcentajeVida = static_cast<float>(valorVida) / PersonajePrincipal::getInstance()->getVidaMax();
    barraVida.setSize(sf::Vector2f(600 * porcentajeVida, 30));
}

void Batalla::actualizarBarraArmor()
{

    float porcentajeArmor = static_cast<float>(PersonajePrincipal::getInstance()->devolverArmor()) / PersonajePrincipal::getInstance()->getVidaMax();
    barraArmor.setSize(sf::Vector2f(600 * porcentajeArmor, 30));
}

Boss &Batalla::getBoss()
{
    return *bossBatalla;
}

sf::FloatRect Batalla::getAdjustedHitbox(MySprite *sprite)
{
    sf::FloatRect originalHitbox = sprite->getHitbox();
    float scale = 0.5f;
    float newWidth = originalHitbox.width * scale;
    float newHeight = originalHitbox.height * scale;
    float offsetX = (originalHitbox.width - newWidth) / 2;
    float offsetY = (originalHitbox.height - newHeight) / 2;

    return sf::FloatRect(
        originalHitbox.left + offsetX,
        originalHitbox.top + offsetY,
        newWidth,
        newHeight);
}

void Batalla::cambiarCarrilProyectil(std::unique_ptr<Proyectil> &proyectil)
{
    int nuevoCarril;
    do
    {
        nuevoCarril = std::rand() % 3 + 1;
    } while (nuevoCarril == proyectil->getCarril());
    // std::cout << "NuevoCarril: " << nuevoCarril << std::endl;

    sf::Vector2f puntoInicial = obtenerPuntoInicial(nuevoCarril);
    sf::Vector2f puntoFinal = obtenerPuntoFinal(nuevoCarril);
    proyectil->actualizarPuntoInicial(puntoInicial);
    proyectil->actualizarPuntoFinal(puntoFinal);

    sf::Vector2f nuevaDireccion1 = proyectil->getPuntoFinal() - proyectil->getPuntoInicial();
    sf::Vector2f nuevaDireccion = proyectil->getPuntoFinal() - proyectil->getPuntoInicial();
    float magnitud = std::sqrt(nuevaDireccion1.x * nuevaDireccion1.x + nuevaDireccion1.y * nuevaDireccion1.y);
    if (magnitud > 0.0f)
    {
        nuevaDireccion = nuevaDireccion1 / magnitud;
    }
    proyectil->cambiarDireccion(nuevaDireccion);

    int x = 0;
    if (proyectil->getPosicionActual().x < motor2D->getSize().x / 2)
    {
        x = motor2D->getSize().x / 2 - proyectil->getPosicionActual().x;
    }
    else if (proyectil->getPosicionActual().x > motor2D->getSize().x / 2)
    {
        x = proyectil->getPosicionActual().x - motor2D->getSize().x / 2;
    }
    else
    {
        x = 0;
    }

    int centro = motor2D->getSize().x / 2;
    int posActualX = proyectil->getPosicionActual().x;
    int posActualY = proyectil->getPosicionActual().y;
    sf::Vector2f nuevaPos(0, 0);
    switch (proyectil->getCarril())
    {
    case 1:
        switch (nuevoCarril)
        {
        case 2:
        {
            nuevaPos = sf::Vector2f(centro, posActualY);
            break;
        }
        case 3:
        {
            x = centro - posActualX;
            nuevaPos = sf::Vector2f(centro + x, posActualY);
            break;
        }
        }
        break;
    case 2:
        switch (nuevoCarril)
        {
        case 1:
        {
            int anchoPantalla = motor2D->getSize().x;
            int altoPantalla = motor2D->getSize().y;
            int centroX = anchoPantalla / 2;
            int baseIzquierdaX = anchoPantalla / 3;
            int posActualY = proyectil->getPosicionActual().y;

            // Calculamos la pendiente para la línea izquierda.
            float pendienteIzquierda = -altoPantalla / (centroX - baseIzquierdaX);
            float nuevaPosX = baseIzquierdaX + ((altoPantalla - posActualY) * (centroX - baseIzquierdaX) / altoPantalla);
            // nuevaPosX = std::max(nuevaPosX, static_cast<float>(baseIzquierdaX));

            nuevaPos = sf::Vector2f(nuevaPosX, posActualY);
            break;
        }
        case 3:
        {
            int anchoPantalla = motor2D->getSize().x;
            int altoPantalla = motor2D->getSize().y;
            int centroX = anchoPantalla / 2;
            int baseDerechaX = (anchoPantalla * 2) / 3;
            int posActualY = proyectil->getPosicionActual().y;

            float pendienteIzquierda = -altoPantalla / (centroX - baseDerechaX);
            float nuevaPosX = baseDerechaX + ((altoPantalla - posActualY) * (centroX - baseDerechaX) / altoPantalla);
            nuevaPos = sf::Vector2f(nuevaPosX, posActualY);
            break;
        }
        }
        break;
    case 3:
        switch (nuevoCarril)
        {
        case 1:
        {
            x = posActualX - centro;
            nuevaPos = sf::Vector2f(centro - x, posActualY);
            break;
        }
        case 2:
        {
            nuevaPos = sf::Vector2f(centro, posActualY);
            break;
        }
        }
        break;
    }

    proyectil->actualizarPosicionAnterior(proyectil->getPosicionActual());
    proyectil->actualizarPosicionActual(nuevaPos);

    // proyectil->carril = nuevoCarril;
    proyectil->actualizarCarril(nuevoCarril);
}

void Batalla::generarProyectil(bool ataque)
{
    int nuevoCarril = std::rand() % 3 + 1;

    sf::Vector2f nuevoPuntoInicial = obtenerPuntoInicial(nuevoCarril);
    sf::Vector2f nuevoPuntoFinal = obtenerPuntoFinal(nuevoCarril);

    tipoProyectil tipoP = tipoProyectil::Romper;
    if (bossBatalla->getTipo() == BossType::COMEDOR || bossBatalla->getTipo() == BossType::REY)
    {
        if (rand() % 100 < 15)
        {
            tipoP = tipoProyectil::Esquivar;
        }
        else
        {
            tipoProyectil::Esquivar;
        }
        // tipoP = tipoProyectil::Esquivar;
    }
    addProyectil(crearProyectilNuevo(nuevoPuntoInicial, nuevoPuntoFinal, nuevoCarril, 100, tipoP, ataque));
}

std::unique_ptr<Proyectil> Batalla::crearProyectilNuevo(sf::Vector2f puntoInicial, sf::Vector2f puntoFinal, int carril, float velocidad, tipoProyectil tipoP, bool ataque)
{
    return std::make_unique<Proyectil>(puntoInicial, puntoFinal, carril, velocidad, tipoP, ataque);
}

sf::Vector2f Batalla::obtenerPuntoInicial(int carril)
{
    sf::Vector2f puntoInicial(0, 0);

    if (carril == 1)
    {
        puntoInicial = sf::Vector2f((motor2D->getSize().x / 2 - (motor2D->getSize().x / 48) * 2), (motor2D->getSize().y / 2) / 2);
    }
    else if (carril == 2)
    {
        puntoInicial = sf::Vector2f((motor2D->getSize().x / 2), (motor2D->getSize().y / 2) / 2);
    }
    else
    {
        puntoInicial = sf::Vector2f((motor2D->getSize().x / 2 + (motor2D->getSize().x / 48) * 2), (motor2D->getSize().y / 2) / 2);
    }
    return puntoInicial;
}

sf::Vector2f Batalla::obtenerPuntoFinal(int carril)
{
    sf::Vector2f puntoFinal(0, 0);

    if (carril == 1)
    {
        puntoFinal = sf::Vector2f(motor2D->getSize().x / 3, motor2D->getSize().y - 60);
    }
    else if (carril == 2)
    {
        puntoFinal = sf::Vector2f(motor2D->getSize().x / 2, motor2D->getSize().y - 60);
    }
    else
    {
        puntoFinal = sf::Vector2f((motor2D->getSize().x * 2 / 3), motor2D->getSize().y - 60);
    }

    return puntoFinal;
}

void Batalla::actualizarVelocidadLanzamiento(float bpm)
{
    BPM = bpm;
}

sf::Vector2f Batalla::obtenerPuntoInicialAtaque(int carril)
{
    sf::Vector2f puntoInicial(0, 0);

    if (carril == 1)
    {
        puntoInicial = sf::Vector2f((motor2D->getSize().x / 3), motor2D->getSize().y - 60);
    }
    else if (carril == 2)
    {
        puntoInicial = sf::Vector2f((motor2D->getSize().x / 2), motor2D->getSize().y - 60);
    }
    else
    {
        puntoInicial = sf::Vector2f((motor2D->getSize().x * 2 / 3), motor2D->getSize().y - 60);
    }
    return puntoInicial;
}

void Batalla::asignarTipoNivel(int tipo)
{
    tipoNivel = tipo;

    if (tipoNivel == 0)
    {
        fondo->cambiarSprite("../../../data/ANGEL/fondos/carcel.png");
    }
    else if (tipoNivel == 1)
    {
        fondo->cambiarSprite("../../../data/ANGEL/fondos/catacumbas.png");
    }
    else if (tipoNivel == 2)
    {
        fondo->cambiarSprite("../../../data/ANGEL/fondos/jardin.png");
    }
    else if (tipoNivel == 3)
    {
        fondo->cambiarSprite("../../../data/ANGEL/fondos/comedor.png");
    }
    else if (tipoNivel == 4)
    {
        fondo->cambiarSprite("../../../data/ANGEL/fondos/trono.png");
    }
}

void Batalla::inicializar()
{
    setTextureBarraBatalla();
    inicializarBarra();
    inicializarBarraVidaBoss();
    inicializarBarraVida();
    inicializarBarraArmor();

    bossNameText.setFont(fuente);
    bossNameText.setCharacterSize(44);           // Tamaño del texto
    bossNameText.setFillColor(sf::Color::White); // Color del texto
    bossNameText.setStyle(sf::Text::Bold);

    contadorInfinitoText.setFont(fuente);
    contadorInfinitoText.setCharacterSize(44);
    contadorInfinitoText.setFillColor(sf::Color::White);
    contadorInfinitoText.setStyle(sf::Text::Bold);

    contadorInfinitoText.setPosition(barraVidaBoss.getPosition().x - barraVidaBoss.getSize().x / 3, barraVidaBoss.getPosition().y - 102);
    contadorInfinitoText.setString("Contador: " + std::to_string(contadorInfinito));

    bossNameText.setPosition(barraVidaBoss.getPosition().x - barraVidaBoss.getSize().x / 3, barraVidaBoss.getPosition().y - 102);

    // std::cout << "Bonificacion: " << bonificacionDano << std::endl;
}

void Batalla::reiniciar()
{
    // std::cout << "Ha entrado a reiniciar" << std::endl;

    proyectilesPunteros.clear();
    ataques.clear();
    efectosTexto.clear();

    valorVida = JSJuego::getInstance()->getVida();
    // std::cout << "VALOR VIDA: " << valorVida << std::endl;

    // COGER LA VIDA DEL BOSS NUEVO QUE TE PASAN
    // valorVidaBoss = maxValorVidaBoss;
    contador = 0;

    inicializarBarraVidaBoss();
    inicializarBarraVida();
    inicializarBarraArmor();

    sprite->setPosition(motor2D->getSize().x / 2, motor2D->getSize().y - 60);

    contadorInfinito = 0;
    // bossBatalla.reset();

    // Para asignar un nuevo boss, creándolo
    /*if(bossBatalla) {
        bossBatalla.reset(); // Destruye el boss actual si existe
        // Vuelve a asignar un nuevo boss con el estado inicial deseado
        auto boss = BossFactory::createBoss("", BossType::REY);
        asignarBoss(move(boss));
    }*/
}

void Batalla::asignarBonificacionDano(int x)
{
    bonificacionDano = x;
}

void Batalla::cambiarAInfinito(bool bol)
{
    esInfinita = bol;
    if (esInfinita == true)
    {
        // std::cout << "HA CAMBIADO A INFINITO" << std::endl;
        auto boss = BossFactory::createBoss("../../../data/ANGEL/fondos/infinito.png", BossType::PRISION);
        asignarBoss(move(boss));

        fondo->cambiarSprite("../../../data/ANGEL/fondos/fondoInfinito.png");
    }
}

void Batalla::cambiarBossInfinito()
{

    // PRIOSIÓN NO QUE ES EL DE ESQUIVAR
    if (contadorInfinito > 7000 && contadorInfinito < 14000 && !bossCatacumbasCreado)
    {
        // std::cout << "ENTRA A 7000" << std::endl;
        auto boss = BossFactory::createBoss("../../../data/ANGEL/fondos/infinito.png", BossType::PRISION);
        asignarBoss(move(boss));
        bossCatacumbasCreado = true;
        bossJardinesCreado = false;
        bossComedorCreado = false;
        bossReyCreado = false;
    }
    else if (contadorInfinito > 14000 && contadorInfinito < 21000 && !bossJardinesCreado)
    {
        auto boss = BossFactory::createBoss("../../../data/ANGEL/fondos/infinito.png", BossType::JARDINES);
        asignarBoss(move(boss));
        bossJardinesCreado = true;
        bossCatacumbasCreado = false;
        bossComedorCreado = false;
        bossReyCreado = false;
    }
    else if (contadorInfinito > 21000 && contadorInfinito < 28000 && !bossComedorCreado)
    {
        auto boss = BossFactory::createBoss("../../../data/ANGEL/fondos/infinito.png", BossType::COMEDOR);
        asignarBoss(move(boss));
        bossComedorCreado = true;
        bossCatacumbasCreado = false;
        bossJardinesCreado = false;
        bossReyCreado = false;
    }
    else if (contadorInfinito > 28000 && !bossReyCreado)
    {
        auto boss = BossFactory::createBoss("../../../data/ANGEL/fondos/infinito.png", BossType::REY);
        asignarBoss(move(boss));
        bossReyCreado = true;
        bossCatacumbasCreado = false;
        bossJardinesCreado = false;
        bossComedorCreado = false;
    }
}

void Batalla::inicializarSpritesObjetos()
{

    fondo_objeto1 = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");
    fondo_objeto2 = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png");

    sf::Vector2u textureSizeFondo_objeto1 = fondo_objeto1->getSprite().getTexture()->getSize();
    fondo_objeto1->setOrigen(textureSizeFondo_objeto1.x / 2.0f, textureSizeFondo_objeto1.y / 2.0f);
    fondo_objeto1->setPosition((motor2D->getSize().x / 2) + 375, (motor2D->getSize().y / 2) + 247);
    fondo_objeto1->setTile(0, 0);
    fondo_objeto1->escalarSprite(2.5f);

    sf::Vector2u textureSizeFondo_objeto2 = fondo_objeto2->getSprite().getTexture()->getSize();
    fondo_objeto2->setOrigen(textureSizeFondo_objeto2.x / 2.0f, textureSizeFondo_objeto2.y / 2.0f);
    fondo_objeto2->setPosition((motor2D->getSize().x / 2) + 525, (motor2D->getSize().y / 2) + 247);
    fondo_objeto2->setTile(0, 0);
    fondo_objeto2->escalarSprite(2.5f);

    (**objeto1->getSprite()).setPosition(motor2D->getSize().x / 2 + 385, 360);
    (**objeto2->getSprite()).setPosition(motor2D->getSize().x / 2 + 535, 360);
}

void Batalla::pasarObjetos(int o1, int x1, int o2, int x2)
{
    auto objetonuevo = std::make_unique<Objeto>("../../../data/ANGEL/sprites/items/spritesheet_objetos.png", o1, x1);
    objeto1 = move(objetonuevo);
    int nivel = JSTienda::getInstance()->obtenerNivelPorID(objeto1->devolverObjeto());
    auto objetonuevo1 = std::make_unique<Objeto>("../../../data/ANGEL/sprites/items/spritesheet_objetos.png", o2, x2);
    objeto2 = move(objetonuevo1);
    // objeto2 = std::make_unique<Objeto>("nueva_ruta_a_spritesheet", o2, x1);

    (**objeto1->getSprite()).setPosition(motor2D->getSize().x / 2 + 387, 360);
    (**objeto2->getSprite()).setPosition(motor2D->getSize().x / 2 + 537, 360);
}