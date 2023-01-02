//
// Created by leon on 1/01/23.
//

#include "Solver.h"

Solver::Solver(const Dictionary &dict, const LettersSet &letters_set) {
    this->dictionary = dict;
    this->letters = letters_set;
}

pair<vector<std::string>, int> Solver::getSolutions(const vector<char> &available_letters, bool score_game) {
    pair<vector<string>,int> soluciones;
    vector<string> palabras;
    soluciones.second = 0; // Initialize score to 0

    //Devuelve todas las palabras del diccionario
    getWords(palabras);
    //Devuelve todas las palabras formadas
    soluciones.first = this->getPossibleWords(available_letters,palabras);

    //Ordenamos las palabras en funcion de longitud o puntuacion
    if (score_game)
        this->compareByPoints(soluciones.first);
    else
        this->compareByPoints(soluciones.first);

    //Creamos ya el pair que contenga las mejores soluciones
    int maxima_puntuacion = this->letters.getScore(soluciones.first.back());
    pair<vector<string>,int> solucion_final;
    solucion_final.second = maxima_puntuacion;
    solucion_final.first.push_back(soluciones.first.back());
    soluciones.first.pop_back();
    while(this->letters.getScore(soluciones.first.back()) == maxima_puntuacion){
        solucion_final.first.push_back(soluciones.first.back());
        soluciones.first.pop_back();
    }

    return solucion_final;
}

void Solver::getWords(vector<string>& words) {
    for (Dictionary::iterator it = this->dictionary.begin(); it != this->dictionary.end(); ++it){
        words.push_back(it.operator*());
    }
}

vector<string> Solver::getPossibleWords(const vector<char> &available_letters, const vector<string> &words) {
    std::vector<std::string> solutions;

    // For each word in the vector of words
    for (const string &word : words) {
        // Check if the word can be formed with the available letters
        bool can_form = true;
        unordered_set<char> used_letters;
        for (char c : word) {
            if (used_letters.count(c) || (find(available_letters.begin(), available_letters.end(), c) == available_letters.end())){
                can_form = false;
                break;
            }
            used_letters.insert(c);
        }

        // If the word can be formed, add it to the vector of solutions
        if (can_form) {
            solutions.push_back(word);
        }
    }

    return solutions;
}

void Solver::compareByPoints(vector<string> &solutions) {
    for (int i = 0; i < solutions.size() - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < solutions.size(); j++) {
            if (this->letters.getScore(solutions[j]) < this->letters.getScore(solutions[min_idx])) {
                min_idx = j;
            }
        }
        swap(solutions[i], solutions[min_idx]);
    }
}

void Solver::compareByLength(vector<string> &solutions) {
    for (size_t i = 0; i < solutions.size() - 1; i++) {
        // Find the minimum element in the unsorted part of the vector
        size_t min_idx = i;
        for (size_t j = i + 1; j < solutions.size(); j++) {
            if (solutions[j].length() < solutions[min_idx].length()) {
                min_idx = j;
            }
        }
        // Swap the minimum element with the element at the current position
        swap(solutions[i], solutions[min_idx]);
    }
}



