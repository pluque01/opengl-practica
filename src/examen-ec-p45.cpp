// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
#include "examen-ec-p45.h"
#include "grafo-escena.h"

MallaPiramideP45::MallaPiramideP45() : MallaInd("MallaPiramideP45") {
  vertices = {
      // Base
      {0.0, 0.0, 0.0}, // esquina 1
      {2.0, 0.0, 0.0}, // esquina 2
      {2.0, 0.0, 2.0}, // esquina 3
      {0.0, 0.0, 2.0}, // esquina 4
                       // Cara 1
      {0.0, 0.0, 0.0}, // esquina 1
      {2.0, 0.0, 0.0}, // esquina 2
      {1.0, 2.0, 1.0}, // Punta
                       // cara 2
      {2.0, 0.0, 0.0}, // esquina 2
      {2.0, 0.0, 2.0}, // esquina 3
      {1.0, 2.0, 1.0}, // Punta
                       // cara 3
      {2.0, 0.0, 2.0}, // esquina 3
      {0.0, 0.0, 2.0}, // esquina 4
      {1.0, 2.0, 1.0}, // Punta
                       // cara 4
      {0.0, 0.0, 0.0}, // esquina 4
      {0.0, 0.0, 2.0}, // esquina 4
      {1.0, 2.0, 1.0}, // Punta
  };
  triangulos = {
      {0, 1, 2},
      {0, 2, 3},
      // Caras
      {4, 5, 6},
      {7, 8, 9},
      {10, 11, 12},
      {13, 14, 15},
  };
  // Genera coordenas de textura para una piramide
  cc_tt_ver = {
      // BASE
      {1.0f, 1.0f}, // esquina 1
      {0.0f, 1.0f}, // esquina 2
      {0.0f, 0.0f}, // esquina 3
      {1.0f, 0.0f}, // esquina 4
      // Cara 1
      {1.0f, 1.0f}, // esquina 1
      {0.0f, 1.0f}, // esquina 2
      {0.5f, 0.0f}, // Punta
      // Cara 2
      {1.0f, 1.0f}, // esquina 2
      {0.0f, 1.0f}, // esquina 3
      {0.5f, 0.0f}, // Punta
      // Cara 3
      {1.0f, 1.0f}, // esquina 3
      {0.0f, 1.0f}, // esquina 4
      {0.5f, 0.0f}, // Punta
      // Cara 4
      {1.0f, 1.0f}, // esquina 4
      {0.0f, 1.0f}, // esquina 1
      {0.5f, 0.0f}, // Punta
  };
  calcularNormales();
}

GrafoPiramideP45::GrafoPiramideP45() {
  agregar(new Material(new Textura("window-icon.jpg"), 0.7, 0.5, 0.0, 30.0));
  agregar(new MallaPiramideP45());
}

MallaTrianguloP45::MallaTrianguloP45(const glm::vec3 &a, const glm::vec3 &b,
                                     const glm::vec3 &c, const unsigned int n)
    : MallaInd() {
  ponerNombre("Triangulo " + std::to_string(n));
  ponerIdentificador(10 + n);
  vertices = {a, b, c};
  triangulos = {{0, 1, 2}};
  ponerColor({1.0, 1.0, 1.0});
  ponerCentroOC((a + b + c) / 3.0f);
  calcularNormales();
}

bool MallaTrianguloP45::cuandoClick(const glm::vec3 &centro_wc) {
  if (is_selected) {
    ponerColor({1.0, 1.0, 1.0});
  } else {
    ponerColor({1.0, 0.0, 0.0});
  }
  is_selected = !is_selected;

  MallaInd::cuandoClick(centro_wc);

  return true;
}

GrafoTriangulosP45::GrafoTriangulosP45() {
  // Base
  agregar(new MallaTrianguloP45({0.0, 0.0, 0.0}, {2.0, 0.0, 0.0},
                                {2.0, 0.0, 2.0}, 1));
  agregar(new MallaTrianguloP45({0.0, 0.0, 0.0}, {2.0, 0.0, 2.0},
                                {0.0, 0.0, 2.0}, 2));
  // Caras
  agregar(new MallaTrianguloP45({0.0, 0.0, 0.0}, {2.0, 0.0, 0.0},
                                {1.0, 2.0, 1.0}, 3));
  agregar(new MallaTrianguloP45({2.0, 0.0, 0.0}, {2.0, 0.0, 2.0},
                                {1.0, 2.0, 1.0}, 4));
  agregar(new MallaTrianguloP45({2.0, 0.0, 2.0}, {0.0, 0.0, 2.0},
                                {1.0, 2.0, 1.0}, 5));
  agregar(new MallaTrianguloP45({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0},
                                {1.0, 2.0, 1.0}, 6));
}
