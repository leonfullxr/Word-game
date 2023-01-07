//
// Created by leon on 1/01/23.
//

#include "solver.h"
#include <cctype>

int Solver::getScore(const string & word, bool score_game) {
    if(score_game) {
        return letters.getScore(word);
    }
    else {
        return word.length();
    }
}

bool Solver::isValid(const string & word, multiset<char> available_letters) {
    for(const char & c : word) { // Para cada letra se comprueba si esta disponilbe
        multiset<char>::iterator it = available_letters.find(tolower(c));
        if(it != available_letters.end()) {
            available_letters.erase(it); // Si lo esta la eliminamos de la bolsa
        }
        else { // Si no, la palabra no es valida
            return false;
        }
    }

    return true;
}

Solver::Solver(const Dictionary &dict, const LettersSet &letters_set) {
    this->dictionary = dict;
    this->letters = letters_set;
}

pair<vector<std::string>, int> Solver::getSolutions(const vector<char> &available_letters, bool score_game) {
    pair<vector<string>, int> solutions;
    vector<string> &palabras_sol = solutions.first;
    int & max_score = solutions.second = 0;

    multiset<char> letras_disponibles;
    for(char c : available_letters) { // Copiamos el contenido del vactor de available_letters en un multiset
        letras_disponibles.insert(tolower(c));
    }

    for(Dictionary::iterator it = dictionary.begin(); it != dictionary.end(); ++it) { // Para cada palabra en el diccionario
        if(!isValid(*it, letras_disponibles)) continue; // Si es menor al maximo acutal o no es valida no la consideramos

        int current_score = getScore(*it, score_game); // Calculamos su puntuacion

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