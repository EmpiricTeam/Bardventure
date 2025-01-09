
#include "Motor2D.h"
// Constructor que recibe la ventana

Motor2D::Motor2D()
{
  // Inicialización opcional
  ventana = new sf::RenderWindow();

  bool fullscreen = true;

  if (fullscreen)
  {
    ventana->create(sf::VideoMode::getDesktopMode(), "Bardventure: Songs of Freedom", sf::Style::Fullscreen);
    ventana->setFramerateLimit(120);
  }
  else
  {
    ventana->create(sf::VideoMode(1920, 1080), "Bardventure: Songs of Freedom");
    ventana->setFramerateLimit(120);
  }
}

// Función getInstance

Motor2D *Motor2D::getInstance()
{
  if (instance == nullptr)
  {
    instance = new Motor2D();
  }
  return instance;
}

Motor2D *Motor2D::instance = nullptr;

void Motor2D::mostrardebuj(std::string texto)
{
  sf::Time timeStartUpdate = comprobacion.getElapsedTime();

  sf::Time resta = timeStartUpdate - restar;

  std::cout << resta.asMilliseconds() << " " << texto << std::endl;

  restar = comprobacion.getElapsedTime();
}

char Motor2D::getInput() {
    sf::Event event;
    char accion = '\0';
    static std::set<sf::Keyboard::Key> teclasPresionadas;

    while (this->ventana->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            accion = 'Q';  // Acción para cerrar la ventana
        } else if (event.type == sf::Event::KeyReleased) {
            teclasPresionadas.erase(event.key.code);  // Marca la tecla como liberada
        } else if (event.type == sf::Event::KeyPressed) {
            // Verifica si la tecla ya fue presionada y aún no se ha liberado
            if (teclasPresionadas.find(event.key.code) == teclasPresionadas.end()) {
                // Marca la tecla como presionada
                teclasPresionadas.insert(event.key.code);
                // Procesa la tecla presionada
                switch (event.key.code) {
                    case sf::Keyboard::Escape: accion = 'Q'; break;
                    case sf::Keyboard::Down: accion = 'd'; break;
                    case sf::Keyboard::Up: accion = 'U'; break;
                    case sf::Keyboard::Space: accion = 's'; break;
                    case sf::Keyboard::P: accion = 'P'; break;
                    case sf::Keyboard::X: accion = 'X'; break;
                    case sf::Keyboard::A: accion = 'A'; break;
                    case sf::Keyboard::S: accion = 'S'; break;
                    case sf::Keyboard::D: accion = 'D'; break;
                    case sf::Keyboard::L: accion = 'L'; break;
                    case sf::Keyboard::C: accion = 'C'; break;
                    case sf::Keyboard::W: accion = 'W'; break;
                    case sf::Keyboard::N: accion = 'N'; break;
                    case sf::Keyboard::K: accion = 'K'; break;
                    case sf::Keyboard::J: accion = 'J'; break;
                    case sf::Keyboard::O: accion = 'O'; break;

                    default: break;
                }
            }
        }
    }
    return accion;
}

void Motor2D::setWindow(sf::RenderWindow &window)
{
  ventana = &window;
}

void Motor2D::draw(MySprite **mySprite)
{
  ventana->draw((*mySprite)->getSprite());
}

void Motor2D::drawText(sf::Text mySprite)
{
  ventana->draw(mySprite);
}

void Motor2D::drawTextura(const sf::Drawable &obj, const sf::RenderStates &states)
{
  ventana->draw(obj, states);
}

void Motor2D::drawRectangle(sf::RectangleShape mySprite)
{
  ventana->draw(mySprite);
}

void Motor2D::drawLinea(sf::VertexArray mySprite)
{
  ventana->draw(mySprite);
}

void Motor2D::setFrameLimits(int frames)
{
  ventana->setFramerateLimit(frames);
}

bool Motor2D::isOpen()
{
  return ventana->isOpen();
}

bool Motor2D::pollEvent(sf::Event *event)
{
  return ventana->pollEvent(*event);
}

void Motor2D::close()
{
  return ventana->close();
}

void Motor2D::display()
{
  return ventana->display();
}

sf::Vector2u Motor2D::getSize()
{
  return ventana->getSize();
}

sf::Vector2f Motor2D::getMousePosition()
{
  sf::Vector2i mousePosInt = sf::Mouse::getPosition(*ventana);
  return sf::Vector2f(static_cast<float>(mousePosInt.x), static_cast<float>(mousePosInt.y));
}

void Motor2D::clear()
{
  return ventana->clear();
}

sf::RenderWindow &Motor2D::getVentana()
{
  if (ventana != nullptr)
  {
    return *ventana;
  }
  else
  {
    throw std::runtime_error("Error: ventana no inicializada.");
  }
}
