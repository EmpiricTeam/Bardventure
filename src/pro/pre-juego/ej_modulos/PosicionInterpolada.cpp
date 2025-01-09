#include "PosicionInterpolada.h"


    PosicionInterpolada::PosicionInterpolada(float iniX, float iniY){
        posXActual = iniX;
        posXAnterior = iniX;
        posYActual = iniY;
        posYAnterior = iniY;
        percentTic = 0.0f;
    }

    // Función para actualizar la posición (llamada en update)
    void PosicionInterpolada::actualizarPosicion(float nuevaX, float nuevaY) {
            posXAnterior = posXActual;
            posYAnterior = posYActual;
            posXActual = nuevaX;
            posYActual = nuevaY;
    }

    // Función para establecer el porcentaje de interpolación (llamada en render)
    void PosicionInterpolada::setPercentTic(float percent) {
        percentTic = percent;
    }

    // Función para obtener la posición interpolada (llamada en render)
    float PosicionInterpolada::getPosicionInterpoladaX() {
        //return posXAnterior + (posXActual - posXAnterior) * percentTic;
        return posXAnterior * (1 - percentTic) + (posXActual) * percentTic;
    }

    float PosicionInterpolada::getPosicionInterpoladaY() {
        //return posYAnterior + (posYActual - posYAnterior) * percentTic;
        return posYAnterior * (1 - percentTic) + (posYActual) * percentTic;
    }

    float PosicionInterpolada::getPosicionX(){
        return posXActual;
    }

    float PosicionInterpolada::getPosicionY(){
        return posYActual;
    }
