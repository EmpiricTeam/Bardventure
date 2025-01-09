#include "Boss.h"

Boss::Boss(const std::string& texture, BossType type): tipo(type) {
    switch (tipo)
    {
    case PRISION:
        vida = 200;
        maxValorVidaBoss = 200;
        nombre = "Alkaychofa, el alcaide";
        break;
    case CATACUMBAS:
        vida = 800;
        maxValorVidaBoss = 800;
        nombre = "Hector Tuga";
        break;
    case JARDINES:
        vida = 400;
        maxValorVidaBoss = 400;
        nombre = "Ludwig Van Garbanzo";
        break;
    case COMEDOR:
        vida = 500;
        maxValorVidaBoss = 500;
        nombre = "Mozartrella";
        break;
    case REY: 
        vida = 600;
        maxValorVidaBoss = 600;
        nombre = "John Lemon";

        break;
    
    }
    sprite = new MySprite(texture);
    Motor2D* motor2d = Motor2D::getInstance();
    sprite->centrar();
    sprite->setPosition(motor2d->getSize().x/2, 250);
    sprite->escalarSprite(0.6);

    // COLOCAR AL SPRITE EN LA POSICIÓN CORRECTA LA CUÁL AÚN NO SE

    
}

BossType Boss::getTipo(){
    return tipo;
}

void Boss::actualizarVida(int cantidad){
    //std::cout << vida << std::endl;
    vida += cantidad;
    if (vida > maxValorVidaBoss) {
        vida = maxValorVidaBoss;
    } else if (vida < 0) {
        vida = 0;
    }
    //std::cout << vida << std::endl;

}

int Boss::getVida(){
    return vida;
}

int Boss::getVidaMax(){
    return maxValorVidaBoss;
}

void Boss::asignarTipoNivel(int level1){
    level = level1;
}

void Boss::cambiarVidaNPC(float vidaNPC){
        std::cout << "LEVEL EN BOSS: " << level << std::endl;

    if(level==0){
        maxValorVidaBoss = vidaNPC;
        vida = vidaNPC;
    }
    else if(level == 1){
        maxValorVidaBoss = vidaNPC;
        vida = vidaNPC + (25/100.0f)*vidaNPC;
    }
    else if(level == 2){
        maxValorVidaBoss = vidaNPC;
        vida = vidaNPC + (50/100.0f)*vidaNPC;
    }
    else if(level == 3){
        std::cout << "ENTRA" << std::endl;
        maxValorVidaBoss = vidaNPC;
        vida = vidaNPC + ((75/100.0f)*vidaNPC);
    }

}

sf::String Boss::getNombre(){
    return nombre;
}

void Boss::asignarNombreNPC(sf::String tipoNPC){
    nombre = tipoNPC;
}

void Boss::asignarSprite(MySprite* spriteB){
    //Tengo que borrar el puntero de antes ???
    sprite = nullptr;
    sprite = new MySprite(spriteB->getPath());
    Motor2D* motor2d = Motor2D::getInstance();
    sprite->centrar();
    if(tipo == BossType::CATACUMBAS){
        sprite->setPosition(motor2d->getSize().x/2, 325);
    }
    else {
        sprite->setPosition(motor2d->getSize().x/2, 250);
    }
    sprite->escalarSprite(0.6);
}

MySprite** Boss::getSprite(){
    return &sprite;
}