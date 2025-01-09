#include "musica.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility> // Para std::pair
#include <cstdlib> // Para std::rand() y std::srand()
#include <ctime>   // Para std::time()
#include <cmath>

Musica::Musica(const std::string &filePath)
{
    cargarMusica(filePath);
}

void Musica::cargarMusica(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    if (!file.is_open())
    {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string nombre;
        float cantidad;

        std::getline(iss, nombre, '/');
        iss >> cantidad;

        canciones.push_back(std::make_pair(nombre, cantidad));
    }
}

void Musica::seleccionarCancionIndice(int index)
{
    if (index >= 0 && index < cancionesDeNivel.size())
    {
        cancionActual = cancionesDeNivel[index].first;
        actualBPM = cancionesDeNivel[index].second;
    }
    else
    {
        std::cout << "Indice de canción inválido." << std::endl;
    }
}

void Musica::seleccionarSiguienteCancion()
{
    int random = devolverCancionRandom();

    if (random >= 0 && random < cancionesDeNivel.size())
    {
        cancionSiguiente = cancionesDeNivel[random].first;
        siguinteBPM = cancionesDeNivel[random].second;
    }
    else
    {
        std::cout << "Indice de canción siguiente inválido." << std::endl;
    }
}

void Musica::sePuedeSiguienteCancion()
{


    if (musica.getStatus() == sf::Music::Stopped)
    {
        cancionActual = cancionSiguiente;
        actualBPM = siguinteBPM;

        seleccionarSiguienteCancion();

        reproducir();


    }
}

void Musica::cargarCancionesPorNivel(int nivel, int dificultad)
{

    if (!cancionesDeNivel.empty())
    {
        // Iterar sobre el vector de canciones
        for (int i = 0; i < cancionesDeNivel.size(); i++)
        {
            cancionesDeNivel.erase(cancionesDeNivel.begin());
        }
    }

    int rango1, rango2;

    switch (nivel)
    {
    case 1:
        if (dificultad == 1)
        {
            rango1 = 0;
            rango2 = 85;
        }
        else if (dificultad == 2)
        {
            rango1 = 85;
            rango2 = 100;
        }
        else
        {
            rango1 = 95;
            rango2 = 110;
        }

        break;

    case 2:
        if (dificultad == 1)
        {
            rango1 = 80;
            rango2 = 95;
        }
        else if (dificultad == 2)
        {
            rango1 = 90;
            rango2 = 105;
        }
        else
        {
            rango1 = 100;
            rango2 = 115;
        }
        break;

    case 3:

        if (dificultad == 1)
        {
            rango1 = 85;
            rango2 = 100;
        }
        else if (dificultad == 2)
        {
            rango1 = 95;
            rango2 = 110;
        }
        else
        {
            rango1 = 105;
            rango2 = 120;
        }
        break;

    case 4:
        if (dificultad == 1)
        {
            rango1 = 90;
            rango2 = 105;
        }
        else if (dificultad == 2)
        {
            rango1 = 100;
            rango2 = 115;
        }
        else
        {
            rango1 = 110;
            rango2 = 125;
        }
        break;

    default:
        break;
    }

    // Iterar sobre el vector de canciones
    for (const auto &cancion : canciones)
    {
        // Comprobar si el BPM de la canción está dentro del rango especificado
        if (cancion.second >= rango1 && cancion.second <= rango2)
        {
            cancionesDeNivel.push_back(cancion);
        }
    }
}

int Musica::devolverCancionRandom()
{

    std::srand(static_cast<unsigned>(std::time(0)));

    int random = 0;

    random = (std::rand() % cancionesDeNivel.size());

    return random;
}

void Musica::seleccionarCancionNombre(std::string nombre)
{
    bool encontrada = false;
    for (size_t i = 0; i < canciones.size(); ++i)
    {
        if (canciones[i].first == nombre)
        {
            cancionActual = canciones[i].first;
            actualBPM = canciones[i].second;
            encontrada = true;
            break;
        }
    }

    if (!encontrada)
    {
        std::cout << "Nombre de canción inválido." << std::endl;
    }
}

void Musica::pausarMusica()
{
    musica.pause();
}

void Musica::pararMusica(){
    musica.stop();
}

bool Musica::estaParada()
{
    return musica.getStatus() == sf::Music::Paused;
}

bool Musica::estaStop()
{
    return musica.getStatus() == sf::Music::Stopped;
}

void Musica::reproducirDesdePausa()
{
    if (musica.getStatus() == sf::Music::Paused)
    {
        musica.play();
    }
}

void Musica::reproducirDesdeParada()
{
    if (musica.getStatus() == sf::Music::Stopped)
    {
        musica.play();
    }
}


void Musica::reproducir()
{
    std::string pathCompleto = "../../../data/OCTAVIO/Canciones/" + cancionActual;
    if (musica.openFromFile(pathCompleto))
    {
        musica.play();
        // Set the pitch based on BPM if needed
        // musica.setPitch(velocity); // Assuming velocity affects pitch in your context
    }
    else
    {
        std::cout << "No se pudo cargar la canción." << std::endl;
    }
}


void Musica::reproducirSonido(std::string pathsonido){
    if (!buffer.loadFromFile(pathsonido)) { // Reemplaza "sound.wav" con la ruta de tu archivo de sonido
        std::cerr << "Failed to load sound file!" << std::endl;
    }

    sonido.setBuffer(buffer);
    sonido.setVolume(volumen+10);

    std::cout << "reproduciendo" << std::endl;

    sonido.play();
}

void Musica::reproducirSonido2(std::string pathsonido){
    if (!buffer2.loadFromFile(pathsonido)) { // Reemplaza "sound.wav" con la ruta de tu archivo de sonido
        std::cerr << "Failed to load sound file!" << std::endl;
    }

    sonido2.setBuffer(buffer2);
    sonido2.setVolume(volumen+10);

    sonido2.play();
}

void Musica::reproducirPorNombre(std::string nombre)
{
    std::string pathCompleto = "../../../data/OCTAVIO/Canciones/" + nombre;

    actualBPM = 105.75;
    if (musica.openFromFile(pathCompleto))
    {
        musica.play();
        // Set the pitch based on BPM if needed
        // musica.setPitch(velocity); // Assuming velocity affects pitch in your context
    }
    else
    {
        std::cout << "No se pudo cargar la canción." << std::endl;
    }
}

float Musica::obtenerBPM() const
{
    return actualBPM;
}

void Musica::crearBarraVolumen(float x, float y, float ancho, float alto)
{
    fondo = new sf::RectangleShape(sf::Vector2f(ancho, alto));
    fondo->setOrigin(ancho / 2, alto / 2);
    fondo->setPosition(x, y);
    fondo->setFillColor(sf::Color(150, 150, 150));

    barra = new sf::RectangleShape(sf::Vector2f(ancho * (volumen / 100.0f), alto));
    barra->setOrigin(ancho / 2, alto / 2);
    barra->setPosition(x, y);
    barra->setFillColor(sf::Color(2, 8, 138));

    updateVolumen(false);
}

void Musica::cambiarVolumen(int n)
{
    float volumenLogaritmico = pow(10, volumen / 20.0); // Convierte el volumen lineal a logarítmico

    // Ajustar el valor de incremento para un cambio más significativo en el volumen
    const float incrementoLogaritmico = 0.25;  // Ajusta este valor según necesites para afinar el incremento a 5

    if (n == 1)
    {
        volumenLogaritmico *= pow(10, -incrementoLogaritmico); // Disminuye el volumen
    }
    else if (n == 2)
    {
        volumenLogaritmico *= pow(10, incrementoLogaritmico); // Aumenta el volumen
    }
    volumen = 20 * log10(volumenLogaritmico); // Convierte el volumen de regreso a la escala lineal
    setVolumen(volumen);
}
void Musica::guardarVolumen()
{
    std::string pathCompleto = "../../../data/ANGEL/txt/";
    std::ofstream file(pathCompleto + "volumen.txt", std::ios::out | std::ios::trunc); // Abre el archivo para escritura y trunca cualquier contenido existente
    if (file.is_open())
    {
        file << volumen; // Escribe el volumen actual en el archivo
        file.close();    // Cierra el archivo
    }
    else
    {
        std::cerr << "No se pudo abrir el archivo para guardar el volumen.\n";
    }
}

void Musica::cargarVolumen(bool juego)
{
    std::string pathCompleto = "../../../data/ANGEL/txt/";
    std::ifstream file(pathCompleto + "volumen.txt", std::ios::in); // Abre el archivo para lectura
    if (file.is_open())
    {
        file >> volumen;     // Lee el volumen desde el archivo
        file.close();        // Cierra el archivo
        if (juego)
        {
            setVolumen(volumen); // Actualiza el volumen en el sistema
        }
    }
    else
    {
        std::cerr << "No se pudo abrir el archivo para leer el volumen.\n";
    }
}

void Musica::updateVolumen(bool juego)
{
    cargarVolumen(juego);
    musica.setVolume(volumen * maxVolumen);
}

void Musica::setVolumen(float nuevoVolumen)
{
    // Asegurar que el volumen esté dentro de los límites permitidos
    if (nuevoVolumen < 0.0f)
    {
        volumen = 0.0f;
    }
    else if (nuevoVolumen > 100.0f)
    {
        volumen = 100.0f;
    }
    else
    {
        volumen = nuevoVolumen;
    }

    // Actualizar el tamaño de la barra según el nuevo volumen

    float anchobarra = fondo->getSize().x; // Debe ser ancho del fondo, no de la barra
    barra->setSize(sf::Vector2f(anchobarra * (volumen / 100.0f), barra->getSize().y));

    // Asegúrate de llamar a actualizar el volumen de la música aquí si es necesario
    musica.setVolume(volumen * maxVolumen);
}

float Musica::getVolumen()
{
    return volumen;
}

void Musica::dibujarBarra(Motor2D *motor)
{
    motor->drawRectangle(*fondo);
    motor->drawRectangle(*barra);
}