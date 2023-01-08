/**
 * @file solver.h
 * @brief Archivo donde se declara la clase Solver y EfficientSolver
 */

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include <vector>
#include "dictionary.h"
#include "letters_set.h"
#include <unordered_set>
#include <algorithm>

using namespace std;

/**
 * @class Solver que extrae las soluciones con el iterador de la clase Dictionary
 */
class Solver {
private:
    Dictionary dictionary;
    LettersSet letters;

    /**
     * @brief Funcion auxiliar que calcula la puntuacion de una palabra dependiendo del modo de juego
     * @param word El string a calcular la puntuacion
     * @param score_game True si la puntuacion es a puntuacion calculada en el metodo getScore de LetterSet o false en caso de longitud
     * @return un entero con el valor de la puntuacion de la palabra
     */
    int getScore(const string & word, bool score_game);

    /**
     * @brief Funcion auxiliar que comprueba si la palabra @word se puede construir con las letras disponibles
     * @param word La palabra a comprobar
     * @param available_letters Las letras disponibles para construir la palabra @word
     * @return True en caso de que se pueda construir y false en caso contrario
     */
    bool isValid(const string & word, multiset<char> available_letters);

public:
    /**
     * @brief Crea un Solver dado un diccionario y un conjunto de letras
     * @param dict El diccionario que se va a usar
     * @param letters_set Las letras de la partida
     */
    Solver(const Dictionary & dict, const LettersSet & letters_set);

    /**
     * @brief Obtiene las mejores soluciones dado unas letras y el modo de juego
     * @param available_letters Vector de las letras disponibles para el juego
     * @param score_game booleano que indica el modo de juego, true por puntuacion y false por longitud
     * @return Un pair que contiene las mejores palabras (puede haber empate) junto con la puntuacion correspondiente
     */
    pair <vector<std::string>,int> getSolutions(const vector<char> & available_letters, bool score_game);
};


/**
 * @class EfficientSolver que extrae las soluciones con el iterador eficiente de la clase Dictionary
 */
class EfficientSolver {
private:
    Dictionary dictionary;
    LettersSet letters;

    /**
     * @brief Funcion auxiliar que calcula la puntuacion de una palabra dependiendo del modo de juego
     * @param word El string a calcular la puntuacion
     * @param score_game True si la puntuacion es a puntuacion calculada en el metodo getScore de LetterSet o false en caso de longitud
     * @return un entero con el valor de la puntuacion de la palabra
     */
    int getScore(const string & word, bool score_game);
public:
    /**
     * @brief Crea un solver dado un diccionario y un conjunto de letras
     * @param dict El diccionario que se va a usar
     * @param letters_set Las letras de la partida
     */
    EfficientSolver(const Dictionary & dict, const LettersSet & letters_set);

    /**
     * @brief Obtiene las mejores soluciones dado unas letras y el modo de juego
     * @param available_letters Vector de las letras disponibles para el juego
     * @param score_game booleano que indica el modo de juego, true por puntuacion y false por longitud
     * @return Un pair que contiene las mejores palabras (puede haber empate) junto con la puntuacion correspondiente
     */
    pair <vector<std::string>,int> getSolutions(const vector<char> & available_letters, bool score_game);
};


#endif //P04_JUEGO_LETRAS_SOLVER_H
