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
    contador += this->getOccurrences(curr_node.left_child(),c); //Nodo de la izquierda
    contador += this->getOccurrences(curr_node.right_sibling(),c); //Nodo de la derecha
    return contador;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){
    std::pair<int,int> par = {0,0};
    if(curr_node.is_null()) return par;
    std::pair<int,int> left_child = this->getTotalUsages(curr_node.left_child(),c);
    std::pair<int,int> right_child = this->getTotalUsages(curr_node.right_sibling(),c);
    par.first += left_child.first + right_child.first;
    par.second += left_child.second + right_child.second;
    if(curr_node.operator*().character == c) par.first += left_child.second + 1;
    if(curr_node.operator*().valid_word) par.second++;
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

/*std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}*/

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
    this->iter = tree<char_info>::const_preorder_iterator();
    this->curr_word = "";
}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    this->iter = iter;
}

std::string Dictionary::iterator::operator*() {
    return this->curr_word;
}

Dictionary::iterator &Dictionary::iterator::operator++() {
    int nivel = this->iter.get_level();
    while(!this->iter.operator*().valid_word){
        this->iter.operator++();
        if(this->iter.get_level() > nivel){
            this->curr_word.push_back(this->iter.operator*().character);
        }else if(this->iter.get_level() < nivel){
            this->curr_word.pop_back();
        }else{
            this->curr_word.pop_back();
            this->curr_word.push_back(this->iter.operator*().character);
        }
    }
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return this->iter == other.iter;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return !(this->iter.operator==(other.iter));
}

Dictionary::iterator Dictionary::begin() const {
    return Dictionary::iterator() = Dictionary::iterator().operator++();
}

Dictionary::iterator Dictionary::end() const {
    return Dictionary::iterator() = tree<char_info>().cend_preorder();
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {

}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {

}

Dictionary::possible_words_iterator::possible_words_iterator() {

}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){

}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){

}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {

}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {

}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {

}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {

}

std::string Dictionary::possible_words_iterator::operator*() const {

}
