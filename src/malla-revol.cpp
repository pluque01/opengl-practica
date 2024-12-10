// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// **
// ** Mallas indexadas creadas por revolución de un perfil (implementación).
// Clase 'MallaRevol' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases
// **    + MallaRevol: malla indexada de triángulos obtenida por
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "malla-revol.h"
#include "ig-aux.h"
#include "lector-ply.h"
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/constants.hpp>

using namespace std;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar(
    const std::vector<glm::vec3>
        &perfil,              // tabla de vértices del perfil original
    const unsigned num_copias // número de copias del perfil
) {
  using namespace glm;

  // PRACTICA 4: Crear normales de los vertices

  // En primer lugar calcular las normales de las aristas
  vector<vec3> nor_aristas;
  for (int i = 0; i < perfil.size() - 1; i++) {
    vec3 mi = perfil[i + 1] - perfil[i];

    // rotar 90º en sentido horario al rededor del eje z
    vec3 mi_rot = {mi.y, -mi.x, mi.z};

    if (length(mi_rot) > 0.0)
      mi_rot = normalize(mi_rot);
    else
      mi_rot = {0.0, 0.0, 0.0};

    // Si el objeto es cerrado, las normales apuntan a fuera
    if (mi_rot.x < 0.0)
      mi_rot = -mi_rot;

    nor_aristas.push_back(mi_rot);
  }

  vector<vec3> nor_ver_perfil;
  nor_ver_perfil.push_back(nor_aristas[0]);
  for (unsigned i = 1; i < perfil.size() - 1; i++) {
    vec3 ni = normalize(nor_aristas[i - 1] + nor_aristas[i]);
    nor_ver_perfil.push_back(ni);
  }
  nor_ver_perfil.push_back(nor_aristas[perfil.size() - 2]);

  // calculamos las coordenadas de textura de cada vértice del perfil
  vector<float> d;
  for (unsigned i = 0; i < perfil.size() - 1; i++) {
    vec3 v1 = perfil[i];
    vec3 v2 = perfil[i + 1];
    d.push_back(length(v2 - v1));
  }

  vector<float> t;
  t.push_back(0.0);
  float suma = 0.0;
  for (unsigned i = 0; i < perfil.size() - 1; i++) {
    suma += d[i];
    t.push_back(suma);
  }

  for (unsigned i = 0; i < t.size(); i++) {
    t[i] /= suma;
  }

  // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de
  // revolución
  //
  // Escribir el algoritmo de creación de una malla indexada por revolución de
  // un perfil, según se describe en el guion de prácticas.

  int num_vertices = perfil.size();
  // Para la tabla de vértices
  for (int i = 0; i < num_copias; i++) {
    float angle =
        (glm::two_pi<float>() * i) / static_cast<float>((num_copias - 1));
    for (int j = 0; j < num_vertices; j++) {
      float vert_x = perfil[j][0] * cos(angle);
      float vert_z = -perfil[j][0] * sin(angle);
      vertices.push_back({vert_x, perfil[j][1], vert_z});
      nor_ver.push_back({nor_ver_perfil[j].x * cos(angle), nor_ver_perfil[j].y,
                         nor_ver_perfil[j].x * (-sin(angle))});

      cc_tt_ver.push_back({float(i) / (num_copias - 1), 1 - t[j]});
    }
  }

  // Para la tabla de triángulos
  for (int i = 0; i < num_copias - 1; i++) {
    for (int j = 0; j < num_vertices - 1; j++) {
      int k = i * num_vertices + j;
      triangulos.push_back({k, k + num_vertices, k + num_vertices + 1});
      triangulos.push_back({k, k + num_vertices + 1, k + 1});
    }
  }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY(const std::string &nombre_arch,
                             const unsigned nperfiles) {
  ponerNombre(
      std::string("malla por revolución del perfil en '" + nombre_arch + "'"));
  // COMPLETAR: práctica 2: crear la malla de revolución
  // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
  // ...........................
  vector<glm::vec3> perfil;
  LeerVerticesPLY(nombre_arch, perfil);
  inicializar(perfil, nperfiles);
}

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles) {
  const float altura = 1.0;
  vector<glm::vec3> perfil;
  for (int i = 0; i < num_verts_per; i++) {
    float vec_y = (altura / (num_verts_per - 1)) * i;
    perfil.push_back({1.0, vec_y, 0.0});
  }
  inicializar(perfil, nperfiles);
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles) {
  const float radio = 1.0;
  vector<glm::vec3> perfil;
  for (int i = num_verts_per - 1; i >= 0; i--) {
    float vec_x = radio / (num_verts_per - 1) * i;
    float vec_y = -vec_x + radio;
    perfil.push_back({vec_x, vec_y, 0.0});
  }
  inicializar(perfil, nperfiles);
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles) {
  const float radio = 1.0;
  const float increment = glm::pi<float>() / (num_verts_per - 1);
  vector<glm::vec3> perfil;
  // Cuarto de circunferencia inferior
  for (int i = 0; i < num_verts_per; i++) {
    float vec_x = radio * cos(-glm::half_pi<float>() + (increment * i));
    float vec_y = radio * sin(-glm::half_pi<float>() + (increment * i));
    perfil.push_back({vec_x, vec_y, 0.0});
  }
  inicializar(perfil, nperfiles);
}
