# IncidenciasCyL-cli
Programa de terminal para visualizar las incidencias en las carreteras de Castilla y León.

## Modo de empleo
incidenciascyl-cli <opciones>

Argumentos sin parámetros:
	-l	imprime la licencia del programa
	-h	imprime la ayuda
Argumentos con parámetros:
	-p	selecciona la provincia de la que se quieren obtener los datos.
		Ejemplo: incidenciascyl-cli -p Valladolid
	-v	selecciona la vía de la que se quieren obtener los datos.
		Ejemplo: incidenciascyl-cli -v CL-605

Si no se especifica ningún parámetro se imprimen todos las incidencias encontradas en Castilla y León.

## Instalación
`git clone https://github.com/davidpob99/incidenciascyl-cli` o descargar y descomprimir el zip del repositorio
`cd incidenciascyl-cli`
`chmod -x INSTALL`
`sudo sh INSTALL`

## Desinstalación
Ejecutar el archivo UNINSTALL de forma similar a la instalación

## Compilación
Es necesario tener instalado jsoncpp, libcurl y g++. Todos ellos se pueden obtener desde los repositorios de la distribución UNIX que se esté usando.
`g++ -std=c++11 main.cpp -ljsoncpp -lcurl`

Si se tiene codeblocks, se puede abrir el proyecto desde incidenciascyl-cli.cbp