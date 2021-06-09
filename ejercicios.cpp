#include <algorithm>
#include "ejercicios.h"
#include <iostream>
using namespace std;

// EJERCICIO 1
bool posicionValida ( pair < tablero, int > const &p ) {
    bool resp = false;
    if (p.first.size() == 1 ) {
        // Si el tablero es vacío devuelve false en el moment
        return false;
    }
    else{
        for (int fil = 0 ; fil < p.first.size() ; fil++ ){
            for (int col = 0 ; col < p.first[0].size() ; col ++){
                // Itera sobre el tablero
                if (p.first[fil][col].first < 5 and p.first[fil][col].first > 1 ){
                // Si encuentra una pieza correcta , cambia la respuesta a true
                    resp = true;
                }
                if (p.first[fil][col].first > 4 and p.first[fil][col].first < 0){
                // Este no es necesario es para optimizar el código , si encuentra alguna casiila que tiene una pieza inválida no mirá el resto
                    return false;
                }
            }
        }
    }
    return resp;
}

// EJERCICIO 2
bool posicionInicial ( posicion const &p ) {
    bool resp = false;

    // completar codigo

    return resp;
}
// EJERCICIO 3
vector <coordenada> casillasAtacadas ( posicion const &p, int j ) {
    vector <coordenada> cA;
    // completar codigo
    return cA;
}
// EJERCICIO 4
bool posicionSiguienteCorrecta ( posicion const &p1, posicion const &p2, coordenada o, coordenada d ) {
    bool resp = false;
    // completar codigo
    return resp;
}
// EJERCICIO 5
void ordenarTablero ( posicion &p ) {
    // completar codigo
    return;
}
// EJERCICIO 6
bool finDeLaPartida ( posicion const &p, int &j ) {
    bool resp = false;
    // completar codigo
    return resp;
}
// EJERCICIO 7
bool hayJaqueDescubierto ( posicion const &p ) {
    bool resp = false;
    // completar codigo
    return resp;
}
// EJERCICIO 8
void ejecutarSecuenciaForzada ( posicion &p, secuencia s ) {
    // completar codigo
    return;
}
// EJERCICIO 9
int seVieneElJaqueEn ( posicion const & p ) {
    int resp = -1;
    // completar codigo
    return resp;
}
