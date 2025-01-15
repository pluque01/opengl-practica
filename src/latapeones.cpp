#include "latapeones.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "materiales-luces.h"

using namespace glm;

LataPeones::LataPeones() {
  NodoGrafoEscena *peon = new Peon(11);
  agregar(new Lata("lata-coke.jpg"));

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

Lata::Lata(std::string nombre_textura) {
  agregar(new MallaRevolPLY("lata-pinf.ply", 50));
  agregar(new MallaRevolPLY("lata-psup.ply", 50));
  agregar(new Material(new Textura(nombre_textura), 0.25, 1.5, 1.5, 50));
  agregar(new MallaRevolPLY("lata-pcue.ply", 50));
}

Peon::Peon(const int id) {
  ponerIdentificador(id);
  unsigned ind = agregar(translate(vec3(0.0, 0.0, 0.0)));
  agregar(translate(vec3(0.0, 0.27, 0.8)));
  agregar(scale(vec3(0.2, 0.2, 0.2)));
  agregar(new MallaRevolPLY("peon.ply", 50));
  mat_tras = leerPtrMatriz(ind);
}

bool Peon::cuandoClick(const glm::vec3 &centro_wc) {
  *mat_tras *= translate(vec3(0.0, 0.0, 0.3));
  return true;
}

VariasLatasPeones::VariasLatasPeones() {
  NodoGrafoEscena *peon_madera = new NodoGrafoEscena();
  NodoGrafoEscena *peon_blanco = new NodoGrafoEscena();
  NodoGrafoEscena *peon_negro = new NodoGrafoEscena();

  // Peon madera
  peon_madera->ponerIdentificador(1);
  peon_madera->ponerNombre("Peón de madera");
  peon_madera->agregar(
      new Material(new TexturaXY("text-madera.jpg"), 0.25, 1.5, 1.5, 50));
  peon_madera->agregar(new Peon(22));
  agregar(peon_madera);

  // Peon blanco
  peon_blanco->ponerIdentificador(2);
  peon_blanco->ponerNombre("Peón blanco");
  peon_blanco->agregar(translate(vec3(0.5, 0.0, 0.0)));
  peon_blanco->agregar(new Material(0.5, 0.5, 0.0, 1));
  peon_blanco->agregar(new Peon(33));
  agregar(peon_blanco);

  // Peon negro
  peon_negro->ponerIdentificador(3);
  peon_negro->ponerNombre("Peón negro");
  peon_negro->agregar(translate(vec3(1.0, 0.0, 0.0)));
  peon_negro->agregar(new Material(0.0, 0.01, 0.8, 10));
  peon_negro->agregar(new Peon(44));
  agregar(peon_negro);

  NodoGrafoEscena *lata_coke = new NodoGrafoEscena();
  NodoGrafoEscena *lata_pepsi = new NodoGrafoEscena();
  NodoGrafoEscena *lata_ugr = new NodoGrafoEscena();

  lata_coke->ponerIdentificador(4);
  lata_coke->ponerNombre("Lata de Coca-Cola");
  lata_coke->agregar(new Lata("lata-coke.jpg"));
  agregar(lata_coke);

  lata_pepsi->ponerIdentificador(5);
  lata_pepsi->ponerNombre("Lata de Pepsi");
  lata_pepsi->agregar(translate(vec3(0.8, 0.0, 0.0)));
  lata_pepsi->agregar(new Lata("lata-pepsi.jpg"));
  agregar(lata_pepsi);

  lata_ugr->ponerIdentificador(6);
  lata_ugr->ponerNombre("Lata de la UGR");
  lata_ugr->agregar(translate(vec3(1.6, 0.0, 0.0)));
  lata_ugr->agregar(new Lata("window-icon.jpg"));
  agregar(lata_ugr);
}
