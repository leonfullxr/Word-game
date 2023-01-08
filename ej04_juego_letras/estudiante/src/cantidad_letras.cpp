/**
 * @file cantidad_letras.cpp
 * @brief Archivo que implementa unas pruebas para Dictionary
 * @details Se le han de pasar 2 argumentos, el primero, una ruta hasta un archivo desde el que cargar el Dictionary y
 * el segundo otra ruta hasta un archivo desde el que cargar el LetterSet. Imprime por pantalla por cada letra, el
 * numero de ocurrencias de la letra en el diccionario y su frecuenia relativa
 *
 * <strong>Ejemplo ejecución:</strong>\n
 * Orden: cantidad_letras ./data/diccionario_mini.txt ./data/letras_mini.txt \n
 * Output:\n
 * Letra\tUsos\tOcurrencias\n
 * A\t8\t3\n
 * C\t3\t1\n
 * L\t2\t2\n
 * M\t4\t1\n
 * O\t4\t2\n
 * R\t2\t2\n
 * Z\t1\t1\n
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

    cout << "Letra\tUsos\tOcurrencias" << endl;
    for(LettersSet::iterator it=conjunto_letras.begin(); it!=conjunto_letras.end(); it.operator++()){
        cout <<  it.operator*().first << "\t" << diccionario.getTotalUsages(it.operator*().first) << "\t" << diccionario.getOccurrences(it.operator*().first) << endl;
    }

}