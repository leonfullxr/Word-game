//
// Created by fluque1995 on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){
    if(curr_node.is_null()) return 0;
    int contador = curr_node.operator*().character == c ? 1 : 0;
    contador += this->getOccurrences(curr_node.left_child(),c); //Hijo izquierdo
    contador += this->getOccurrences(curr_node.right_sibling(),c); //Hermano a la derecha
    return contador;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){
    std::pair<int,int> par = {0,0};
    if(curr_node.is_null()) return par;
    std::pair<int,int> left_child = this->getTotalUsages(curr_node.left_child(),c);
    std::pair<int,int> right_child = this->getTotalUsages(curr_node.right_sibling(),c);
    par.first += left_child.first + right_child.first;
    par.second += left_child.second + right_child.second;
    if(curr_node.operator*().character == c) par.first += left_child.second;
    if(curr_node.operator*().valid_word)  {
        par.second++;
        if(curr_node.operator*().character == c) {
            par.first++;
        }
    }
    return par;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
    return this->getOccurrences(this->words.get_root(),c);
}

int Dictionary::getTotalUsages(const char c){
    return this->getTotalUsages(this->words.get_root(),c).first;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() {
    curr_word = "";
    iter = tree<char_info>::const_preorder_iterator();
}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    curr_word = "";
    for(int i=0; i<iter.get_level(); i++) {
        curr_word += ' ';
    }
    this->iter = iter;
}

std::string Dictionary::iterator::operator*() {
    return  curr_word;
}

Dictionary::iterator &Dictionary::iterator::operator++() {
    do {
        ++iter;

        if (iter == tree<char_info>::const_preorder_iterator())  { // Si ha llegado al final
            curr_word = "";
            return *this;
        }

        if(iter.get_level() > curr_word.length()) { // Si se desciende un nivel
            // Se añade una letra a la palabra
            curr_word += (*iter).character;
        }
        else if(iter.get_level() < curr_word.length()) { // Si se asciende un nivel
            // Se elimina una letra de la palabra
            int longitud_inicial = curr_word.length();
            for(int i = 0; i < longitud_inicial - iter.get_level(); i++) {
                curr_word.pop_back();
            }
            curr_word[iter.get_level() - 1] = (*iter).character;
        }
        else { // Si se queda en el mismo nivel
            // Cambiamos la ultima letra por la nueva
            curr_word[curr_word.length() - 1] = (*iter).character;
        }

    } while (!(*iter).valid_word);

    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return iter == other.iter;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return iter != other.iter;
}

Dictionary::iterator Dictionary::begin() const {
    Dictionary::iterator it(words.get_root());
    return ++it;
}

Dictionary::iterator Dictionary::end() const {
    return Dictionary::iterator();
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////

Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    Dictionary::possible_words_iterator iter(words.get_root(), available_characters);
    ++iter;
    return iter;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    return Dictionary::possible_words_iterator();
}

Dictionary::possible_words_iterator::possible_words_iterator() {
    available_letters = multiset<char>();
    current_node = node();
    current_word = "";
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){
    node aux = this->current_node = current_node;
    for(const char & letter : available_letters) {
        this->available_letters.insert(letter);
    }
    while(!(aux.parent().is_null())) { // Mientras no estemos en la raiz
        current_word += (*aux).character;
        aux = aux.parent();
    }
}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    *this = other;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    current_node = node(other.current_node);
    available_letters = other.available_letters;
    current_word = other.current_word;
    return *this;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    return current_node == other.current_node && available_letters == other.available_letters;
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return !((*this)==other);
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {
    if(available_letters.size() > 0 && !current_node.left_child().is_null()) { // Si quedan letras en la bolsa y tiene hijos
        current_node = current_node.left_child(); // Vamos al hijo
        comprueba_si_esta_en_la_bolsa();
    }
    else {
        comprueba_si_tiene_hermanos(true);
    }

    return *this;
}

void Dictionary::possible_words_iterator::comprueba_si_esta_en_la_bolsa() {
    if(available_letters.find((*current_node).character) != available_letters.end()) { // Si esta en la bolsa
        current_word += (*current_node).character;
        available_letters.erase(available_letters.find((*current_node).character));
        if((*current_node).valid_word) {// Si es palabra valida
            return;
        }
        else {
            ++(*this);
        }
    }
    else {
        comprueba_si_tiene_hermanos(false);
    }
}

void Dictionary::possible_words_iterator::comprueba_si_tiene_hermanos(bool sacar_letra) {
    if (sacar_letra) {
        available_letters.insert(current_word.back()); // Devuelve la ultima letra a la bolsa
        current_word.pop_back(); // La elimina de la palabra
    }

    if(!current_node.right_sibling().is_null()) { // Si tiene hermano
        current_node = current_node.right_sibling(); // Se mueve al hermano
        comprueba_si_esta_en_la_bolsa();
    }
    else if(!current_node.parent().is_null()) { // Si tiene padre
        current_node = current_node.parent();
        comprueba_si_tiene_hermanos(true);
    }
    else { // Si no tiene ni padre ni hermanos
        // Lo igualamos al final de dicho iterador en diccionario
        available_letters = multiset<char>();
        current_node = node();
        current_word = "";
    }
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return current_word;
}
