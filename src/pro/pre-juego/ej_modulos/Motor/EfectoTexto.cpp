#include "EfectoTexto.h"

EfectoTexto::EfectoTexto(const std::string& contenido, sf::Font& fuente, sf::Vector2f posicionInicial, sf::Color color, float duracionMs, float escala) {
    
    posicionActual = posicionInicial;
    //texto.setScale(escala, escala);
    texto.setString(contenido);

    texto.setFont(fuente);
    texto.setCharacterSize(40);
    texto.setFillColor(color);
    texto.setPosition(posicionInicial);
    texto.setOutlineColor(sf::Color::Black);
    texto.setOutlineThickness(5);

    // Definir la velocidad en X e Y para que 'flote' hacia arriba y a los lados
    velocidad = sf::Vector2f((rand() % 2 * 2 - 1) * 5.0f, -10.0f);

    // Establecer la duración de la animación
    this->duracionMs = duracionMs;
    duracion.restart();
}

bool EfectoTexto::update() {
    float delta = duracion.getElapsedTime().asSeconds();

    // Verificar si la animación debe terminar
    if (duracion.getElapsedTime().asMilliseconds() > duracionMs) {
        return false; // Termina la animación
    }

    // Calcular la nueva posición
    // Aumentar la velocidad en Y para simular la caída
    posicionAnterior = posicionActual;
    sf::Vector2f movimiento(velocidad.x * delta, (velocidad.y + 10.0f * delta) * delta); // El factor 10.0f incrementa la "gravedad"
    posicionActual += movimiento;
    //texto.move(movimiento);

    

    // Actualizar la opacidad y la escala para el efecto de desvanecimiento y encogimiento
    sf::Color color = texto.getFillColor();
    float alpha = std::max(0.0f, static_cast<float>(color.a) - (255.0f * delta / duracionMs));
    float scale = std::max(0.2f, texto.getScale().x - (delta / duracionMs)); // Asegurarse de que la escala no sea 0
    //float scale = std::max(0.2f, texto.getScale().x - 0.5f); // Asegurarse de que la escala no sea 0

    texto.setFillColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha)));
    texto.setScale(scale, scale);

    return true;
}


void EfectoTexto::draw(float factorInterpolacion){
    sf::Vector2f posicionInterpolada = posicionAnterior * (1 - factorInterpolacion) + posicionActual * factorInterpolacion;

    texto.setPosition(posicionInterpolada);
    Motor2D::getInstance()->drawText(texto);
    
}