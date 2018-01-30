# IncidenciasCyL-cli
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=GRXHT9CGJ4L7G)
[![Website](https://img.shields.io/website-up-down-green-red/http/shields.io.svg?label=my-website)](https://davidpob99.github.io/IncidenciasCyL/)

Programa de terminal para visualizar las incidencias en las carreteras de Castilla y León.

## Instalación

Antes de proceder a la instalación, es necesario tener libcurl y jsoncpp instalados. En Debian y derivados dichos paquetes son `libcurl-dev`, `libcurl4-gnutls-dev` y `libjsoncpp-dev`.

1. `git clone https://github.com/davidpob99/incidenciascyl-cli` o descargar y descomprimir el zip del repositorio
2. `cd incidenciascyl-cli`
3. `chmod -x INSTALL`
4. `sudo sh INSTALL`

## Desinstalación
Ejecutar el archivo UNINSTALL de forma similar a la instalación

## Compilación
Es necesario tener instalado jsoncpp, libcurl y g++. Todos ellos se pueden obtener desde los repositorios de la distribución UNIX que se esté usando.
`g++ -std=c++11 main.cpp -ljsoncpp -lcurl`

Si se tiene codeblocks, se puede abrir el proyecto desde incidenciascyl-cli.cbp

## Ayuda
La lista completa de opciones se puede obtener ejecutando: `incidenciascyl-cli -h`