//
// Created by leon on 1/01/23.
//

#include "solver_eficiente.h"
#include <cctype>

int solver_eficiente::getSocre(const string & word, bool score_game) {
    if(score_game) {
        return letters.getScore(word);
    }
    else {
        return word.length();
    }
}

solver_eficiente::solver_eficiente(const Dictionary &dict, const LettersSet &letters_set) {
    this->dictionary = dict;
    this->letters = letters_set;
}

pair<vector<std::string>, int> solver_eficiente::getSolutions(const vector<char> &available_letters, bool score_game) {
    pair<vector<string>, int> solutions;
    vector<string> &palabras_sol = solutions.first;
    int & max_score = solutions.second = 0;

    multiset<char> letras_disponibles;
    for(char c : available_letters) { // Copiamos el contenido del vactor de available_letters en un multiset
        letras_disponibles.insert(tolower(c));
    }

    for(Dictionary::iterator it = dictionary.begin(); it != dictionary.end(); ++it) { // Para cada palabra en el diccionario
        int current_score = getSocre(*it, score_game); // Calculamos su puntuacion

        if( current_score > max_score) { // Si supera el maximo es la nueva unica palabra en el vector de soluciones
            palabras_sol = vector<string>(1, *it);
            max_score = current_score;
        }
        else if(current_score == max_score) { // Si es igual al maximo la añadimos al vector de soluciones
            palabras_sol.push_back(*it);
        }
    }

    return solutions;
}