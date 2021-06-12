#include "definiciones.h"
#include "auxiliares.h"
#include <iostream>
using namespace std;

// Funciones auxiliares preliminares:
pair<int,int> mp(int a, int b) {
    return make_pair(a, b);
}

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

posicion cambioDePosicion(posicion p, coordenada o, coordenada d){ //Pre: mov y cap valido
    tablero t = tableroActual(p);
    if (enLineaFinalInicial(d) && pieza(t,o)==PEON){
        t[d.first][d.second] = mp(TORRE,color(t,o));
        t[o.first][o.second] = cVACIA;
    } else {
        t[d.first][d.second] = t[o.first][o.second];
        t[o.first][o.second] = cVACIA;
    }
    posicion posicion_cambiada = make_pair(t,contrincante(jugadorPosicion(p)));
    return posicion_cambiada;
}

posicion cambioForzado(posicion p){
    pair<coordenada,coordenada> movimiento = unicoMovimientoForzado(p,jugadorPosicion(p));
    posicion forzada = cambioDePosicion(p,movimiento.first,movimiento.second);
    return forzada;
}

vector<coordenada> secuenciaDePiezasDeJugador(posicion p, int jugador){
    tablero t = tableroActual(p);
    vector<coordenada> piezas;
    coordenada c;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int j=0; j<ANCHO_TABLERO; j++){
            c = mp(i,j);
            if (color(t,c) == jugador)
                piezas.push_back(c);
        }
    }
    return piezas;
}

vector<coordenada> coordenadasConMovimientos(posicion p, int jugador){
    tablero t = tableroActual(p);
    vector<coordenada> piezasConMovimiento;
    vector<coordenada> piezas = secuenciaDePiezasDeJugador(p,jugador);
    int i=0;
    while (i<piezas.size()){
        piezasConMovimiento.push_back(piezas[i]);
        if(!tienenMovimiento(p,piezasConMovimiento)){
            piezasConMovimiento.pop_back();
        }
        i++;
    }
    return piezas;
}

vector<coordenada> casillaMovimientosPosibles(posicion p, int jugador){
    vector<coordenada> lugares;
    vector<coordenada> piezas = secuenciaDePiezasDeJugador(p,jugador);
    coordenada d;
    bool b;
    for (int i=0; i<ANCHO_TABLERO; i++){
        for (int j=0; j<ANCHO_TABLERO; j++){
            d = mp(i,j);
            b = false;
            for (int k=0; k<piezas.size() && !b; k++){
                if (esMovimientoValido(p,piezas[k],d) || esCapturaValida(p,piezas[k],d)){
                    lugares.push_back(d);
                    b = true;
                }
            }
        }
    }
    return lugares;
}

coordenada coordenadaRey(tablero t, int jugador){
    bool resp = false;
    coordenada c;
    for (int i=0; i<ANCHO_TABLERO && !resp; i++){
        for (int j=0; j<ANCHO_TABLERO && !resp; j++){
            c = mp(i,j);
            if (t[i][j] == mp(REY,jugador)){
                resp = true;
            }
        }
    }
    return c;
}

secuencia movimientosLegales(posicion p, int jugador){
    vector<coordenada> piezas = coordenadasConMovimientos(p,jugador);
    vector<coordenada> lugares = casillaMovimientosPosibles(p,jugador);
    secuencia s;
    pair<coordenada,coordenada> movimiento;
    for (int i=0; i<piezas.size(); i++){
        if (lugares.size()>0){ //No hay empate o jaquemate.
            for (int j=0; j<lugares.size(); j++){
                if (esJugadaLegal(p,piezas[i],lugares[j])){
                    movimiento = make_pair(piezas[i],lugares[j]);
                    s.push_back(movimiento);
                }
            }
        }
    }
    return s;
}

pair<coordenada,coordenada> unicoMovimientoForzado(posicion p, int jugador){ //Pre: movimiento forzado.
    secuencia movimientos = movimientosLegales(p,jugador);
    return movimientos[0];
}

//Predicados auxiliares:
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

void imprimir_secuencia_doble_coordenada(secuencia s){
    cout << "<";
    if (s.size()>0){
        for (int i=0; i<s.size(); i++){
            cout << "<";
            imprimir_coordenada(s[i].first);
            cout << ",";
            imprimir_coordenada(s[i].second);
            cout << ">";
        }
    }
    cout << ">" << endl;
}

//Ejercicio 1:

bool esJugadorValido(int j){
    return (j == BLANCO || j == NEGRO);
}

bool esMatriz(tablero t){
    bool resp = (t.size() == ANCHO_TABLERO);
    if (resp){
        for (int i=0; i<ANCHO_TABLERO && resp; i++){
            if (t[i].size() != ANCHO_TABLERO){
                resp = false;
            }
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
    for (int i=0; i<ANCHO_TABLERO && resp; i++){
        if (pieza(t,mp(0,i))==PEON || pieza(t,mp(ANCHO_TABLERO-1,i))==PEON){
            resp = false;
        }
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
    for (int i=0; i<ANCHO_TABLERO && resp; i++){
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
    for (int i=0; i<ANCHO_TABLERO && !resp; i++){
        for (int j=0; j<ANCHO_TABLERO && !resp; j++){
            d = mp(i,j);
            if (o != d && color(t,d)==jugador && casillaAtacada(t,d,o)){ // d ataca a o
                resp = true;
            }
        }
    }
    return resp;
}

//Ejercicio 4:

bool coordenadaEnSecuencia(vector<coordenada> s, coordenada c){
    bool resp = false;
    for (int i=0; i<s.size() && !resp; i++){
        if (s[i]==c)
            resp = true;
    }
    return resp;
}

bool posicionesIgualesExceptoEn(posicion p, posicion q, vector<coordenada> s){
    bool resp = true;
    tablero t_p = tableroActual(p), t_q = tableroActual(q);
    for (int i=0; i<ANCHO_TABLERO && resp; i++){
        for (int j=0; j<ANCHO_TABLERO && resp; j++){
            if (!coordenadaEnSecuencia(s,mp(i,j))){
                resp = resp && t_p[i][j] == t_q[i][j]; //casillas iguales
            }
        }
    }
    return resp;
}

bool esMovimientoValido(posicion p, coordenada o, coordenada d){
    tablero t = tableroActual(p);
    bool resp = jugadorPosicion(p) == color(t,o);
    resp = resp && !casillaVacia(t[o.first][o.second]);
    resp = resp && casillaVacia(t[d.first][d.second]);
    resp = resp && movimientoPiezaValido(t,o,d);
    return resp;
}

bool esCapturaValida(posicion p, coordenada o, coordenada d){
    tablero t = tableroActual(p);
    bool resp = !casillaVacia(t[o.first][o.second]);
    resp = resp && !casillaVacia(t[d.first][d.second]);
    resp = resp && color(t,o) != color(t,d);
    resp = resp && casillaAtacada(t,o,d);
    return resp;
} 

bool enLineaFinalInicial(coordenada d){
    return (d.first == 0 || d.first == ANCHO_TABLERO - 1); 
}

bool piezaCorrectaEnDestino(posicion p, posicion q, coordenada o, coordenada d){
    tablero t_p = tableroActual(p), t_q = tableroActual(q);
    bool resp = color(t_p,o) == color(t_q,d);
    bool opcion_1 = pieza(t_p,o) == PEON && enLineaFinalInicial(d) && pieza(t_q,d) == TORRE;
    bool opcion_2 = !(pieza(t_p,o) == PEON && enLineaFinalInicial(d)) && pieza(t_p,o) == pieza(t_q,d);
    return resp && (opcion_1 || opcion_2);
}

bool posicionSiguiente(posicion p, posicion q, coordenada o, coordenada d){
    vector<coordenada> s;
    s.push_back(o);
    s.push_back(d);
    tablero t_q = tableroActual(q);
    bool resp = posicionesIgualesExceptoEn(p,q,s);
    resp = resp && casillaVacia(t_q[o.first][o.second]);
    resp = resp && (esMovimientoValido(p,o,d) || esCapturaValida(p,o,d));
    resp = resp && piezaCorrectaEnDestino(p,q,o,d);
    return resp;
}

//Ejercicio 5:

void ordenarFila(tablero &t, int f){ //SelectionSort modificado (eligiendo minimo no 0).
    for (int i=0; i<ANCHO_TABLERO; i++){ 
        if (!casillaVacia(t[f][i])){
            seleccionMinimo(t,f,i);
        }
    }
}

void seleccionMinimo(tablero &t, int f, int i){
    int minimo = i;
    for (int j=i; j<ANCHO_TABLERO; j++){
        if ((!casillaVacia(t[f][j])) && t[f][j].first < t[f][minimo].first){
            minimo = j;
        }
    }
    swapCasillas(t,f,i,minimo);
}

void swapCasillas(tablero &t, int f, int i, int j){
    casilla c = t[f][i];
    t[f][i] = t[f][j];
    t[f][j] = c;
}

//Ejercicio 6:

bool soloHayReyes(tablero t){
    bool resp = aparicionesEnTablero(t,mp(REY,BLANCO)) == 1 && aparicionesEnTablero(t,mp(REY,NEGRO)) == 1;
    for (int i=PEON; i<REY && resp; i++){
        if (aparicionesEnTablero(t,mp(i,BLANCO)) != 0 || aparicionesEnTablero(t,mp(i,NEGRO)) != 0)
            resp = false;
    }
    return resp;
}

bool jugadorEnJaque(posicion p, int jugador){
    tablero t = tableroActual(p);
    coordenada rey = coordenadaRey(t,jugador);
    return esCasillaAtacada(t,contrincante(jugador),rey);
}

bool piezasDeJugador(posicion p, vector<coordenada> s){
    bool resp = true;
    if (s.size() > 0){
        for (int i=0; i<s.size() && resp; i++){
            if (color(tableroActual(p),s[i]) != jugadorPosicion(p))
                resp = false;
        }
    }
    return resp;
}

bool tienenMovimiento(posicion p, vector<coordenada> piezas){
    bool resp = (piezas.size() > 0);
    tablero t = tableroActual(p);
    coordenada d;
    int k = 0;
    while (k<piezas.size() && resp){
        resp = false;
        for (int i=0; i<ANCHO_TABLERO && !resp; i++){
            for (int j=0; j<ANCHO_TABLERO && !resp; j++){
                d = mp(i,j);
                if (esMovimientoValido(p,piezas[k],d) || esCapturaValida(p,piezas[k],d)){
                    resp = true;
                }
            }
        }
        k++;
    }
    return (k==piezas.size());
}

bool hayMovimientosLegales(posicion p){
    bool resp = false;
    coordenada c;
    vector<coordenada> piezas;
    for (int i=0; i<ANCHO_TABLERO && !resp; i++){
        for (int j=0; j<ANCHO_TABLERO && !resp; j++){
            c = mp(i,j);
            piezas.push_back(c);
            if (piezasDeJugador(p,piezas) && tienenMovimiento(p,piezas)){
                resp = true;
            } else {
                piezas.pop_back();
            }
        }
    }
    return resp;
}

bool esEmpate(posicion p){ 
    bool opcion_1 = soloHayReyes(tableroActual(p));
    bool opcion_2 = (!jugadorEnJaque(p,jugadorPosicion(p)) && !hayMovimientosLegales(p));
    return opcion_1 || opcion_2;
}

bool loPoneEnJaque(posicion p, coordenada o, coordenada d){
    posicion p_siguiente = cambioDePosicion(p,o,d); //si no es mov valido, lo deja igual
    bool resp = posicionSiguiente(p,p_siguiente,o,d);
    resp = resp && jugadorEnJaque(p_siguiente,jugadorPosicion(p));
    return resp;
}

bool esJugadaLegal(posicion p, coordenada o, coordenada d){
    bool resp = esMovimientoValido(p,o,d) || esCapturaValida(p,o,d);
    resp = resp && !loPoneEnJaque(p,o,d);
    return resp;
}

bool existeMovimientoParaSalirDelJaque(posicion p){
    tablero t = tableroActual(p);
    vector<coordenada> movibles = coordenadasConMovimientos(p,jugadorPosicion(p));
    vector<coordenada> lugares = casillaMovimientosPosibles(p,jugadorPosicion(p));
    bool resp = false;
    if (movibles.size() > 0 && lugares.size() > 0){
        for (int i=0; i<movibles.size() && !resp; i++){
            for (int j=0; j<lugares.size() && !resp; j++){
                if (esJugadaLegal(p,movibles[i],lugares[j])){ //esa jugada es valida y no tiene jaque
                    resp = true;
                }
            }
        }
    }
    return resp;
}

bool esJaqueMate(posicion p){
    bool resp = jugadorEnJaque(p,jugadorPosicion(p));
    resp = resp && !existeMovimientoParaSalirDelJaque(p);
    return resp;
}

//Ejercicio 7:

bool alMoverQuedaEnJaque(posicion p){
    posicion posicion_siguiente;
    secuencia movimientos = movimientosLegales(p,jugadorPosicion(p));
    bool resp = false;
    for (int i=0; i<movimientos.size() && !resp; i++){
        posicion_siguiente = cambioDePosicion(p,movimientos[i].first,movimientos[i].second);
        if (jugadorEnJaque(posicion_siguiente,jugadorPosicion(posicion_siguiente)))
            resp = true;
    }
    return resp;
}

//Ejercicio 9:

bool movimientoForzado(posicion p){
    secuencia movimientos = movimientosLegales(p,jugadorPosicion(p));
    return movimientos.size() == 1;
}

bool hayMateEnUno(posicion p){ //Pre: La jugada no termino (mov>0).
    posicion posicion_siguiente;
    secuencia movimientos = movimientosLegales(p,jugadorPosicion(p));
    bool resp = false;
    for (int i=0; i<movimientos.size() && !resp; i++){
        posicion_siguiente = cambioDePosicion(p,movimientos[i].first,movimientos[i].second);
        if (esJaqueMate(posicion_siguiente))
            resp = true;
    }
    return resp;
}

bool hayMateForzadoEn(posicion p,int k){ //Solo se evalua en k=1 y k=2.
    bool resp = false;
    if (k==1){
        resp = hayMateEnUno(p);
    } else {
        posicion posicion_siguiente, posicion_forzada;
        secuencia movimientos = movimientosLegales(p,jugadorPosicion(p));
        for (int i=0; i<movimientos.size() && !resp; i++){
            posicion_siguiente = cambioDePosicion(p,movimientos[i].first,movimientos[i].second);
            if (movimientoForzado(posicion_siguiente)){
                posicion_forzada = cambioForzado(posicion_siguiente);
                if (hayMateEnUno(posicion_forzada))
                    resp = true;
            }
        }
    }
    return resp;
}


