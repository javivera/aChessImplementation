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
                          
///

bool piezaEnCoordenada(tablero t, coordenada c, int pza, int col){
    return pieza(t,c)==pza && color(t,c)==col;
}

bool peonesEnCoordenadas(tablero t){
    bool resp = true;
    for (int i=0; i<ANCHO_TABLERO; i++){
        if (!piezaEnCoordenada(t,mp(1,i),PEON,NEGRO) || !piezaEnCoordenada(t,mp(6,i),PEON,BLANCO)){
            resp = false;
        }
    }
    return resp;
}

bool torresEnCoordenadas(tablero t){
    bool resp = piezaEnCoordenada(t,mp(0,0),TORRE,NEGRO);
    resp = resp && piezaEnCoordenada(t,mp(0,ANCHO_TABLERO - 1),TORRE,NEGRO);
    resp = resp && piezaEnCoordenada(t,mp(ANCHO_TABLERO - 1,0),TORRE,BLANCO);
    resp = resp && piezaEnCoordenada(t,mp(ANCHO_TABLERO - 1,ANCHO_TABLERO - 1),TORRE,BLANCO);
    return resp;
}

bool alfilesEnCoordenadas(tablero t){
    bool resp = piezaEnCoordenada(t,mp(0,2),ALFIL,NEGRO);
    resp = resp && piezaEnCoordenada(t,mp(0,ANCHO_TABLERO - 3),ALFIL,NEGRO);
    resp = resp && piezaEnCoordenada(t,mp(ANCHO_TABLERO - 1,2),ALFIL,BLANCO);
    resp = resp && piezaEnCoordenada(t,mp(ANCHO_TABLERO - 1,ANCHO_TABLERO - 3),ALFIL,BLANCO);
    return resp;
}

bool reyesEnCoordenadas(tablero t){
    bool resp = piezaEnCoordenada(t,mp(0,4),REY,NEGRO);
    resp = resp && piezaEnCoordenada(t,mp(ANCHO_TABLERO - 1,4),REY,BLANCO);
    return resp;
}

bool piezasEnCoordenadas(tablero t){
    bool resp = peonesEnCoordenadas(t);
    resp = resp && torresEnCoordenadas(t);
    resp = resp && alfilesEnCoordenadas(t); 
    resp = resp && reyesEnCoordenadas(t);
    return resp;
}

bool cantidadPiezasAlInicio(tablero t){
    bool resp = aparicionesEnTablero(t,mp(TORRE,NEGRO)) == 2;
    resp = resp && aparicionesEnTablero(t,mp(TORRE,BLANCO)) == 2;
    resp = resp && aparicionesEnTablero(t,mp(ALFIL,NEGRO)) == 2;
    resp = resp && aparicionesEnTablero(t,mp(ALFIL,BLANCO)) == 2;
    resp = resp && aparicionesEnTablero(t,mp(PEON,NEGRO)) == ANCHO_TABLERO;
    resp = resp && aparicionesEnTablero(t,mp(PEON,BLANCO)) == ANCHO_TABLERO;
    return resp;
}


