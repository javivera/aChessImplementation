#include "../definiciones.h"
#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"
# include <utility>

using namespace std;

TEST(seVieneElJaqueEnTEST, hayMateEn1) {
    //hayMateEn1 (tablero de ejercicio 16 del TPE)
    tablero t = {{cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cREY_N},
                {cPEON_N, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_N},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B},
                {cVACIA, cVACIA, cVACIA, cVACIA, cTORRE_B, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cALFIL_B, cALFIL_B, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cREY_B, cVACIA, cVACIA, cVACIA, cVACIA},
    };
    posicion p = make_pair(t,BLANCO);
    int K_esperado = 1;

    EXPECT_EQ(K_esperado, seVieneElJaqueEn(p));
}
    
TEST(seVieneElJaqueEnTEST, hayMateEn2_v1) {
    //hayMateEn2 (tablero de ejercicio 17 del TPE)
    tablero t = {{cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cREY_N},
                {cVACIA, cVACIA, cPEON_B, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cTORRE_B, cVACIA},
                {cVACIA, cVACIA, cREY_B, cVACIA, cVACIA, cVACIA, cVACIA, cTORRE_B},
    };
    posicion p = make_pair(t,BLANCO);
    int K_esperado = 2;

    EXPECT_EQ(K_esperado, seVieneElJaqueEn(p));
}

TEST(seVieneElJaqueEnTEST, hayMateEn2_v2) {
    //hayMateEn2
    tablero t = {{cTORRE_N, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cTORRE_N, cREY_N},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cALFIL_N, cVACIA, cPEON_N, cVACIA, cVACIA, cPEON_N, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cPEON_N, cPEON_N, cVACIA, cVACIA, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B, cTORRE_N, cVACIA, cVACIA},
                {cVACIA, cALFIL_B, cPEON_B, cVACIA, cVACIA, cVACIA, cTORRE_B, cVACIA},
                {cPEON_B, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B, cVACIA, cPEON_B},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cTORRE_B, cREY_B},
    };
    posicion p = make_pair(t,BLANCO);
    int K_esperado = 2;

    EXPECT_EQ(K_esperado, seVieneElJaqueEn(p));
}

TEST(seVieneElJaqueEnTEST, hayMateEn3) {
    //hayMateEn3
    tablero t = {{cTORRE_N, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                {cPEON_N, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_N},
                {cVACIA, cPEON_N, cVACIA, cTORRE_B, cVACIA, cVACIA, cPEON_N, cVACIA},
                {cVACIA, cTORRE_B, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cALFIL_N},
                {cVACIA, cPEON_B, cVACIA, cVACIA, cPEON_N, cVACIA, cREY_N, cVACIA},
                {cPEON_B, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cPEON_B, cVACIA},
                {cTORRE_N, cVACIA, cVACIA, cVACIA, cPEON_B, cPEON_B, cREY_B, cVACIA},
                {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
    };
    posicion p = make_pair(t,BLANCO);
    int K_esperado = 3;

    EXPECT_EQ(K_esperado, seVieneElJaqueEn(p));
}
