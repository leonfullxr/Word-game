/**
 * @file cantidad_letras.cpp
 * @brief Archivo que implementa unas pruebas para Dictionary
 * @details Se le han de pasar 2 argumentos, el primero, una ruta hasta un archivo desde el que cargar el LettersSet y
 * el segundo otra ruta hasta un archivo desde el que cargar el Dictionary. Imprime por pantalla por cada letra, el
 * numero de ocurrencias de la letra en el diccionario y su frecuenia relativa
 *
 * <strong>Ejemplo ejecución:</strong>\n
 * Orden: cantidad_letras ./data/diccionario_pub.txt \n
 * Output:\n
 * Letra	FAbs.	Frel.\n todo - esto esta mal
 *  A	2	0.0210526\n
 *  E	14	0.147368\n
 *  I	6	0.0631579\n
 *  O	8	0.0842105\n
 *  U	8	0.0842105\n
 */

#include <iostream>
#include "dictionary.h"
#include "fstream"
#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=3){
        cout << "Error, se deben introducir 2 argumentos --> <fichero_palabras> <fichero_letras> " << endl;
    }

    string fichero_palabras = argv[1];       //fichero con las palabras del diccionario
    string fichero_letras = argv[2];   //longitud de palabras
    Dictionary diccionario;         //Declaramos el diccionario
    LettersSet conjunto_letras;      //Declaramos el LetterSet
    ifstream archivo_palabras;
    ifstream archivo_letras;
    string palabra;

    archivo_palabras.open(fichero_palabras);
    if (!archivo_palabras.is_open())
    {
        cerr << "Error al abrir " << fichero_palabras << endl;
        exit(EXIT_FAILURE);
    }

    while(archivo_palabras >> palabra){
        diccionario.insert(palabra);
    }
    archivo_palabras.close(); //no se si hace falta la vd

    archivo_letras.open(fichero_letras);
    if(!archivo_letras.is_open()){
        cerr << "Error al abrir " << fichero_letras << endl;
        exit(EXIT_FAILURE);
    }
    archivo_letras >> conjunto_letras;
    archivo_letras.close();

    cout << "Letra\tUsos.\tOcurrencias." << endl;
    for(LettersSet::iterator it=conjunto_letras.begin(); it!=conjunto_letras.end(); it.operator++()){
        cout <<  it.operator*().first << "\t" << diccionario.getTotalUsages(it.operator*().first) << "\t" << diccionario.getOccurrences(it.operator*().first) << endl;
    }

}