#include "modelo-jer.h"
#include "malla-ind.h"
#include <cassert>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/transform.hpp>

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
