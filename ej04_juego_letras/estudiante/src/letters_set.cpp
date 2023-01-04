/**
 * @file letters_set.cpp
 * @brief Archivo deonde se define la implementación de la calse LettersSet y sus operadores de flujo de entrada/salida
 */

#include <iostream>
#include <vector>
#include <cctype>
#include "letters_set.h"
#include "FuncionesVarias.h"

LettersSet::LettersSet(){}

LettersSet::LettersSet(const LettersSet &other){
    *this = other;
}

bool LettersSet::insert(const std::pair<char, LetterInfo> &val){
    std::pair<char, LetterInfo> insert = val;
    insert.first = toupper(val.first);
    return letters.insert(insert).second;
}

bool LettersSet::erase(const char &key){
    char upper = toupper(key);
    return letters.erase(key) != 0;
}

void LettersSet::clear(){
    letters.clear();
}

bool LettersSet::empty() const{
    return letters.empty();
}

unsigned int LettersSet::size() const{
    return letters.size();
}

int LettersSet::getScore(std::string word) const{
    int score = 0;
    for(int i=0; i < word.length(); i++){
        score += letters.at(toupper(word[i])).score;
    }
    return score;
}

LettersSet& LettersSet::operator=(const LettersSet &cl){
    letters = cl.letters;
    return *this;
}

LetterInfo& LettersSet::operator[](const char &val){
    return letters.at(val);
}

LettersSet::iterator LettersSet::begin(){
    return LettersSet::iterator(letters.begin());
}

LettersSet::const_iterator LettersSet::begin() const{
    return LettersSet::const_iterator(letters.begin());
}

LettersSet::iterator LettersSet::end(){
    return LettersSet::iterator(letters.end());
}

LettersSet::const_iterator LettersSet::end() const{
    return LettersSet::const_iterator(letters.end());
}

std::ostream& operator<<(std::ostream &os, const LettersSet &cl){
    std::vector<std::string> tit_columnas{"LETRA", "CANTIDAD", "PUNTOS"}; // Titulo de las columnas

    for(int n_columna=0; n_columna < tit_columnas.size(); n_columna++) { // Imprime los titulos de las columnas
        os << tit_columnas[n_columna];
        if(n_columna != tit_columnas.size() -1)  os << "\t";
    }
    os << std::endl;

    // Para cada elemento lo imprime en su columna
    for(LettersSet::const_iterator iter = cl.begin(); iter!=cl.end(); iter++) {
        os << (*iter).first << "\t" << (*iter).second.repetitions << "\t" << (*iter).second.score << std::endl;
    }
    return os;
}
std::istream& operator>>(std::istream &is, LettersSet &cl){
    std::string basura; // Donde se vuelcan los datos inutiles de is

    is >> basura >> basura >> basura; // El titulo de las columnas
    while(!is.eof()) {
        char letra;
        int rep, punt;
        std::pair<char, LetterInfo> insertando;
        // Almacenamos los elementos que definen un elemento
        is >> letra >> rep >> punt;
        // Los insertamos en un elemento
        insertando.first = toupper(letra);
        insertando.second.repetitions = rep;
        insertando.second.score = punt;
        cl.insert(insertando);
    }
    return is;
}