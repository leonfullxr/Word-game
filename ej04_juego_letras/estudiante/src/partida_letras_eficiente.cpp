/**
 * @file partida_letras_eficiente.cpp
 * @brief Archivo que implementa unas pruebas para solver_eficiente
 * @details Se le han de pasar 4 argumentos, el primero, una ruta hasta un archivo desde el que cargar el Diccionario,
 * el segundo otra ruta hasta un archivo desde el que cargar el LetterSet, el tercero una letra 'L' que indica que el
 * juego se hara por longitud de palabra o 'P' que indica que se hara por puntuacion y el ultimo argumento un numero
 * entero para indicar cuatas letras se van a usar. Imprime por pantalla por cada letra, el numero de ocurrencias de
 * la letra en el diccionario y su frecuenia relativa
 *
 * <strong>Ejemplo ejecución:</strong>\n
 * Orden: partida_letras_eficiente ./data/diccionario.txt ./data/letras.txt L 9 \n
 *
 */

#include <iostream>
#include "dictionary.h"
#include "letters_set.h"
#include <fstream>
#include "letters_bag.h"
#include "solver_eficiente.h"

int main(int argc, char *argv[]){
    if(argc!=5){
        cout << "Error, se deben introducir 4 argumentos --> <fichero_palabras> <fichero_letras> <modo_juego> <cantidad_letras> " << endl;
    }

    string fichero_palabras = argv[1];       //fichero con las palabras del diccionario
    string fichero_letras = argv[2];   //longitud de palabras
    bool modo_de_juego = argv[3] == "P" ? true : false;       //Longitud false, Puntuacion true
    int cantidad_letras = stoi(argv[4]);
    Dictionary diccionario;         //Declaramos el diccionario
    LettersSet conjunto_letras;      //Declaramos el LetterSet

    ifstream archivo_palabras;
    ifstream archivo_letras;
    string palabra;

    archivo_palabras.open(fichero_palabras);
    if (!archivo_palabras.is_open())
    {
        cout << "Error al abrir " << fichero_palabras;
        exit(EXIT_FAILURE);
    }

    while(archivo_palabras >> palabra){
        diccionario.insert(palabra);
    }
    archivo_palabras.close();

    archivo_letras.open(fichero_letras);
    if(!archivo_letras.is_open()){
        cout << "Error al abrir " << fichero_letras;
        exit(EXIT_FAILURE);
    }
    archivo_letras >> conjunto_letras;
    archivo_letras.close();

    LettersBag bolsa_letras(conjunto_letras);
    vector<char> available_letters;

    for(int i = 0; i < cantidad_letras; i++)
        available_letters.push_back(bolsa_letras.extractLetter());

    solver_eficiente programa(diccionario,conjunto_letras);

    pair<vector<string>,int> soluciones = programa.getSolutions(available_letters,modo_de_juego);

    cout << "LETRAS DISPONIBLES:" << endl;
    for(auto letra : available_letters)
        cout << letra << " ";
    cout << endl;
    cout << "SOLUCIONES:" << endl;
    for(auto palabra : soluciones.first)
        cout << palabra << endl;
    cout << "PUNTUACION:" << endl;
    cout << soluciones.second;
}
