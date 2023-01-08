/**
 * @file partida_letras_eficiente.cpp
 * @brief Archivo donde se realiza la ejecucion del solver eficiente
 * @details Se le deben pasar 4 argumentos, el primero siendo una ruta a un fichero donde
 * cargar el diccionario, el segundo una ruta donde cargar el LetterSet, el tercero una letra
 * 'L' o 'P' indicando si la partida se realizara a longitud o puntuacion de palabras y por
 * ultimo el cuarto argumento siendo un entero que indique el numero de letras que se van a usar.
 *
 * El programa cargará el diccionario y el LetterSet, para luego hacer que el iterador eficiente
 * recorra las palabras validas y se impriman por pantalla
 *
 * <strong>Ejemplo de ejecución:</strong>\n
 * Orden: partida_letras_eficiente data/diccionario.txt data/letras.txt L 9\n
 * Output:\n
 * LETRAS DISPONIBLES:\n
 * E O I E C I L X O \n
 * SOLUCIONES:\n
 * eolico\n
 * exilio\n
 * lexico\n
 * oleico\n
 * PUNTUACION:\n
 * 6\n
 */

#include <iostream>
#include <fstream>
#include <cctype>
#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include "solver.h"


using namespace std;

int main(int argc, char*argv[]) {
    if(argc != 5) {
        cerr << "ERROR: Parametros necesarios: <ruta_a_diccionario> <ruta_a_letras> "
             << "<modo_de_juego(L=longitud,P=puntuacion)> <cantidad_letras>" << endl;
        return -1;
    }

    // Inicializamos el arch_diccionario
    ifstream arch_diccionario;
    arch_diccionario.open(argv[1]);
    if(!arch_diccionario.is_open()) {
        cerr << "Error al abrir el archivo " << argv[1] << endl;
        return -1;
    }
    Dictionary diccionario;
    arch_diccionario >> diccionario;
    arch_diccionario.close();

    // Inicilaizamos el letras
    ifstream arch_letras;
    arch_letras.open(argv[2]);
    if(!arch_letras.is_open()) {
        cerr << "Error al abrir el archivo " << argv[2] << endl;
        return -1;
    }
    LettersSet letras;
    arch_letras >> letras;
    arch_letras.close();

    // Establecemos modod de juego
    bool scoregame;
    if(toupper(argv[3][0]) == 'L') {
        scoregame = false;
    }
    else if(toupper(argv[3][0]) == 'P') {
        scoregame = true;
    }
    else {
        cerr << "ERROR: Modo de juego ha de ser L o P" << endl;
    }

    // Establecemos el numero de letras
    int num_letras = stoi(argv[4]);

    // Creamos la bolsa de letras
    LettersBag bolsa(letras);

    // Extraemos las que se usarán para la partida
    vector<char> disponibles;
    for(int i=0; i< num_letras; i++) {
        disponibles.push_back(bolsa.extractLetter());
    }

    // Le pedimos al sover las soluciones
    EfficientSolver solver(diccionario, letras);
    pair<vector<string>, int> soluciones = solver.getSolutions(disponibles, scoregame);

    // Las imprimimos
    cout << "LETRAS DISPONIBLES:" << endl;
    for(char & c : disponibles) {
        cout << c << " ";
    }
    cout << endl;
    cout << "SOLUCIONES:" << endl;
    for(string & sol : soluciones.first) {
        cout << sol << endl;
    }
    cout << "PUNTUACION:" << endl;
    cout << soluciones.second << endl;
}