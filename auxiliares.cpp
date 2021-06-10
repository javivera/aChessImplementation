#include "definiciones.h"
#include "auxiliares.h"
#include <iostream>
using namespace std;

// Funciones auxiliares preliminares:
pair<int,int> mp(int a, int b) {
    return make_pair(a, b);
}

// TEST
vector<pair<int,int>> ordenarVectorPares(vector<pair<int,int>> &v) {
    sort(v.begin(), v.end());
//    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

coordenada setCoord(int i, int j) {
    return make_pair(i,j);
}

tablero tableroActual ( posicion const &p ) {
    return p.first;
}

tablero inicializarTablero(){
    vector<casilla> fila(ANCHO_TABLERO, cVACIA);
    tablero out(ANCHO_TABLERO, fila);
    return out;
}

////// Nuevos segun orden de aparición:

//Funciones auxiliares:
int jugadorPosicion(posicion p){
    return p.second;
}

int pieza(tablero t, coordenada c){
    return (t[c.first][c.second]).first;
}

int color(tablero t, coordenada c){
    return (t[c.first][c.second]).second;
}

int contrincante(int j){
    if (j==BLANCO)
        return NEGRO;
    else
        return BLANCO;
}

int aparicionesEnTablero(tablero t, casilla c){
    int contador=0;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int j=0; j<ANCHO_TABLERO; j++){
            if (t[i][j]==c)
                contador = contador + 1;
        }
    }
    return contador;
}

//Predicados auxiliares:
bool esJugadorValido(int j){
    return (j == BLANCO || j == NEGRO);
}

bool esMatriz(tablero t){
    bool resp = (t.size() == ANCHO_TABLERO);
    if (resp){
        for (int i=0; i<ANCHO_TABLERO; i++){
            if (t[i].size() != ANCHO_TABLERO)
                resp = false;
        }
    }
    return resp;
}

bool casillaVacia(casilla c){
    return (c.first == 0 && c.second == 0);
}

bool casillasValidas(tablero t){
    bool resp = true;
    casilla c;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int j=0; j<ANCHO_TABLERO; j++){
            c = t[i][j];
            resp = resp && (casillaVacia(c) || (PEON<=c.first<=REY && BLANCO<=c.second<=NEGRO));
        }
    }
    return resp;
}

bool sinPeonesNoCoronados(tablero t){
    bool resp = true;
    for (int i=0; i<ANCHO_TABLERO; i++){
        if (pieza(t,mp(0,i))==PEON || pieza(t,mp(ANCHO_TABLERO-1,i))==PEON)
            resp = false;
    }
    return resp;
}

bool piezasTorresValidas(tablero t){
    casilla c_t,c_p;
    c_t = mp(TORRE,BLANCO);
    c_p = mp(PEON,BLANCO);
    bool resp = (aparicionesEnTablero(t,c_t) <= 2 + ANCHO_TABLERO - aparicionesEnTablero(t,c_p));
    c_t = mp(TORRE,NEGRO);
    c_p = mp(PEON,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c_t) <= 2 + ANCHO_TABLERO - aparicionesEnTablero(t,c_p));
    return resp;
}

bool piezasPeonesValidas(tablero t){
    casilla c;
    c = mp(PEON,BLANCO);
    bool resp = (aparicionesEnTablero(t,c) <= ANCHO_TABLERO);
    c = mp(PEON,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c) <= ANCHO_TABLERO);
    return resp;
}

bool piezasAlfilesValidas(tablero t){
    casilla c;
    c = mp(ALFIL,BLANCO);
    bool resp = (aparicionesEnTablero(t,c) <= 2);
    c = mp(ALFIL,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c) <= 2);
    return resp;
}

bool piezasReyesValidas(tablero t){
    casilla c;
    c = mp(REY,BLANCO);
    bool resp = (aparicionesEnTablero(t,c) == 1);
    c = mp(REY,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c) == 1);
    return resp;
}

bool cantidadValidaDePiezas(tablero t){
    bool resp = piezasTorresValidas(t);
    resp = resp && piezasPeonesValidas(t);
    resp = resp && piezasAlfilesValidas(t);
    resp = resp && piezasReyesValidas(t);
    return resp;
}

bool esTableroValido(tablero t){
    bool resp = esMatriz(t);
    resp = resp && casillasValidas(t);
    resp = resp && sinPeonesNoCoronados(t);
    resp = resp && cantidadValidaDePiezas(t);
    return resp;
}
                          
