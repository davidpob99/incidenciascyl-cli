/*
    IncidenciasCyL-cli
    @author David Población Criado
    @version 1.0 25/01/2018
*/

#define CURL_STATICLIB
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <curl/curl.h>
#include <json/json.h>

void imprimir(std::string provincia, std::string via, double pkinicio, double pkfin, std::string tramo, std::string tipo, std::string causa, std::string calzada, std::string observaciones,
              std::string fechaalta, std::string rutaalt, std::string masinfo);
void imprimirLicencia();
void imprimirAyuda();

namespace
{
std::size_t callback(
    const char* in,
    std::size_t size,
    std::size_t num,
    char* out)
{
    std::string data(in, (std::size_t) size * num);
    *((std::stringstream*) out) << data;
    return size * num;
}
}

int main( int argc, char **argv )
{
    char *mprovincia;
    bool bprovincia = false;
    char *mvia;
    bool bvia = false;

    int opt;

    while ((opt = getopt(argc, argv, "p:v: lh")) != -1)
    {

        switch (opt)
        {
        case 'p':
            mprovincia = optarg;
            bprovincia = true;
            break;
        case 'v':
            mvia = optarg;
            bvia = true;
            break;
        case 'l':
            imprimirLicencia();
            return 0;
        case 'h':
            imprimirAyuda();
            return 0;
        }
    }
    // Informacion y licencia
    std::cout << "IncidenciasCyL-cli v1.0" << std::endl;
    std::cout << "Copyright 2018 David Población Criado" << std::endl;
    std::cout << "Apache License, Version 2.0" << std::endl;
    std::cout << std::endl;
    std::cout << "De los datos: CC-BY Junta de Castilla y León (https://datosabiertos.jcyl.es/)" << std::endl;

    // CURL
    const std::string url("https://datosabiertos.jcyl.es/web/jcyl/risp/es/transporte/incidencias_carreteras/1284212099243.json");

    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    int httpCode(0);
    // std::unique_ptr<std::string> httpData(new std::string());

    std::stringstream httpData;

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    //Si es correcta la peticion
    if (httpCode == 200)
    {

        Json::Value jsonData;
        Json::CharReaderBuilder jsonReader;
        std::string errs;

        if (Json::parseFromStream(jsonReader, httpData, &jsonData, &errs))
        {
            const std::string fecha(jsonData["fecha"].asString());
            std::cout << "Fecha de los datos: " << fecha << std::endl;
            std::cout << "---------"<< std::endl;
            const Json::Value incidencias = jsonData["incidencias"];
            for (Json::Value::ArrayIndex i = 0; i != incidencias.size(); i++)
            {
                std::string provincia(incidencias[i].get("Provincia", "ASCII").asString());
                std::string via(incidencias[i].get("Via", "ASCII").asString());
                double pkinicio(incidencias[i].get("PKInicio", "ASCII").asDouble());
                double pkfin(incidencias[i].get("PKFin", "ASCII").asDouble());
                std::string tramo(incidencias[i].get("Tramo", "ASCII").asString());
                std::string tipo(incidencias[i].get("Tipo", "ASCII").asString());
                std::string causa(incidencias[i].get("Causa", "ASCII").asString());
                std::string calzada(incidencias[i].get("Calzada", "ASCII").asString());
                std::string observaciones(incidencias[i].get("Observaciones", "ASCII").asString());
                std::string fechaalta(incidencias[i].get("FechaAlta", "ASCII").asString());
                std::string rutaalt(incidencias[i].get("RutaAlt", "ASCII").asString());
                std::string masinfo(incidencias[i].get("MasInfo", "ASCII").asString());

                if(!bprovincia && !bvia) imprimir( provincia, via, pkinicio, pkfin, tramo, tipo, causa, calzada, observaciones, fechaalta, rutaalt, masinfo);
                else
                {
                    if(bprovincia && bvia)
                    {
                        if(provincia == mprovincia && via == mvia) imprimir( provincia, via, pkinicio, pkfin, tramo, tipo, causa, calzada, observaciones, fechaalta, rutaalt, masinfo);
                    }
                    else if(bprovincia && !bvia)
                    {
                        if(provincia == mprovincia) imprimir( provincia, via, pkinicio, pkfin, tramo, tipo, causa, calzada, observaciones, fechaalta, rutaalt, masinfo);
                    }
                    else if(!bprovincia && bvia)
                    {
                        if(via == mvia) imprimir( provincia, via, pkinicio, pkfin, tramo, tipo, causa, calzada, observaciones, fechaalta, rutaalt, masinfo);
                    }
                }


            }
        }
        else
        {
            // Devuelve un codigo distinto al 200
            std::cout << "No se pueden obtener los datos. Revise su configuración y el proxy." << std::endl;
            std::cout << "HTTP data was:\n" << httpData.str() << std::endl;
            return 1;
        }
    }
    else
    {
        // No hay conexion a Internet
        std::cout << "No se pueden obtener los datos. Revise su conexión a Internet." << std::endl;
        return 1;
    }

    return 0;
}
void imprimir(std::string provincia, std::string via, double pkinicio, double pkfin, std::string tramo, std::string tipo, std::string causa, std::string calzada, std::string observaciones,
              std::string fechaalta, std::string rutaalt, std::string masinfo)
{
    std::cout << "Provincia: " << provincia << std::endl;
    std::cout << "Vía: " << via << std::endl;
    std::cout << "KM inicio: " << pkinicio << std::endl;
    std::cout << "KM fin: " << pkfin << std::endl;
    std::cout << "Tramo: " << tramo << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Causa: " << causa << std::endl;
    std::cout << "Calzada: " << calzada << std::endl;
    std::cout << "Observaciones: " << observaciones << std::endl;
    std::cout << "Fecha de alta: " << fechaalta << std::endl;
    std::cout << "Ruta alternativa: " << rutaalt << std::endl;
    std::cout << "Mas información: " << masinfo << std::endl;
    std::cout << "---------"<< std::endl;

}

void imprimirLicencia()
{
    std::cout << "Copyright 2018 David Población Criado\n\nLicensed under the Apache License, Version 2.0 (the 'License');\nyou may not use this file except in compliance with the License.\nYou may obtain a copy of the License at\n\n    http://www.apache.org/licenses/LICENSE-2.0\n\nUnless required by applicable law or agreed to in writing, software\ndistributed under the License is distributed on an 'AS IS' BASIS,\nWITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\nSee the License for the specific language governing permissions and\nlimitations under the License."<<std::endl;
}
void imprimirAyuda()
{
    std::cout << "IncidenciasCyL-cli es una aplicación de terminal (o consola) disponible para máquinas UNIX (incluidos sus derivados como GNU/Linux o MacOS) y Windows.\nObtiene las incidencias en las carreteras de titularidad de la Junta de Castilla y León desde su portal de datos abiertos.\n\nModo de empleo: incidenciascyl-cli <opciones>\n\nArgumentos sin parámetros:\n	-l	imprime la licencia del programa\n	-h	imprime la ayuda\nArgumentos con parámetros:\n	-p	selecciona la provincia de la que se quieren obtener los datos.\n		Ejemplo: incidenciascyl-cli -p Valladolid\n	-v	selecciona la vía de la que se quieren obtener los datos.\n		Ejemplo: incidenciascyl-cli -v CL-605\n\nSi no se especifica ningún parámetro se imprimen todos las incidencias encontradas en Castilla y León.\n\nCódigo fuente del programa: https://github.com/davidpob99/incidenciascyl-cli/\nPágina web del desarrollador: https://davidpob99.github.io/" << std::endl;

}
