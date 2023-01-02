//
// Created by leon on 1/01/23.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include <vector>
#include "dictionary.h"
#include "letters_set.h"

using namespace std;

class Solver {
private:
    Dictionary dictionary;
    LettersSet letters;
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

    /**
 * @brief Auxiliar function to get all the words formed by a tree
 * @param curr_node Current node of the tree
 * @param word String that stores the current word formed by the tree
 * @param words Vector that will store all the words formed by the tree
 */
    void getWords(const Dictionary::iterator curr_node, string word, vector<string>& words);

};


#endif //P04_JUEGO_LETRAS_SOLVER_H
