/**
 * @file letters_set.h
 * @brief Archivo donde se declara la clase LettersSet, sus iteradores y del flujo de entrada salida
 */

#ifndef __LETTERS_SET_H__
#define __LETTERS_SET_H__

#include<map>
#include<string>
#include "baseIterators.h"

/**
 * @brief TDA LetterInfo
 *
 * @details Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra. Estandariza todas las letras a mayuscula.
 */
struct LetterInfo {
    int repetitions, score;
};

/**
 * @brief TDA LettersSet
 *
 * @details Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra. Sólo se almacena la versión en maysucula de cada letra.
 */
//Debera tener un metodo begin() y end()
class LettersSet{
private:
    /**
     * @brief Donde se van a almacenar las letras junto a su informacion asociada
     */
    std::map<char, LetterInfo> letters;

public:
    /**
     * @brief La clase iterador de LettersSet
     */
    class iterator : public BaseIterator<std::map<char, LetterInfo>, std::map<char, LetterInfo>::iterator> {
    public:
        using BaseIterator<std::map<char, LetterInfo>, std::map<char, LetterInfo>::iterator>::BaseIterator; // Hereda los constructores
    };

    /**
     * @brief La calse iterador constante de LettersSet
     */
    class const_iterator : public BaseConstIterator<std::map<char, LetterInfo>>{
    public:
        using BaseConstIterator<std::map<char, LetterInfo>>::BaseConstIterator;
    };

    /**
     * Constructor por defecto, no hace nada
     */
    LettersSet();

    /**
     * @brief constructor de copia, crea copias de los elementos de other y las inserta en el objeto que se crea
     * @param other el LettersSet del que se van a copiar los elementos
     */
    LettersSet(const LettersSet &other);

    /**
     * @bief Inserta un elemento en el LetterSet. Si la letra que se intenta insertar es minuscula, se cambiará a
     * minuscula
     * @param val El elemento que se insertará, una pareja formada por una letra junto a su LetterInfo
     * @return true si se ha podido insertar, false si no
     * @pre La letra no debe de estar contenida ya en el LettersSet
     * @post Si la letra no existia, aumenta el tamaño del LettersSet en 1
     */
    bool insert(const std::pair<char, LetterInfo> &val);

    /**
     * @brief Elimina un elemento dada la letra a la que se asocia, si se intenta eliminar una letra minuscial, se cambia
     * a mayuscula
     * @param key Letra a la que se asocia el elemento que se va a eliminar
     * @return true si se ha podido eleiminar, false si no
     * @post Si ele elemento existia, reduce el tamaño del LettersSet en 1
     */
    bool erase(const char &key);

    /**
     * @brief vacía el LettersSet
     */
    void clear();

    /**
     * @brief Comprueba si el LettersSet esta vacío
     * @return true si esta vacío, false si no
     */
    bool empty() const;

    /**
     * @brief Devuelve el numero de letras en el LettersSet
     * @return El tamaño de LettersSet
     */
    unsigned int size() const;

    /**
     * @brief Calcula La puntuacion asociada a una palabra, empezando en 0 y sumandole el score asociado a cada letra
     * que apareza, suma varias veces si la letra aparece mas de una vez
     * @param word La palabra a la que se le va a calcular la puntuación.
     * @return La puntuacion correspondiente a la word
     * @pre El LettersSet debe tener llaves correspondientes a todas las letras que aparecen en word.
     */
    int getScore(std::string word) const;

    /**
     * @brief Copia cl en el LettersSet actual
     * @param cl El LettersSet cuyos valores se copiarán
     * @return El LettersSet actual
     */
    LettersSet& operator=(const LettersSet &cl);

    /**
     * @brief Permite acceder a la informacion asociada a una letra del LettersSet
     * @param val La letra de la que se quiere consultar la información
     * @return El LetterInfo asociado a val.
     * @pre El contenedor debe contener la llave val.
     */
    LetterInfo& operator[](const char &val);

    /**
     * @brief Devuelve un iterador apuntando al primer elemento en LettersSet
     * @return Un iterador apuntando al primer elemento en LettersSet
     */
    LettersSet::iterator begin();

    /**
     * @brief Devuelve un iterador constante apuntando al primer elemento en LettersSet
     * @return Un iterador constante apuntando al primer elemento en LettersSet
     */
    //const std::_Rb_tree_const_iterator<std::pair<const char, int>> begin() const;
    LettersSet::const_iterator begin() const;
    /**
    * @brief Devuelve un iterador apuntando a después del ultimo elemento en LettersSet
    * @return Un iterador apuntando a después del ultimo elemento en LettersSet
    */
    LettersSet::iterator end();

    /**
    * @brief Devuelve un iterador constante apuntando a después del ultimo elemento en LettersSet
    * @return Un iterador constante apuntando a después del ultimo elemento en LettersSet
    */
    LettersSet::const_iterator end() const;
};

/**
 * @brief Imprime en os el LettersSet con el siguiente formato
 *
 * @details
 * LETRA          CANTIDAD       PUNTOS
 *
 * a              r_a            p_a
 *
 * ...
 *
 * z              r_z            p_z
 *
 * donde a es la primera letra del LettersSet, z es la última. r_i son las repeticiones
 * de i y p_y es la puntuacion asociada a i.
 * Es posible inicializar un LettersSet con el operador >> desde la salida de este operador
 * @param os El flujo de salida donde se imprimirá el LettersSet
 * @param cl El LettersSet que se imprimirá
 * @return El flujo de salida donde se va a imprimir, para permitir el encadenamiento.
 */
std::ostream& operator<<(std::ostream &os, const LettersSet &cl);

/**
 * @brief Carga un Leterset desde un flujo de entrada con el siguiente formato:
 *
 * @details
 * BsBsBsas(r_a)s(p_a)s...zs(r_z)s(p_z)
 *
 * donde B es un dato que se ignorará, s es un separador, a es la primera letra del LettersSet, z es la última.
 * r_i son las repeticiones de i y p_y es la puntuacion asociada a i.
 * Si se intentan insertar letras minuscilas, las cambia a maysucula.
 * @param is El flujo de entrada desde donde se cargará la informacion
 * @param cl El LettersSet donde se cargará la información
 * @return El flujo de entrada desde donde se va a cargar, para permitir el encadenamiento.
 */
std::istream& operator>>(std::istream &is, LettersSet &cl);

#endif
