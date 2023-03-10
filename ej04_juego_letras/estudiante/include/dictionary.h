/**
 * @file dictionary.h
 * @brief Archivo donde se declara la clase Dictionary
 */

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

/**
 * @brief TDA Dictionary, contenedor de palabras en minúscula
 * @details Las palabras almacenadas en la clase, si tienen algun caracter en mayscula se conviete a minuscula.
 */
class Dictionary {
private:
    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        inline bool operator==(const char_info &rhs) {
          return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        inline bool operator*() { return this->character; }

        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
          os << other.character << (other.valid_word ? "✓" : "×");
          return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    /**
     * @brief Funcion recursiva para getOcurrences()
     * @param curr_node el nodo actual del arbol
     * @param c el caracter a contar el numero de ocurrencias
     * @return El numero de veces que aparece el caracter c
     */
    int getOccurrences(node curr_node, char c);

    /**
     * @brief Funcion recursiva para getTotalUsages()
     * @param curr_node el nodo actual del arbol
     * @param c el caracter a contar el numero de usos
     * @return Un pair que devuelve el numero de ocurrencias del caracter c en los nodos que estan
     * por debajo de curr_node y el numero de palabras que acaban por debajo del nodo curr_node
     */
    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    /**
     * @brief Cuenta el numero de veces que aparece el caracter c en arbol que forma el diccionario
     * @param c el caracter a contar las ocurrencias
     * @return El numero de ocurrencias del caracter c
     */
    int getOccurrences(const char c);

    /**
     * @brief Cuenta el numero de veces que aparece el caracter c en las palabras del diccionario
     * @param c el caracter para contar el numero de usos
     * @return El numero de usos del caracter
     */
    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    /**
     * @class iterator Permite recorrer el diccionario palabra a palabra
     */
    class iterator {
    private:
        /**
         * @brief La palabra a la que apunta en un momento dado
         */
        std::string curr_word;
        /**
         * @brief Iteraor que usa para moverse en el arbol
         */
        tree<char_info>::const_preorder_iterator iter;

    public:
        /**
         * @brief Crea un iterador vacio
         */
        iterator();

        /**
         * @brief Crea un iterador que empieza en iter
         * @details Si se encuentra en el nivel n se asume que las n letras anteriores son espacios en blanco
         * @param iter La letra en la que emieza el iterador
         */
        iterator(tree<char_info>::const_preorder_iterator iter);

        /**
         * @brief Devuelve a la palabra que apunta el iteraodor
         * @return La palabra a la que apunta el iterador, una string vacia si no apunta a nada
         */
        std::string operator*();

        /**
         * @brief Hace avanzar el iterador una palabra en el diccionario
         * @return Una referencia al mismo iterador, para poder encadenar
         */
        iterator &operator++();

        /**
         * @brief Compara el objeto con otro iteraodor
         * @param other El otro iterador con el que se compara
         * @return True si son iguales y false si no
         */
        bool operator==(const iterator &other);

        /**
         * @brief Compara el objeto con otro iteraodor
         * @param other El otro iterador con el que se compara
         * @return True si son no iguales y false si lo son
         */
        bool operator!=(const iterator &other);

    };

    /**
     * @brief Devuelve un iterador que apunta a la primera palabra del diccionario
     * @return Un iterador que apunta a la primera palabra del diccionario, si no hay palabras en el diccionario, apunta
     * al final
     */
    iterator begin() const;

    /**
     * @brief Devuelve un iterador que apunta al final del diccionario
     * @return Un iterador que apunta al final del diccionario
     */
    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    /**
     * @class iterator Permite recorrer el diccionario pasando solo por las palabras validas de manera eficiente
     */
    class possible_words_iterator {
    public:
        /**
         * @brief Crea un iterador vacío
         */
        possible_words_iterator();

        /**
         * @brief Crea un iterador que empieze en el nodo dado y que recorrerá las que se puedan formar a partir de las
         * letras dadas
         * @details Si current node no es la raíz, los nodos pabre se añadirán a la palabra actual y por tanto contarán
         * como letras disponibles si dejan de estar en esta.
         * @param current_node EL nodo en el que se emezará a recorrer el diccionario
         * @param available_letters
         */
        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
         * @brief Crea una copia de estado profunda
         * @param other El iterador que se va a copiar
         */
        possible_words_iterator(const possible_words_iterator &other);

        /**
         * @brief Crea una copia de estado profunda
         * @param other El iterador que se va a copiar
         * @return Una referencia al mismo iterador, para poder encadenar
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
         * @brief Compara el objeto con otro iteraodor
         * @detials Hand e ser iguales tanto en la posicion en la que se encuentran en el diccionario, como en sus
         * letras disponibles
         * @param other El otro iterador con el que se compara
         * @return True si son iguales, false si no
         */
        bool operator==(const possible_words_iterator &other) const;

        /**
         * @brief Compara el objeto con otro iteraodor
         * @param other El otro iterador con el que se compara
         * @return True si son no iguales y false si lo son
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Hace avanzar el diccionario a la siguente palabra válida
         * @return Una referencia al mismo iterador, para poder encadenar
         */
        possible_words_iterator &operator++();

        /**
         * @brief Devuelve a la palabra que apunta el iteraodor
         * @return La palabra a la que apunta el iterador, una string vacia si no apunta a nada
         */
        std::string operator*() const;

    private:
        /**
         * @brief Las letras con las que se juega, las que hay disponibles
         */
        multiset<char> available_letters;
        // int level; // No es necesario, se tiene con la longitud de la palabra actual
        /**
         * @brief El nodo actual
         */
        node current_node;
        /**
         * @brief La palabra actual
         */
        string current_word;

        /**
         * @brief Función auxiliar para implementar el operador ++
         */
        void comprueba_si_esta_en_la_bolsa();

        /**
         * @brief Función auxiliar para implementar el operador ++
         * @param sacar_letra Si debe o no sacar la ultima letra de la palabra actual
         */
        void comprueba_si_tiene_hermanos(bool sacar_letra);
    };

    /**
     * @brief Devuelve un iterador de palabras validas apuntando a la primera palabra del diccionario que se puede
     * formar con las letras dadas
     * @param available_characters Las letras que usará el iterador para determinar si una palabra es o no válida
     * @return Un iterador de palabras validas apuntando a la primera palabra del diccionario que se puede
     */
    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
     * @brief Devuelve un iterador de palabras válidas que apunta al final del diccionario
     * @return Un iterador de pababras váidas que apunta al final del diccionario
     */
    possible_words_iterator possible_words_end() const;
};

#endif //TREE_DICTIONARY_HPP
