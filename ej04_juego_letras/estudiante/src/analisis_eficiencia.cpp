#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include "solver.h"
#include "letters_bag.h"
#include "letters_set.h"
#include "dictionary.h"

using namespace std;
using namespace std::chrono;

typedef duration<float,ratio<1,1000>> milliseconds_f ;

int main(int argc, char *argv[]) {
    // Parametros del analisis
    const int DICCIONARIOS_INICIO = 5000;
    const int DICCIONARIOS_FINAL = 70000;
    const int PASO_DICCIONARIOS = 5000;
    const int LERTAS_INICIO = 2;
    const int LERTAS_FINAL = 56; // Ha de ser <= al numero de letras que indica el archivo de letras
    const int PASO_LETRAS = 2;
    const int NUM_BOLSAS_POR_ANALISIS = 10;
    const string RUTA_ARCH_LETRAS = "./data/letras.txt";
    const string RUTA_BASE_DICCIONARIO = "./data_eficiencia/diccionario_";
    const string RUTA_DIR_RESULTADOS = "./estudiante/resultados/";
    const string ARCH_RESULTADOS_SOLVER = "results_solver.txt";
    const string ARCH_RESULTADOS_SOLVER_EFICIENTE = "results_efficient_solver.txt";

    // Constantes
    const int NUM_DIC = (DICCIONARIOS_FINAL - DICCIONARIOS_INICIO + PASO_DICCIONARIOS) / PASO_DICCIONARIOS;
    const int NUM_GRUPOS_LETRAS = (LERTAS_FINAL - LERTAS_INICIO + PASO_LETRAS) / PASO_LETRAS;
    const string RUTA_RESULTADOS_SOLVER = RUTA_DIR_RESULTADOS + ARCH_RESULTADOS_SOLVER;
    const string RUTA_RESULTADOS_SOLVER_EFIVIENTE = RUTA_DIR_RESULTADOS + ARCH_RESULTADOS_SOLVER_EFICIENTE;

    // Objetos que se usaran
    ifstream arch_letras; // Archivo desde donde se cargará el lettersSet
    ifstream arch_dic; // Archivo desde donde se cargarn los diccionarios usados para el analisis
    ofstream arch_result_solver; // Archivo donde se guardanán los resutlados de eficiencia para el solver
    ofstream arch_result_efficient_solver; // Archivo donde se guardanán los resutlados de eficiencia para el solver eficiente
    LettersSet letras; // Las letras y la informacion sobre estas que se usará en las partidas
    Dictionary diccionario_actual;

            // Matriz de vectores de letras disponibles. La primera coordenada ordena los grupos en funcion de su
            // numero de letras, y la segunda les da un número de grupo
    vector<vector<vector<char>>> letras_disponibles = vector<vector<vector<char>>>(NUM_GRUPOS_LETRAS,
                                                             vector<vector<char>>(NUM_BOLSAS_POR_ANALISIS,
                                                             vector<char>()));

    // Se cargan las letras
    arch_letras.open(RUTA_ARCH_LETRAS);
    if(!arch_letras.is_open()) {
        cerr << "Error al abrir el archivo de letras: " << RUTA_ARCH_LETRAS << endl;
        return -1;
    }
    arch_letras >> letras;
    arch_letras.close();

    // Creamos una bolsa con todas las letras, la cual usaremos para restaurar las bolsas que llavamos vaciando
    const LettersBag BOLSA_LLENA(letras);

    // Creamos las bolsas que se usarán en los analisis
    // Creamos varias para cada numero de letras para normalizar los resultados
    for(int numBolsa=0; numBolsa < NUM_BOLSAS_POR_ANALISIS; numBolsa++) {
        LettersBag bolsa = BOLSA_LLENA;
        vector<char> a_insertar = vector<char>();
        for(int grupoLetras = 0; grupoLetras < NUM_GRUPOS_LETRAS; grupoLetras++) {
            for(int letra=0; letra < PASO_LETRAS; letra++) {
                a_insertar.push_back(bolsa.extractLetter());
            }
            letras_disponibles[grupoLetras][numBolsa] = a_insertar;
        }
    }

    // Para comprobar que los grupos de letras se crean correctamente
//    for(int grupoLetra=0; grupoLetra<NUM_GRUPOS_LETRAS; grupoLetra++) {
//        cout << "Grupos de " << ((grupoLetra + 1)*PASO_LETRAS) << " letras: " << endl;
//        for(int numBolsa=0; numBolsa < NUM_BOLSAS_POR_ANALISIS; numBolsa++) {
//            cout << numBolsa << ". ";
//            for(int i=0; i<letras_disponibles[grupoLetra][numBolsa].size(); i++) {
//                cout << letras_disponibles[grupoLetra][numBolsa][i] << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//    }

    // Abrimos los archivos de resultados
    arch_result_solver.open(RUTA_RESULTADOS_SOLVER);
    if(!arch_result_solver.is_open()) {
        cerr << "Error al abrir el archivo de resultados: " << RUTA_RESULTADOS_SOLVER << endl;
    }
    arch_result_efficient_solver.open(RUTA_RESULTADOS_SOLVER_EFIVIENTE);
    if(!arch_result_efficient_solver.is_open()) {
        cerr << "Error al abrir el archivo de resultados: " << RUTA_RESULTADOS_SOLVER_EFIVIENTE << endl;
    }

    // Se declara una breve explicacion para dejar en los archivos resultado
    string cabecera;
    cabecera = "\"Analisis para " + to_string(NUM_DIC) + " diccionarios, el primero con "
            + to_string(DICCIONARIOS_INICIO) + " palabras, aumentando en " + to_string(PASO_DICCIONARIOS)
            + " cada vez, hasta llegar a " + to_string(DICCIONARIOS_FINAL) +".\n"
            + "Para cada diccionario se analiza la duracion del solver cuando se le pide que encuentre las "
            + "solucionies partiendo de " + to_string(LERTAS_INICIO) + " letras, aumentoado en "
            + to_string(PASO_LETRAS) + ", hasta llegar a " + to_string(LERTAS_FINAL) + ". \n"
            + "Para cada numero de letras se hace la media de " + to_string(NUM_BOLSAS_POR_ANALISIS) + " grupos de"
            + " esa canditdad de letras.\n"
            + "Las filas cambian junto al numero de palabras por diccionario y las columnas junto al numero de letras "
            + "que se le pasan al solver.\n"
            + "Las unidades estan en ms.\",\n";
    arch_result_solver << cabecera;
    arch_result_efficient_solver << cabecera;

    //Imprimimos el numero de palabras por columna
    arch_result_solver << ", ";
    arch_result_efficient_solver << ", ";
    for(int numLetras=LERTAS_INICIO; numLetras<=LERTAS_FINAL; numLetras+=PASO_LETRAS) {
        arch_result_solver << numLetras << ", ";
        arch_result_efficient_solver << numLetras << ", ";
    }
    arch_result_solver << "\n";
    arch_result_efficient_solver << "\n";

    // Hacemos el analisis para cada diccionario y numero de letras
    for(int numDic=DICCIONARIOS_INICIO; numDic <= DICCIONARIOS_FINAL; numDic += PASO_DICCIONARIOS) {
        arch_result_solver << numDic << ", ";
        arch_result_efficient_solver << numDic << ", ";

        string ruta_a_abrir = RUTA_BASE_DICCIONARIO + to_string(numDic) + ".txt";
        arch_dic.open(ruta_a_abrir);
        if(!arch_dic.is_open()) {
            cerr << "Error al abrir el archivo de diccionario: " << ruta_a_abrir << endl;
            arch_result_solver.close();
            arch_result_efficient_solver.close();
            return -1;
        }
        diccionario_actual = Dictionary();
        arch_dic >> diccionario_actual;
        arch_dic.close();
        Solver solver(diccionario_actual, letras);
        EfficientSolver efficientSolver(diccionario_actual, letras);

        for(int numLetras=0; numLetras < NUM_GRUPOS_LETRAS; numLetras++) {
            float tiempoMedioSolver = 0;
            float tiempoMedioEfficientSolver = 0;
            for(int numBolsa=0; numBolsa<NUM_BOLSAS_POR_ANALISIS; numBolsa++) {
                time_point<high_resolution_clock> inicio_calc_sol;
                float duracion_calc_sol;
                // Se establece el tipo de juego a longitud porque el calculo de la puntuacion de cada palabra es menor
                // De esta manera, así la mayoria del tiempo de computo se emplea en recorrer el diccionario
                // Calculamos tiempo del solver
                inicio_calc_sol = high_resolution_clock::now();
                solver.getSolutions(letras_disponibles[numLetras][numBolsa], false);
                duracion_calc_sol = milliseconds_f(high_resolution_clock::now() - inicio_calc_sol).count();
                tiempoMedioSolver += duracion_calc_sol;

                // Calculamos tiempo del solver eficiente
                inicio_calc_sol = high_resolution_clock::now();
                efficientSolver.getSolutions(letras_disponibles[numLetras][numBolsa], false);
                duracion_calc_sol = milliseconds_f(high_resolution_clock::now() - inicio_calc_sol).count();
                tiempoMedioEfficientSolver += duracion_calc_sol;
            }

            tiempoMedioSolver /= NUM_BOLSAS_POR_ANALISIS;
            tiempoMedioEfficientSolver /= NUM_BOLSAS_POR_ANALISIS;

            arch_result_solver << tiempoMedioSolver << ',';
            arch_result_efficient_solver << tiempoMedioEfficientSolver << ',';
        }
        arch_result_solver << '\n';
        arch_result_efficient_solver << '\n';
    }

    arch_result_solver.close();
    arch_result_efficient_solver.close();
}