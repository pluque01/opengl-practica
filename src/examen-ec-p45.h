// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP
#include "malla-ind.h"
#include "grafo-escena.h"
#include <glm/ext/vector_float3.hpp>

class MallaPiramideP45 : public MallaInd {

public:
  MallaPiramideP45();
};

class GrafoPiramideP45 : public NodoGrafoEscena {
public:
  GrafoPiramideP45();
};

class MallaTrianguloP45 : public MallaInd {
public:
  bool is_selected = false;
  MallaTrianguloP45(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c,
                    const unsigned int n);
  bool cuandoClick(const glm::vec3 &centro_wc);
};

class GrafoTriangulosP45 : public NodoGrafoEscena {
public:
  GrafoTriangulosP45();
};

#endif // !EXAMEN_EC_P45_HPP
