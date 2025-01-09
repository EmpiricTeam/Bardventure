#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <iostream>
#include "MySprite.h"

MySprite::MySprite()
{
    
}
// Constructor que carga la textura y crea el sprite
MySprite::MySprite(const std::string &texturePath)
{
    if (!texture.loadFromFile(texturePath))
    {
        throw std::runtime_error("Error al cargar la textura desde " + texturePath);
    }
    sprite.setTexture(texture);
    path = texturePath;
}

// Constructor que carga las texturas de los botones y crea el sprite
MySprite::MySprite(const std::string &normalPath, const std::string &hoverPath, const std::string &clickPath)
{
    isAnimated = false;
    if (!textureNormal.loadFromFile(normalPath) || !textureHover.loadFromFile(hoverPath) || !textureClick.loadFromFile(clickPath))
    {
        throw std::runtime_error("Error al cargar las texturas de los botones desde " + normalPath + ", " + hoverPath + "y " + clickPath + ".");
    }
    sprite.setTexture(textureNormal);
}

MySprite::MySprite(const std::string &texturePath, int numeroFrames, int tamFrameX, int tamFrameY, float durFrame, int framesPorFila) {
    isAnimated = true;
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Error al cargar la textura desde " + texturePath);
    }
    sprite.setTexture(texture);
    frameCount = numeroFrames;
    frameSizeX = tamFrameX;
    frameSizeY = tamFrameY;
    frameDuration = durFrame;
    framesPerRow = framesPorFila;

    // Establece el rectángulo inicial del sprite al primer frame
    sprite.setTextureRect(sf::IntRect(0, 0, frameSizeX, frameSizeY));
    reloj.restart();
}

void MySprite::updateAnimacion() {
    float deltaTime = reloj.restart().asSeconds();
    timeSinceLastFrame += deltaTime;
    timeSinceLastFrame = std::min(timeSinceLastFrame, frameDuration);

    if (timeSinceLastFrame >= frameDuration) {
        currentFrame = (currentFrame + 1) % frameCount;

        int column = currentFrame % framesPerRow;
        int row = currentFrame / framesPerRow;

        sf::IntRect frameRect(column * frameSizeX, row * frameSizeY, frameSizeX, frameSizeY);
        sprite.setTextureRect(frameRect);
        sprite.setOrigin(frameRect.width / 2.0f, frameRect.height / 2.0f);

        timeSinceLastFrame -= frameDuration;
    }
}

void MySprite::setFrameOne() 
{
    currentFrame = 0;
}


// Método para cambiar el estado del botón
void MySprite::cambiaEstado(const std::string &state)
{
    if (state == "normal")
    {
        sprite.setTexture(textureNormal);
    }
    else if (state == "hover")
    {
        sprite.setTexture(textureHover);
    }
    else if (state == "click")
    {
        sprite.setTexture(textureClick);
    }
}

// Método para seleccionar un tile específico del mapa de texturas
void MySprite::setTile(int tileX, int tileY)
{
    // Tamaño de cada tile en la textura
    int tileSize = 32;
    sprite.setTextureRect(sf::IntRect(tileX * tileSize, tileY * tileSize, tileSize, tileSize));
}

// Método para seleccionar un tile específico del mapa de texturas
void MySprite::setRectTextura(int one, int two, int three, int four)
{
    sprite.setTextureRect(sf::IntRect(one, two, three, four));
}

// Método para establecer la posición del sprite
void MySprite::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
    hitboxPersonalizada.left = x - (hitboxPersonalizada.width / 2);
    hitboxPersonalizada.top = y - (hitboxPersonalizada.height / 2);
}


// Método para establecer el origen del sprite en el centro
void MySprite::centrarOrigen()
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

// Método para cambiar el tamaño del sprite
void MySprite::escalarSprite(float factor)
{
    sprite.setScale(factor, factor);
}

void MySprite::escalarSpritePorValor(float factorX, float factorY)
{
    sprite.setScale(factorX,factorY);
}

//Método para rotar el sprite
void MySprite::rotarSprite(float angulo)
{
    sprite.setRotation(angulo);
}

void MySprite::setOrigen(float x, float y){
    sprite.setOrigin(x,y);
}

void MySprite::mover(float x, float y){
    sprite.move(x,y);
}

sf::Vector2f MySprite::getPosicion(){
   return sprite.getPosition();
}

sf::FloatRect MySprite::getHitbox(){
    return sprite.getGlobalBounds();
}

void MySprite::cambiarColor(sf::Color color) {
    sprite.setColor(color);
}

// Método para obtener el sprite para hacer getGlobalBounds
sf::Sprite &MySprite::getSprite()
{
    return sprite;
}

sf::Vector2u MySprite::tamText(){
    return texture.getSize();
}

std::string MySprite::getPath(){
    return path;
}

void MySprite::cambiarSprite(const std::string &ruta){

    if (!texture.loadFromFile(ruta))
    {
        throw std::runtime_error("Error al cargar la textura desde " + ruta);
    }
    sprite.setTexture(texture);
    path = ruta;

}

void MySprite::cambiarSpriteBoton(const std::string &normalPath, const std::string &hoverPath, const std::string &clickPath){

    isAnimated = false;
    if (!textureNormal.loadFromFile(normalPath) || !textureHover.loadFromFile(hoverPath) || !textureClick.loadFromFile(clickPath))
    {
        throw std::runtime_error("Error al cargar las texturas de los botones desde " + normalPath + ", " + hoverPath + "y " + clickPath + ".");
    }
    sprite.setTexture(textureNormal);
}

void MySprite::setTileDinamico(int tileX, int tileY, int tamX, int tamY)
{
    
    sprite.setTextureRect(sf::IntRect(tileX * tamX, tileY * tamY, tamX, tamY));
}

void MySprite::setHitboxPersonalizada(const sf::FloatRect& newHitbox) {
    hitboxPersonalizada = newHitbox;
}

sf::FloatRect MySprite::getHitboxPersonalizada() const {
    return hitboxPersonalizada;
}

void MySprite::centrar(){
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
}

sf::Vector2f MySprite::obtenerEscala(){
    return sprite.getScale();
}