#include <algorithm>
#include "ejercicios.h"
#include "definiciones.h"
#include "auxiliares.h"
#include <iostream>
using namespace std;

// EJERCICIO 1
bool posicionValida ( pair < tablero, int > const &p ) {
    return esJugadorValido(jugadorPosicion(p)) && esTableroValido(tableroActual(p));
}

// EJERCICIO 2
bool posicionInicial ( posicion const &p ) { //Pre: esPosicionValida(p)
    bool resp = piezasEnCoordenadas(tableroActual(p));
    resp = resp && cantidadPiezasAlInicio(tableroActual(p));
    resp = resp && jugadorPosicion(p) == BLANCO;
    return resp;
}

// EJERCICIO 3
vector <coordenada> casillasAtacadas ( posicion const &p, int j ) {
    vector <coordenada> cA;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int k=0; k<ANCHO_TABLERO; k++){
            if (esCasillaAtacada(tableroActual(p),j,mp(i,k)))
                cA.push_back(mp(i,k));
        }
    }
    return cA;
}

// EJERCICIO 4
bool posicionSiguienteCorrecta ( posicion const &p1, posicion const &p2, coordenada o, coordenada d ) {
    return posicionSiguiente(p1,p2,o,d);
}

// EJERCICIO 5
void ordenarTablero ( posicion &p ) {
    tablero t = tableroActual(p);
    for (int f=0; f<ANCHO_TABLERO; f++){
        ordenarFila(t,f);
    }
    p = make_pair(t,jugadorPosicion(p));
    return;
}

// EJERCICIO 6
bool finDeLaPartida ( posicion const &p, int &j ) {
    bool resp;
    if (esEmpate(p)){ //jugador = 0
        j = 0;
        resp = true; //termina
    } else if (esJaqueMate(p)){
        j = contrincante(jugadorPosicion(p)); //jugador ganador
        resp = true; //termina
    } else {
        resp = false; //no termina
    }
    return resp;
}

// EJERCICIO 7
bool hayJaqueDescubierto ( posicion const &p ) {
    return alMoverQuedaEnJaque(p);
}

// EJERCICIO 8
void ejecutarSecuenciaForzada ( posicion &p, secuencia s ) {
    posicion posicion_secuencia, posicion_forzada = p;
    for (int i=0; i<s.size(); i++){ //Pre: s.size()>0
        posicion_secuencia = cambioDePosicion(posicion_forzada,s[i].first,s[i].second);
        posicion_forzada = cambioForzado(posicion_secuencia); //Pre: es forzado.
    }
    p = posicion_forzada;
    return;
}

// EJERCICIO 9
int seVieneElJaqueEn ( posicion const & p ) { //Pre: maximo 3 jugadas.
    int k = 1;
    bool resp = false;
    while (k<3 && !resp){
        resp = hayMateForzadoEn(p,k);
        k = k + 1;
    }
    if (resp){ //El ciclo termino antes de 3.
        k = k - 1;
    }
    return k;
}
