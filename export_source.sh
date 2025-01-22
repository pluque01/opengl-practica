#!/bin/bash

# Comprobar que se han pasado dos parámetros
if [[ $# -ne 1 ]]; then
  echo "Uso: $0 <nombre-del-zip>"
  exit 1
fi

# Ruta de destino para el archivo ZIP y nombre base
output_dir="export/$1"
base_name="$1"

# Comprobar si las carpetas src y archivos-alumno existen
if [[ ! -d "src" || ! -d "archivos-alumno" ]]; then
  echo "Error: Las carpetas 'src' y 'archivos-alumno' deben existir en el directorio actual."
  exit 1
fi

# Asegurarse de que la ruta de destino existe
mkdir -p "$output_dir"

# Generar un nombre único para el archivo ZIP
counter=1
output_zip="$output_dir/$base_name.zip"
while [[ -e "$output_zip" ]]; do
  output_zip="$output_dir/$base_name-$counter.zip"
  ((counter++))
done

# Crear el archivo ZIP con los archivos específicos
zip -r "$output_zip" src archivos-alumno -i "*.cpp" "*.h" "*.ply" "*.jpg" "*.jpeg"

# Comprobar el estado de la operación
if [[ $? -eq 0 ]]; then
  echo "El archivo ZIP ha sido creado con éxito en: $output_zip"
else
  echo "Error al crear el archivo ZIP."
fi
