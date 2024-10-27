#include "modelo-jer.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include <cassert>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/trigonometric.hpp>

GrafoCubos::GrafoCubos() {
  using namespace glm;
  NodoGrafoEscena *lateral = new NodoGrafoEscena();
  lateral->agregar(translate(vec3(0.5, -0.5, -0.5)));
  lateral->agregar(rotate(radians(90.0f), vec3{0.0, 0.0, 1.0}));
  lateral->agregar(new RejillaY(7, 7));
  lateral->agregar(translate(vec3(0.5, -0.25, 0.5)));
  lateral->agregar(scale(vec3(0.1, 0.25, 0.1)));
  unsigned ind = lateral->agregar(rotate(0.0f, vec3{0.0, -1.0, 0.0}));
  lateral->agregar(new Cubo());
  for (int i = 0; i < 4; i++) {
    agregar(lateral);
    agregar(rotate(radians(90.0f), vec3{0.0, 0.0, 1.0}));
  }
  agregar(rotate(radians(90.0f), vec3{0.0, 1.0, 0.0}));
  agregar(lateral);
  agregar(rotate(radians(180.0f), vec3{0.0, 1.0, 0.0}));
  agregar(lateral);
  matriz_rotacion = lateral->leerPtrMatriz(ind);
}

unsigned GrafoCubos::leerNumParametros() const { return 1; }
void GrafoCubos::actualizarEstadoParametro(const unsigned iParam,
                                           const float tSec) {
  assert(iParam < leerNumParametros());
  float alpha = float(2 * M_PI * 0.3 * tSec);
  *matriz_rotacion = (rotate(alpha, glm::vec3{0.0, -1.0, 0.0}));
}
GrafoEstrellaX::GrafoEstrellaX(unsigned int n) {
  using namespace glm;
  NodoGrafoEscena *cono_escena = new NodoGrafoEscena;
  Cono *cono = new Cono(2, 20);

  cono_escena->agregar(translate(vec3(-0.5, -0.5, 0.0)));
  cono_escena->agregar(translate(vec3(1.0, 0.5, 0.0)));
  cono_escena->agregar(rotate(radians(90.0f), vec3(0.0, 0.0, -1.0)));
  cono_escena->agregar(scale(vec3(0.14, 0.15, 0.14)));
  cono_escena->agregar(cono);

  unsigned ind = agregar(rotate(0.0f, vec3{0.0, 0.0, 1.0}));
  for (unsigned int i = 0; i < n; i++) {
    agregar(cono_escena);
    agregar(rotate(radians(360.0f / n), vec3(0.0, 0.0, -1.0)));
  }
  agregar(translate(vec3(-0.5, -0.5, 0.0)));
  agregar(new EstrellaZ(n));

  matriz_rotacion = leerPtrMatriz(ind);
}
unsigned GrafoEstrellaX::leerNumParametros() const { return 1; }
void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam,
                                               const float tSec) {
  assert(iParam < leerNumParametros());
  float alpha = float((2 * M_PI) * 2.5 * tSec);
  *matriz_rotacion = (rotate(alpha, glm::vec3{0.0, 0.0, 1.0}));
}
