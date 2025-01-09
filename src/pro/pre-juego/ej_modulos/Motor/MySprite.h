#ifndef MYSPRITE_H
#define MYSPRITE_H

#include <SFML/Graphics.hpp>
#include <string>

class MySprite : public sf::Transformable
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    
    sf::Texture textureNormal;
    sf::Texture textureHover;
    sf::Texture textureClick;
    std::string path;

    sf::FloatRect hitboxPersonalizada;

    std::size_t currentFrame = 0;
    float timeSinceLastFrame = 0.0f;
    int frameCount;          // Número total de frames
    int frameSizeX;           // Tamaño de cada frame 
    int frameSizeY;
    float frameDuration;
    int framesPerRow;
    sf::Clock reloj;
    sf::Vector2f escala;

public:
    bool isAnimated;

    // Contructor por defecto vacío
    MySprite();
    // Constructor para cargar una textura
    MySprite(const std::string &texturePath);
    // Constructor para cargar las texturas de los botones (normal, hover y click)
    MySprite(const std::string &normalPath, const std::string &hoverPath, const std::string &clickPath);
    // Construcotr para animaciones
    MySprite(const std::string &texturePath, int numeroFrames, int tamFrameX, int tamFrameY, float durFrame, int framesPorFila);

    // Cambia el estado del botón
    void cambiaEstado(const std::string &state);

    // Establece el tile basado en coordenadas de tile en la textura
    void setTile(int tileX, int tileY);
    void setTileDinamico(int tileX, int tileY, int tamX, int tamY);

    void setRectTextura(int one, int two, int three, int four);

    // Establece la posición del sprite
    void setPosition(float x, float y);

    // Establece el origen del sprite en el centro
    void centrarOrigen();

    // Cambia el tamaño del sprite
    void escalarSprite(float factor);
    void escalarSpritePorValor(float factorX, float factorY);

    // Método para rotar el sprite
    void rotarSprite(float angulo);

    void setOrigen(float x, float y);

    void mover(float x, float y);

    sf::Vector2f getPosicion();

    sf::FloatRect getHitbox();

    void cambiarColor(sf::Color color);

    // Devuelve el sprite para hacer getGlobalBounds
    sf::Sprite &getSprite();
    
    sf::Vector2u tamText();

    std::string getPath();

    void cambiarSprite(const std::string &ruta);

    void cambiarSpriteBoton(const std::string &normalPath, const std::string &hoverPath, const std::string &clickPath);

    void updateAnimacion();

    void setHitboxPersonalizada(const sf::FloatRect& newHitbox);
    sf::FloatRect getHitboxPersonalizada() const;
    void centrar();

    void setFrameOne();

    sf::Vector2f obtenerEscala();
    
};

#endif // MYSPRITE_H
