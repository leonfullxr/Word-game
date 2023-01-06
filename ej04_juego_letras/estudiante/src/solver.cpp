/**
 * @file solver.cpp
 * @brief Archivo que implementa los metodos de la clase solver.h
 */

#include "solver.h"

solver::solver(const Dictionary &dict, const LettersSet &letters_set) {
    this->dictionary = dict;
    this->letters = letters_set;
}

pair<vector<std::string>, int> solver::getSolutions(const vector<char> &available_letters, bool score_game) {
    pair<vector<string>,int> soluciones;
    vector<string> palabras;

    //Almacena todas las palabras del diccionario
    for (Dictionary::iterator it = this->dictionary.begin(); it != this->dictionary.end(); ++it)
        palabras.push_back(it.operator*());

    //Devuelve todas las palabras formadas
    soluciones.first = this->getPossibleWords(available_letters,palabras);

    //Creamos ya el pair que contenga las mejores soluciones
    pair<vector<string>,int> solucion_final;

    //Ordenamos las palabras en funcion de longitud o puntuacion
    int maxima_puntuacion;
    if (score_game) {
        this->compareByPoints(soluciones.first);
        maxima_puntuacion = this->letters.getScore(soluciones.first.back());
        solucion_final.second = maxima_puntuacion;

        for(auto letra : soluciones.first) {
            if (maxima_puntuacion == this->letters.getScore(soluciones.first.back())) {
                solucion_final.first.push_back(soluciones.first.back());
                soluciones.first.pop_back();

            }
        }
    }else {
        this->compareByLength(soluciones.first);
        maxima_puntuacion = soluciones.first.back().length();
        solucion_final.second = maxima_puntuacion;

        for(auto letra : soluciones.first){
            if(maxima_puntuacion == soluciones.first.back().length()) {
                solucion_final.first.push_back(soluciones.first.back());
                soluciones.first.pop_back();
            }
        }
    }

    return solucion_final;
}

void solver::getWords(vector<string>& words) {


}

vector<string> solver::getPossibleWords(const vector<char> &available_letters, const vector<string> &words) {
    std::vector<std::string> solutions;

    // Create a map to store the count of each letter in the available_letters vector
    std::unordered_map<char, int> letter_count;
    std::unordered_map<char, int> copy;
    vector<char> aux;
    for (char c : available_letters) {
        letter_count[tolower(c)]++;
        copy[tolower(c)]++;
    }

    // For each word in the vector of words
    for (const string &word : words) {
        // Check if the word can be formed with the available letters
        bool can_form = true;
        for (char c : word) {
            // Decrement the count for each letter that is used to form the word
            if (letter_count[c] > 0) {
                letter_count[c]--;
                aux.push_back(c);
            } else {
                can_form = false;
                break;
            }
        }

        // If the word can be formed, add it to the vector of solutions
        if (can_form) {
            solutions.push_back(word);
        }

        // Reset the letter count for the next word
//        for (char c : aux) {
//            letter_count[c]++;
//            aux.pop_back();
//        }
        letter_count = copy;
    }

    return solutions;
}

void solver::compareByLength(std::vector<std::string> &arr) {
    sort(arr.begin(), arr.end(), [](const std::string &a, const std::string &b) {
        return a.length() < b.length();
    });
}


void solver::compareByPoints(std::vector<std::string>& strings)
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





