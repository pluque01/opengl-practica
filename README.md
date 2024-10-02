# Un ejemplo OpenGL mínimo (usando OpenGL 3.3)

En esta carpeta se encuentra el código fuente mínimo de una programa OpenGL en C++, suficiente para dibujar un triángulo. Se usa exclusivamente funcionalidad de OpenGL 3.3, y por tanto se requiere esa versión como mínimo. Los fuentes se pueden compilar y ejecutar Linux, MacOS o Windows. Se usan las librerías GLFW (para gestión de ventanas), GLM (vectores y matrices) y GLEW (acceso a funciones de OpenGL de la versión 3, únicamente en Linux y Windows).

1. [Requisitos](#Requisitos)
   - 1.1 [Linux](#ReqLinux)
1. [Clonar este repositorio](#ClonarRepo)
1. [Compilar y ejecutar](#CompilarEjecutar)
1. [Uso de _VS Code_](#vscode)

## 1. <a name='Requisitos'>Requisitos</a>

### 1.1 <a name='ReqLinux'>Linux</a>

En linux es necesario tener instalado el compilador de C++ de GNU o del proyecto LLVM, esto permite invocar la orden `g++` y la orden `make`. Si no se tienen disponibles, estas herramientas se pueden instalar con la orden:

```
sudo apt install build-essential
```

Se debe usar _apt_ para instalar _cmake_, que se usa para poder compilar fácilmente el ejemplo, se hace con:

```
sudo apt install cmake
```

Finalmente se deben instalar los paquetes _libglew-dev_, _libglfw3-dev_ y _libglm-dev_ (tienen las librerías que se usan en estos fuentes, es decir *GLEW*, *GLFW* y *GLM*), se puede hacer con:

```
sudo apt install libglew-dev
sudo apt install libglfw3-dev
sudo apt install libglm-dev
```

## 2. <a name='ClonarRepo'></a>Clonar este repositorio</a>

Para clonar el repositorio se necesita ejecutar:

```
git clone https://github.com/carlos-urena/opengl3-minimo.git [subcarpeta]
```

donde `[subcarpeta]` es opcional, si se especifica designa el path relativo de una subcarpeta donde quedará alojado el repositorio.

## 3. <a name='CompilarEjecutar'></a>Compilar y Ejecutar</a>

Para la generación de los archivos de compilación y la compilación en sí se usa `cmake`, para ello es necesario ir a la carpeta `builds/macos` o `builds/linux`, según el sistema operativo. En esa carpeta debemos asegurarnos de que la sub-carpeta `cmake` está vacía (si no lo estaba ya, hay que borrar todos los archivos ahí, excepto `.gitignore`).  Para generar los archivos de compilación, hay que hacer entrar a la carpeta `cmake` y ahí escribir:

```
cmake ..
```

Esto hay que hacerlo una vez, o cada vez que se añadan nuevos fuentes o se quiera cambiar la configuración de compilación. Esto genera diversos archivos y carpetas en `cmake`. Después, para compilar los fuentes, hay que ejecutar (en esa misma carpeta):

```
make
```

Si la compilación va bien se genera el ejecutable, que tiene el nombre  `debug_exe` y está en la carpeta `bin`. La orden `make` también se puede usar con un argumento para otros fines:

- `make clean` para eliminar el programa compilado y los archivos asociados.
- `make release_exe` para generar el ejecutable `release_exe` (también en `bin`), el cual no tiene los símbolos de depuración y además está optimizado (es más pequeño y puede que sea más rápido al ejecutarse)

Para forzar un recompilado de todos los fuentes, basta con vaciar la carpeta `cmake` y volver a hacer `cmake ..` en ella. Es necesario hacerlo si se añaden o quitan unidades de compilación o cabeceras de las carpetas con los fuentes.
