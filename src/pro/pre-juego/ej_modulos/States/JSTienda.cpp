#include "JSTienda.h"

// Constructor y destructor
JSTienda::JSTienda() : JState(), currentPage(0), estadoActual(PESTANA_OBJETOS), iAct(0), puedo(false), deltaT(0.0), contMov(0)
{
    motor2D = Motor2D::getInstance();

    std::string directorio = "../../../data/ANGEL/";

    if (!font.loadFromFile(directorio + "Fonts/alagard.ttf"))
    {
        std::cerr << "Error loading font\n";
    }
    compra = false;

    tinyxml2::XMLDocument doc;
    doc.LoadFile("../../../data/OCTAVIO/tienda.xml");

    tinyxml2::XMLElement *root = doc.FirstChildElement("tienda");
    pathObjetos = root->FirstChildElement("pathObjetos")->GetText();

    tinyxml2::XMLElement *stats = root->FirstChildElement("estadisticas");
    nivelVida = std::stoi(stats->FirstChildElement("vida")->Attribute("nivel"));
    nivelArmadura = std::stoi(stats->FirstChildElement("armadura")->Attribute("nivel"));
    monedas = std::stoi(stats->FirstChildElement("monedas")->Attribute("cantidad"));

    tinyxml2::XMLElement *objetos = root->FirstChildElement("objetos");
    for (tinyxml2::XMLElement *obj = objetos->FirstChildElement("objeto"); obj != nullptr; obj = obj->NextSiblingElement("objeto"))
    {
        int num = std::stoi(obj->Attribute("id"));
        std::string nombre = obj->Attribute("nombre");
        std::string descripcion = obj->FirstChildElement("descripcion")->GetText();
        int nivel = std::stoi(obj->Attribute("nivel"));

        numObjetos.push_back(num);

        MySprite *sprite = new MySprite(pathObjetos); // Asegúrate de que MySprite puede ser construido con un string
        sf::Vector2u text = sprite->getSprite().getTexture()->getSize();
        sprite->setOrigen(text.x / 2.0f, text.y / 2.0f);
        sprite->setPosition((motor2D->getSize().x / 2) + 630, (motor2D->getSize().y / 2) + 120);
        sprite->setTile(0, num);
        sprite->escalarSprite(2.5f);
        spritesObjetos.push_back(sprite);

        MySprite *sprite2 = new MySprite("../../../data/ANGEL/fondos/marco_objeto_lvl" + std::to_string(nivel) + ".png"); // Asegúrate de que MySprite puede ser construido con un string
        sf::Vector2u text2 = sprite2->getSprite().getTexture()->getSize();
        sprite2->setOrigen(text2.x / 2.0f, text2.y / 2.0f);
        sprite2->setPosition((motor2D->getSize().x / 2) + 630, (motor2D->getSize().y / 2) + 120);
        fondoObjetos.push_back(sprite2);

        sf::Text textNombre;
        textNombre.setFont(font); // Asegúrate de que 'font' está inicializado antes de usarlo
        textNombre.setCharacterSize(35);
        textNombre.setFillColor(sf::Color::White);
        textNombre.setOutlineColor(sf::Color::Black);
        textNombre.setOutlineThickness(5);
        textNombre.setString(nombre);
        nombreObjeto.push_back(textNombre);

        sf::Text textDescripcion;
        textDescripcion.setFont(font);
        textDescripcion.setCharacterSize(27);
        textDescripcion.setFillColor(sf::Color::White);
        textDescripcion.setOutlineColor(sf::Color::Black);
        textDescripcion.setOutlineThickness(5);
        textDescripcion.setString(descripcion);
        descripcionObjeto.push_back(textDescripcion);

        nivelObjetos.push_back(nivel);

        sf::RectangleShape *contador = new sf::RectangleShape(sf::Vector2f(100, 30));
        contador->setSize(sf::Vector2f(300, 30));
        contador->setFillColor(sf::Color::Green);
        contador->setScale(1.0f, 1.0f);
        contadoresMejora.push_back(contador);

        MySprite *sprite_mas = new MySprite(directorio + "fondos/boton_mejora_lvl" + std::to_string(2) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(2) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(2) + "_click.png");

        
        if (nivel + 1 <= 3)
        {
            sprite_mas->cambiarSpriteBoton(directorio + "fondos/boton_mejora_lvl" + std::to_string(nivel + 1) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivel + 1) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivel + 1) + "_click.png"); // Asegúrate de que MySprite puede ser construido con un string
        }

        sf::Vector2u text_mas = sprite_mas->getSprite().getTexture()->getSize();
        sprite_mas->setOrigen(text_mas.x / 2.0f, text_mas.y / 2.0f);
        sprite_mas->setPosition((motor2D->getSize().x / 2) + 630, (motor2D->getSize().y / 2) + 120);
        sprite_mas->escalarSprite(1.2f);
        botonParaMejorar.push_back(sprite_mas);

        MySprite *sprite_barra_mej = new MySprite("../../../data/ANGEL/fondos/marco_barra_lvl" + std::to_string(nivel) + ".png"); // Asegúrate de que MySprite puede ser construido con un string
        sf::Vector2u text_barra_m = sprite_barra_mej->getSprite().getTexture()->getSize();
        sprite_barra_mej->setOrigen(text_barra_m.x / 2.0f, text_barra_m.y / 2.0f);
        sprite_barra_mej->setPosition(430, (motor2D->getSize().y / 2) + 120);
        barraMejoraObjetos.push_back(sprite_barra_mej);
    }
    herrero = new MySprite("../../../data/JORGE/npcs/bored_02.png", // Ruta a la textura
                          10,                                                              // Número de frames
                          32, 
                          32,                                                            // Tamaño de cada frame (supongamos 32x32 píxeles)
                          0.15f,                                                           // Duración de cada frame en segundos
                          10                                                                // Número de frames por fila en la textura
    );
    herrero2 = new MySprite("../../../data/JORGE/npcs/work_01.png", // Ruta a la textura
                          5,                                                              // Número de frames
                          32,     
                          32,                                                        // Tamaño de cada frame (supongamos 32x32 píxeles)
                          0.15f,                                                           // Duración de cada frame en segundos
                          5                                                                // Número de frames por fila en la textura
    );
    inizializarInterfaz();
}

JSTienda::~JSTienda()
{
    // Limpieza de recursos dinámicos
    for (auto *sprite : spritesObjetos)
    {
        delete sprite;
    }
    for (auto *sprite2 : fondoObjetos)
    {
        delete sprite2;
    }
    for (auto *contador : contadoresMejora)
    {
        delete contador;
    }
    for (auto *mejorar : barraMejoraObjetos)
    {
        delete mejorar;
    }
    for (auto *moned : botonParaMejorar)
    {
        delete moned;
    }

    delete rectArmor;
    delete rectVida;
    delete mejoraArmor;
    delete mejoraVida;
    delete spriteMonedas;
    delete personaje_sprite;
    delete fondoArmor;
    delete fondoVida;
}

JSTienda *JSTienda::instance = nullptr;

JSTienda *JSTienda::getInstance()
{
    if (instance == nullptr)
    {
        instance = new JSTienda();
    }
    return instance;
}

void JSTienda::inizializarInterfaz()
{
    std::string directorio = "../../../data/ANGEL/";

    flecha_pasar = new MySprite(directorio + "fondos/volver_normal.png", directorio + "fondos/volver_hover.png", directorio + "fondos/volver_click.png");
    flecha_pasar->centrarOrigen();
    flecha_pasar->setPosition((motor2D->getSize().x / 2) - 720, motor2D->getSize().y - 220);
    flecha_pasar->escalarSprite(2.0f);

    flecha_atras = new MySprite(directorio + "fondos/avanzar_normal.png", directorio + "fondos/avanzar_hover.png", directorio + "fondos/avanzar_click.png");
    flecha_atras->centrarOrigen();
    flecha_atras->setPosition((motor2D->getSize().x / 2) + 700, motor2D->getSize().y - 220);
    flecha_atras->escalarSprite(2.0f);

    volver = new MySprite(directorio + "fondos/atras_normal.png", directorio + "fondos/atras_hover.png", directorio + "fondos/atras_click.png");
    sf::Vector2u volver_tex = volver->getSprite().getTexture()->getSize();
    volver->setOrigen(volver_tex.x / 2.0f, volver_tex.y / 2.0f);
    volver->setPosition((motor2D->getSize().x / 2) - 900, motor2D->getSize().y - 1000);
    volver->escalarSprite(2.0f);

    pestana_personaje = new MySprite(directorio + "fondos/personaje_normal.png", directorio + "fondos/personaje_hover.png", directorio + "fondos/personaje_click.png");
    pestana_personaje->centrarOrigen();
    pestana_personaje->setPosition((motor2D->getSize().x / 2) - 620, (motor2D->getSize().y / 2) - 420);

    pestana_objetos = new MySprite(directorio + "fondos/objetos_normal.png", directorio + "fondos/objetos_hover.png", directorio + "fondos/objetos_click.png");
    pestana_objetos->centrarOrigen();
    pestana_objetos->setPosition((motor2D->getSize().x / 2) - 400, (motor2D->getSize().y / 2) - 420);

    mantenerBotonPulsado();

    fondo = new MySprite("../../../data/ANGEL/fondos/fondo_piedra.png");

    fondo_pequeno = new MySprite("../../../data/ANGEL/fondos/marco_objetos.png");
    fondo_pequeno->centrarOrigen();
    fondo_pequeno->setPosition((motor2D->getSize().x / 2), (motor2D->getSize().y / 2));

    personaje_sprite = new MySprite("../../../data/ALE/Spritesheet/personajePrincipal.png");
    personaje_sprite->centrarOrigen();
    personaje_sprite->setPosition((motor2D->getSize().x / 2) + 190, (motor2D->getSize().y / 2) + 450);
    personaje_sprite->escalarSprite(8.0f);
    personaje_sprite->setTileDinamico(0, 0, 16, 24);

    if (!font.loadFromFile(directorio + "Fonts/alagard.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    textoVida.setFont(font);
    textoVida.setCharacterSize(35);
    textoVida.setFillColor(sf::Color::White);
    textoVida.setOutlineColor(sf::Color::Black);
    textoVida.setOutlineThickness(5);
    textoVida.setString("Vida");

    rectVida = new sf::RectangleShape(sf::Vector2f(100, 30));
    rectVida->setSize(sf::Vector2f(300, 30));
    rectVida->setFillColor(sf::Color::Green);
    rectVida->setScale(1.0f, 1.0f);

    if (nivelVida + 1 <= 3)
    {
        mejoraVida = new MySprite(directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelVida + 1) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelVida + 1) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelVida + 1) + "_click.png"); // Asegúrate de que MySprite puede ser construido con un string
        sf::Vector2u text_mas_vida = mejoraVida->getSprite().getTexture()->getSize();
        mejoraVida->setOrigen(text_mas_vida.x / 2.0f, text_mas_vida.y / 2.0f);
        mejoraVida->setPosition((motor2D->getSize().x / 2) - 74, (motor2D->getSize().y / 2) - 261);
        mejoraVida->escalarSprite(1.2f);
    }
    barraMejoraVida = new MySprite("../../../data/ANGEL/fondos/marco_barra_lvl" + std::to_string(nivelVida) + ".png"); // Asegúrate de que MySprite puede ser construido con un string
    sf::Vector2u text_barra_m_v = barraMejoraVida->getSprite().getTexture()->getSize();
    barraMejoraVida->setOrigen(text_barra_m_v.x / 2.0f, text_barra_m_v.y / 2.0f);
    barraMejoraVida->setPosition(645, 280);

    fondoVida = new MySprite("../../../data/ANGEL/fondos/marco_objeto_lvl" + std::to_string(nivelVida) + ".png"); // Asegúrate de que MySprite puede ser construido con un string
    sf::Vector2u text_fondo_vida = fondoVida->getSprite().getTexture()->getSize();
    fondoVida->setOrigen(text_fondo_vida.x / 2.0f, text_fondo_vida.y / 2.0f);
    fondoVida->setPosition((motor2D->getSize().x / 2) - 10, (motor2D->getSize().y / 2) - 275);

    fondoArmor = new MySprite("../../../data/ANGEL/fondos/marco_objeto_lvl" + std::to_string(nivelArmadura) + ".png"); // Asegúrate de que MySprite puede ser construido con un string
    sf::Vector2u text_fondo_armor = fondoArmor->getSprite().getTexture()->getSize();
    fondoArmor->setOrigen(text_fondo_armor.x / 2.0f, text_fondo_armor.y / 2.0f);
    fondoArmor->setPosition((motor2D->getSize().x / 2) - 10, (motor2D->getSize().y / 2) - 105);

    textArmor.setFont(font);
    textArmor.setCharacterSize(35);
    textArmor.setFillColor(sf::Color::White);
    textArmor.setOutlineColor(sf::Color::Black);
    textArmor.setOutlineThickness(5);
    textArmor.setString("Armadura");

    rectArmor = new sf::RectangleShape(sf::Vector2f(0, 30));
    rectArmor->setSize(sf::Vector2f(0, 30));
    rectArmor->setFillColor(sf::Color::Green);
    rectArmor->setScale(1.0f, 1.0f);

    if (nivelArmadura + 1 <= 3)
    {
        mejoraArmor = new MySprite(directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelArmadura + 1) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelArmadura + 1) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelArmadura + 1) + "_click.png"); // Asegúrate de que MySprite puede ser construido con un string
        sf::Vector2u text_mas_armor = mejoraArmor->getSprite().getTexture()->getSize();
        mejoraArmor->setOrigen(text_mas_armor.x / 2.0f, text_mas_armor.y / 2.0f);
        mejoraArmor->setPosition((motor2D->getSize().x / 2) - 74, (motor2D->getSize().y / 2) - 85);
        mejoraArmor->escalarSprite(1.2f);
    }

    barraMejoraArmor = new MySprite("../../../data/ANGEL/fondos/marco_barra_lvl" + std::to_string(nivelArmadura) + ".png"); // Asegúrate de que MySprite puede ser construido con un string
    sf::Vector2u text_barra_m_a = barraMejoraArmor->getSprite().getTexture()->getSize();
    barraMejoraArmor->setOrigen(text_barra_m_a.x / 2.0f, text_barra_m_a.y / 2.0f);
    barraMejoraArmor->setPosition(645, (motor2D->getSize().y / 2) - 85);

    std::string monedasString = std::to_string(monedas);

    textMonedas.setFont(font);
    textMonedas.setCharacterSize(35);
    textMonedas.setFillColor(sf::Color::White);
    textMonedas.setPosition(1500, 80);
    textMonedas.setOutlineColor(sf::Color::Black);
    textMonedas.setOutlineThickness(5);
    textMonedas.setString(monedasString);

    spriteMonedas = new MySprite("../../../data/ANGEL/sprites/items/spritesheet_objetos.png"); // Asegúrate de que MySprite puede ser construido con un string
    sf::Vector2u text_mon = spriteMonedas->getSprite().getTexture()->getSize();
    spriteMonedas->setOrigen(text_mon.x / 2.0f, text_mon.y / 2.0f);
    spriteMonedas->setPosition(1620, 350);
    spriteMonedas->escalarSprite(1.3f);
    spriteMonedas->setTile(1, 0);
}

void JSTienda::subirNivelObjeto(const std::string &pathArchivo, int idObjeto, int nuevoNivel)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(pathArchivo.c_str());

    tinyxml2::XMLElement *root = doc.FirstChildElement("tienda");
    tinyxml2::XMLElement *objetos = root->FirstChildElement("objetos");
    for (tinyxml2::XMLElement *obj = objetos->FirstChildElement("objeto"); obj != nullptr; obj = obj->NextSiblingElement("objeto"))
    {
        int id = obj->IntAttribute("id");
        if (id == idObjeto)
        {
            obj->SetAttribute("nivel", nuevoNivel);
            break;
        }
    }

    doc.SaveFile(pathArchivo.c_str());
}

void JSTienda::actualizarEstadistica(const std::string &pathArchivo, const std::string &estadistica, int nuevoValor)
{
    compra = true;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(pathArchivo.c_str());

    // Obtiene el elemento raíz 'tienda'
    tinyxml2::XMLElement *root = doc.FirstChildElement("tienda");
    if (!root)
    {
        std::cerr << "No se encontró el elemento 'tienda'. Asegúrate de que el XML está bien formado." << std::endl;
        return;
    }

    // Accede al nodo 'estadisticas'
    tinyxml2::XMLElement *stats = root->FirstChildElement("estadisticas");
    if (!stats)
    {
        std::cerr << "No se encontró el elemento 'estadisticas'. Asegúrate de que el XML está bien formado." << std::endl;
        return;
    }

    // Encuentra la estadística correcta
    tinyxml2::XMLElement *statElement = stats->FirstChildElement(estadistica.c_str());
    if (statElement)
    {
        // Actualiza el atributo relevante dependiendo de la estadística
        if (estadistica == "vida" || estadistica == "armadura")
        {
            statElement->SetAttribute("nivel", nuevoValor);
        }
        else if (estadistica == "monedas")
        {
            statElement->SetAttribute("cantidad", nuevoValor);
            monedas = nuevoValor;
        }
        else
        {
            std::cerr << "Estadística no reconocida." << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "No se encontró el elemento de estadística: " << estadistica << std::endl;
        return;
    }

    // Guarda el archivo modificado
    doc.SaveFile(pathArchivo.c_str());
}

std::string JSTienda::obtenerFuncionPorID(int idObjeto)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("../../../data/OCTAVIO/tienda.xml"); // Asegúrate de que la ruta al archivo XML es correcta
    if (doc.Error())
    {
        std::cerr << "Error al cargar el archivo XML" << std::endl;
        return ""; // Retorna una cadena vacía en caso de error
    }

    tinyxml2::XMLElement *root = doc.FirstChildElement("tienda");
    if (!root)
    {
        std::cerr << "No se encontró el elemento 'tienda'." << std::endl;
        return ""; // Retorna una cadena vacía si no se encuentra el elemento raíz
    }

    tinyxml2::XMLElement *objetos = root->FirstChildElement("objetos");
    if (!objetos)
    {
        std::cerr << "No se encontró el elemento 'objetos'." << std::endl;
        return ""; // Retorna una cadena vacía si no se encuentra el elemento 'objetos'
    }

    for (tinyxml2::XMLElement *obj = objetos->FirstChildElement("objeto"); obj != nullptr; obj = obj->NextSiblingElement("objeto"))
    {
        int currentID = std::stoi(obj->Attribute("id"));
        if (currentID == idObjeto)
        {
            tinyxml2::XMLElement *funcionElement = obj->FirstChildElement("funcion");
            if (funcionElement)
            {
                return funcionElement->GetText() ? funcionElement->GetText() : "";
            }
            break;
        }
    }

    std::cerr << "No se encontró un objeto con el ID especificado: " << idObjeto << std::endl;
    return ""; // Retorna una cadena vacía si no se encuentra el objeto
}

void JSTienda::mantenerBotonPulsado()
{
    if (estadoActual == EstadoTienda::PESTANA_PERSONAJE)
    {
        pestana_objetos->cambiaEstado("normal");
        pestana_personaje->cambiaEstado("click");
        pestana_objetos->escalarSprite(1.0f);
        pestana_personaje->escalarSprite(1.2f);
    }
    else if (estadoActual == EstadoTienda::PESTANA_OBJETOS)
    {
        pestana_personaje->cambiaEstado("normal");
        pestana_objetos->cambiaEstado("click");
        pestana_personaje->escalarSprite(1.0f);
        pestana_objetos->escalarSprite(1.2f);
    }
}

void JSTienda::handleButtonClick(const std::string &buttonName)
{
    if (buttonName.empty())
        return;

    if (buttonName == "personaje")
    {
        estadoActual = PESTANA_PERSONAJE;
    }

    if (buttonName == "objetos")
    {
        estadoActual = PESTANA_OBJETOS;
    }

    if (buttonName == "mejoraO")
    {
        if (puedo)
        {
            botonParaMejorar[iAct]->cambiarSpriteBoton(directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelObjetos[iAct] + 1) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelObjetos[iAct] + 1) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelObjetos[iAct] + 1) + "_click.png");
            puedo = false;
        }
    }

    if (buttonName == "mejoraV")
    {
        if (puedo)
        {
            mejoraVida->cambiarSpriteBoton(directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelVida + 1) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelVida + 1) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelVida + 1) + "_click.png");
            puedo = false;
        }
    }

    if (buttonName == "mejoraA")
    {
        if (puedo)
        {
            mejoraArmor->cambiarSpriteBoton(directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelArmadura + 1) + "_normal.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelArmadura + 1) + "_hover.png", directorio + "fondos/boton_mejora_lvl" + std::to_string(nivelArmadura + 1) + "_click.png");
            puedo = false;
        }
    }

    if (buttonName == "atras")
    {
        nextPage();
    }

    if (buttonName == "pasar")
    {
        previousPage();
    }

    if (buttonName == "volver")
    {
        Juego::getInstance()->resetToMainMenu();
    }

    if (buttonName == "boton_menos" || buttonName == "boton_mas")
    {
    }

    if (buttonName == "salir")
    {
        this->quit = true;
    }
}

int JSTienda::obtenerNivelPorID(int id)
{
    tinyxml2::XMLDocument doc;
    // Carga el archivo XML, asegúrate de especificar correctamente la ruta al archivo.
    doc.LoadFile("../../../data/OCTAVIO/tienda.xml");
    if (doc.Error())
    {
        std::cerr << "Error al cargar el archivo XML" << std::endl;
        return -1; // Indicador de error en la carga del archivo.
    }

    tinyxml2::XMLElement *root = doc.FirstChildElement("tienda");
    if (!root)
    {
        std::cerr << "No se encontró el elemento 'tienda'." << std::endl;
        return -1; // Indicador de error si no se encuentra el elemento raíz.
    }

    tinyxml2::XMLElement *objetos = root->FirstChildElement("objetos");
    if (!objetos)
    {
        std::cerr << "No se encontró el elemento 'objetos'." << std::endl;
        return -1; // Indicador de error si no se encuentra el elemento 'objetos'.
    }

    // Recorre todos los elementos 'objeto' hasta encontrar el con el ID correspondiente.
    for (tinyxml2::XMLElement *obj = objetos->FirstChildElement("objeto"); obj != nullptr; obj = obj->NextSiblingElement("objeto"))
    {
        int currentID = std::stoi(obj->Attribute("id"));
        if (currentID == id)
        {
            int nivel = std::stoi(obj->Attribute("nivel"));
            return nivel; // Retorna el nivel del objeto.
        }
    }

    std::cerr << "No se encontró un objeto con el ID especificado." << std::endl;
    return -1; // Retorna -1 si no se encuentra el objeto.
}

void JSTienda::renderObjects(sf::RenderTarget *target)
{
    if (!target)
        target = &this->motor2D->getVentana();

    int start = currentPage * objectsPerPage;
    int end = std::min(start + objectsPerPage, (int)spritesObjetos.size());

    float initialX = 200;
    float initialY = 200;
    float offsetY = 170; // Aumentado para dar más espacio entre objetos

    for (int i = start; i < end; ++i)
    {
        fondoObjetos[i]->setPosition(initialX + 750, 65 + initialY + offsetY * (i - start));
        motor2D->draw(&fondoObjetos[i]);

        spritesObjetos[i]->setPosition(initialX + 215, 545 + initialY + offsetY * (i - start));
        motor2D->draw(&spritesObjetos[i]);

        // Ajustar las posiciones de los textos para evitar que se superpongan
        nombreObjeto[i].setPosition(initialX + 230, initialY + offsetY * (i - start));
        descripcionObjeto[i].setPosition(initialX + 230, initialY + offsetY * (i - start) + 40); // Espacio adicional para la descripción

        target->draw(nombreObjeto[i]);
        target->draw(descripcionObjeto[i]);

        sf::RectangleShape *contador = contadoresMejora[i];
        contador->setSize(sf::Vector2f(0, 30));
        contador->setFillColor(sf::Color::Blue);
        contador->setScale(1.43f, 0.8f);
        contador->setPosition(initialX + 230, initialY + offsetY * (i - start) + 90); // Posición ajustada debajo de la descripción

        float porcentaje = static_cast<float>(100 * nivelObjetos[i]) / 300;
        contador->setSize(sf::Vector2f(300 * porcentaje, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

        motor2D->drawRectangle(*contador);

        if (nivelObjetos[i] +1 <= 3)
        {
            std::cout << "cojo el id: " << i << std::endl;

            botonParaMejorar[i]->setPosition(initialX + 700, initialY + offsetY * (i - start) + 102);
            motor2D->draw(&botonParaMejorar[i]);
        }
        barraMejoraObjetos[i]->setPosition(initialX + 443, initialY + offsetY * (i - start) + 102);
        motor2D->draw(&barraMejoraObjetos[i]);  

    }
}

void JSTienda::nextPage()
{
    if ((currentPage + 1) * objectsPerPage < spritesObjetos.size())
    {
        currentPage++;
    }
}

void JSTienda::previousPage()
{
    if (currentPage > 0)
    {
        currentPage--;
    }
}

bool JSTienda::puedoSubirNivel(int nuevoNivel)
{
    bool puedoComprar = false;

    if (nuevoNivel == 2)
    {
        if (monedas - 20 >= 0)
        {
            actualizarEstadistica("../../../data/OCTAVIO/tienda.xml", "monedas", monedas - 10);
            puedoComprar = true;
            monedas -= 10;
        }
    }
    else if (nuevoNivel == 3)
    {
        if (monedas - 40 >= 0)
        {
            actualizarEstadistica("../../../data/OCTAVIO/tienda.xml", "monedas", monedas - 20);
            puedoComprar = true;
            monedas -= 20;
        }
    }

    return puedoComprar;
}

// Funciones

void JSTienda::endState()
{
    std::cout << "Fin del Juego"
              << "\n";
}

void JSTienda::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void JSTienda::update(const float &dt, char &accion)
{
    std::string path = "../../../data/OCTAVIO/tienda.xml";
    compra = false;
    sf::Vector2f mousePosition = this->motor2D->getMousePosition();

    relojDelta.restart();

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
        pestana_personaje->cambiaEstado(pestana_personaje->getHitbox().contains(mousePosition) ? "hover" : "normal");
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pestana_personaje->getHitbox().contains(mousePosition))
        {
            pestana_personaje->cambiaEstado("click");
            lastClickedButton = "personaje"; // Guarda el botón clickeado
            clickTimer = clickDuration;      // Reiniciar temporizador
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pestana_objetos->getHitbox().contains(mousePosition))
        {
            lastClickedButton = "objetos"; // Guarda el botón clickeado
            clickTimer = clickDuration;    // Reiniciar temporizador
        }

        flecha_pasar->cambiaEstado(flecha_pasar->getHitbox().contains(mousePosition) ? "hover" : "normal");
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && flecha_pasar->getHitbox().contains(mousePosition))
        {
            flecha_pasar->cambiaEstado("click");
            lastClickedButton = "pasar"; // Guarda el botón clickeado
            clickTimer = clickDuration;  // Reiniciar temporizador
        }

        flecha_atras->cambiaEstado(flecha_atras->getHitbox().contains(mousePosition) ? "hover" : "normal");
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && flecha_atras->getHitbox().contains(mousePosition))
        {
            flecha_atras->cambiaEstado("click");
            lastClickedButton = "atras"; // Guarda el botón clickeado
            clickTimer = clickDuration;  // Reiniciar temporizador
        }

        volver->cambiaEstado(volver->getHitbox().contains(mousePosition) ? "hover" : "normal");
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && volver->getHitbox().contains(mousePosition))
        {
            volver->cambiaEstado("click");
            lastClickedButton = "volver"; // Guarda el botón clickeado
            clickTimer = clickDuration;   // Reiniciar temporizador
        }

        if (estadoActual == EstadoTienda::PESTANA_OBJETOS)
        {
            int start = currentPage * objectsPerPage;
            int end = std::min(start + objectsPerPage, (int)botonParaMejorar.size()); // Asegúrate de no exceder el tamaño del vector

            // Verifica si el clic es en algún botón de mejora en la página actual
            for (int i = start; i < end; ++i)
            {
                botonParaMejorar[i]->cambiaEstado(botonParaMejorar[i]->getHitbox().contains(mousePosition) ? "hover" : "normal");
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && botonParaMejorar[i]->getHitbox().contains(mousePosition))
                {
                    lastClickedButton = "mejoraO"; // Guarda el botón clickeado
                    clickTimer = clickDuration;    // Reiniciar temporizador
                    // Incrementar el nivel del objeto correspondiente
                    if (nivelObjetos[i] + 1 <= 3)
                    {
                        // nivelObjetos[i] += 1; // Asumiendo que nivelObjetos guarda los niveles de los objetos

                        if (puedoSubirNivel(nivelObjetos[i] + 1))
                        {
                            botonParaMejorar[i]->cambiaEstado("click");
                            nivelObjetos[i] += 1;
                            subirNivelObjeto("../../../data/OCTAVIO/tienda.xml", numObjetos[i], nivelObjetos[i]);
                            fondoObjetos[i]->cambiarSprite("../../../data/ANGEL/fondos/marco_objeto_lvl" + std::to_string(nivelObjetos[i]) + ".png");
                            barraMejoraObjetos[i]->cambiarSprite("../../../data/ANGEL/fondos/marco_barra_lvl" + std::to_string(nivelObjetos[i]) + ".png");
                            float porcentaje = static_cast<float>(100 * nivelObjetos[i]) / 300;
                            contadoresMejora[i]->setSize(sf::Vector2f(300 * porcentaje, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

                            if (nivelObjetos[i] + 1 <= 3)
                            {
                                iAct = i;
                                puedo = true;
                            }
                        }
                    }
                    break;
                }
            }
        }

        if (estadoActual == EstadoTienda::PESTANA_PERSONAJE)
        {
            if (nivelArmadura + 1 <= 3)
            {
                mejoraArmor->cambiaEstado(mejoraArmor->getHitbox().contains(mousePosition) ? "hover" : "normal");

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mejoraArmor->getHitbox().contains(mousePosition))
                {
                    lastClickedButton = "mejoraA"; // Guarda el botón clickeado
                    clickTimer = clickDuration;    // Reiniciar temporizador
                    if (nivelArmadura + 1 <= 3)
                    {
                        // nivelObjetos[i] += 1; // Asumiendo que nivelObjetos guarda los niveles de los objetos

                        if (puedoSubirNivel(nivelArmadura + 1))
                        {
                            nivelArmadura += 1;

                            mejoraArmor->cambiaEstado("click");

                            float suma = 120 + 120 * ((nivelArmadura - 1) / 2.0f);

                            barraMejoraArmor->cambiarSprite("../../../data/ANGEL/fondos/marco_barra_lvl" + std::to_string(nivelArmadura) + ".png");
                            fondoArmor->cambiarSprite("../../../data/ANGEL/fondos/marco_objeto_lvl" + std::to_string(nivelArmadura) + ".png");

                            PersonajePrincipal::getInstance()->subirArmorMax(suma);
                            PersonajePrincipal::getInstance()->quitarVida(PersonajePrincipal::getInstance()->getVidaMax(), suma);

                            actualizarEstadistica("../../../data/OCTAVIO/tienda.xml", "armadura", nivelArmadura);
                            float porcentaje = static_cast<float>(100 * nivelArmadura) / 300;
                            rectArmor->setSize(sf::Vector2f(300 * porcentaje, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

                            if (nivelArmadura + 1 <= 3)
                            {
                                puedo = true;
                            }
                        }
                    }
                }
            }
            if (nivelVida + 1 <= 3)
            {
                mejoraVida->cambiaEstado(mejoraVida->getHitbox().contains(mousePosition) ? "hover" : "normal");

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mejoraVida->getHitbox().contains(mousePosition))
                {
                    lastClickedButton = "mejoraV"; // Guarda el botón clickeado
                    clickTimer = clickDuration;    // Reiniciar temporizador
                    if (nivelVida + 1 <= 3)
                    {
                        // nivelObjetos[i] += 1; // Asumiendo que nivelObjetos guarda los niveles de los objetos

                        if (puedoSubirNivel(nivelVida + 1))
                        {
                            nivelVida += 1;

                            mejoraVida->cambiaEstado("click");

                            float suma = 120 + 120 * ((nivelVida - 1) / 2.0f);

                            barraMejoraVida->cambiarSprite("../../../data/ANGEL/fondos/marco_barra_lvl" + std::to_string(nivelVida) + ".png");
                            fondoVida->cambiarSprite("../../../data/ANGEL/fondos/marco_objeto_lvl" + std::to_string(nivelVida) + ".png");

                            PersonajePrincipal::getInstance()->subirVidaMax(suma);
                            PersonajePrincipal::getInstance()->quitarVida(suma, PersonajePrincipal::getInstance()->getArmorMax());

                            // std::cout << "nueva vida maxima: " << suma << std::endl;

                            actualizarEstadistica("../../../data/OCTAVIO/tienda.xml", "vida", nivelVida);
                            float porcentaje = static_cast<float>(100 * nivelVida) / 300;
                            rectVida->setSize(sf::Vector2f(300 * porcentaje, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho

                            if (nivelVida + 1 <= 3)
                            {
                                puedo = true;
                            }
                        }
                    }
                }
            }
        }
        mantenerBotonPulsado();
    }

    switch (accion)
    {
    case 'L':
        monedas = 999;
        actualizarEstadistica("../../../data/OCTAVIO/tienda.xml", "monedas", 999);
        break;
    }
}
void JSTienda::renderPersonaje(sf::RenderTarget *target)
{
    motor2D->draw(&fondoArmor);
    motor2D->draw(&fondoVida);

    textoVida.setPosition(430, 220);
    target->draw(textoVida);

    float porcentaje = static_cast<float>(nivelVida * 100) / 300;
    rectVida->setSize(sf::Vector2f(300 * porcentaje, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho
    rectVida->setFillColor(sf::Color::Red);
    rectVida->setPosition(430, 270);
    rectVida->setScale(1.43f, 0.8f);

    target->draw(*rectVida);

    textArmor.setPosition(430, 394);
    target->draw(textArmor);

    float porcentaje2 = static_cast<float>(nivelArmadura * 100) / 300;
    rectArmor->setSize(sf::Vector2f(300 * porcentaje2, 30)); // Asumimos que la barra de progreso es de 200 píxeles de ancho
    rectArmor->setFillColor(sf::Color::Blue);
    rectArmor->setPosition(430, 444);
    rectArmor->setScale(1.43f, 0.8f);

    target->draw(*rectArmor);

    if (nivelVida >= 3)
    {
    }
    else
    {
        motor2D->draw(&mejoraVida);
    }

    if (nivelArmadura >= 3)
    {
    }
    else
    {
        motor2D->draw(&mejoraArmor);
    }

    motor2D->draw(&barraMejoraVida);
    motor2D->draw(&barraMejoraArmor);
}

void JSTienda::render(sf::RenderTarget *target)
{

    if (!target)
    {
        target = &this->motor2D->getVentana();
    }

    float reloj = relojDelta.getElapsedTime().asMilliseconds() / 66.6;
    reloj += 0.25;
    deltaT = std::min(1.f, reloj);
    deltaT = std::round(deltaT * 100) / 100.0;

    this->motor2D->draw(&fondo);
    this->motor2D->draw(&fondo_pequeno);
    this->motor2D->draw(&pestana_personaje);
    this->motor2D->draw(&pestana_objetos);
    this->motor2D->draw(&volver);

    if (compra == false)
    {
        this->motor2D->draw(&herrero);
        herrero->setPosition((motor2D->getSize().x / 2) + 700, (motor2D->getSize().y / 2) - 300);
        herrero->escalarSprite(5.0);
        herrero->updateAnimacion();
    }
    if (compra == true)
    {
        this->motor2D->draw(&herrero2);
        herrero2->setPosition((motor2D->getSize().x / 2) + 700, (motor2D->getSize().y / 2) - 300);
        herrero2->escalarSprite(5.0);
        herrero2->updateAnimacion();
    }
    
    
    
    
    
    
        
    if (estadoActual == PESTANA_OBJETOS)
    {
        renderObjects(target);
        this->motor2D->draw(&flecha_atras);
        this->motor2D->draw(&flecha_pasar);
    }
    else if (estadoActual == PESTANA_PERSONAJE)
    {
        renderPersonaje(target);
        this->motor2D->draw(&personaje_sprite);
    }

    std::string monedasString = std::to_string(monedas);
    textMonedas.setString(monedasString);

    target->draw(textMonedas);
    motor2D->draw(&spriteMonedas);

    idlePersonaje();
}

void JSTienda::idlePersonaje()
{
    if (tiempoEspera.getElapsedTime().asSeconds() >= 0.7)
    {
        personaje_sprite->setTileDinamico(contMov, 0, 16, 24);
        if (deltaT > 0.19 && deltaT < 0.29)
        {
            contMov++;
            if (contMov > 1)
            {
                contMov = 0;
            }
        }
    }
}

int JSTienda::devolverMonedas(){
    return monedas;
}