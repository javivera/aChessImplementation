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

// Funciones auxiliares:
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
int jugadorPosicion (posicion p){
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
    int contador=0,i=0,j=0;
    int dim=ANCHO_TABLERO;
    while (i<dim){
        while(j<dim){
            if (t[i][j]==c){
                contador = contador + 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    return contador;
}

//Predicados auxiliares:
bool esJugadorValido(int j){
    return (j == BLANCO || j == NEGRO);
}

bool esMatriz(tablero t){
    int dim = ANCHO_TABLERO;
    bool resp = (t.size() == dim);
    int i = 0;
    while (i<dim){
        if (t[i].size() != dim)
            resp = false;
        i = i + 1;
    }
    return resp;
}

bool casillaVacia(casilla c){
    return (c.first==0 && c.second==0);
}

bool casillasValidas(tablero t){
    int dim = ANCHO_TABLERO;
    int i=0,j=0;
    bool resp=true;
    casilla c;
    while (i<dim){
        while (j<dim){
            c = t[i][j];
            resp &= (casillaVacia(c) || (PEON<=c.first<=REY && BLANCO<=c.second<=NEGRO));
            j = j + 1;
        }
        i = i + 1;
    }
    return resp;
}

bool sinPeonesNoCoronados(tablero t){
    int dim = ANCHO_TABLERO;
    int i=0;
    bool resp = true;
    while(i<dim){
        if(pieza(t,setCoord(0,i))==PEON || pieza(t,setCoord(dim-1,i))==PEON){
            resp = false;
        }
        i = i + 1; 
    }
    return resp;
}

bool cantidadValidaDePiezas(tablero t){
    bool resp = piezasTorresValidas(t);
    resp &= piezasPeonesValidas(t);
    resp &= piezasAlfilesValidas(t);
    resp &= piezasReyesValidas(t);
    return resp;
}

bool piezasTorresValidas(tablero t){
    int dim = ANCHO_TABLERO;
    casilla c_t,c_p;
    c_t = mp(TORRE,BLANCO);
    c_p = mp(PEON,BLANCO);
    bool resp = (aparicionesEnTablero(t,c_t) <= 2 + dim - aparicionesEnTablero(t,c_p));
    c_t = mp(TORRE,NEGRO);
    c_p = mp(PEON,NEGRO);
    resp &= (aparicionesEnTablero(t,c_t) <= 2 + dim - aparicionesEnTablero(t,c_p));
    return resp;
}

bool piezasPeonesValidas(tablero t){
    int dim = ANCHO_TABLERO;
    casilla c;
    c = mp(PEON,BLANCO);
    bool resp = (aparicionesEnTablero(t,c)<=dim);
    c = mp(PEON,NEGRO);
    resp &= (aparicionesEnTablero(t,c)<=dim);
    return resp;
}

bool piezasAlfilesValidas(tablero t){
    casilla c;
    c = mp(ALFIL,BLANCO);
    bool resp = (aparicionesEnTablero(t,c)<=2);
    c = mp(ALFIL,NEGRO);
    resp &= (aparicionesEnTablero(t,c)<=2);
    return resp;
}

bool piezasReyesValidas(tablero t){
    casilla c;
    c = mp(REY,BLANCO);
    bool resp = (aparicionesEnTablero(t,c)==1);
    c = mp(REY,NEGRO);
    resp &= (aparicionesEnTablero(t,c)==1);
    return resp;
}

bool esTableroValido(tablero t){
    bool resp = esMatriz(t);
    resp &= casillasValidas(t);
    resp &= sinPeonesNoCoronados(t);
    resp &= cantidadValidaDePiezas(t);
    return resp;
}

