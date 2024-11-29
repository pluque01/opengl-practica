#include "practicap3.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;
Ejercicio1::Ejercicio1() {
  NodoGrafoEscena *cilindro = new NodoGrafoEscena();
  unsigned ind_escalado_cilindro =
      cilindro->agregar(scale(vec3(1.0, 1.0, 1.0)));
  cilindro->agregar(scale(vec3(0.2, 1, 0.2)));
  cilindro->agregar(new Cilindro(2, 30));

  NodoGrafoEscena *prisma = new NodoGrafoEscena();
  prisma->agregar(scale(vec3(0.8, 0.3, 0.4)));
  prisma->agregar(new Cubo());

  NodoGrafoEscena *elipsoide = new NodoGrafoEscena();
  elipsoide->agregar(scale(vec3(0.1, 1.0, 0.3)));
  elipsoide->agregar(new Esfera(20, 30));

  agregar(cilindro);
  unsigned ind_traslacion = agregar(translate(vec3(0.0, 0.0, 0.0)));
  agregar(translate(vec3(0.0, 1.3, 0.0)));
  agregar(prisma);
  agregar(translate(vec3(0.9, 0.0, 0.0)));
  unsigned ind_rotacion = agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
  agregar(elipsoide);

  matriz_traslacion = leerPtrMatriz(ind_traslacion);
  matriz_esfera = leerPtrMatriz(ind_rotacion);
  matriz_escalado_cilindro = cilindro->leerPtrMatriz(ind_escalado_cilindro);
}

unsigned Ejercicio1::leerNumParametros() const { return 2; }

void Ejercicio1::actualizarEstadoParametro(const unsigned iParam,
                                           const float tSec) {
  switch (iParam) {
  case 0: {
    float desplazamiento = abs(float(sin(M_PI * 0.3 * tSec)));
    *matriz_escalado_cilindro = scale(vec3(1.0, desplazamiento + 1, 1.0));
    *matriz_traslacion = translate(vec3(0.0, desplazamiento, 0.0));
    break;
  }
  case 1:
    *matriz_esfera =
        rotate(float(M_PI / 8) * float(M_PI * 0.3 * tSec), vec3(1.0, 0.0, 0.0));
    break;
  }
}

Ejercicio2::Ejercicio2() {
  NodoGrafoEscena *cono = new NodoGrafoEscena();
  cono->agregar(scale(vec3(0.2, 0.5, 0.2)));
  cono->agregar(new Cono(2, 20));

  NodoGrafoEscena *prisma = new NodoGrafoEscena();
  prisma->agregar(scale(vec3(0.2, 0.3, 0.2)));
  prisma->agregar(new Cubo());

  agregar(translate(vec3(0.5, 0.0, 0.0)));
  agregar(cono);
  unsigned ind_rotacion1 = agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));
  agregar(translate(vec3(0.0, 0.8, 0.0)));
  agregar(prisma);
  agregar(translate(vec3(0.0, 0.3, 0.0)));
  agregar(cono);
  unsigned ind_rotacion2 = agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));
  agregar(translate(vec3(0.0, 0.8, 0.0)));
  agregar(prisma);

  matriz_rotacion1 = leerPtrMatriz(ind_rotacion1);
  matriz_rotacion2 = leerPtrMatriz(ind_rotacion2);
}
unsigned Ejercicio2::leerNumParametros() const { return 2; }
void Ejercicio2::actualizarEstadoParametro(const unsigned iParam,
                                           const float tSec) {
  switch (iParam) {
  case 0:
    *matriz_rotacion1 = rotate(float(M_PI * 0.3 * tSec), vec3(0.0, 1.0, 0.0));
    break;
  case 1:
    *matriz_rotacion2 = rotate(float(M_PI * 0.3 * tSec), vec3(0.0, 1.0, 0.0));
    break;
  }
}

Ejercicio3::Ejercicio3(const int num_verts_per, const unsigned nperfiles) {
  const float radio = 0.5;
  const float increment = glm::half_pi<float>() / (num_verts_per - 1);
  std::vector<glm::vec3> perfil;
  // Cuarto de circunferencia inferior
  for (int i = 0; i < num_verts_per; i++) {
    float vec_x = radio * cos(-glm::half_pi<float>() + (increment * i));
    float vec_y = radio * sin(-glm::half_pi<float>() + (increment * i));
    perfil.push_back({vec_x, -vec_y, 0.0});
  }
  // for (int i = 0; i < num_verts_per; i++) {
  //   float vec_x = radio * cos(-glm::half_pi<float>() + (increment * i));
  //   float vec_y = radio * sin(-glm::half_pi<float>() + (increment * i));
  //   perfil.push_back({0.5 + vec_x, 0.5 + vec_y, 0.0});
  // }
  inicializar(perfil, nperfiles);
}

Ejercicio4::Ejercicio4() {
  vertices = {
      // Base inferior
      {0.3, -0.25, 0.3},
      {-0.3, -0.25, 0.3},
      {-0.3, -0.25, -0.3},
      {0.3, -0.25, -0.3},

      // Base superior
      {0.5, 0.25, 0.5},
      {-0.5, 0.25, 0.5},
      {-0.5, 0.25, -0.5},
      {0.5, 0.25, -0.5},
      // Extremo
      {0.0, 1.0, 0.0},
  };
  triangulos = {
      // Caras de tronco de piramide
      {0, 1, 4},
      {1, 4, 5},
      {1, 2, 5},
      {2, 5, 6},
      {2, 3, 6},
      {3, 6, 7},
      {3, 0, 7},
      {0, 7, 4},
      // Base de tronco de piramide
      {0, 1, 2},
      {0, 2, 3},
      // Piramide
      {4, 5, 8},
      {5, 6, 8},
      {6, 7, 8},
      {7, 4, 8},
  };
}

Ejercicio5_Flecha::Ejercicio5_Flecha(const float hPunta, const float hAstil,
                                     const float nRev) {
  const float radio_astil = 0.1;
  const float radio_cono = 0.6;
  std::vector<glm::vec3> perfil;
  // Astil
  perfil.push_back({0.0, 0.0, 0.0});
  perfil.push_back({radio_astil, 0.0, 0.0});
  perfil.push_back({radio_astil, hAstil, 0.0});

  // Cono
  perfil.push_back({radio_cono, hAstil, 0.0});
  perfil.push_back({0.0, hAstil + hPunta, 0.0});
  ponerColor(vec3{0.0, 1.0, 0.0});

  inicializar(perfil, nRev);
}

Sombrilla::Sombrilla(const unsigned num_varillas) {
  NodoGrafoEscena *varilla = new NodoGrafoEscena();
  unsigned ind_rotacion = varilla->agregar(rotate(0.0f, vec3(0.0, 0.0, 1.0)));
  varilla->agregar(translate(vec3(0.05, 0.0, 0.0)));
  varilla->agregar(rotate(radians(10.0f), vec3(0.0, 0.0, 1.0)));
  varilla->agregar(translate(vec3(0.0, -0.3, 0.0)));
  varilla->agregar(scale(vec3(0.05, 0.3, 0.05)));
  varilla->agregar(new Cubo());

  NodoGrafoEscena *soporte = new NodoGrafoEscena();
  unsigned ind_escalado = soporte->agregar(scale(vec3(1.0, 1.0, 1.0)));
  soporte->agregar(scale(vec3(0.05, 1, 0.05)));
  soporte->agregar(new Cilindro(2, 20));

  agregar(soporte);
  unsigned ind_traslacion = agregar(translate(vec3(0.0, 0.0, 0.0)));
  agregar(translate(vec3(0.0, 1.0, 0.0)));
  for (int i = 0; i < num_varillas; i++) {
    agregar(varilla);
    agregar(rotate(radians(float(360.0 / num_varillas)), vec3(0.0, 1.0, 0.0)));
  }
  matriz_escalado = soporte->leerPtrMatriz(ind_escalado);
  matriz_traslacion = leerPtrMatriz(ind_traslacion);
  matriz_rotacion = varilla->leerPtrMatriz(ind_rotacion);
}
unsigned Sombrilla::leerNumParametros() const { return 2; }

void Sombrilla::actualizarEstadoParametro(const unsigned iParam,
                                          const float tSec) {
  switch (iParam) {
  case 0:
    *matriz_rotacion =
        rotate(float(M_PI / 3) * float(abs(sin(M_PI * 0.3 * tSec))),
               vec3(0.0, 0.0, 1.0));
    break;
  case 1: {
    float desplazamiento = 0.5 * abs(sin(M_PI * 0.3 * tSec));
    *matriz_escalado = scale(vec3(1.0, 1.0 + desplazamiento, 1.0));
    *matriz_traslacion = translate(vec3(0.0, desplazamiento, 0.0));
    break;
  }
  }
}

Ejercicio1_EX::Ejercicio1_EX() {
  vertices = {
      {0.0, 0.0, 0.0}, {0.3, 0.0, 0.0}, {0.6, 0.3, 0.0}, // Punto alto
      {0.9, 0.0, 0.0}, {1.2, 0.0, 0.0},

      {0.0, 0.0, 0.6}, {0.3, 0.0, 0.6}, {0.6, 0.3, 0.6}, // Punto alto
      {0.9, 0.0, 0.6}, {1.2, 0.0, 0.6},

  };

  triangulos = {{0, 1, 5}, {1, 5, 6}, {1, 2, 6}, {2, 6, 7},
                {2, 3, 7}, {3, 7, 8}, {3, 4, 8}, {4, 8, 9},
                {0, 5, 1}, {1, 6, 2}, {2, 7, 3}, {3, 8, 4}};

  // set white color to vertices with y > 0 and gray to the rest
  for (auto &v : vertices) {
    if (v.y > 0.0) {
      col_ver.push_back({1.0, 1.0, 1.0});
    } else {
      col_ver.push_back({0.5, 0.5, 0.5});
    }
  }
}

Ejercicio2_EX::Ejercicio2_EX(unsigned n) {
  float longitud_rec = 0.6;
  float ancho_rec = 0.3;
  int vertices_por_fila = 5;

  // Añado los vertices
  float x_fila = 0.0;
  for (int i = 0; i < n + 1; i++) {
    float z_fila = 0.0;
    for (int j = 0; j < 5; j++) {
      if (j == 2) {
        vertices.push_back({x_fila, 0.4, z_fila});
      } else {
        vertices.push_back({x_fila, 0.0, z_fila});
      }
      z_fila += ancho_rec;
    }
    x_fila += longitud_rec;
  }

  // Creo los triangulos
  for (int fila = 0; fila < n - 1; fila++) {
    for (int columna = 0; columna < vertices_por_fila - 1; columna++) {
      triangulos.push_back({fila * vertices_por_fila + columna,
                            fila * vertices_por_fila + columna + 1,
                            (fila + 1) * vertices_por_fila + columna});
      triangulos.push_back({(fila + 1) * vertices_por_fila + columna,
                            (fila + 1) * vertices_por_fila + columna + 1,
                            fila * vertices_por_fila + columna + 1});
    }
  }

  // Doy color
  vec3 gris_oscuro = {0.2f, 0.2f, 0.2f};
  vec3 blanco = {1.0f, 1.0f, 1.0f};

  for (int i = 0; i <= n; i++)
    for (int j = 0; j < 5; ++j)
      if (j == 2)
        col_ver.push_back(blanco);
      else
        col_ver.push_back(gris_oscuro);
}

Ejercicio3_EX::Ejercicio3_EX() {
  NodoGrafoEscena *cubo = new NodoGrafoEscena();
  cubo->agregar(scale(vec3(0.5, 0.5, 0.5)));
  cubo->agregar(new Cubo());

  NodoGrafoEscena *cubo_inferior = new NodoGrafoEscena();
  unsigned ind_cubo_inferior =
      cubo_inferior->agregar(scale(vec3(1.0, 1.0, 1.0)));
  cubo_inferior->agregar(translate(vec3(0.0, 0.5, 0.0)));
  cubo_inferior->agregar(cubo);

  agregar(cubo_inferior);
  agregar(translate(vec3(0.0, 1.5, 0.0)));
  unsigned ind_cubo_superior = agregar(rotate(0.0f, vec3(0.0, 0.0, 1.0)));
  agregar(cubo);

  matriz_cubo_inferior = cubo_inferior->leerPtrMatriz(ind_cubo_inferior);
  matriz_cubo_superior = leerPtrMatriz(ind_cubo_superior);
}
unsigned Ejercicio3_EX::leerNumParametros() const { return 2; }

void Ejercicio3_EX::actualizarEstadoParametro(const unsigned iParam,
                                              const float tSec) {
  switch (iParam) {
  case 0: {
    float desplazamiento = 1.0 * abs(sin(M_PI * 0.3 * tSec));
    *matriz_cubo_inferior = scale(vec3(1.0, 1.0 + desplazamiento, 1.0));
    *matriz_cubo_superior = translate(vec3(0.0, desplazamiento, 0.0));
    break;
  }
  case 1: {
    *matriz_cubo_superior *=
        translate(vec3(-0.5, -0.5, 0.0)) *
        rotate(float(M_PI) * float(abs(sin(M_PI * 0.3 * tSec))),
               vec3(0.0, 0.0, 1.0)) *
        translate(vec3(0.5, 0.5, 0.0));
  }
  }
}
