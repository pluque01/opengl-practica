#include "latapeones.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "materiales-luces.h"

using namespace glm;

LataPeones::LataPeones() {
  NodoGrafoEscena *peon = new Peon();
  agregar(new Lata());

  // Peon madera
  agregar(new Material(new TexturaXY("text-madera.jpg"), 0.25, 1.5, 1.5, 50));
  agregar(peon);

  // Peon blanco
  agregar(translate(vec3(0.5, 0.0, 0.0)));
  agregar(new Material(0.5, 0.5, 0.0, 1));
  agregar(peon);

  // Peon negro
  agregar(translate(vec3(0.5, 0.0, 0.0)));
  agregar(new Material(0.0, 0.01, 0.8, 10));
  agregar(peon);
}

Lata::Lata() {
  agregar(new MallaRevolPLY("lata-pinf.ply", 50));
  agregar(new MallaRevolPLY("lata-psup.ply", 50));
  agregar(new Material(new Textura("lata-coke.jpg"), 0.25, 1.5, 1.5, 50));
  agregar(new MallaRevolPLY("lata-pcue.ply", 50));
}

Peon::Peon() {
  agregar(translate(vec3(0.0, 0.27, 0.8)));
  agregar(scale(vec3(0.2, 0.2, 0.2)));
  agregar(new MallaRevolPLY("peon.ply", 50));
}
