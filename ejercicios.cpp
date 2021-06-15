#include <iostream>
#include "ejercicios.h"
#include "definiciones.h"
#include "auxiliares.h"
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
}

// EJERCICIO 6
bool finDeLaPartida ( posicion const &p, int &j ) {
    bool resp;
    if (esEmpate(p)){ 
        j = 0; //Devuelve jugador = 0.
        resp = true; //La partida termina en empate.
    } else if (esJaqueMate(p)){
        j = contrincante(jugadorPosicion(p)); //Devuelve jugador ganador.
        resp = true; //La partida termina en jaqueMate.
    } else {
        resp = false; //La partida no termina.
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
        posicion_secuencia = cambioDePosicion(posicion_forzada,s[i].first,s[i].second); //Pre: es legal.
        posicion_forzada = cambioForzado(posicion_secuencia); //Pre: es forzado (unico movimiento) y legal.
    }
    p = posicion_forzada;
    return;
}

// EJERCICIO 9
int seVieneElJaqueEn ( posicion const &p ) { //Pre: máximo 3 jugadas, mínimo una jugada.
    int k = 1;
    bool resp = false; //Pre: La partida no termino.
    while (k<3 && !resp){
        resp = hayMateForzadoEn(p,k); //Se evalua en k=1 y k=2; si estos fallan, por descarte es k=3.
        k = k + 1;
    }
    if (resp){ //El ciclo termino antes de 3.
        k = k - 1;
    }
    return k;
}

