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

    // Check all possible words in the dictionary
    getWords(dictionary.begin(),"",palabras);

    // Sort the resulting words in descending order of score
    sort(soluciones.first.begin(), soluciones.first.end(), [score_game](const std::string& a, const std::string& b) {
        if (score_game) {
            return getPoints(a) > getPoints(b);
        } else {
            return a.length() > b.length();
        }
    }
}

void Solver::getWords(const Dictionary::iterator& curr_node, string word, vector<string>& words) {
    // If current node is not a leaf, add its character to the current word
    if(curr_node.right() || curr_node.left()) {
        word += *curr_node;
    }

    // If current node is a valid word, add it to the vector
    if((*curr_node).valid_word) {
        words.push_back(word);
    }

    // Recursively call the function on the left child and right sibling
    if(curr_node.left()) {
        getWords(curr_node.left(), word, words);
    }
    if(curr_node.right()) {
        getWords(curr_node.right(), word, words);
    }
}

