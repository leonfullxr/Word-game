/**
 * @file letters_bag.cpp
 * @brief Archivo donde se define la implementación de la clase LettersBag
 */

#include "letters_bag.h"

using namespace std;

LettersBag::LettersBag()= default;

LettersBag::LettersBag(const LettersSet & letterSet){
    for(LettersSet::const_iterator it = letterSet.begin(); it != letterSet.end(); it++){ //Recorremos las letras en letterSet
        for(int j = 0; j < (*it).second.repetitions; j++){ //Para el número de veces que está repetida la letra
            letters.add(it.operator*().first);
        }
    }
}

void LettersBag::insertLetter(const char & l){
    this->letters.add(l);
}

char LettersBag::extractLetter(){
    return letters.get();
}

vector<char> LettersBag::extractLetters(int num){
    vector<char> letras;
    for(int i = 0; i < num; i++){
        letras.push_back(letters.get());
    }
    return letras;
}

void LettersBag::clear(){
    letters.clear();
}

unsigned int LettersBag::size() const{
    return letters.size();
}

LettersBag & LettersBag::operator=(const LettersBag & other){
    letters = other.letters;
    return *this;
}