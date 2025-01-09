#include "PersonajePrincipal.h"

constexpr int TILE_SIZE = 32;
PersonajePrincipal::PersonajePrincipal() : sprite((new MySprite("../../../data/ALE/Spritesheet/personajePrincipal.png"))), posicionInterpolada(0,0)
{
    sprite->setTileDinamico(0, 0,16,24);
    sprite->escalarSpritePorValor(2.0,1.6);
    sprite->setPosition(0,0);

    vidaMax = 120;

    dirMove = 0;
    contMove = 0;
    vida = vidaMax;
    armor = 0;
    
    hitbox = sprite->getHitbox();
}

PersonajePrincipal *PersonajePrincipal::instance = nullptr;

PersonajePrincipal *PersonajePrincipal::getInstance()
{
    if (instance == nullptr)
    {
        instance = new PersonajePrincipal();
    }
    return instance;
}

PersonajePrincipal::~PersonajePrincipal()
{

}

float PersonajePrincipal::devolverVida(){
    return vida;
}

float PersonajePrincipal::devolverArmor(){
    return armor;
}

void PersonajePrincipal::quitarVidaFlecha(){
    float sobrante = 0;
    if (armor>0)
    { 
        armor = armor - 30;
        if (armor <0)
        {
            sobrante = abs(armor);
        }
    }else{
        vida = vida - 30;
    }
    
    if (sobrante > 0)
    {
        vida = vida - sobrante;
    }
    

    if (vida<0)
    {
        vida = 0;
    }

    if (armor < 0){
        armor = 0;
    }
    
}

void PersonajePrincipal::quitarVida(int vidaP){
    float sobrante = 0;
    if (armor>0)
    { 
        armor = armor - vidaP;
        if (armor <0)
        {
            sobrante = abs(armor);
        }
    }else{
        vida = vida - vidaP;
    }
    
    if (sobrante > 0)
    {
        vida = vida - sobrante;
    }
    

    if (vida<0)
    {
        vida = 0;
    }

    if (vida > vidaMax){
        vida = vidaMax;
    }

    if (armor < 0){
        armor = 0;
    }
    
}

void PersonajePrincipal::DarArmadura(float armadura){
    if(armor + armadura > vida){
        armor = vida;
    }else{
        armor += armadura;
    }
}

void PersonajePrincipal::update(int movimiento) {

    
    const float desplazamiento = TILE_SIZE; // La distancia que se mueve en cada dirección
    float nuevaX = posicionInterpolada.getPosicionX();
    float nuevaY = posicionInterpolada.getPosicionY();

    // Calcular nuevas posiciones finales basadas en el input de movimiento
    switch (movimiento) {
        case 1: nuevaY -= desplazamiento; 
                sprite->setTileDinamico(0,2,16,24);    
                dirMove = 2;
                break; // Arriba
        case 2: nuevaY += desplazamiento; 
                sprite->setTileDinamico(0,0,16,24);   
                dirMove = 0; 
                break; // Abajo
        case 3: nuevaX -= desplazamiento; 
                sprite->setTileDinamico(0,3,16,24);   
                dirMove = 3;
                break; // Izquierda
        case 4: nuevaX += desplazamiento; 
                sprite->setTileDinamico(0,1,16,24);  
                dirMove = 1;
                break; // Derecha
    }

    posicionInterpolada.actualizarPosicion(nuevaX, nuevaY);

    
    hitbox = sprite->getHitbox();
    
}

void PersonajePrincipal::movePj(float deltaT){
    
    if(posicionInterpolada.getPosicionX() == sprite->getPosicion().x && posicionInterpolada.getPosicionY() == sprite->getPosicion().y)
    {
        posicionInterpolada.actualizarPosicion(posicionInterpolada.getPosicionX(),posicionInterpolada.getPosicionY());
        if(tiempoEspera.getElapsedTime().asSeconds() >= 0.7){
            sprite->setTileDinamico(contMove,dirMove,16,24);
            if(deltaT > 0.19 && deltaT < 0.29)
            {
                contMove++;
                if (contMove >1)
                {
                    contMove=0;
                }
                
            }
        }
    }else{
        
        sprite->setTileDinamico(contMove,dirMove,16,24);


        posicionInterpolada.setPercentTic(deltaT);

        float nuevaX = posicionInterpolada.getPosicionInterpoladaX();
        float nuevaY = posicionInterpolada.getPosicionInterpoladaY();

        sprite->setPosition(nuevaX,nuevaY); 
        contMove++;
        if (contMove >3)
        {
            contMove=0;
        }
        tiempoEspera.restart();
    }
    hitbox = sprite->getHitbox();
    
}

void PersonajePrincipal::subirVidaMax(float vM){

    vidaMax = vM;
}

float PersonajePrincipal::getVidaMax(){
    return vidaMax;
}

void PersonajePrincipal::subirArmorMax(float aM){

    vidaMax = aM;
}

float PersonajePrincipal::getArmorMax(){
    return vidaMax;
}

void PersonajePrincipal::sumarVida(int suma){
    if(vida + suma >= vidaMax){
        vida = vidaMax;
    }else if(vida + suma <=0){
        vida = 0;
    }else{
        vida = vida + suma;
    }
}

void PersonajePrincipal::quitarVida(float hp, float armadura){

    vida = hp;
    armor = armadura;    
}

// Método setPosicion
void PersonajePrincipal::setPosicion(int x, int y) {
    int posx = (TILE_SIZE * x);
    int posy = (TILE_SIZE * y);

    std::cout <<"Estoy en Personaje principal y x es:" <<x << " y y es: "<< y<<std::endl;
    std::cout <<"Estoy en Personaje principal y posx es:" <<posx << " y posy es: "<< posy<<std::endl;

    posicionInterpolada.actualizarPosicion(posx,posy);
    posicionInterpolada.actualizarPosicion(posx,posy);
    sprite->setPosition(posx, posy);
}

sf::FloatRect PersonajePrincipal::getHitbox()
{
    return hitbox;
}
MySprite** PersonajePrincipal::getSprite(){
    return &sprite;
}

sf::Vector2f PersonajePrincipal::getPosicion()
{
    return sprite->getPosicion();
}
