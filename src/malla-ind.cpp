// Nombre: Pablo, Apellidos: Luque Salguero, Titulación: GIIADE
// Email: pluque01@correo.ugr.es, DNI: 20100264N
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// **
// ** Mallas indexadas (implementación). Clase 'MallaInd' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada
// de MallaInd)
// **        + algunas clases derivadas de MallaInd.
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "malla-ind.h" // declaración de 'ContextoVis'
#include "aplicacion-ig.h"
#include "cauce.h"
#include "ig-aux.h"
#include "lector-ply.h"
#include "seleccion.h" // para 'ColorDesdeIdent'
#include "vaos-vbos.h"
#include <cmath>
#include <glm/ext/vector_uint3.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <sys/types.h>

// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd() {
  // nombre por defecto
  ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd(const std::string &nombreIni) {
  // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
  ponerNombre(nombreIni);
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba
// calculada

void MallaInd::calcularNormalesTriangulos() {
  using namespace glm;

  // si ya está creada la tabla de normales de triángulos, no es necesario
  // volver a crearla
  const unsigned nt = triangulos.size();
  assert(1 <= nt);
  if (0 < nor_tri.size()) {
    assert(nt == nor_tri.size());
    return;
  }

  // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
  // ....
  for (unsigned i = 0; i < nt; i++) {
    vec3 a = vertices[triangulos[i][0]];
    vec3 b = vertices[triangulos[i][1]];
    vec3 c = vertices[triangulos[i][2]];
    vec3 n = cross(b - a, c - a);
    // si la longitud del vector es cero no se intenta normalizar
    if (length(n) == 0) {
      n = vec3(0.0, 0.0, 0.0);
    } else {
      n = normalize(n);
    }
    nor_tri.push_back(n);
  }
}

// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales() {
  using namespace glm;
  // COMPLETAR: en la práctica 4: calculo de las normales de la malla
  // se debe invocar en primer lugar 'calcularNormalesTriangulos'
  // .......

  calcularNormalesTriangulos();

  std::map<int, vec3> normales_vertice;

  // Inicializar la tabla de normales de vértices a 0
  for (const auto &tri : triangulos) {
    normales_vertice[tri[0]] = vec3(0, 0, 0);
    normales_vertice[tri[1]] = vec3(0, 0, 0);
    normales_vertice[tri[2]] = vec3(0, 0, 0);
  }

  // Para cada triángulo, sumar su normal a los vértices que lo componen
  for (int i = 0; i < triangulos.size(); i++) {
    vec3 n = nor_tri[i];
    normales_vertice[triangulos[i][0]] += n;
    normales_vertice[triangulos[i][1]] += n;
    normales_vertice[triangulos[i][2]] += n;
  }

  // Normalizar las normales de los vértices
  for (auto &par : normales_vertice) {
    if (length(par.second) == 0) {
      par.second = vec3(0, 0, 0);
    } else {
      par.second = normalize(par.second);
    }
    // Insertar las normales en las tabla
    nor_ver.push_back(par.second);
  }
}

// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL() {
  // comprobar algunas precondiciones básicas
  using namespace std;
  assert(aplicacionIG != nullptr);
  Cauce *cauce = aplicacionIG->cauce;
  assert(cauce != nullptr);
  CError();

  // si la malla no vértices o no tiene triángulos, imprimir advertencia y
  // salir.
  if (triangulos.size() == 0 || vertices.size() == 0) {
    cout << "advertencia: intentando dibujar malla vacía '" << leerNombre()
         << "'" << endl
         << flush;
    return;
  }

  // COMPLETAR: práctica 1: cambiar color del cauce
  //
  // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
  //    - hacer push del color actual del cauce
  //    - fijar el color en el cauce usando el color del objeto (se lee con
  //    'leerColor()')

  if (tieneColor()) {
    cauce->pushColor();
    cauce->fijarColor(leerColor());
  }

  // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
  //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
  //   * en primer lugar se crea el descriptor de VAO, con su constructor
  //     (se le pasa como parámetro la tabla de posiciones y el número de
  //     atributos del cauce).
  //   * se añade el descriptor de VBO con la tabla de índices (la tabla de
  //   triángulos),
  //   * finalmente se añaden al VAO los descriptores VBOs con tablas de
  //   atributos
  //     que no estén vacías
  //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
  //

  if (dvao == nullptr) {
    // 1. Crear el descriptor de VBO de posiciones, y usarlo para crear el
    // descriptor VAO.
    DescrVBOAtribs *pos_dvbo =
        new DescrVBOAtribs(ind_atrib_posiciones, vertices);
    dvao = new DescrVAO(numero_atributos_cauce, pos_dvbo);

    // 2. Crear y añadir (con el método agregar) el descriptor del VBO de
    // índices con la tabla de índices (es la tabla de triángulos)

    DescrVBOInds *ind_dvbo = new DescrVBOInds(triangulos);
    dvao->agregar(ind_dvbo);

    // 3. Para cada tabla de atributos (distintos de las posiciones de los
    // vértices) que no esté vacía, se crea el correspondiente descriptor de VBO
    // y se añade al descriptor del VAO (de nuevo con agregar).
    if (col_ver.size() > 0) {
      DescrVBOAtribs *col_dvbo = new DescrVBOAtribs(ind_atrib_colores, col_ver);
      dvao->agregar(col_dvbo);
    }
    if (nor_ver.size() > 0) {
      DescrVBOAtribs *norv_dvbo =
          new DescrVBOAtribs(ind_atrib_normales, nor_ver);
      dvao->agregar(norv_dvbo);
    }
    // if (nor_tri.size() > 0) {
    //   DescrVBOAtribs *nort_dvbo =
    //       new DescrVBOAtribs(ind_atrib_normales, nor_tri);
    //   dvao->agregar(nort_dvbo);
    // }
    if (cc_tt_ver.size() > 0) {
      DescrVBOAtribs *cc_tt_dvbo =
          new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver);
      dvao->agregar(cc_tt_dvbo);
    }
  }

  // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de
  // 'DescrVAO'
  dvao->draw(GL_TRIANGLES);
  // COMPLETAR: práctica 1: restaurar color anterior del cauce
  //
  // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
  //    - hacer 'pop' del color actual del cauce
  if (tieneColor())
    cauce->popColor();
}

// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están
// vacías.

void MallaInd::visualizarGeomGL() {
  // Comprobar que el descriptor de VAO ya está creado
  // (es decir, este método únicamente se podrá invocar después de que
  // se haya llamado a 'visualizaGL')

  assert(dvao != nullptr);

  // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto
  //
  //    1. Desactivar todas las tablas de atributos del VAO (que no estén
  //    vacías)
  if (!col_ver.empty()) {
    dvao->habilitarAtrib(ind_atrib_colores, false);
  }
  if (!nor_ver.empty()) {
    dvao->habilitarAtrib(ind_atrib_normales, false);
  }
  // if (!nor_tri.empty()) {
  //   dvao->habilitarAtrib(ind_atrib_normales, false);
  // }
  if (!cc_tt_ver.empty()) {
    dvao->habilitarAtrib(ind_atrib_coord_text, false);
  }
  //    2. Dibujar la malla (únicamente visualizará los triángulos), se usa el
  //    método 'draw' del VAO (dvao)
  dvao->draw(GL_TRIANGLES);
  //    3. Volver a activar todos los atributos para los cuales la tabla no esté
  //    vacía
  if (!col_ver.empty()) {
    dvao->habilitarAtrib(ind_atrib_colores, true);
  }
  if (!nor_ver.empty()) {
    dvao->habilitarAtrib(ind_atrib_normales, true);
  }
  // if (!nor_tri.empty()) {
  //   dvao->habilitarAtrib(ind_atrib_normales, true);
  // }
  if (!cc_tt_ver.empty()) {
    dvao->habilitarAtrib(ind_atrib_coord_text, true);
  }
}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL() {
  using namespace std;
  assert(aplicacionIG != nullptr);
  Cauce *cauce = aplicacionIG->cauce;
  assert(cauce != nullptr);

  if (nor_ver.size() == 0) {
    cout << "Advertencia: intentando dibujar normales de una malla que no "
            "tiene tabla ("
         << leerNombre() << ")." << endl;
    return;
  }

  if (nor_ver.size() != vertices.size()) {
    cout << "Error visu. normales: tabla de normales no vacía y de tamaño "
            "distinto a la de vértices."
         << endl;
    cout << "Nombre del objeto        : " << leerNombre() << endl;
    cout << "Tamaño tabla vértices    : " << vertices.size() << endl;
    cout << "Tamaño tabla de normales : " << nor_ver.size() << endl;
    exit(1);
  }
  CError();

  // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
  //
  // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es
  // nulo,
  //    debemos de crear dicho descriptor, con estos pasos:
  //
  //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
  //             - Leer la correspondiente normal 'n_i' del vector de normales
  //             ('nor_ver').
  //             - Añadir 'v_i' al vector 'segmentos_normales'.
  //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
  //
  //       * Crear el objeto descriptor del VAO de normales, para ello se usa el
  //       vector
  //          'segmentos_normales' y se tiene en cuenta que esa descriptor
  //          únicamente gestiona una tabla de atributos de vértices (la de
  //          posiciones, ya que las otras no se necesitan).
  //
  // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor,
  // con el
  //       tipo de primitiva 'GL_LINES'.
  if (dvao_normales == nullptr) {
    for (int i = 0; i < vertices.size(); i++) {
      segmentos_normales.push_back(vertices[i]);
      segmentos_normales.push_back(
          vertices[i] + 0.2f * nor_ver[i]); // 0.2f es el factor de longitud
    }
    DescrVBOAtribs *pos_dvbo =
        new DescrVBOAtribs(ind_atrib_posiciones, segmentos_normales);
    dvao_normales = new DescrVAO(1, pos_dvbo);
  }
  dvao_normales->draw(GL_LINES);
}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los
// colores basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() {

  using namespace std;
  assert(aplicacionIG != nullptr);
  Cauce *cauce = aplicacionIG->cauce;
  assert(cauce != nullptr);

  // COMPLETAR: práctica 5: visualizar la malla en modo selección
  //
  // Se debe escribir código para visualizar únicamente la geometría, pero
  // usando el color obtenido a partir del identificador. El código da estos
  // pasos:
  //
  // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto
  // tiene
  //    identificador (es decir, si su identificador no es -1)
  //       + Hacer push del color del cauce, con 'pushColor'.
  //       + Fijar el color del cauce (con 'fijarColor') usando un color
  //       obtenido a
  //         partir del identificador (con 'ColorDesdeIdent').
  // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
  // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
  //
  if (leerIdentificador() != -1) {
    cauce->pushColor();
    cauce->fijarColor(ColorDesdeIdent(leerIdentificador()));
  }
  visualizarGeomGL();
  if (leerIdentificador() != -1) {
    cauce->popColor();
  }
}

// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY(const std::string &nombre_arch) {
  ponerNombre(std::string("malla leída del archivo '") + nombre_arch + "'");

  // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
  // ..........................
  LeerPLY(nombre_arch, vertices, triangulos);

  // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de
  // normales
  // .................
  calcularNormales();
}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo() : MallaInd("cubo 8 vértices") {

  vertices = {
      {-1.0, -1.0, -1.0}, // 0
      {-1.0, -1.0, +1.0}, // 1
      {-1.0, +1.0, -1.0}, // 2
      {-1.0, +1.0, +1.0}, // 3
      {+1.0, -1.0, -1.0}, // 4
      {+1.0, -1.0, +1.0}, // 5
      {+1.0, +1.0, -1.0}, // 6
      {+1.0, +1.0, +1.0}, // 7
  };

  triangulos = {
      {0, 1, 3}, {0, 3, 2}, // X-
      {4, 7, 5}, {4, 6, 7}, // X+ (+4)

      {0, 5, 1}, {0, 4, 5}, // Y-
      {2, 3, 7}, {2, 7, 6}, // Y+ (+2)

      {0, 6, 4}, {0, 2, 6}, // Z-
      {1, 5, 7}, {1, 7, 3}  // Z+ (+1)
  };
  calcularNormales();
}

// ****************************************************************************
// Clase 'Tetraedro

Tetraedro::Tetraedro(const glm::vec3 &p_nuevo_color)
    : MallaInd("Tetraedro 4 vértices") {

  vertices = {
      {-1.0, -1.0, -1.0}, // 0
      {0.0, -1.0, +1.0},  // 1
      {+1.0, -1.0, -1.0}, // 2
      {0.0, +1.0, 0.0},   // 3
  };

  triangulos = {{0, 1, 2}, {0, 1, 3}, {1, 2, 3}, {0, 2, 3}};
  ponerColor(p_nuevo_color);
  calcularNormales();
}

// ****************************************************************************
// Clase 'CuboColores

CuboColores::CuboColores() : MallaInd("cubo 8 vértices con colores") {

  vertices = {
      {-1.0, -1.0, -1.0}, // 0
      {-1.0, -1.0, +1.0}, // 1
      {-1.0, +1.0, -1.0}, // 2
      {-1.0, +1.0, +1.0}, // 3
      {+1.0, -1.0, -1.0}, // 4
      {+1.0, -1.0, +1.0}, // 5
      {+1.0, +1.0, -1.0}, // 6
      {+1.0, +1.0, +1.0}, // 7
  };

  triangulos = {
      {0, 1, 3}, {0, 3, 2}, // X-
      {4, 7, 5}, {4, 6, 7}, // X+ (+4)

      {0, 5, 1}, {0, 4, 5}, // Y-
      {2, 3, 7}, {2, 7, 6}, // Y+ (+2)

      {0, 6, 4}, {0, 2, 6}, // Z-
      {1, 5, 7}, {1, 7, 3}  // Z+ (+1)
  };

  glm::vec<3, float> rgb_color;
  for (auto &vert : vertices) {
    rgb_color = {0.0, 0.0, 0.0};
    for (int i = 0; i < 3; i++) {
      if (vert[i] == -1.0)
        rgb_color[i] = 0.0;
      else if (vert[i] == 1.0)
        rgb_color[i] = 1.0;
    }
    col_ver.push_back(rgb_color);
  }
}

// ****************************************************************************
// Clase 'EstrellaZ

EstrellaZ::EstrellaZ(uint n) : MallaInd("Estrella de n puntas") {
  glm::vec3 centro = {0.5, 0.5, 0.0};
  float radio_mayor = 0.5;
  float radio_menor = radio_mayor / 2;
  vertices.push_back(centro);
  col_ver.push_back({1.0, 1.0, 1.0});

  float angulo = 360 / n;

  for (int i = 0; i < n; i++) {
    // Para vertices mayores
    float vert_x = centro[0] + radio_mayor * cos(glm::radians(angulo * i));
    float vert_y = centro[1] + radio_mayor * sin(glm::radians(angulo * i));
    vertices.push_back({vert_x, vert_y, 0.0});
    col_ver.push_back({vert_x, vert_y, 0.0});

    // Para vertices interiores
    vert_x =
        centro[0] + radio_menor * cos(glm::radians(angulo * i + angulo / 2));
    vert_y =
        centro[1] + radio_menor * sin(glm::radians(angulo * i + angulo / 2));
    vertices.push_back({vert_x, vert_y, 0.0});
    col_ver.push_back({vert_x, vert_y, 0.0});
  }

  uint vert1 = 1, vert2 = 2;
  for (int i = 0; i < 2 * n; i++) {
    triangulos.push_back({0, vert1, vert2});
    if (i % 2 == 0) {
      vert1 += 2;
    } else {
      vert2 += 2;
    }

    if (vert1 > 2 * n) {
      vert1 = 1;
    }
  }
}

// ****************************************************************************
// Clase 'CasaX
CasaX::CasaX() : MallaInd("CasaX con colores") {
  vertices = {
      {0.0, 0.0, 0.0},      // 0
      {0.0, 0.0, +0.75},    // 1
      {0.0, +0.75, 0.0},    // 2
      {0.0, +0.75, +0.75},  // 3
      {+1.0, 0.0, 0.0},     // 4
      {+1.0, 0.0, +0.75},   // 5
      {+1.0, +0.75, 0.0},   // 6
      {+1.0, +0.75, +0.75}, // 7
      {0.0, 1.0, 0.385},    // 8
      {1.0, 1.0, 0.385},    // 9
  };

  triangulos = {
      {0, 1, 3},
      {0, 3, 2}, // X-
      {4, 7, 5},
      {4, 6, 7}, // X+ (+4)

      // {0, 5, 1}, {0, 4, 5}, // Y-
      {3, 8, 9},
      {7, 3, 9}, // Y+ (+2)
      {2, 8, 9},
      {6, 2, 9}, // Y+ (+2)

      // Triangulos
      {2, 3, 8}, // Y+ (+2)
      {6, 7, 9}, // Y+ (+2)

      {0, 6, 4},
      {0, 2, 6}, // Z-
      {1, 5, 7},
      {1, 7, 3} // Z+ (+1)
  };

  for (auto &vert : vertices) {
    col_ver.push_back(vert);
  }
}

// ****************************************************************************
// Clase 'MallaTriangulo
MallaTriangulo::MallaTriangulo() : MallaInd("MallaTriangulo") {
  vertices = {
      {0.0, 0.0, 0.0},
      {0.0, std::sqrt(2.0), 0.0},
      {1.0, 0.0, 0.0},
  };
  triangulos = {
      {0, 1, 2},
  };
}

// ****************************************************************************
// Clase 'MallaCuadrado
MallaCuadrado::MallaCuadrado() : MallaInd("MallaCuadrado") {
  vertices = {
      {0.0, 0.0, 0.0},
      {0.0, 2.0, 0.0},
      {2.0, 0.0, 0.0},
      {2.0, 2.0, 0.0},
  };
  triangulos = {
      {0, 1, 2},
      {1, 2, 3},
  };
}

// ****************************************************************************
// Clase 'MallaPiramideL
MallaPiramideL::MallaPiramideL() : MallaInd("MallaPiramideL") {
  vertices = {
      {0.0, 0.0, 0.0}, // esquina 1
      {2.0, 0.0, 0.0}, // esquina 2
      {0.0, 0.0, 2.0}, // esquina 3
      {1.0, 0.0, 1.0}, // centro inferior
      {1.0, 2.0, 1.0}, // centro superior
      {2.0, 0.0, 1.0}, // esquina mitad 1
      {1.0, 0.0, 2.0}, // esquina mitad 2
  };
  triangulos = {
      // BASE
      {0, 1, 2},
      {1, 5, 3},
      {2, 6, 3},
      // Caras grandes
      {0, 1, 4},
      {0, 2, 4},
      // Caras pequeñas
      {1, 5, 4},
      {2, 6, 4},
      // Caras internas
      {3, 4, 5},
      {3, 4, 6},
  };
}
// ****************************************************************************
// Clase 'PiramideEstrellaZ

PiramideEstrellaZ::PiramideEstrellaZ(uint n)
    : MallaInd("Estrella de n puntas") {
  glm::vec3 centro = {0.5, 0.5, 0.0};
  float radio_mayor = 0.5;
  float radio_menor = radio_mayor / 2;
  vertices.push_back(centro);
  col_ver.push_back({1.0, 1.0, 1.0});

  float angulo = 360.0 / static_cast<float>(n);

  for (int i = 0; i < n; i++) {
    // Para vertices mayores
    float vert_x = centro[0] + radio_mayor * cos(glm::radians(angulo * i));
    float vert_y = centro[1] + radio_mayor * sin(glm::radians(angulo * i));
    vertices.push_back({vert_x, vert_y, 0.0});
    col_ver.push_back({vert_x, vert_y, 0.0});

    // Para vertices interiores
    vert_x =
        centro[0] + radio_menor * cos(glm::radians(angulo * i + angulo / 2));
    vert_y =
        centro[1] + radio_menor * sin(glm::radians(angulo * i + angulo / 2));
    vertices.push_back({vert_x, vert_y, 0.0});
    col_ver.push_back({vert_x, vert_y, 0.0});
  }

  vertices.push_back({0.5, 0.5, 0.5});
  col_ver.push_back({1.0, 1.0, 1.0});

  uint vert1 = 1, vert2 = 2;
  for (int i = 0; i < 2 * n; i++) {
    triangulos.push_back({0, vert1, vert2});
    if (i < 2 * n) {
      triangulos.push_back({vertices.size() - 1, vert1, vert2});
    }
    if (i % 2 == 0) {
      vert1 += 2;
    } else {
      vert2 += 2;
    }

    if (vert1 > 2 * n) {
      vert1 = 1;
    }
  }
}
// EstrellaPiramideZ::EstrellaPiramideZ(unsigned n)
//     : MallaInd(" Estrella de n vértices") {
//
//   float cordX_Central = 0.5;
//   float cordY_Central = 0.5;
//   float cordZ_Central = 0.5;
//   float radio = 0.5;
//
//   vertices.push_back({cordX_Central, cordY_Central, 0});
//   col_ver.push_back({1, 1, 1});
//
//   float x;
//   float y;
//   float x1;
//   float y1;
//
//   float angulo_ini = (360 / n) * M_PI / 180;
//   float angulo_ini_abajo = angulo_ini / 2;
//   float angulo = 0;
//   float angulo_abajo = angulo_ini_abajo;
//
//   for (unsigned i = 0; i < n; i++) {
//
//     x1 = cordX_Central + (radio / 2) * cos(angulo_abajo);
//     y1 = cordY_Central + (radio / 2) * sin(angulo_abajo);
//     vertices.push_back({x1, y1, 0});
//     col_ver.push_back({x1, y1, 0});
//     angulo_abajo += angulo_ini;
//
//     angulo += angulo_ini;
//     x = cordX_Central + radio * cos(angulo);
//     y = cordY_Central + radio * sin(angulo);
//     vertices.push_back({x, y, 0});
//     col_ver.push_back({x, y, 0});
//   }
//
//   vertices.push_back({cordX_Central, cordY_Central, cordZ_Central});
//
//   for (unsigned i = 1; i < 2 * n; i++) {
//
//     triangulos.push_back({0, i, i + 1});
//     triangulos.push_back({0, i, 2 * n + 1});
//   }
//
//   triangulos.push_back({0, 1, 2 * n});
//   triangulos.push_back({0, 2 * n, 2 * n + 1});
// }

// ****************************************************************************
// Clase 'RejillaY
RejillaY::RejillaY(uint n, uint m) : MallaInd("Rejilla en plano Y") {
  float x_incr = 1.0 / (n - 1);
  float z_incr = 1.0 / (m - 1);

  for (float i = 0; i < n; i++) {

    for (float j = 0; j < m; j++) {
      vertices.push_back({i * x_incr, 0, j * z_incr});
      col_ver.push_back({i * x_incr, 0, j * z_incr});
    }
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < m - 1; j++) {
      triangulos.push_back({i * m + j, i * m + j + 1, (i + 1) * m + j});
      triangulos.push_back(
          {i * m + j + 1, (i + 1) * m + j + 1, (i + 1) * m + j});
    }
  }
}

// ****************************************************************************
// Clase 'MallaTorre
MallaTorre::MallaTorre(uint n) : MallaInd("Malla torre con n plantas") {
  const float size = 0.5;
  const int altura = 1;

  for (int i = 0; i < n; i++) {
    vertices.push_back({size, i * altura, size});
    vertices.push_back({size, i * altura, -size});
    vertices.push_back({-size, i * altura, -size});
    vertices.push_back({-size, i * altura, size});

    vertices.push_back({size, (i + 1) * altura, size});
    vertices.push_back({size, (i + 1) * altura, -size});
    vertices.push_back({-size, (i + 1) * altura, -size});
    vertices.push_back({-size, (i + 1) * altura, size});
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      glm::uvec3 t1, t2;
      if (j == 3) {
        t1 = {i * 8 + j, i * 8, i * 8 + 4 + j};
        t2 = {i * 8, i * 8 + 4 + j, i * 8 + 4};
      } else {
        t1 = {i * 8 + j, i * 8 + j + 1, i * 8 + 4 + j};
        t2 = {i * 8 + j + 1, i * 8 + 4 + j, i * 8 + 4 + j + 1};
      }
      triangulos.push_back(t1);
      triangulos.push_back(t2);
      // std::cout << "t1: " << glm::to_string(t1) << std::endl;
      // std::cout << "t2: " << glm::to_string(t2) << std::endl;
    }
  }
}
// ****************************************************************************
// Clase 'Cubo24

Cubo24::Cubo24() : MallaInd("cubo 24 vértices") {

  vertices = {
      {-1.0, -1.0, -1.0}, // 0
      {-1.0, -1.0, +1.0}, // 1
      {-1.0, +1.0, -1.0}, // 2
      {-1.0, +1.0, +1.0}, // 3
      {+1.0, -1.0, -1.0}, // 4
      {+1.0, -1.0, +1.0}, // 5
      {+1.0, +1.0, -1.0}, // 6
      {+1.0, +1.0, +1.0}, // 7

      {-1.0, -1.0, -1.0}, // 8
      {-1.0, -1.0, +1.0}, // 9
      {-1.0, +1.0, -1.0}, // 10
      {-1.0, +1.0, +1.0}, // 11
      {+1.0, -1.0, -1.0}, // 12
      {+1.0, -1.0, +1.0}, // 13
      {+1.0, +1.0, -1.0}, // 14
      {+1.0, +1.0, +1.0}, // 15

      {-1.0, -1.0, -1.0}, // 16
      {-1.0, -1.0, +1.0}, // 17
      {-1.0, +1.0, -1.0}, // 18
      {-1.0, +1.0, +1.0}, // 19
      {+1.0, -1.0, -1.0}, // 20
      {+1.0, -1.0, +1.0}, // 21
      {+1.0, +1.0, -1.0}, // 22
      {+1.0, +1.0, +1.0}, // 23
  };

  triangulos = {
      {0, 1, 3},    {0, 3, 2}, // X-          0
      {4, 7, 5},    {4, 6, 7}, // X+ (+4)     2

      {8, 13, 9},   {8, 12, 13},  // Y-             4
      {10, 11, 15}, {10, 15, 14}, // Y+ (+2)     6

      {16, 22, 20}, {16, 18, 22}, // Z-          8
      {17, 21, 23}, {17, 23, 19}  // Z+ (+1)     10
  };

  // calculamos las coordenadas de textura
  cc_tt_ver = {
      {0.0, 1.0}, {1.0, 1.0}, {0.0, 0.0}, {1.0, 0.0},
      {1.0, 1.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0},

      {0.0, 1.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 1.0},
      {1.0, 1.0}, {1.0, 0.0}, {1.0, 0.0}, {1.0, 1.0},

      {1.0, 1.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0},
      {0.0, 1.0}, {1.0, 1.0}, {0.0, 0.0}, {1.0, 0.0},
  };
  calcularNormales();
}

MallaDiscoP4::MallaDiscoP4() : MallaInd("DiscoP4") {
  ponerColor({1.0, 1.0, 1.0});
  const unsigned ni = 23, nj = 31;
  for (unsigned i = 0; i < ni; i++)
    for (unsigned j = 0; j < nj; j++) {
      const float fi = float(i) / float(ni - 1), fj = float(j) / float(nj - 1),
                  ai = 2.0 * M_PI * fi, x = fj * cos(ai), y = fj * sin(ai),
                  z = 0.0;
      vertices.push_back({x, y, z});
    }
  for (unsigned i = 0; i < ni - 1; i++)
    for (unsigned j = 0; j < nj - 1; j++) {
      triangulos.push_back(
          {i * nj + j, i * nj + (j + 1), (i + 1) * nj + (j + 1)});
      triangulos.push_back(
          {i * nj + j, (i + 1) * nj + (j + 1), (i + 1) * nj + j});
    }

  // Ejercicio Adicional 1
  // for (auto &vert : vertices) {
  //   cc_tt_ver.push_back({(vert.x + 1) / 2, (vert.y + 1) / 2});
  // }
  // Ejercicio Adicional 2
  for (unsigned i = 0; i < vertices.size(); i++) {
    float r = sqrt(pow(vertices[i].x, 2) + pow(vertices[i].y, 2));
    cc_tt_ver.push_back({acos(vertices[i].x / r) / (2 * M_PI), r});
  }
}

// -----------------------------------------------------------------------------------------------
