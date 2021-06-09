#include <iostream>
#include <cmath> 
#include <vector>
#include <algorithm>
#include <utility>
#include "test.h"
#include "ejercicios.h"
#include "definiciones.h"
#include "auxiliares.h"

using namespace std;

// EJERCICIO 1
bool posicionValida ( pair < tablero, int > const &p ) {
    bool resp = esJugadorValido(jugadorPosicion(p));
    resp &= esTableroValido(tableroActual(p));
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
int seVieneElJaqueEn ( posicion const &p ) {
    int resp = -1;
    // completar codigo
    return resp;
}
