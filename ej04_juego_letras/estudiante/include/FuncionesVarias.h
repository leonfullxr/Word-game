/**
 * @file FuncionesVarias.h
 * @brief Archivo donde se definen funciones auxiliares para la práctica
 */

#ifndef P04_TDAS_NO_LINEALES_FUNCIONESVARIAS_H
#define P04_TDAS_NO_LINEALES_FUNCIONESVARIAS_H

#include <cctype>

class FuncionesVarias {
public:

    /**
     * @brief Calcula el numero de digitos de un entero
     * @param i El entero del que se van a calcular el número de digitos
     * @return El numerod e dígitos de i
     */
    static int digitosDe(int i) {
        int digitos = 1;
        if (i < 0) digitos++;
        while(i > 9) {
            i/=10;
            digitos++;
        }
        return digitos;
    }

    static std::string stringToLower(const std::string & expr) {
        std::string expr_tolower;
        for(std::string::const_iterator iter = expr.begin(); iter != expr.end(); iter++) expr_tolower += tolower(*iter);
        return expr_tolower;
    }
};

#endif //P04_TDAS_NO_LINEALES_FUNCIONESVARIAS_H
