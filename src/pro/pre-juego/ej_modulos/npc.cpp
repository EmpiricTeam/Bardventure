#include "npc.h"


Npc::Npc(const std::string& texture, NPCType type, int x, int y)
    : sprite(new MySprite(texture)), type(type), posicionInterpolada((x*32), (y*32)) {
    movement = sf::Vector2f(0.f, 0.f);
    int posx = (32*x)-16;
    int posy = (32*y)-16;
    dirMove = 0;
    contMove = 0;
    recarga = false;
    switch (type) {
    case PEON:
        hp = 100.0;
        //sprite->setOrigen(-16, -16);
        sprite->setTileDinamico(0 * 16, 0 * 16, 16, 16);
        sprite->setPosition(posx, posy);
        sprite->escalarSprite(2.0);
        break;
    case ALFIL:
        hp = 110.0;
        //sprite->setOrigen(-16, -16);
        sprite->setTileDinamico(0 * 16, 0 * 16, 16, 16);
        sprite->setPosition(posx, posy);
        sprite->escalarSprite(2.0);
        break;
    case REINA:
        hp = 130.0;
        //sprite->setOrigen(-16, -16);
        sprite->setTileDinamico(0 * 16, 0 * 16, 16, 16);
        sprite->setPosition(posx, posy);
        sprite->escalarSprite(2.0);
        break;
    case ARQUERO:
        hp = 100.0;
        //sprite->setOrigen(-16, -16);
        sprite->setTileDinamico(0 * 16, 0 * 16, 16, 16);
        sprite->setPosition(posx, posy);
        sprite->escalarSprite(2.0);
        contadorFlecha = 0;
        recarga = true;
        break;
    case JEFE:
        hp = 100.0;
        //sprite->setOrigen(-16, -16);
        sprite->setTileDinamico(0 , 0 , 16, 16);
        sprite->escalarSprite(2.0);
        sprite->setPosition(posx, posy);
        break;
    }
    
    
    
}

void Npc::updateNpc(sf::Vector2i playerPosition) {
    float nuevaX = playerPosition.x * 32;
    float nuevaY = playerPosition.y * 32;

    posicionInterpolada.actualizarPosicion(nuevaX,nuevaY);
         
}
void Npc::cargarFlechas(const std::string &texturaFlecha, sf::Vector2f posicionInicial, sf::Vector2f posicionPj) {
    sf::Vector2f direccion = ataqueArquero(posicionPj, posicionInicial);
    recarga = false;
    if(!carcaj.empty()){
        carcaj.erase(carcaj.begin());
    }

    carcaj.push_back(std::make_unique<Flecha>(texturaFlecha, direccion, posicionInicial));
}

void Npc::avanzaFlecha() {
    for (auto& flecha : carcaj) {
        float nuevaX = flecha->getPosicionInterpolada()->getPosicionX() + flecha->getdireccion()->x;
        float nuevaY = flecha->getPosicionInterpolada()->getPosicionY() + flecha->getdireccion()->y;

        flecha->getPosicionInterpolada()->actualizarPosicion(nuevaX,nuevaY);

        flecha->actualizarHitbox(flecha->getHitbox());
    }
}

void Npc::moveNPC(float deltaT){

    if(posicionInterpolada.getPosicionX() == sprite->getPosicion().x && posicionInterpolada.getPosicionY() == sprite->getPosicion().y){
        posicionInterpolada.actualizarPosicion(posicionInterpolada.getPosicionX(),posicionInterpolada.getPosicionY());
        if(tiempoEspera.getElapsedTime().asSeconds() >= 0.7 && recarga==false)
        {
            sprite->setTileDinamico(contMove,dirMove,16,16);
            
            if (deltaT > 0.19 && deltaT < 0.29)
            {
                contMove++;
                if (contMove >1)
                {
                    contMove=0;
                    if (type==ARQUERO)
                    {
                        recarga = true;
                    }  
                }
            }
            
        }
    }else{
        posicionInterpolada.setPercentTic(deltaT);
        sprite->setTileDinamico(contMove,dirMove,16,16);

        float nuevaX = posicionInterpolada.getPosicionInterpoladaX();
        float nuevaY = posicionInterpolada.getPosicionInterpoladaY();

        if (contMove >3)
        {
            contMove=0;
        }
        tiempoEspera.restart();

        sprite->setPosition(nuevaX,nuevaY); 
    }
}

sf::Vector2f Npc::ataqueArquero(sf::Vector2f posicionPj, sf::Vector2f posicionEn) {
    sf::Vector2f direccionProyectil(0.f, 0.f);
    sf::Vector2f delta = posicionPj - posicionEn;

    if(std::abs(delta.x) > std::abs(delta.y)) {
        direccionProyectil.x = (delta.x < 0) ? -32.0f : 32.0f; 
        if (direccionProyectil.x>0)
        {
            sprite->setTileDinamico(0,1,16,16);
            dirMove=1;
        }else{
            sprite->setTileDinamico(0,3,16,16);
            dirMove=3;

        }
    
    } else {
        direccionProyectil.y = (delta.y < 0) ? -32.0f : 32.0f; 
        if (direccionProyectil.y>0)
        {
            sprite->setTileDinamico(0,0,16,16);
            dirMove=0;
        }else{
            sprite->setTileDinamico(0,2,16,16);
            dirMove=2;
        }
    }

    return direccionProyectil;
}

sf::Vector2i Npc::nuevaPos(sf::Vector2f playerPosition) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    sf::Vector2f enemyPosition = sprite->getPosicion();
    float nuevaX = posicionInterpolada.getPosicionX();
    float nuevaY = posicionInterpolada.getPosicionY();
    const int tileSize = 32;

    std::uniform_int_distribution<int> smallDist(0, 9);  // Reemplaza 'rand() % 10'
    std::uniform_int_distribution<int> directionDist(0, 3);  // Para direcciones aleatorias
    std::uniform_int_distribution<int> moveDist(-1, 1);  // Para mover -tileSize, 0, tileSize

    switch (type) {
        case PEON: {
            sf::Vector2f result = playerPosition - enemyPosition;
            sf::Vector2f vectorAbs(std::abs(result.x), std::abs(result.y));

            int prob = smallDist(rng);

            if (prob < 2) {
                int randomDirection = directionDist(rng);
                switch (randomDirection) {
                    case 0: nuevaX += tileSize; 
                            sprite->setTileDinamico(0,1,16,16);
                            dirMove=1;
                        break;
                    case 1: nuevaX -= tileSize; 
                            sprite->setTileDinamico(0,3,16,16);
                            dirMove=3;
                        break;
                    case 2: nuevaY += tileSize; 
                            sprite->setTileDinamico(0,0,16,16);
                            dirMove = 0;
                        break;
                    case 3: nuevaY -= tileSize; 
                            sprite->setTileDinamico(0,2,16,16);
                            dirMove = 2;
                        break;
                }
            } else {
                if (vectorAbs.x >= vectorAbs.y) {
                    if (result.x < 0) {
                        nuevaX -= tileSize;
                        sprite->setTileDinamico(0,3,16,16);
                        dirMove = 3;
                    } else {
                        nuevaX += tileSize;
                        sprite->setTileDinamico(0,1,16,16);
                        dirMove = 1;
                    }
                } else {
                    if (result.y < 0) {
                        nuevaY -= tileSize;
                        sprite->setTileDinamico(0,2,16,16);
                        dirMove = 2;
                    } else {
                        nuevaY += tileSize;
                        sprite->setTileDinamico(0,0,16,16);
                        dirMove = 0;
                    }
                }
            }
            break;
        }
        case REINA: {
            sf::Vector2f result = playerPosition - enemyPosition;
            int prob = smallDist(rng);

            if (prob < 3) {
                int rX = moveDist(rng);
                int rY = moveDist(rng);
                nuevaX +=  rX * tileSize;
                nuevaY += rY * tileSize;

                if (rX > 0 && rY>0)
                {
                    sprite->setTileDinamico(0,1,16,16);
                    dirMove = 1;
                }else if(rX > 0 && rY==0){
                    sprite->setTileDinamico(0,2,16,16);
                    dirMove = 2;
                }else if(rX > 0 && rY<0){
                    sprite->setTileDinamico(0,3,16,16);
                    dirMove = 3;
                }else if(rX == 0 && rY>0){
                    sprite->setTileDinamico(0,0,16,16);
                    dirMove = 0;
                }else if(rX== 0 && rY<0){
                    sprite->setTileDinamico(0,4,16,16);
                    dirMove = 4;
                }else if(rX < 0 && rY<0){
                    sprite->setTileDinamico(0,5,16,16);
                    dirMove = 5;
                }else if(rX < 0 && rY==0){
                    sprite->setTileDinamico(0,6,16,16);
                    dirMove = 6;
                }else if(rX < 0 && rY>0){
                    sprite->setTileDinamico(0,7,16,16);
                    dirMove = 7;
                }
                
            } else if (prob < 7) {
                if (std::abs(result.x) > std::abs(result.y)) {
                    nuevaX = result.x < 0 ? nuevaX - tileSize : nuevaX + tileSize;
                } else {
                    nuevaY = result.y < 0 ? nuevaY - tileSize : nuevaY + tileSize;
                }
                if (result.x > 0 && result.y>0)
                {
                    sprite->setTileDinamico(0,1,16,16);
                    dirMove = 1;
                }else if(result.x > 0 && result.y==0){
                    sprite->setTileDinamico(0,2,16,16);
                    dirMove = 2;
                }else if(result.x > 0 && result.y<0){
                    sprite->setTileDinamico(0,3,16,16);
                    dirMove = 3;
                }else if(result.x == 0 && result.y>0){
                    sprite->setTileDinamico(0,0,16,16);
                    dirMove = 0;
                }else if(result.x == 0 && result.y<0){
                    sprite->setTileDinamico(0,4,16,16);
                    dirMove = 4;
                }else if(result.x < 0 && result.y<0){
                    sprite->setTileDinamico(0,5,16,16);
                    dirMove = 5;
                }else if(result.x < 0 && result.y==0){
                    sprite->setTileDinamico(0,6,16,16);
                    dirMove = 6;
                }else if(result.x < 0 && result.y>0){
                    sprite->setTileDinamico(0,7,16,16);
                    dirMove = 7;
                }
            } else {
                nuevaX = result.x < 0 ? nuevaX - tileSize : (result.x > 0 ? nuevaX + tileSize : nuevaX);
                nuevaY = result.y < 0 ? nuevaY - tileSize : (result.y > 0 ? nuevaY + tileSize : nuevaY);
                if (result.x > 0 && result.y>0)
                {
                    sprite->setTileDinamico(0,1,16,16);
                    dirMove = 1;
                }else if(result.x > 0 && result.y==0){
                    sprite->setTileDinamico(0,2,16,16);
                    dirMove = 2;
                }else if(result.x > 0 && result.y<0){
                    sprite->setTileDinamico(0,3,16,16);
                    dirMove = 3;
                }else if(result.x == 0 && result.y>0){
                    sprite->setTileDinamico(0,0,16,16);
                    dirMove = 0;
                }else if(result.x == 0 && result.y<0){
                    sprite->setTileDinamico(0,4,16,16);
                    dirMove = 4;
                }else if(result.x < 0 && result.y<0){
                    sprite->setTileDinamico(0,5,16,16);
                    dirMove = 5;
                }else if(result.x < 0 && result.y==0){
                    sprite->setTileDinamico(0,6,16,16);
                    dirMove = 6;
                }else if(result.x < 0 && result.y>0){
                    sprite->setTileDinamico(0,7,16,16);
                    dirMove = 7;
                }
            }

            
            std::cout << "nuevaX: " << result.x << ", nuevaY: " << result.y << std::endl;


            break;
        }
        case ALFIL: {
            int prob = smallDist(rng);
            if (prob < 2) {
                int diagonalDirection = directionDist(rng);
                switch (diagonalDirection) {
                    case 0: nuevaX += tileSize; nuevaY -= tileSize; sprite->setTileDinamico(0,2,16,16); dirMove = 2; break;
                    case 1: nuevaX -= tileSize; nuevaY -= tileSize; sprite->setTileDinamico(0,3,16,16); dirMove = 3; break;
                    case 2: nuevaX += tileSize; nuevaY += tileSize; sprite->setTileDinamico(0,1,16,16); dirMove = 1; break;
                    case 3: nuevaX -= tileSize; nuevaY += tileSize; sprite->setTileDinamico(0,4,16,16); dirMove = 4; break;
                }
            } else {
                sf::Vector2f diff = playerPosition - enemyPosition;
                if (diff.x>0 && diff.y>0)
                {
                    nuevaX = nuevaX + tileSize;
                    nuevaY = nuevaY + tileSize;
                    sprite->setTileDinamico(0,1,16,16); 
                    dirMove = 1;
                }else if (diff.x>0 && diff.y < 0)
                {
                    nuevaX = nuevaX + tileSize;
                    nuevaY = nuevaY - tileSize;
                    sprite->setTileDinamico(0,2,16,16); 
                    dirMove = 2;
                }else if(diff.x<0 && diff.y>0){
                    nuevaX = nuevaX - tileSize;
                    nuevaY = nuevaY + tileSize;
                    sprite->setTileDinamico(0,4,16,16); 
                    dirMove = 4;
                }else{
                    nuevaX = nuevaX - tileSize;
                    nuevaY = nuevaY - tileSize;
                    sprite->setTileDinamico(0,3,16,16); 
                    dirMove = 3;
                }
                
                
            }
            break;
        }
        case ARQUERO: {
            nuevaX = sprite->getPosicion().x;
            nuevaY = sprite->getPosicion().y;
            avanzaFlecha();

            break;
        }
        case JEFE: {
            sf::Vector2f result = playerPosition - enemyPosition;
            int prob = smallDist(rng);
    
            nuevaX = result.x < 0 ? nuevaX - tileSize : (result.x > 0 ? nuevaX + tileSize : nuevaX);
            nuevaY = result.y < 0 ? nuevaY - tileSize : (result.y > 0 ? nuevaY + tileSize : nuevaY);
            
            break;
        }
    }
    sf::Vector2i posiblePosicion(nuevaX / 32, nuevaY / 32);
    return posiblePosicion;
}


int Npc::getX(){
    return posicionInterpolada.getPosicionX()/32;
}

int Npc::getY(){
    return posicionInterpolada.getPosicionY()/32;
}

int Npc::getContadorFlecha()
{
    return contadorFlecha;
}

void Npc::aumContador()
{
    contadorFlecha = (contadorFlecha + 1) % 10;
}

sf::FloatRect Npc::getFlecha()
{
    sf::FloatRect dev;
    for (auto& flecha : carcaj) {
        dev = flecha->getHitbox();
    }
    return dev;
}

sf::String Npc::getTipo() {
    switch (type) {
        case PEON:
            return "PEON";
            break;
        case ALFIL:
            return "ALFIL";
            break;
        case REINA:
            return "REINA";
            break;
        case ARQUERO:
            return "ARQUERO";
            break;
        case JEFE:
            //std::cout << "Soy un JEFE" << std::endl;
            return "JEFE";
            break;
    }
}

void Npc::setRecarga()
{
    recarga = true;
}

MySprite** Npc::getSprite(){
    return &sprite;
}

std::string Npc::getPathSprite(){
    return sprite->getPath();
}

int Npc::getHp()
{
    return hp;
}

sf::Vector2f Npc::getPosicion()
{
    return sprite->getPosicion();
}

std::vector<std::unique_ptr<Flecha>>& Npc::getCarcaj() {
    return carcaj;
}