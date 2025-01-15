#ifndef LATA_PEONES_HPP
#define LATA_PEONES_HPP

#include "grafo-escena.h"
#include "materiales-luces.h"

class LataPeones : public NodoGrafoEscena {
public:
  LataPeones();
};

class Lata : public NodoGrafoEscena {
public:
  Lata(std::string nombre_textura);
};

class Peon : public NodoGrafoEscena {
protected:
  glm::mat4 *mat_tras = nullptr;

public:
  Peon(const int id);
  bool cuandoClick(const glm::vec3 &centro_wc);
};

class VariasLatasPeones : public NodoGrafoEscena {
public:
  VariasLatasPeones();
};
#endif // GRAFO_ESCENA_HPP
