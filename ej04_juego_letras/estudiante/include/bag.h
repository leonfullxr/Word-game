/**
 * @file bag.h
 * @brief Archivo donde se declara la clase Bag
 */

#ifndef __BAG_H__
#define __BAG_H__
#include <vector>
#include <random>

using namespace std;
/**
 *  @brief TDA abstracto Bolsa
 *
 *  @details Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 *  Funciona como una bolsa de caracteres.
 */
template <class T>
class Bag{
private:
    vector<T> v;
public:

    /**
     * @brief Construtor por defecto
     */
    Bag()= default;

    /**
     * @brief Constructor de copia, crea una copia exacta de otro objeto de tipo Bag
     * @param other objeto de tipo Bag<T> del que se va a realiar la copia
     */
    Bag(const Bag<T> & other){
        (*this) = other;
    }

    /**
     * @brief Añade un elemento a la bolsa
     * @param element elemento del tipo T a añadir a una bolsa
     * @post Aumenta el tamaño de la bolsa en 1
     */
    void add(const T & element){
        v.push_back(element);
    }

    /**
     * @brief Devuelve un elemento aleatorio de la bolsa y lo elimina de la misma
     * @return Elemento del tipo T extraído de la bolsa
     * @pre La bolsa no debe de estar vacía
     * @post El elemento devuelto se ha eliminado de la bolsa
     */
    T get(){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, this->size()-1); // distribution en [0, size-1]

        int pos_aleatoria = dist(rng); //Obtenemos la posicion aleatoria
        typename std::vector<T>::const_iterator pos = v.begin() + pos_aleatoria; // Creamos un iterador que apunte al elemento buscado
        T elemento = *pos; //Muy importante devolver el elemento y no la posición
        v.erase(pos); //borramos el elemento
        return elemento;  //devolvemos el elemento
    }

    /**
     * @brief Elimina todos los elementos de la bolsa
     */
    void clear(){
        v.clear();
    }

    /**
     * @brief Tamaño de la bolsa
     * @return Número de elementos que hay en la bolsa
     */
    unsigned int size() const{
        return v.size();
    }

    /**
     * @brief Comprueba si la bolsa está vacía
     * @return true si la bolsa está vacía, false en caso contrario
     */
    bool empty() const{
        return v.empty();
    }

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other Bag<T> a copiar
     * @return Referencia a this para poder encadenar el operador
     */
    const Bag<T> & operator=(const Bag<T> & other){
        for(int i=0; i<other.size(); i++){
            v.push_back(other.v[i]);
        }
        return *this;
    }
};

#endif