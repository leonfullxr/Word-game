/**
 * @file letters_bag.h
 * @brief Archivo donde se declara la calse LettersBag
 */

#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__
#include <bag.h>
#include <letters_set.h>

/**
 * @brief TDA LettersBag
 *
 * @details Este TDA almacena un conjunto de letras.
 */

class LettersBag{
private:
    Bag <char> letters;
public:

    /**
     * @brief Constructor por defecto
     */
    LettersBag();

    /**
     * @brief Constructor dado un LettersSet
     * @param letterSet TDA LettersSet a parsear
     */
    LettersBag(const LettersSet & letterSet);

    /**
     * @brief Introduce una letra en la bolsa
     * @param l letra a añadir a la LettersBag
     */
    void insertLetter(const char & l);

    /**
     * @brief Extrae una letra aleatoriamente de la bolsa
     * @return la letra extraida
     * @post Se elimina la ocurrenca de la letra en la bolsa
     */
    char extractLetter();

    /**
     * @brief Extrae un conjunto de letras
     * @param num número de letras a extraer
     * @return Lista con las letras extraídas aleatoriamente
     * @pre Num debe de ser igual o mayor que el tamaño de la bolsa
     * @post Se eliminan las ocurrencias de las letras extraidas
     */
    std::vector<char> extractLetters(int num);

    /**
     * @brief Vacía la LettersBag
     */
    void clear();

    /**
     * @brief Tamaño de la bolsa
     * @return El numero de elementos en la bolsa
     */
    unsigned int size() const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other LettersBag a copiar
     * @return Referencia a la instancia de la bolsa
     */
    LettersBag & operator=(const LettersBag & other);
};

#endif