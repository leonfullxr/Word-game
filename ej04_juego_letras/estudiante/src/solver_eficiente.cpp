/**
 * @file solver_eficiente.cpp
 * @brief Archivo que implementa los metodos de la clase solver.h de manera eficiente
 */

#include "solver.h"

solver::solver(const Dictionary &dict, const LettersSet &letters_set) {
    this->dictionary = dict;
    this->letters = letters_set;
}

pair<vector<std::string>, int> solver::getSolutions(const vector<char> &available_letters, bool score_game) {
    pair<vector<string>,int> soluciones;

    for(Dictionary::possible_words_iterator it = this->dictionary.possible_words_begin(available_letters); it != this->dictionary.possible_words_end(); it.operator++())
        soluciones.first.push_back(*it); //vamos insertando las palabras

    //Ordenamos las palabras en funcion de longitud o puntuacion
    int maxima_puntuacion;
    pair<vector<string>,int> soluciones_final;    //Son las soluciones con respecto al score_game
    if (score_game) {
        this->compareByPoints(soluciones.first);
        maxima_puntuacion = this->letters.getScore(soluciones.first.back());
        soluciones_final.second = maxima_puntuacion;

        for(auto letra : soluciones.first) {
            if (maxima_puntuacion == this->letters.getScore(soluciones.first.back())) {
                soluciones_final.first.push_back(soluciones.first.back());
                soluciones.first.pop_back();

            }
        }
    }else {
        this->compareByLength(soluciones.first);
        maxima_puntuacion = soluciones.first.back().length();
        soluciones_final.second = maxima_puntuacion;

        for(auto letra : soluciones.first){
            if(maxima_puntuacion == soluciones.first.back().length()) {
                soluciones_final.first.push_back(soluciones.first.back());
                soluciones.first.pop_back();
            }
        }
    }

    return soluciones_final;
}
