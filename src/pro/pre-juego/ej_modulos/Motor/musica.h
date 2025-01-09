#pragma once
#ifndef MUSICA_H
#define MUSICA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility> // Para std::pair
// Assuming sf::Music is part of the SFML library
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Motor2D.h"  

class Musica {

private:
    std::vector<std::string> nombres;
    std::vector<float> bpms;
    std::vector<std::pair<std::string,float>> canciones;
    std::vector<std::pair<std::string,float>> cancionesDeNivel;
    //sustituir los dos vectores por un unico vector clave valor
    
    std::string cancionActual;
    float actualBPM;

    std::string cancionSiguiente;
    float siguinteBPM;

    sf::Music musica;

    sf::Sound sonido;
    sf::SoundBuffer buffer;

    sf::Sound sonido2;
    sf::SoundBuffer buffer2;

    float maxVolumen = 0.5f;
    float volumen;

    sf::RectangleShape *fondo;
    sf::RectangleShape *barra;

public:

    Musica(const std::string& filePath);
    void cargarMusica(const std::string& filePath);
    void cargarCancionesPorNivel(int nivel, int dificultad);
    void seleccionarCancionIndice(int index);
    void seleccionarSiguienteCancion();
    void seleccionarCancionNombre(std::string nombre);
    int devolverCancionRandom();
    void reproducir();
    void pausarMusica();
    void pararMusica();
    bool estaParada();
    bool estaStop();
    void reproducirDesdePausa();
    void reproducirDesdeParada();
    void reproducirPorNombre(std::string nombre);
    float obtenerBPM() const;

    void reproducirSonido(std::string pathsonido);
    void reproducirSonido2(std::string pathsonido);

    void sePuedeSiguienteCancion();

    void crearBarraVolumen(float x, float y, float ancho, float alto);
    void cambiarVolumen(int n);
    void guardarVolumen();
    void cargarVolumen(bool juego);
    void updateVolumen(bool juego);
    void setVolumen(float nuevoVolumen);
    float getVolumen();
    void dibujarBarra(Motor2D* motor);
    
};

#endif