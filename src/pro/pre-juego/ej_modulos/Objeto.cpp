#include "Objeto.h"

Objeto::Objeto(const std::string &texture, int num, float x) : sprite(new MySprite(texture)){
    switch (num)
    {
    case 0:
        type = ObjectType::Vacio;
        consumible = false;
        nivel = -1;
        break;
    case 1:
        type = ObjectType::Armadura;
        consumible = true;
        break;
    case 2:
        type = ObjectType::Armadura2;
        consumible = true;
        break;    
    case 3:
        type = ObjectType::Vida;
        consumible = true;
        break;
    case 4:
        type = ObjectType::Vida2;
        consumible = true;
        break;
    case 5:
        type = ObjectType::Ritmo2;
        consumible = true;
        break;
    case 6:
        type = ObjectType::Ritmo;
        consumible = true;
        break;
    case 7:
        type = ObjectType::Dados;
        consumible = true;
        break;
    case 8:
        type = ObjectType::Daga;
        consumible = true;
        break;
    case 9:
        type = ObjectType::DagaInv;
        consumible = true;
        break;
    case 10:
        type = ObjectType::PactoSangre;
        consumible = false;
        break;
    case 11:
        type = ObjectType::BombaHumo;
        consumible = true;
        break;
    case 12:
        type = ObjectType::Tp;
        consumible = true;
        break;   
    default:
        break;
    }

    Motor2D *motor2D = Motor2D::getInstance();

    sprite->setOrigen(75 / 2, 75 / 2);
    sprite->setTile(0,num);
    sprite->escalarSprite(2.5f);
    sprite->setPosition(x, (motor2D->getSize().y / 2) - 307);

    std::cout << "Me acabo de crear y soy consumible?: " << this->consumible << std::endl;

    nivel = 1;

}

int Objeto::obtenerNivelObjeto()
{
    return nivel;
}

void Objeto::establecerNivel(int nivelNuevo){
    nivel = nivelNuevo;
}

void Objeto::asignarType(int tipo){
    switch (tipo)
    {
    case 0:
        type = ObjectType::Vacio;
        consumible = false;
        break;
    case 1:
        type = ObjectType::Armadura;
        consumible = true;
        break;
    case 2:
        type = ObjectType::Armadura2;
        consumible = true;
        break;    
    case 3:
        type = ObjectType::Vida;
        consumible = true;
        break;
    case 4:
        type = ObjectType::Vida2;
        consumible = true;
        break;
    case 5:
        type = ObjectType::Ritmo2;
        consumible = true;
        break;
    case 6:
        type = ObjectType::Ritmo;
        consumible = true;
        break;
    case 7:
        type = ObjectType::Dados;
        consumible = true;
        break;
    case 8:
        type = ObjectType::Daga;
        consumible = true;
        break;
    case 9:
        type = ObjectType::DagaInv;
        consumible = true;
        break;
    case 10:
        type = ObjectType::PactoSangre;
        consumible = true;
        break;
    case 11:
        type = ObjectType::BombaHumo;
        consumible = true;
        break;
    case 12:
        type = ObjectType::Tp;
        consumible = true;
        break;   
    
    default:
        break;
    }

    sprite->setTile(0,tipo);
}

void Objeto::moverX(float x){
    Motor2D *motor2D = Motor2D::getInstance();

    sprite->setPosition(x, (motor2D->getSize().y / 2) - 307);
}


std::string Objeto::DarNombreObjeto(){

    std::string acc = "";

    switch (type)
    {
    case ObjectType::Vacio:
        acc = "";
        break;
    case ObjectType::Armadura:
        acc = "Armadurita";
        break;
    case ObjectType::Armadura2:
        acc = "Armadura grande";
        break;    
    case ObjectType::Vida:
        acc = "Pocioncita";
        break;
    case ObjectType::Vida2:
        acc = "Pocion grande";
        break;
    case ObjectType::Ritmo2:
        acc = "Pua de oro";
        break;
    case ObjectType::Ritmo:
        acc = "Pua de plata";
        break;
    case ObjectType::Dados:
        acc = "Dados trucados";
        break;
    case ObjectType::Daga:
        acc = "Daga de doble filo";
        break;
    case ObjectType::DagaInv:
        acc = "La Tricolor";
        break;
    case ObjectType::PactoSangre:
        acc = "Pacto de Sangre";
        break;
    case ObjectType::BombaHumo:
        acc = "Bomba de Humo";
        break;
    case ObjectType::Tp:
        acc = "Cuerda Huida";
        break;   
   
    default:
        break;
    }

    return acc;

}

int Objeto::usarObjeto(){

    int acc = -1;

    switch (type)
    {
    case ObjectType::Vacio:
        acc = -1;
        break;
    case ObjectType::Armadura:
        acc = 0;
        break;
    case ObjectType::Armadura2:
        acc = 1;
        break;    
    case ObjectType::Vida:
        acc = 2;
        break;
    case ObjectType::Vida2:
        acc = 3;
        break;
    case ObjectType::Ritmo2:
        acc = 4;
        break;
    case ObjectType::Ritmo:
        acc = 5;
        break;
    case ObjectType::Dados:
        acc = 6;
        break;
    case ObjectType::Daga:
        acc = 7;
        break;
    case ObjectType::DagaInv:
        acc = 8;
        break;
    case ObjectType::PactoSangre:
        acc = 9;
        break;
    case ObjectType::BombaHumo:
        acc = 10;
        break;
    case ObjectType::Tp:
        acc = 11;
        break;   
    
    default:
        break;
    }

    return acc;
}

int Objeto::devolverObjeto(){
    return static_cast<int>(type);
}

MySprite** Objeto::getSprite(){
    return &sprite;
}

bool Objeto::esConsumible()
{
    return consumible;
}

