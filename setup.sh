echo "Iniciando script..."

# Mostrar el directorio actual para verificar que estamos en el lugar correcto
echo "Directorio actual: $(pwd)"

# Eliminar el directorio "data" si ya existe
if [ -d "data" ]; then
    echo "'data' existe, eliminando..."
    rm -rf data
    echo "'data' eliminado."
else
    echo "'data' no existe, no se necesita eliminar."
fi

# Crear el directorio "data"
mkdir data
echo "'data' creado."

# Navegar al directorio "data"
cd data 

# Descargar el archivo zip de Dropbox
echo "Descargando archivo..."
wget -O data.zip "https://www.dropbox.com/scl/fo/pxhvjy5d6q5qrbjh76m8m/h?rlkey=by325namz372mes1h96p4jp9f&dl=1" || { echo "Error al descargar el archivo. Verifique la conexión y la URL."; exit 1; }


# Verificar el estado de salida de unzip
unzip data.zip
status=$?

if [ $status -eq 0 ]; then
    echo "Archivo descomprimido exitosamente."
elif [ $status -eq 2 ]; then
    echo "Se encontraron advertencias durante la descompresión."
else
    echo "Error al descomprimir. Verifique la existencia del archivo y 'unzip' instalado."
    exit 1
fi

# Continuar con la limpieza del archivo zip
echo "Limpiando..."
rm data.zip
