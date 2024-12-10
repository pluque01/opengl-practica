// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
#include "modelo-jer.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "materiales-luces.h"
#include <cassert>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/trigonometric.hpp>

using namespace glm;

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

BrazoMecanico::BrazoMecanico() {
  agregar(new BaseBrazo());
  unsigned ind_rotacion_inferior = agregar(rotate(0.0f, vec3(1.0, 0.0, 1.0)));
  agregar(new BrazoInferior());
  unsigned ind_rotacion_superior = agregar(rotate(0.0f, vec3(1.0, 0.0, 1.0)));
  agregar(new BrazoSuperior());
  agregar(new BaseGancho());

  Gancho *gancho = new Gancho();

  unsigned ind_translacion_gancho_izquierdo =
      gancho->agregar(translate(vec3(0.0, 0.0, 0.0)));
  gancho->agregar(new GanchoIzquierdo());
  unsigned ind_translacion_gancho_derecho =
      gancho->agregar(translate(vec3(0.0, 0.0, 0.0)));
  gancho->agregar(new GanchoDerecho());
  agregar(gancho);

  matriz_rotacion_inferior = leerPtrMatriz(ind_rotacion_inferior);
  matriz_rotacion_superior = leerPtrMatriz(ind_rotacion_superior);
  matriz_translacion_gancho_derecho =
      gancho->leerPtrMatriz(ind_translacion_gancho_derecho);
  matriz_translacion_gancho_izquierdo =
      gancho->leerPtrMatriz(ind_translacion_gancho_izquierdo);
}
unsigned BrazoMecanico::leerNumParametros() const { return 3; }
void BrazoMecanico::actualizarEstadoParametro(const unsigned iParam,
                                              const float tSec) {
  assert(iParam < leerNumParametros());
  switch (iParam) {
  case 0:
    *matriz_rotacion_inferior =
        translate(vec3(
            0.0, 2 * BaseBrazo::altura + SoporteInferior::altura + 0.1, 0.0)) *
        rotate(float(M_PI / 4) * sin(float(M_PI * 0.3 * tSec)),
               vec3(1.0, 0.0, 0.0)) *
        translate(vec3(0.0,
                       -(2 * BaseBrazo::altura + SoporteInferior::altura + 0.1),
                       0.0));
    break;
  case 1: {
    float angleMin = 160.0 * M_PI / 180.0;
    float angleMax = 380.0 * M_PI / 180.0;

    float angle =
        angleMin + (angleMax - angleMin) * ((sin(M_PI * 0.3 * tSec) + 1) / 2.0);
    *matriz_rotacion_superior =
        translate(vec3(0.0,
                       2 * BaseBrazo::altura + SoporteInferior::altura +
                           2 * BrazoInferior::altura - BrazoSuperior::altura,
                       0.0)) *
        rotate(angle, vec3(1.0, 0.0, 0.0)) *
        translate(vec3(0.0,
                       -(2 * BaseBrazo::altura + SoporteInferior::altura +
                         2 * BrazoInferior::altura - BrazoSuperior::altura),
                       0.0));
    break;
  }
  case 2:
    float desplazamiento =
        abs((BaseGancho::ancho - 2 * Gancho::ancho) * sin(M_PI * 0.2 * tSec));
    *matriz_translacion_gancho_derecho =
        translate(vec3(2 * desplazamiento, 0.0, 0.0));
    *matriz_translacion_gancho_izquierdo =
        translate(vec3(-(desplazamiento), 0.0, 0.0));
    break;
  }
}

float BaseBrazo::altura = 0.05;
BaseBrazo::BaseBrazo() {
  agregar(new SoporteInferior());
  agregar(translate(vec3(0.0, altura, 0.0)));
  agregar(scale(vec3(0.7, altura, 0.7)));
  ponerColor(vec3(0.82, 0.65, 0.47));
  agregar(new Cubo());
}

float Tornillo::altura = 0.3;
float Tornillo::radio = 0.02;
Tornillo::Tornillo() {
  ponerColor(vec3(0.70, 0.70, 0.70));
  agregar(scale(vec3(Tornillo::altura, Tornillo::radio, Tornillo::radio)));
  agregar(rotate(radians(90.0f), vec3(0.0, 0.0, 1.0)));
  agregar(new Cilindro(2, 10));
}

float SoporteInferior::altura = 0.2;
float SoporteInferior::base = 0.15;
float SoporteInferior::ancho = 0.05;
SoporteInferior::SoporteInferior() {
  ponerColor(vec3(0.42, 0.26, 0.15));
  NodoGrafoEscena *lateral_soporte_inferior = new NodoGrafoEscena();

  lateral_soporte_inferior->agregar(
      translate(vec3(0.0, altura + 2 * BaseBrazo::altura, 0.0)));
  lateral_soporte_inferior->agregar(scale(vec3(ancho, altura, base)));
  lateral_soporte_inferior->agregar(new Cubo());

  agregar(translate(vec3(0.15, 0.0, 0.0)));
  agregar(lateral_soporte_inferior);
  agregar(translate(vec3(-0.3, 0.0, 0.0)));
  agregar(lateral_soporte_inferior);
  agregar(translate(vec3(
      2 * base, 2 * BaseBrazo::altura + SoporteInferior::altura + 0.1, 0.0)));
  agregar(new Tornillo());
}

float BrazoInferior::altura = 0.4;
float BrazoInferior::base = 0.1;
float BrazoInferior::ancho = 0.01;
BrazoInferior::BrazoInferior() {
  ponerColor(vec3(0.42, 0.26, 0.15));
  NodoGrafoEscena *lateral_brazo_inferior = new NodoGrafoEscena();
  lateral_brazo_inferior->agregar(
      translate(vec3(0.0, altura + 2 * BaseBrazo::altura + 0.2, 0.0)));
  lateral_brazo_inferior->agregar(scale(vec3(ancho, altura, base)));
  lateral_brazo_inferior->agregar(new Cubo());
  agregar(translate(vec3(0.15 - 2 * SoporteInferior::ancho, 0.0, 0.0)));
  agregar(lateral_brazo_inferior);
  agregar(translate(vec3(-0.3 + 4 * SoporteInferior::ancho, 0.0, 0.0)));
  agregar(lateral_brazo_inferior);
}
float BrazoSuperior::altura = 0.1;
float BrazoSuperior::base = 0.4;
float BrazoSuperior::ancho = 0.01;
BrazoSuperior::BrazoSuperior() {
  ponerColor(vec3(0.42, 0.26, 0.15));
  NodoGrafoEscena *lateral_brazo_superior = new NodoGrafoEscena();
  lateral_brazo_superior->agregar(translate(vec3(
      0.0, 2 * BaseBrazo::altura + 0.2 + 2 * BrazoInferior::altura - altura,
      base - BrazoInferior::base)));
  lateral_brazo_superior->agregar(scale(vec3(ancho, altura, base)));
  lateral_brazo_superior->agregar(new Cubo());
  agregar(translate(vec3(0.15, 0.0, 0.0)));
  agregar(lateral_brazo_superior);
  agregar(translate(vec3(-0.3, 0.0, 0.0)));
  agregar(lateral_brazo_superior);
  agregar(translate(vec3(
      0.3, 2 * BaseBrazo::altura + 0.2 + 2 * BrazoInferior::altura - altura,
      0.0)));
  agregar(new Tornillo());
}

float BaseGancho::altura = 0.05;
float BaseGancho::base = 0.1;
float BaseGancho::ancho = 0.2;
BaseGancho::BaseGancho() {
  ponerColor(vec3(0.29, 0.29, 0.29));
  agregar(translate(
      vec3(0.0, BaseBrazo::altura + 0.2 + 2 * BrazoInferior::altura - altura,
           2 * BrazoSuperior::base - base)));
  agregar(scale(vec3(ancho, altura, base)));
  agregar(new Cubo());
}

float Gancho::altura = 0.03;
float Gancho::base = 0.1;
float Gancho::ancho = 0.03;
Gancho::Gancho() { ponerColor(vec3(0.29, 0.29, 0.29)); }

GanchoIzquierdo::GanchoIzquierdo() {
  agregar(translate(vec3(-Gancho::ancho,
                         BaseBrazo::altura + 0.2 + 2 * BrazoInferior::altura -
                             BaseGancho::altura,
                         2 * BrazoSuperior::base + Gancho::base)));
  agregar(scale(vec3(Gancho::ancho, Gancho::altura, Gancho::base)));
  agregar(new Cubo());
}
GanchoDerecho::GanchoDerecho() {
  agregar(translate(vec3(Gancho::ancho,
                         BaseBrazo::altura + 0.2 + 2 * BrazoInferior::altura -
                             BaseGancho::altura,
                         2 * BrazoSuperior::base + Gancho::base)));
  agregar(scale(vec3(Gancho::ancho, Gancho::altura, Gancho::base)));
  agregar(new Cubo());
}

NodoCubo24::NodoCubo24() {
  // agregar(new Material(new Textura("window-icon.jpg"), 0.5, 0.5, 0.5, 40.0));

  agregar(new Material(new Textura("window-icon.jpg"), 0.2, 0.8, 0.0, 1.0));
  agregar(new Cubo24());
}
