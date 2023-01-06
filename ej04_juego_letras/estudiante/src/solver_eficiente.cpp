/**
 * @file solver_eficiente.cpp
 * @brief Archivo que implementa los metodos de la clase solver_eficiente.h
 */

#include "solver_eficiente.h"

solver_eficiente::solver_eficiente(const Dictionary &dict, const LettersSet &letters_set) {
    this->dictionary = dict;
    this->letters = letters_set;
}

pair<vector<std::string>, int> solver_eficiente::getSolutions(const vector<char> &available_letters, bool score_game) {
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

void solver_eficiente::compareByLength(std::vector<std::string> &arr) {
    sort(arr.begin(), arr.end(), [](const std::string &a, const std::string &b) {
        return a.length() < b.length();
    });
}


void solver_eficiente::compareByPoints(std::vector<std::string>& strings)
{
    // Find the maximum points value among all strings
    int maxPoints = 0;
    for (const std::string& s : strings)
    {
        maxPoints = std::max(maxPoints, this->letters.getScore(s));
    }

    // Perform radix sort
    int exp = 1;
    while (maxPoints / exp > 0)
    {
        std::vector<int> counts(10, 0);
        std::vector<std::string> output(strings.size());

        // Count the number of strings with a given digit in the current position
        for (const std::string& s : strings)
        {
            counts[(this->letters.getScore(s) / exp) % 10]++;
        }

        // Compute the starting index for each digit
        for (int i = 1; i < counts.size(); i++)
        {
            counts[i] += counts[i - 1];
        }

        // Place the strings in the output array
        for (int i = strings.size() - 1; i >= 0; i--)
        {
            int digit = (this->letters.getScore(strings[i]) / exp) % 10;
            output[counts[digit] - 1] = strings[i];
            counts[digit]--;
        }

        // Copy the sorted strings back to the input array
        strings = output;

        // Move to the next digit position
        exp *= 10;
    }
}
