#include "Habitacion.h"
#include "../third_party/tinyxml2.h" // Asegúrate de ajustar la ruta de inclusión según sea necesario

bool Habitacion::cargaHabitacion(const std::string &archivoMapa)
{
  std::cout<<"Estoy cargando la habitacion"<<std::endl;
  npcs.clear();
  tinyxml2::XMLDocument archivo;
  if (archivo.LoadFile(archivoMapa.c_str()) != tinyxml2::XML_SUCCESS)
    return false;

  tinyxml2::XMLElement *map = archivo.FirstChildElement("map");
  if (!map)
    return false;

  map->QueryIntAttribute("width", &_width);
  map->QueryIntAttribute("height", &_heigth);
  map->QueryIntAttribute("tilewidth", &_tilewidth);
  map->QueryIntAttribute("tileheight", &_tileheigth);
  tilesetSize = {static_cast<unsigned int>(_tilewidth), static_cast<unsigned int>(_tileheigth)};

  tinyxml2::XMLElement *tilesetElement = map->FirstChildElement("tileset");
  const char *tsxFileName = tilesetElement->Attribute("source");
  tinyxml2::XMLDocument archivo2;
  std::string tsxFilePath = "../../../data/ALE/" + std::string(tsxFileName);
  if (archivo2.LoadFile(tsxFilePath.c_str()) != tinyxml2::XML_SUCCESS)
    return false;
  tinyxml2::XMLElement *tilesetImgSource = archivo2.FirstChildElement("tileset")->FirstChildElement("image");
  const char *filename = tilesetImgSource->Attribute("source");
  std::string tilesetSource = "../../../data/ALE/" + std::string(filename);

  tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
  _numlayers = 0;
  std::vector<int *> tiles;
  while (layer)
  {
    _numlayers++;
    const char *name = layer->Attribute("name");
    tinyxml2::XMLElement *data = layer->FirstChildElement("data");
    std::vector<std::string> tileStrings = split(data->GetText(), ','); // Asegúrate de que la función split está definida
    int *layerTiles = new int[tileStrings.size()];
    for (size_t i = 0; i < tileStrings.size(); ++i)
    {
      layerTiles[i] = std::stoi(tileStrings[i]);
    }

    if (name != nullptr && strcmp(name, "Spawn") == 0)
    {
      tilemapSpawn = layerTiles;
    }else if (name !=nullptr && strcmp(name,"Hitbox")==0)
    {
      tilemapHitbox.resize(_heigth);
      for (int y = 0; y < _heigth; ++y) {
          tilemapHitbox[y].resize(_width);
          for (int x = 0; x < _width; ++x) {
              int index = y * _width + x;
              tilemapHitbox[y][x] = layerTiles[index];
          }
      }
    }else if(name !=nullptr && strcmp(name,"Movimiento")==0)
    {
      tilemapMovimientos.resize(_heigth);
      for (int y = 0; y < _heigth; ++y) {
          tilemapMovimientos[y].resize(_width);
          for (int x = 0; x < _width; ++x) {
              int index = y * _width + x;
              tilemapMovimientos[y][x] = layerTiles[index];
          }
      }
    }
    else
    {
      if(name !=nullptr && strcmp(name,"Capa de patrones 6")==0){
        for (int y = 0; y < _heigth; ++y) {
          for (int x = 0; x < _width; ++x) {
              int index = y * _width + x;
              if(layerTiles[index]==1165){
                std::unique_ptr<MySprite> newSprite = std::make_unique<MySprite>(
                            "../../../data/ALE/Spritesheet/Efectos/11_fire_spritesheet.png", // Ruta a la textura
                            61,    // Número de frames
                            100,    // Tamaño de cada frame (supongamos 32x32 píxeles)
                            100,
                            0.05f,  // Duración de cada frame en segundos
                            8      // Número de frames por fila en la textura
                        );
                newSprite->setPosition(x*32+15,y*32+10);
                newSprite->escalarSprite(0.7f);
                vfx.push_back(std::move(newSprite));
              }
          }
      }
      }
      Tilemap tm;
      tm.load(tilesetSource, tilesetSize, layerTiles, _width, _heigth);
      tilemaps.push_back(tm);
    }

    layer = layer->NextSiblingElement("layer");
  }
  
  return true;
}

void Habitacion::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();


    if (tilemaps.size() >= 2)
    {
      for (int i = 0; i < 2; ++i) {
              target.draw(tilemaps[i], states);
          }
    }else{
      target.draw(tilemaps[0], states);
      
    }
}

void Habitacion::drawRest(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    
    for (size_t i = 2; i < tilemaps.size(); ++i) {
        target.draw(tilemaps[i], states);
    }

    for (const auto& sprite : vfx) {
        sprite->updateAnimacion();
        target.draw(sprite->getSprite(), states);
    }
}


std::vector<std::string> Habitacion::split(const std::string &str, char delim)
{
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = str.find(delim);
  while (end != std::string::npos)
  {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delim, start);
  }
  tokens.push_back(str.substr(start));
  return tokens;
}

void Habitacion::crearYAgregarNPC(std::string &tex, NPCType tipo, int x, int y)
{
  auto npc = NPCFactory::createNPC(tex, tipo, x, y);
  npcs.push_back(std::move(npc));
}

bool Habitacion::spawnEntidades(int tipo)
{

  sf::Texture *tex = new sf::Texture();
  std::string path = "";
  
  

  for (int h = 0; h < _heigth; h++)
  {
    for (int w = 0; w < _width; w++)
    {
      int index = h * _width + w; // Calcula el índice correcto
      if (tilemapSpawn && tilemapSpawn[index] != 0)
      {
        int tipoEnemigo = tilemapSpawn[index];
        switch (tipoEnemigo)
        {
        case 794:
          /* PEON */
          path = "../../../data/ALE/Spritesheet/peon.png";
          std::cout << "Genero peon" << std::endl;
          crearYAgregarNPC(path, NPCType::PEON, w, h);
          break;
        case 795:
          /* ALFIL */
          path = "../../../data/ALE/Spritesheet/alfil.png";
          std::cout << "Genero alfil" << std::endl;
          crearYAgregarNPC(path, NPCType::ALFIL, w, h);
          break;
        case 842:
          /* REINA */
          path = "../../../data/ALE/Spritesheet/reina.png";
          std::cout << "Genero reina" << std::endl;
          crearYAgregarNPC(path, NPCType::REINA, w, h);
          break;
        case 843:
          /* ARQUERO */
          path = "../../../data/ALE/Spritesheet/arquero.png";
          std::cout << "Genero arquero" << std::endl;
          crearYAgregarNPC(path, NPCType::ARQUERO, w, h);
          break;
        case 890:
          /* BOSS */
          switch (tipo)
          {
          case 0:
            //CARCEL
            
            path = "../../../data/JORGE/npcs/alcaichofa.png";
            break;
          case 1:
            //CATACUMBA
            
            path = "../../../data/JORGE/npcs/tortuga.png";

            break;
          case 2:
            //JARDIN
            path = "../../../data/JORGE/npcs/garbanzo.png";
            
            break;
          case 3:
            //COMEDOR
            path = "../../../data/JORGE/npcs/motzarela.png";
            break;
          case 4:
            //TRONO
            path = "../../../data/JORGE/npcs/lemon.png";
            break;
          default:
            //BASICO

            break;
          }
          std::cout << "Genero boss" << std::endl;
          crearYAgregarNPC(path, NPCType::JEFE, w, h);
          break;
        default:
          /*JUGADOR*/
          sf::Vector2f posicioninicialPJ(w,h);
          std::cout <<"Estoy en Habitacion y w es:" <<w << " y h es: "<< h<<std::endl;
          PersonajePrincipal::getInstance()->setPosicion(w,h);
          break;
        }
      }
    }
  }
  return true;
}

bool Habitacion::checkMoveEntidad(int iterador, int x, int y){
  if (iterador < 0 || iterador >= npcs.size()) {
    std::cerr << "Índice fuera de rango." << std::endl;
    return false;  
  }
  if(tilemapHitbox[y][x]!=0){
    return false;
  }
  for(int i = 0; i < npcs.size(); i++){
    if(i != iterador){  
      Npc* npcCheck = npcs[i].get(); 
      if(npcCheck->getX() == x && npcCheck->getY() == y){
        return false; 
      }
    }
  }
  return true;
}

Npc* Habitacion::checkNPCbatalla(int tileX,int tileY){
  int xFuturo = tileX;
  int yFuturo = tileY;

  Npc* npcBatallero = nullptr;
    for(int i=0; i < npcs.size(); i++){
        Npc* npcActual = npcs[i].get();
        if((npcActual->getTipo()=="JEFE")&&(abs(npcActual->getX() - xFuturo) <= 2) && (abs(npcActual->getY() - yFuturo) <= 2)){
          npcBatallero = npcActual;
          break; 
        }
        else if ((abs(npcActual->getX() - xFuturo) <= 1) && (abs(npcActual->getY() - yFuturo) <= 1)){
            npcBatallero = npcActual;
            break;
        }
            
    }

  if (npcBatallero == nullptr) {
        return nullptr;
    } else {
        return npcBatallero;
    }
}

void Habitacion::eliminarNPC(Npc* npcActual) {
    // Encuentra el iterador al elemento correspondiente
    auto it = std::find_if(npcs.begin(), npcs.end(), [npcActual](const std::unique_ptr<Npc>& npc) {
        return npc.get() == npcActual;
    });

    // Si el NPC fue encontrado, elimínalo del vector
    if (it != npcs.end()) {
        npcs.erase(it);
    }
}


std::vector<std::vector<int>> Habitacion::getTilemapHitbox(){
  return tilemapHitbox;
}

std::vector<std::vector<int>> Habitacion::getTilemapMovimientos(){
  return tilemapMovimientos;
}

const std::vector<std::unique_ptr<Npc>>& Habitacion::getNpcs() const {
  return npcs;
}   


