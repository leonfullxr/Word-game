/**
 * @file diccionario.cpp
 * @brief Archivo donde se implementa una prueba para el iteador de Dictonary
 * @details El único argumento que se le debe pasar es el arcivo desde el cual cargar el diccionario
 *
 * El programa cargará el diccionario y recorriendolo con el iterador imprimirá su contenido
 *
 * <strong>Ejemplo de ejecución:</strong>\n
 * Orden: diccionario ./data/diccionario_mini.txt 6\n
 * Output:\n
 * a\n
 * ama\n
 * amar\n
 * amo\n
 * amor\n
 * cal\n
 * col\n
 * coz\n
 */

#include <fstream>
#include <iostream>

#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 2){
    cout << "Los parametros son: " << endl;
    cout << "1.- El fichero con el diccionario" << endl;
    return 1;
  }

  ifstream f_diccionario(argv[1]);

  if(!f_diccionario){
    cout << "No puedo abrir el fichero " << argv[1] << endl;
    return 0;
  }

  Dictionary diccionario;
  f_diccionario >> diccionario;
  f_diccionario.close();

  for (Dictionary::iterator it = diccionario.begin(); it != diccionario.end(); ++it){
    cout << *it << endl;
  }

  return 0;
}
