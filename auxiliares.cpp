#include "definiciones.h"
#include "auxiliares.h"
#include <iostream>
using namespace std;
// aqui se pueden ubicar todas las funciones auxiliares de soporte para la resolucion de los ejercicios
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
        j = 0;
        while(j<dim){
            if (t[i][j]==c){
                contador++;
            }
            j++;
        }
        i++;
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
    if(resp) {
        int i = 0;
        while (i < dim) {
            if (t[i].size() != dim)
                resp = false;
            i = i + 1;
        }
    }
    return resp;
}

bool casillaVacia(casilla c){
    return (c.first == 0 && c.second == 0);
}

bool casillasValidas(tablero t){
    int dim = ANCHO_TABLERO;
    int i=0,j=0;
    bool resp=true;
    casilla c;
    while (i<dim){
        j = 0;
        while (j<dim){
            c = t[i][j];
            cout << c.first;
            resp = resp && (casillaVacia(c) || (PEON<=c.first<=REY && BLANCO<=c.second<=NEGRO));
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


bool piezasTorresValidas(tablero t){
    int dim = ANCHO_TABLERO;
    casilla c_t,c_p;
    c_t = mp(TORRE,BLANCO);
    c_p = mp(PEON,BLANCO);
    bool resp = (aparicionesEnTablero(t,c_t) <= 2 + dim - aparicionesEnTablero(t,c_p));
    c_t = mp(TORRE,NEGRO);
    c_p = mp(PEON,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c_t) <= 2 + dim - aparicionesEnTablero(t,c_p));
    return resp;
}

bool piezasPeonesValidas(tablero t){
    int dim = ANCHO_TABLERO;
    casilla c;
    c = mp(PEON,BLANCO);
    bool resp = (aparicionesEnTablero(t,c)<=dim);
    c = mp(PEON,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c)<=dim);
    return resp;
}

bool piezasAlfilesValidas(tablero t){
    casilla c;
    c = mp(ALFIL,BLANCO);
    bool resp = (aparicionesEnTablero(t,c)<=2);
    c = mp(ALFIL,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c)<=2);
    return resp;
}

bool piezasReyesValidas(tablero t){
    casilla c = mp(4,1);
    int prueba = REY;
    bool resp = (aparicionesEnTablero(t,c)==1);
    c = mp(REY,NEGRO);
    resp = resp && (aparicionesEnTablero(t,c)==1);
    return resp;
}

bool cantidadValidaDePiezas(tablero t){
    bool resp = piezasTorresValidas(t) && piezasPeonesValidas(t) && piezasAlfilesValidas(t) && piezasReyesValidas(t);
    return resp;
}

bool esTableroValido(tablero t){
    bool resp = esMatriz(t) && casillasValidas(t) && sinPeonesNoCoronados(t) && cantidadValidaDePiezas(t);
    return resp;
}
