#include "grafo-escena.h"
#include "malla-revol.h"
#include <glm/ext/matrix_float4x4.hpp>

// EJERCICIO 1: Modelo jerárquico con dos articulaciones: un cilindro que se
// escala en Y(primera articulación) que sostiene un prisma que tiene situado
// en un extremo un elipsoide (esfera escalada) como si fuera un aspa que rota
// en X(segunda articulación).

class Ejercicio1 : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_escalado_cilindro = nullptr;
  glm::mat4 *matriz_traslacion = nullptr;
  glm::mat4 *matriz_esfera = nullptr;

public:
  Ejercicio1();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

// EJERCICIO 2: Modelo jerárquico con dos articulaciones: un cono con centro en
// un punto (a,0,0) que tiene situado sobre él un prisma (primer nivel). Sobre
// prisma tenemos situado otro cono que sostiene otro prisma(segundo nivel).
// Los prismas rotan entorno al vértice superior(puntos pivote) de sus
// respectivos conos.

class Ejercicio2 : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_rotacion1 = nullptr;
  glm::mat4 *matriz_rotacion2 = nullptr;

public:
  Ejercicio2();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

// Añadir un nuevo objeto por revolución con el perfil de la derecha (2.5
// puntos). Se valorará la consecución o no de los objetivos marcados
// (visualización del modelo y creación del perfil, según los siguientes
// aspectos: perfil con dos curvas con radio 0.5, anchura total 1.25 y altura
// total 1. Considerar la tapa inferior).

class Ejercicio3 : public MallaRevol {
public:
  Ejercicio3(const int num_verts_per, const unsigned nperfiles);
};

// Añadir un nuevo objeto a las opciones de objetos de las prácticas: la fusión
// de un tronco de pirámide invertido con una pirámide en la parte superior.
// Se valorará la consecución o no del objeto marcado (visualización del
// objeto final)

class Ejercicio4 : public MallaInd {
public:
  Ejercicio4();
};
// Cree una clase Flecha3D que tenga el siguiente constructor:
// Flecha::Flecha(float hPunta=1, float hAstil=1, flota nRev=30)
// Donde hPunta es la altura de la punta de la flecha, hAstil la altura del
// cuerpo, y nRev el número de instancias del objeto de revolución.
// El radio de la base de la punta se deja a elección del alumno. Debe generar
// una figura similar a esta. Ubíquela en la escena como si fuera un árbol.

class Ejercicio5_Flecha : public MallaRevol {
public:
  Ejercicio5_Flecha(const float hPunta = 1.0, const float hAstil = 1.0,
                    const float nRev = 30);
};

// Descargue su código de la práctica 2 o en caso de que no la tenga hecha, el
// esqueleto de la práctica 1 que hay en Prado y e implemente el modelo de una
// sombrilla. Para ello se usará el cubo para las varillas y el cilindro para el
// soporte (o el cubo si no tiene cilindro).
// 1. Cree el objeto varilla con las siguientes dimensiones (1,10,1) y una
// inclinación de 10 grados con respecto a la vertical. Se activa con la
// tecla 7. Implementar al menos el modo de visualización chess. (20% de la nota
// total)
// 2. Permita que la varilla se pueda subir y bajar con las teclas A y S. (20%
// de la nota total)
// 3. Cree el objeto soporte con un cilindro (o cubo) de tamaño (1,15,1) y con
// una varilla que pivota con respecto al borde del cilindro. Se activa con la
// tecla 8. Implementar al menos el modo de visualización chess. (20% de la nota
// total)
// 4. Permita que la varilla del soporte se pueda subir y bajar con las teclas Z
// y X. (20% de la nota total)
// 5. Modificar el objeto soporte para poder incluir M varillas repartidas de
// manera uniforme. El numero M se calculará de la siguiente manera: se toma la
// primera letra del primer apellido y se le asigna el valor de su posición. Por
// ejemplo, la A tiene el valor 1. Se calcula el modulo (%) con 5 y al resultado
// se le suma 4. (20% de la nota total)
// Para cada apartado, se valorará con la nota establecida el que se haya
// programado y se visualice correctamente y con 0 en otro caso. Cada apartado
// se valorará si el anterior está correcto.

class Sombrilla : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_escalado = nullptr;
  glm::mat4 *matriz_traslacion = nullptr;
  glm::mat4 *matriz_rotacion = nullptr;

public:
  Sombrilla(const unsigned num_varillas = 1);
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Ejercicio1_EX : public MallaInd {
public:
  Ejercicio1_EX();
};

class Ejercicio2_EX : public MallaInd {
public:
  Ejercicio2_EX(unsigned n);
};

class Ejercicio3_EX : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_cubo_inferior = nullptr;
  glm::mat4 *matriz_cubo_superior = nullptr;

public:
  Ejercicio3_EX();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};
