// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
#include "examen-ec-p123.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include <vector>

using namespace glm;

EX123_Ejercicio1::EX123_Ejercicio1() {
  vertices = {
      // fila con z = 0.0
      {0.0, 0.0, 0.0},
      {0.5, 0.0, 0.0},
      {0.8, 0.2, 0.0},
      {1.1, 0.2, 0.0},
      {1.4, 0.2, 0.0},
      {1.7, 0.2, 0.0},

      // fila con z = 0.5
      {0.0, 0.0, 0.5},
      {0.5, 0.0, 0.5},
      {0.8, 0.0, 0.5},
      {1.1, 0.0, 0.5},
      {1.4, 0.0, 0.5},
      {1.7, 0.0, 0.5},
  };

  triangulos = {
      {0, 1, 7}, {0, 6, 7},  {1, 2, 8},  {1, 7, 8},  {2, 3, 9},
      {2, 8, 9}, {3, 4, 10}, {3, 9, 10}, {4, 5, 11}, {4, 10, 11},
  };

  col_ver = {
      {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0},
      {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5},
      {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0},
  };
}

EX123_Ejercicio2::EX123_Ejercicio2(unsigned int n) {
  assert(n > 0);
  std::vector<glm::vec3> v_aux = {
      // fila con z = 0.0
      {0.0, 0.0, 0.0},
      {0.5, 0.0, 0.0},
      {0.8, 0.2, 0.0},
      {1.1, 0.2, 0.0},
      {1.4, 0.2, 0.0},
      {1.7, 0.2, 0.0},

      // fila con z = 0.5
      {0.0, 0.0, 0.5},
      {0.5, 0.0, 0.5},
      {0.8, 0.0, 0.5},
      {1.1, 0.0, 0.5},
      {1.4, 0.0, 0.5},
      {1.7, 0.0, 0.5},
  };

  for (auto &v : v_aux) {
    vertices.push_back(v);
  }

  for (int i = 1; i < n; i++) {
    for (auto &v : v_aux) {
      vertices.push_back(
          rotate(float(2.0f * M_PI / n * i), vec3(0.0f, 0.0f, 1.0f)) *
          vec4(v, 1.0f));
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 5; j++) {
      triangulos.push_back({j + 12 * i, j + 1 + 12 * i, j + 7 + 12 * i});
      triangulos.push_back({j + 7 + 12 * i, j + 6 + 12 * i, j + 12 * i});
    }
  }
}

EX123_Ejercicio3::EX123_Ejercicio3(const float w, const float h) {
  const float lado_cubo = 0.3;
  this->h = h;
  NodoGrafoEscena *tablero = new NodoGrafoEscena();
  unsigned ind_matriz_tablero = tablero->agregar(scale(vec3(1.0, 1.0, 1.0)));
  tablero->agregar(scale(vec3(w / 2, h / 2, w / 2)));
  tablero->agregar(translate(vec3(0.0, 1.0, 0.0)));
  tablero->agregar(new Cubo());

  NodoGrafoEscena *cubo = new NodoGrafoEscena();
  unsigned ind_matriz_cubo = cubo->agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));
  cubo->agregar(translate(vec3(w / 2 - lado_cubo / 2, h + lado_cubo / 2, 0.0)));
  cubo->agregar(scale(vec3(lado_cubo / 2, lado_cubo / 2, lado_cubo / 2)));
  cubo->agregar(new Cubo());

  agregar(tablero);
  agregar(cubo);

  matriz_cubo = cubo->leerPtrMatriz(ind_matriz_cubo);
  matriz_tablero = tablero->leerPtrMatriz(ind_matriz_tablero);
}

unsigned EX123_Ejercicio3::leerNumParametros() const { return 2; }

void EX123_Ejercicio3::actualizarEstadoParametro(const unsigned iParam,
                                                 const float tSec) {
  switch (iParam) {
  case 0: {
    float desplazamiento = 2.0 * abs(sin(M_PI * 0.5 * tSec));
    *matriz_tablero = scale(vec3(1.0, 1.0 + desplazamiento, 1.0));
    *matriz_cubo = translate(vec3(0.0, desplazamiento * h, 0.0));
    break;
  }
  case 1: {
    *matriz_cubo *=
        rotate(float(M_PI) * float(M_PI * 0.3 * tSec), vec3(0.0, 1.0, 0.0));
  }
  }
}
