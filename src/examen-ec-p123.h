// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "grafo-escena.h"
#include "malla-ind.h"

class EX123_Ejercicio1 : public MallaInd {
public:
  EX123_Ejercicio1();
};

class EX123_Ejercicio2 : public MallaInd {
public:
  EX123_Ejercicio2(unsigned int n = 8);
};

class EX123_Ejercicio3 : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_tablero = nullptr;
  glm::mat4 *matriz_cubo = nullptr;
  float h;

public:
  EX123_Ejercicio3(const float w = 1.5, const float h = 0.3);
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

#endif // !EXAMEN_EC_P123_HPP
