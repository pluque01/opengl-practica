#include "grafo-escena.h"
class GrafoCubos : public NodoGrafoEscena {
protected:
  glm::mat4 *matriz_rotacion = nullptr;

public:
  GrafoCubos();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};
