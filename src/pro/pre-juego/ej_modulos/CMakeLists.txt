#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    
    
    "${CMAKE_CURRENT_SOURCE_DIR}/nota.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pentagrama.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PersonajePrincipal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PosicionInterpolada.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Habitacion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/npc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/factoryNpc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Flecha.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Level.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Objeto.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/States/JState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/States/JSMenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/States/JSJuego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/States/JSMenuJuego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/States/JSBatalla.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/States/JSTransicion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/States/JSTienda.cpp"


    "${CMAKE_CURRENT_SOURCE_DIR}/Motor/Motor2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Motor/MySprite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Motor/musica.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Motor/Tilemap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Motor/EfectoTexto.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Proyectil.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Boss.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BossFactory.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

