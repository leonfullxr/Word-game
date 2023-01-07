/**
 * @file palabras_validas_diccionario.cpp
 * @brief Archivo donde se implementa una prueba para el iteador de palabras validas de Dictonary
 * @details El primer argumento que se le debe pasar es el arcivo desde el cual cargar el diccionario.
 * A continuacion se la pasan las letras disponibles, cada una como un argumento
 *
 * El programa cargará el diccionario y imprimirá las palabras que se puedan formar con las letras especificadas,
 * recorriendo el diccionario con el iterador de palabras validas
 *
 * <strong>Ejemplo de ejecución:</strong>\n
 * Orden: palabras_validas_diccionario ./data/diccionario.txt e i l n p\n
 * Output:\n
 * e\n
 * el\n
 * en\n
 * i\n
 * in\n
 * l\n
 * le\n
 * len\n
 * n\n
 * ne\n
 * ni\n
 * niel\n
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    ifstream dict_file(argv[1]);
    vector <char> available_letters;
    for (int i = 2; i < argc; ++i) {
        available_letters.push_back(std::tolower(argv[i][0]));
    }
    if(!dict_file){
        cerr << "No puedo abrir el fichero " << argv[1] << endl;
        return 0;
    }

    Dictionary dictionary;
    dict_file >> dictionary;
    dict_file.close();

    vector <string> available_words;
    for (auto it = dictionary.possible_words_begin(available_letters); it != dictionary.possible_words_end(); ++it) {
        available_words.push_back(*it);
    }

    for (auto word: available_words){
        cout << word << endl;
    }

    return 0;
}
