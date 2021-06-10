#ifndef AJEDREZLITE_AUXILIARES_H
#define AJEDREZLITE_AUXILIARES_H

#include "definiciones.h"
using namespace std;

// Funciones preliminares:
pair<int,int> mp(int a, int b);
vector<pair<int,int>> ordenarVectorPares(vector<pair<int,int>> &v);
coordenada setCoord(int i, int j);
tablero tableroActual ( posicion const &p );
tablero inicializarTablero();


////// Nuevos segun orden de aparición:
//Funciones auxiliares:
int jugadorPosicion(posicion p);
int pieza(tablero t, coordenada c);
int color(tablero t, coordenada c);
int contrincante(int j);
int aparicionesEnTablero(tablero t, casilla c);


//Predicados auxiliares:
bool esJugadorValido(int j);
bool esMatriz(tablero t);
bool casillaVacia(casilla c);
bool casillasValidas(tablero t);
bool sinPeonesNoCoronados(tablero t);
bool piezasTorresValidas(tablero t);
bool piezasPeonesValidas(tablero t);
bool piezasAlfilesValidas(tablero t);
bool piezasReyesValidas(tablero t);
bool cantidadValidaDePiezas(tablero t);
bool esTableroValido(tablero t);


#endif //AJEDREZLITE_AUXILIARES_H
