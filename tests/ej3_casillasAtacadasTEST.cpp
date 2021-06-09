#include "../definiciones.h"
#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"
# include <utility>

using namespace std;

TEST(casillasAtacadasTEST, atacadasDelJugadorActual) {
	tablero t = {
            {cVACIA, cREY_N, cVACIA, cALFIL_N, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_N, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cREY_B, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
    };
	posicion p = make_pair(t, BLANCO);

	int j = BLANCO;

	vector<coordenada> esperado = { 
		make_pair(6,3), make_pair(5,3), make_pair(5,4), make_pair(5,5), make_pair(6,5), make_pair(7,5), make_pair(7,4), make_pair(7,3), //Rey Blanco en (6,4)
		make_pair(3,4), make_pair(3,6)	//Peon Blanco en (4,5)
	};
	
	vector<coordenada> atacadas = casillasAtacadas(p, j);
	EXPECT_EQ(ordenarVectorPares(esperado), ordenarVectorPares(atacadas));
}

TEST(casillasAtacadasTEST, atacadasDelContrincante) {
	tablero t = {
            {cVACIA, cREY_N, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_N, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cREY_B, cVACIA, cVACIA, cVACIA},
            {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
    };
	posicion p = make_pair(t, BLANCO);

	int j = NEGRO;

	vector<coordenada> esperado = {
		make_pair(0,0), make_pair(0,2), make_pair(1,0), make_pair(1,1), make_pair(1,2), //Rey Negro en (0,1)
		make_pair(4,5), make_pair(4,7) //Peon Negro en (3,6)

	};

	vector<coordenada> atacadas = casillasAtacadas(p, j);
	EXPECT_EQ(ordenarVectorPares(esperado), ordenarVectorPares(atacadas));
}
