#pragma once
#ifndef MOTOR2D_H
#define MOTOR2D_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
// Assuming sf::Music is part of the SFML library
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MySprite.h"

class Motor2D {
    public:
    // Constructor que recibe la ventana
        //static Motor2D& getInstance(int width, int height, bool fullscreen, const std::string& title);
        static Motor2D* getInstance();

        void setWindow(sf::RenderWindow& window);
        void draw(MySprite** mySprite);
        void drawText(sf::Text mySprite);
        void drawRectangle(sf::RectangleShape mySprite);
        void drawLinea(sf::VertexArray mySprite);
        void drawTextura(const sf::Drawable& obj, const sf::RenderStates& states);
        void setFrameLimits(int frames);
        bool isOpen();
        bool pollEvent(sf::Event *event);
        void close();
        void clear();
        void display();
        void mostrardebuj(std::string texto);
        char getInput();


        sf::Vector2f getMousePosition();
        sf::Vector2u getSize();
        sf::RenderWindow& getVentana();

        Motor2D(Motor2D const&) = delete;
        void operator=(Motor2D const&) = delete;

    private:
        sf::RenderWindow* ventana = nullptr;

        sf::Clock comprobacion;
        sf::Time restar = comprobacion.getElapsedTime();
        
        static Motor2D* instance;
        Motor2D();
};

#endif