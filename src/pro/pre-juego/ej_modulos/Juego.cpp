#include "Juego.h"

// Funciones Estaticas

// Inicializador de funciones
void Juego::initWindow()
{
    
}

void Juego::initStates()
{
    this->states.push(JSMenu::getInstance());
}

// Constructor y destructor
Juego::Juego()
{
    this->initWindow();
    this->initStates();
    this->accion = '\0';
}

Juego::~Juego()
{
    delete &Motor2D::getInstance()->getVentana();
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

Juego *Juego::instance = nullptr;

Juego* Juego::getInstance(){
    if (instance == nullptr) {
            instance = new Juego();
    }
    return instance;
}

// Funciones

// Regular
void Juego::endApplication()
{
    std::cout << "Fin de la aplicacion"
              << "\n";
}

// Update
void Juego::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}
/*void Juego::updateSFMLEvents()
{
    while (this->motor2D->pollEvent(&this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
        {
            this->motor2D->close();
        }
    }
}*/

void Juego::update()
{
    //this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt, this->accion);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Fin de la aplicacion
    else
    {
        this->endApplication();
        Motor2D::getInstance()->close();
    }
}

// Render
void Juego::render()
{
    Motor2D::getInstance()->clear();

    // Renderizar
    
    if (!this->states.empty())
    {
        this->states.top()->render(&Motor2D::getInstance()->getVentana());
    }

    Motor2D::getInstance()->display();
}

std::stack<JState*> Juego::devolverStates(){
    return states;
}

void Juego::resetToMainMenu() {
   auto& stack = states;

    // Elimina todos los estados excepto el estado principal (asumiendo que JSMenu es siempre el fondo del stack)
    while (stack.size() > 1) {
        stack.pop();
        actualizar(stack);
    }
}

void Juego::actualizar(std::stack<JState*> state){
    states = state;
}

// Core
void Juego::run()
{

    int renderCount = 0;

    while (Motor2D::getInstance()->isOpen())
    {
        /*if (relojBucle.getElapsedTime().asMilliseconds() - tiempoBucle.asMilliseconds() > kUpdateTimePS)
        {
            this->updateDt();
            this->update();
            tiempoBucle = relojBucle.getElapsedTime();
        }

        this->render(); */

        if (relojBucle.getElapsedTime().asMilliseconds() - tiempoBucle.asMilliseconds() > 66.6)
        {
            this->updateDt(); // Actualiza el delta time

            this->accion = Motor2D::getInstance()->getInput();

            // Si ya se hicieron 4 renders, hacer un update
                this->update();
                renderCount = 0;                           // Resetea el contador después de un update
                tiempoBucle = relojBucle.getElapsedTime(); // Resetea el tiempo del último update
            
        }

        this->render(); // Llama a render cada iteración
        renderCount++;  // Incrementa el contador de render
    }
}