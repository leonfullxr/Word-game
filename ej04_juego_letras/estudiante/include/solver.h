//
// Created by leon on 1/01/23.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include <vector>
#include "dictionary.h"
#include "letters_set.h"
#include <unordered_map>
#include <algorithm>

using namespace std;

class solver {
private:
    Dictionary dictionary;
    LettersSet letters;
public:
    /**
     * @brief Crea un solver dado un diccionario y un conjunto de letras
     * @param dict El diccionario que se va a usar
     * @param letters_set Las letras de la partida
     */
    solver(const Dictionary & dict, const LettersSet & letters_set);

    /**
     * @brief Obtiene las mejores soluciones dado unas letras y el modo de juego
     * @param available_letters Vector de las letras disponibles para el juego
     * @param score_game booleano que indica el modo de juego, true por puntuacion y false por longitud
     * @return Un pair que contiene las mejores palabras (puede haber empate) junto con la puntuacion correspondiente
     */
    pair <vector<std::string>,int> getSolutions(const vector<char> & available_letters, bool score_game);

    /**
     * @brief Devuelve todas las palabras que se pueden formar dado unas letras disponibles y un vector de palabras
     * @param available_letters Vector de letras disponibles
     * @param words Vector de las letras a comprobar
     * @return Vector de strings que contiene las palabras formadas
     */
    vector<string> getPossibleWords(const vector<char> &available_letters, const vector<string> &words);

    /**
     * @brief Ordena las longitudes de palabras de menor a mayor
     * @param arr Vector de string que contiene las palabras
     */
    void compareByLength(std::vector<std::string> &arr);

    /**
     * @brief Ordena las palabras por su puntuacion
     * @param solutions Vector de string que contiene las palabras
     */
    void compareByPoints(std::vector<std::string>& solutions);
};

#endif //P04_JUEGO_LETRAS_SOLVER_H
