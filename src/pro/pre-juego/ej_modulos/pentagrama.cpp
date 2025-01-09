#include "pentagrama.h"


void Pentagrama::agregarNotaInicial(const std::string& tex, Motor2D *motor)
{
    auto nuevaNota = std::make_unique<Nota>(tex, motor);
    notasIniciales.push_back(std::move(nuevaNota));
}

void Pentagrama::agregarNotaFinal(const std::string& tex, const sf::Vector2f& inicial, Motor2D *motor)
{
    auto nuevaNota = std::make_unique<Nota>(tex, inicial, motor);
    notasFinales.push_back(std::move(nuevaNota));
}

void Pentagrama::borrarTodas(){
  
  while (!notasIniciales.empty())
  {
    notasIniciales.erase(notasIniciales.begin());
  }

  while (!notasFinales.empty())
  {
    notasFinales.erase(notasFinales.begin());
  }
  
}

void Pentagrama::comprobacionGolpeo(Motor2D* motor, std::string &prueba2, std::string &prueba3, int &contador){

  if (!notasIniciales.empty())
          {
            auto &primeraNota = notasIniciales[0];
            sf::FloatRect hitboxNota = primeraNota->devolverSpriteSinPunt()->getHitbox();
            // sf::FloatRect hitboxAnillo = sprite.getGlobalBounds();
            float limiteIzquierdo = motor->getSize().x / 2 - 15;
            float limiteDerecho = motor->getSize().x / 2 + 15;

            if (hitboxNota.left >= limiteIzquierdo && hitboxNota.left + hitboxNota.width <= limiteDerecho)
            {
              //std::cout << "PERFECT MÁQUINA" << std::endl;

              agregarNotaFinal(prueba2, primeraNota->devolverSpriteSinPunt()->getPosicion(), motor);
              notasIniciales.erase(notasIniciales.begin());

              if (contador + 5 <= 200)
              {
                contador = contador + 5;
              }

            }
            else if ((hitboxNota.left <= limiteDerecho && hitboxNota.left + hitboxNota.width >= limiteDerecho) || (hitboxNota.left <= limiteIzquierdo && hitboxNota.left + hitboxNota.width >= limiteIzquierdo))
            {
              //std::cout << "DENTRO" << std::endl;
              agregarNotaFinal(prueba2, primeraNota->devolverSpriteSinPunt()->getPosicion(), motor);
              notasIniciales.erase(notasIniciales.begin());

              if (contador + 5 <= 200)
              {
                contador = contador + 5;
              }

            }
            else
            {
              //std::cout << "MAL" << std::endl;
              agregarNotaFinal(prueba3, primeraNota->devolverSpriteSinPunt()->getPosicion(), motor);
              notasIniciales.erase(notasIniciales.begin());
              if (contador - 5 >= 0)
              {
                contador = contador - 5;
              }

            }
          }
}

void Pentagrama::cambioPentagrama(){
    notasFinales.push_back(std::move(notasIniciales.front()));
    notasIniciales.erase(std::move(notasIniciales.begin()));
}


void Pentagrama::update(Motor2D *motor, float velocidad, std::string &prueba3, int& contador, float deltaT){

  float ini = 0;


  if (!notasIniciales.empty()) {
    ini = notasIniciales[0]->obtenerPuntoInicial(*motor).x;
  }

  float desplazamiento = velocidad*deltaT;

  for (size_t i = 0; i < notasIniciales.size(); i++)
    {
      auto &n = notasIniciales[i];

      if (ini > n->devolverFinal()->x)
      {
      }
      else
      {
        
        /*sf::Vector2f direccion(n->puntoFinal.x - n->puntoInicial.x, 0);
        float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
        if (magnitud > 0.0f)
        {
          direccion /= magnitud;
        }

        n->sprite.setPosition(n->sprite.getPosition().x + direccion.x * velocidad, window.getSize().y - 83);*/

        // Calcula la distancia restante hasta el punto final para asegurar que no nos pasemos
        //float distanciaRestante = n->puntoFinal.x - n->sprite.getPosition().x;
        
        // Si el desplazamiento es mayor que la distancia restante, ajusta el desplazamiento
        // para que la nota no se mueva más allá de su punto final
        //float movimiento = std::min(desplazamiento, distanciaRestante);

        float avanzar = desplazamiento+velocidad/2;

        // Mueve la nota horizontalmente usando el movimiento calculado
        n->devolverSpriteSinPunt()->mover(avanzar, 0);
      }
    }
    for (size_t i = 0; i < notasFinales.size(); i++)
    {
      auto &n = notasFinales[i];

      if (ini > n->devolverFinal()->x)
      {
      }
      else
      {
        
        /*sf::Vector2f direccion(n->puntoFinal.x - n->puntoInicial.x, 0);
        float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
        if (magnitud > 0.0f)
        {
          direccion /= magnitud;
        }

        n->sprite.setPosition(n->sprite.getPosition().x + direccion.x * velocidad, window.getSize().y - 83);*/

        float avanzar = desplazamiento+velocidad/2;

        // Mueve la nota horizontalmente usando el movimiento calculado
        n->devolverSpriteSinPunt()->mover(avanzar, 0);
      }
    }

    if (!notasFinales.empty() && notasFinales[0]->devolverSpriteSinPunt()->getPosicion().x > notasFinales[0]->devolverFinal()->x)
    {
      notasFinales.erase(notasFinales.begin());
    }

    float limiteDerecho = motor->getSize().x / 2 + 15;

    if (!notasIniciales.empty() && notasIniciales[0]->devolverSpriteSinPunt()->getHitbox().left > limiteDerecho)
    {
      agregarNotaFinal(prueba3, notasIniciales[0]->devolverSpriteSinPunt()->getPosicion(), motor);

      if (contador - 5 >= 0)
      {
        contador = contador - 5;
      }

      notasIniciales.erase(notasIniciales.begin());
    }
}

void Pentagrama::render(Motor2D *motor){

  float ini = 0;

  if (!notasIniciales.empty()) {
    ini = notasIniciales[0]->obtenerPuntoInicial(*motor).x;
    // Resto del código
  }

  for (size_t i = 0; i < notasIniciales.size(); i++)
    {
      auto &n = notasIniciales[i];

      if (ini > n->devolverFinal()->x)
      {
      }
      else
      {
        motor->draw(n->devolverSprite());
      }

    }

    for (size_t i = 0; i < notasFinales.size(); i++)
    {
      auto &n = notasFinales[i];

      if (ini > n->devolverInicial()->x)
      {
      }
      else
      {
        motor->draw(n->devolverSprite());
        // std::cout << "Posicion Acutalizada: " << n.sprite.getPosition().x << std::endl;
      }
    }

}


std::vector<std::unique_ptr<Nota>>& Pentagrama::devolverNotasIni(){
    return notasIniciales;
}

std::vector<std::unique_ptr<Nota>>& Pentagrama::devolverNotasFin(){
    return notasFinales;
}