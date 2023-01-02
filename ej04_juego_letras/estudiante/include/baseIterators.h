/**
 * @file baseIterators.h
 * @brief Archivo donde se declara y definen las clase BaseIterator y BaseConstIterator
 */

#ifndef P04_TDAS_NO_LINEALES_BASEITERATORS_H
#define P04_TDAS_NO_LINEALES_BASEITERATORS_H

template<typename Contenedor, typename Iterador>
class BaseIterator {
protected:
    Iterador iterador;
public:
    /**
     * @brief Constructor por defecto, no hace nada.
     */
    BaseIterator(){}


    /**
     * @brief Crea una copia en estado a partir de otro Baseiterator.
     * @param other Otro iterador de Contenedor.
     */
    BaseIterator(const BaseIterator<Contenedor, typename Contenedor::iterator> &other){
        (*this) = other;
    }


    /**
     * @brief Crea un iterador de BaseIterator a partir de uno de Contenedor.
     * @param otro_iterador Un iterador de MapaInterno.
     */
    BaseIterator(const typename Contenedor::iterator &otro_iterador) {
        (*this) = otro_iterador;
    }


    /**
     * @brief Asigna el estado de other a esta instancia.
     * @param other El objeto de la que se copiara el estado.
     * @return Una referencia a este objeto para que se pueda encadenar.
     */
    BaseIterator<Contenedor, Iterador>& operator=(const BaseIterator<Contenedor, typename Contenedor::iterator> &other) {
        return (*this) = other.iterador;
    }


    /**
     * @brief Cambia a donde apunta el iterador, para que apunte a donde lo ahce otro_iterador.
     * @param otro_iterador El objeto de la que se usará para cambiar el estado.
     * @return Una referencia a este objeto para que se pueda encadenar.
     */
    BaseIterator<Contenedor, Iterador>& operator=(const typename Contenedor::iterator &otro_iterador) {
        iterador = otro_iterador;
        return (*this);
    }


    /**
     * @brief Permite a acceder al valor del elemento al que apunta el iterador.
     * @return Una referencia constante al elemento al que apunta el iterador.
     */
    typename Contenedor::value_type& operator*() {
        return *iterador;
    }


    /**
     * @brief Hace avanzar al iterador.
     * @return El valor del itarador antes de ser modificado.
     */
    BaseIterator<Contenedor, Iterador>& operator++() {
        iterador++;
        return (*this);
    }


    /**
     * @brief Hace avanzar al iterador.
     * @returnEl una referencia al iterador.
     */
    BaseIterator<Contenedor, Iterador> operator++(int) {
        BaseIterator<Contenedor, Iterador> cp(*this);
        ++(*this);
        return cp;
    }


    /**
     * @brief Hace retroceder al iterador.
     * @return valor del iterador antes de ser modificado.
     */
    BaseIterator<Contenedor, Iterador>& operator--() {
        iterador--;
        return (*this);
    }


    /**
     * @brief Hace retroceder al iterador.
     * @return una referencia al iterador.
     */
    BaseIterator<Contenedor, Iterador> operator--(int) {
        BaseIterator<Contenedor, Iterador> cp(*this);
        --(*this);
        return cp;
    }


    /**
     * @brief Comprueba si dos iteradores apuntan al mismo elemento.
     * @param other El otro iterador con el que se comprueba.
     * @return True si apuntan al mismo sitio, false si no.
     */
    template <typename OtroIterador>
    bool operator==(const BaseIterator<Contenedor, OtroIterador> &other) const {
        return (*this) == other.iterador;
    }


    /**
     * @brief Comprueba si dos iteradores apuntan al mismo elemento.
     * @param otro_iterador El otro iterador con el que se comprueba.
     * @return True si apuntan al mismo sitio, false si no.
     */
    bool operator==(const typename Contenedor::const_iterator &otro_iterador) const { // Const porque el normal se puede convertir a const
        return iterador == otro_iterador;
    }


    /**
     * @brief Comprueba si dos iteradores apuntan al mismo elemento.
     * @param otro_iterador El otro iterador con el que se comprueba.
     * @return False si apuntan al mismo sitio, true si no.
     */
    template <typename OtroIterador>
    bool operator!=(const BaseIterator<Contenedor, OtroIterador> &other) const {
        return (*this) != other.iterador;
    }


    /**
     * @brief Comprueba si dos iteradores apuntan al mismo elemento.
     * @param otro_iterador El otro iterador con el que se comprueba.
     * @return False si apuntan al mismo sitio, true si no.
     */
    bool operator!=(const typename Contenedor::const_iterator &otro_iterador) const {
        return iterador != otro_iterador;
    }
};

template <typename Contenedor>
class BaseConstIterator : public BaseIterator<Contenedor, typename Contenedor::const_iterator> {
public:
    using BaseIterator<Contenedor, typename Contenedor::const_iterator>::BaseIterator; // Hereda los constructores

    // Añadimos metodos para copiar el estado desde iteradores constantes
    /**
     * @brief Crea un BaseConsntIterator a partir de uno de Contenedor.
     * @param otro_iterador Un iterador constante de Contenedor.
     */
    BaseConstIterator(const typename Contenedor::const_iterator &otro_iterador) {
        (*this) = otro_iterador;
    }

    /**
     * @brief Cambia a donde apunta el iterador, para que apunte a donde lo hace otro_iterador.
     * @param otro_iterador El objeto de la que se usará para cambiar el estado.
     * @return Una referencia a este objeto para que se pueda encadenar.
     */
    const BaseConstIterator<Contenedor>& operator=(const typename Contenedor::const_iterator &otro_iterador) {
        this->iterador = otro_iterador;
        return (*this);
    }

    /**
     * @brief Permite a acceder al valor del elemento al que apunta el iterador.
     * @return Una referencia constante al elemento al que apunta el iterador.
     */
    const typename Contenedor::value_type& operator*() const {
        return *(this->iterador);
    }
};


#endif //P04_TDAS_NO_LINEALES_BASEITERATORS_H