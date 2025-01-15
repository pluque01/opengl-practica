// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
#include "grafo-escena.h"
class GrafoCubos : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_rotacion = nullptr;

public:
  GrafoCubos();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class GrafoEstrellaX : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_rotacion = nullptr;

public:
  GrafoEstrellaX(unsigned int n);
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class BrazoMecanico : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_rotacion_inferior = nullptr;
  glm::mat4 *matriz_rotacion_superior = nullptr;
  glm::mat4 *matriz_translacion_gancho_derecho = nullptr;
  glm::mat4 *matriz_translacion_gancho_izquierdo = nullptr;

public:
  BrazoMecanico();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class BaseBrazo : public NodoGrafoEscena {
public:
  static float altura;
  BaseBrazo();
};
class Tornillo : public NodoGrafoEscena {
public:
  static float altura;
  static float radio;
  Tornillo();
};
class SoporteInferior : public NodoGrafoEscena {
public:
  static float altura;
  static float base;
  static float ancho;
  SoporteInferior();
};

class BrazoInferior : public NodoGrafoEscena {
public:
  static float altura;
  static float base;
  static float ancho;
  BrazoInferior();
};
class BrazoSuperior : public NodoGrafoEscena {
public:
  static float altura;
  static float base;
  static float ancho;
  BrazoSuperior();
};
class BaseGancho : public NodoGrafoEscena {
public:
  static float altura;
  static float base;
  static float ancho;
  BaseGancho();
};
class Gancho : public NodoGrafoEscena {
public:
  static float altura;
  static float base;
  static float ancho;
  Gancho();
};
class GanchoIzquierdo : public NodoGrafoEscena {
public:
  GanchoIzquierdo();
};
class GanchoDerecho : public NodoGrafoEscena {
public:
  GanchoDerecho();
};

class NodoCubo24 : public NodoGrafoEscena {
public:
  NodoCubo24();
};

class NodoDiscoP4 : public NodoGrafoEscena {
public:
  NodoDiscoP4();
};

class BeethovenP4 : public NodoGrafoEscena {
public:
  BeethovenP4(const bool horizontal);
};

class TexturaBeethoven : public Textura {
public:
  TexturaBeethoven(const std::string &nom, const bool horizontal)
      : Textura(nom) {
    modo_gen_ct = mgct_coords_objeto;
    if (horizontal) {
      coefs_s[0] = 0.0;
      coefs_s[1] = 1.0;
    } else {
      coefs_s[0] = 1.0;
      coefs_s[1] = 0.0;
    }
  }
};
