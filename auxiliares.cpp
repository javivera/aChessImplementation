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

int minimo(int x, int y){
    if (x<y)
        return x;
    else
        return y;
}

int maximo(int x, int y){
    if (x<y)
        return y;
    else
        return x;
}

//Predicados auxiliares:
//Ejercicio 1:
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
                          
//Ejercicio 2:

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

//Impresion:

void imprimir_coordenada(coordenada c){
    cout << "(" << c.first << ", " << c.second << ")";
}

void imprimir_vector_de_coordenadas(vector<coordenada> v){
    cout << "<";
    if (v.size()>0){
        for (int i=0; i<v.size()-1; i++){
            imprimir_coordenada(v[i]);
            cout << ", ";
        }
        imprimir_coordenada(v[v.size()-1]);
    }
    cout << ">" << endl;
}

void imprimir_casilla(casilla c){
    if (c==mp(0,0))
        cout << " cVacia ";
    else if (c==mp(PEON,BLANCO))
        cout << "cPeon_B ";
    else if (c==mp(PEON,NEGRO))
        cout << "cPeon_N ";
    else if (c==mp(TORRE,BLANCO))
        cout << "cTorre_B";
    else if (c==mp(TORRE,NEGRO))
        cout << "cTorre_N";
    else if (c==mp(ALFIL,BLANCO))
        cout << "cAlfil_B";
    else if (c==mp(ALFIL,NEGRO))
        cout << "cAlfil_N";
    else if (c==mp(REY,BLANCO))
        cout << " cRey_B ";
    else if (c==mp(REY,NEGRO))
        cout << " cRey_N ";
}

void imprimir_tablero(tablero t){ //Pre: tableroValido(p)
    cout << endl;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int j=0; j<ANCHO_TABLERO; j++){
            imprimir_casilla(t[i][j]);
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Ejercicio 3:

bool mueveEnHorizontal(coordenada o, coordenada d){
    return (abs(o.first - d.first) == 0) && (abs(o.second - d.second) == 1);
}

bool mueveEnVertical(coordenada o, coordenada d){
    return (abs(o.first - d.first) == 1) && (abs(o.second - d.second) == 0);
}

bool mueveEnDiagonal(coordenada o, coordenada d){
    return (abs(o.first - d.first) == 1) && (abs(o.second - d.second) == 1);
}

bool movimientoPeonValido(int color, coordenada o, coordenada d){
    bool resp = (o.second == d.second);
    bool opcion_1 = (color == BLANCO && (d.first == o.first - 1));
    bool opcion_2 = (color == NEGRO && (d.first == o.first + 1));
    return resp && (opcion_1 || opcion_2);
}

bool movimientoAlfilValido(tablero t, coordenada o, coordenada d){
    int a = d.first - o.first;
    int b = d.second - o.second;
    bool resp = (abs(a) == abs(b));
    if (resp){
        for (int i=1; i<abs(a); i++){ ///REVISAAARR
            if (a>0 && b>0)
                resp = resp && casillaVacia(t[o.first + i][o.second + i]); 
            else if (a>0 && b<0)
                resp = resp && casillaVacia(t[o.first + i][o.second - i]);
            else if (a<0 && b>0)
                resp = resp && casillaVacia(t[o.first - i][o.second + i]);
            else if (a<0 && b<0)
                resp = resp && casillaVacia(t[o.first - i][o.second - i]);
        }
    }
    return resp;
}

bool movimientoTorreValido(tablero t, coordenada o, coordenada d){ //REVISAAAR
    bool opcion_1 = d.second == o.second;
    bool opcion_2 = d.first == o.first;
    bool resp = opcion_1 || opcion_2;
    if (opcion_1){ //Movimiento horizontal
        for (int i=minimo(d.first,o.first)+1; i<maximo(d.first,o.first); i++){
            resp = resp && casillaVacia(t[i][d.second]);
        }
    }
    if (opcion_2){ //Movimiento vertical
        for (int i=minimo(d.second,o.second)+1; i<maximo(d.second,o.second); i++){
            resp = resp && casillaVacia(t[d.first][i]);
        }
    }
    return resp;
}

bool movimientoReyValido(coordenada o, coordenada d){
    return mueveEnDiagonal(o,d) || mueveEnVertical(o,d) || mueveEnHorizontal(o,d);
}

bool movimientoPiezaValido(tablero t, coordenada o, coordenada d){
    bool opcion_1 = (pieza(t,o) == PEON && movimientoPeonValido(color(t,o),o,d));
    bool opcion_2 = (pieza(t,o) == ALFIL && movimientoAlfilValido(t,o,d));
    bool opcion_3 = (pieza(t,o) == TORRE && movimientoTorreValido(t,o,d));
    bool opcion_4 = (pieza(t,o) == REY && movimientoReyValido(o,d));
    return (opcion_1 || opcion_2 || opcion_3 || opcion_4);
}

bool capturaPeonValida(tablero t, coordenada o, coordenada d){ // o ataca a d
    bool resp = abs(d.second - o.second) == 1;
    bool opcion_1 = (color(t,o) == BLANCO && (d.first == o.first - 1));
    bool opcion_2 = (color(t,o) == NEGRO && (d.first == o.first + 1));
    return resp && (opcion_1 || opcion_2);
}

bool casillaAtacada(tablero t, coordenada o, coordenada d){ // o ataca a d
    bool resp = !casillaVacia(t[o.first][o.second]);
    bool opcion_1 = (pieza(t,o) != PEON) && movimientoPiezaValido(t,o,d);
    bool opcion_2 = (pieza(t,o) == PEON) && capturaPeonValida(t,o,d);
    return resp && (opcion_1 || opcion_2);
}

bool esCasillaAtacada(tablero t, int jugador, coordenada o){
    bool resp = false;
    coordenada d;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int j=0; j<ANCHO_TABLERO; j++){
            d = mp(i,j);
            if (o != d && color(t,d)==jugador && casillaAtacada(t,d,o)) // d ataca a o
                resp = true;
        }
    }
    return resp;
}

