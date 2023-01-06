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
     * @brief Auxiliar function to get all the words formed by a tree
     * @param curr_node Current node of the tree
     * @param word String that stores the current word formed by the tree
     * @param words Vector that will store all the words formed by the tree
     */
    void getWords(vector<string>& words);

    /**
     * @brief Get all the solutions that can be formed using the available letters
     *
     * @param available_letters Vector of available letters
     * @param words Vector of words to be checked
     * @return Vector of strings containing the solutions that can be formed
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
