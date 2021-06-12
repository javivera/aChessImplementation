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

int minimo(int x, int y);
int maximo(int x, int y);

posicion cambioDePosicion(posicion p, coordenada o, coordenada d);
posicion cambioForzado(posicion p);

vector<coordenada> secuenciaDePiezasDeJugador(posicion p, int jugador);
vector<coordenada> coordenadasConMovimientos(posicion p, int jugador);
vector<coordenada> casillaMovimientosPosibles(posicion p, int jugador);

coordenada coordenadaRey(tablero t, int jugador);

pair<coordenada,coordenada> unicoMovimientoForzado(posicion p, int jugador);

//Predicados auxiliares:
//Impresion:
void imprimir_coordenada(coordenada c);
void imprimir_vector_de_coordenadas(vector<coordenada> v);
void imprimir_casilla(casilla c);
void imprimir_tablero(tablero t);
void imprimir_secuencia_doble_coordenada(secuencia s);

//Ejercicio 1:
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

//Ejercicio 2:
bool piezaEnCoordenada(tablero t, coordenada c, int pza, int col);
bool peonesEnCoordenadas(tablero t);
bool torresEnCoordenadas(tablero t);
bool alfilesEnCoordenadas(tablero t);
bool reyesEnCoordenadas(tablero t);
bool piezasEnCoordenadas(tablero t);
bool cantidadPiezasAlInicio(tablero t);

//Ejercicio 3:
bool mueveEnHorizontal(coordenada o, coordenada d);
bool mueveEnVertical(coordenada o, coordenada d);
bool mueveEnDiagonal(coordenada o, coordenada d);
bool movimientoPeonValido(tablero t, coordenada o, coordenada d);
bool movimientoAlfilValido(tablero t, coordenada o, coordenada d);
bool movimientoTorreValido(tablero t, coordenada o, coordenada d);
bool movimientoReyValido(tablero t, coordenada o, coordenada d);
bool movimientoPiezaValido(tablero t, coordenada o, coordenada d);
bool capturaPeonValida(tablero t, coordenada o, coordenada d);
bool casillaAtacada(tablero t, coordenada o, coordenada d);
bool esCasillaAtacada(tablero t, int jugador, coordenada o);

//Ejercicio 4:
bool coordenadaEnSecuencia(vector<coordenada> s, coordenada c);
bool posicionesIgualesExceptoEn(posicion p, posicion q, vector<coordenada> s);
bool esMovimientoValido(posicion p, coordenada o, coordenada d);
bool esCapturaValida(posicion p, coordenada o, coordenada d);
bool enLineaFinalInicial(coordenada d);
bool piezaCorrectaEnDestino(posicion p, posicion q, coordenada o, coordenada d);
bool posicionSiguiente(posicion p, posicion q, coordenada o, coordenada d);

//Ejercicio 5:

//Ejercicio 6:
bool soloHayReyes(tablero t);
bool jugadorEnJaque(posicion p, int jugador);
bool piezasDeJugador(posicion p, vector<coordenada> s);
bool tienenMovimiento(posicion p, vector<coordenada> piezas);
bool hayMovimientosLegales(posicion p); 
bool esEmpate(posicion p);
bool loPoneEnJaque(posicion p, coordenada o, coordenada d);
bool esJugadaLegal(posicion p, coordenada o, coordenada d);
bool existeMovimientoParaSalirDelJaque(posicion p);
bool esJaqueMate(posicion p);

//Ejercicio 7:
bool alMoverQuedaEnJaque(posicion p);



#endif //AJEDREZLITE_AUXILIARES_H
