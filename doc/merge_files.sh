#!/bin/bash

# Nombre del archivo Markdown de salida
output_file="merged_code.md"

# Vaciar el contenido del archivo Markdown de salida si ya existe
echo "" >"$output_file"

# Recorrer todos los archivos de la carpeta actual
for file in ../src/*; do
  # Comprobar si es un archivo regular
  if [[ -f "$file" ]]; then
    # Obtener la extensión del archivo
    extension="cpp"

    # Añadir el título con el nombre del archivo al Markdown
    echo "## $file" >>"$output_file"

    # Añadir el bloque de código con la extensión adecuada
    echo '```'$extension >>"$output_file"
    # Convertir el archivo a UTF-8 y añadir su contenido
    iconv -f $(file -bi "$file" | sed -n 's/.*charset=//p') -t UTF-8 "$file" >> "$output_file"
    echo '```' >>"$output_file"
    echo "" >>"$output_file" # Línea vacía para separación
  fi
done

# Mensaje de finalización
echo "El archivo $output_file ha sido generado con éxito."
