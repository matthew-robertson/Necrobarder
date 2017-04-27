#include "mapTiles.h"
const unsigned int wallB[64] __attribute__((aligned(4)))=
{
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
    0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,0x04040404,
};

const unsigned int wallU[64] __attribute__((aligned(4)))=
{
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
    0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,
};

const unsigned int dfloor[64] __attribute__((aligned(4)))=
{
    0x02010100,0x03040303,0x03010202,0x03020302,0x04040304,0x03040101,0x01010404,0x04010101,
    0x02030302,0x02020303,0x01040301,0x03040401,0x03010103,0x02030302,0x01010301,0x01020104,
    0x01010203,0x00030103,0x03030303,0x02020203,0x03020303,0x03010103,0x01040303,0x03010302,
    0x01010103,0x02030401,0x01010303,0x02030101,0x03030303,0x03030303,0x01010104,0x02020303,
    0x04010301,0x03010101,0x03030303,0x03030203,0x04010203,0x01010303,0x01010203,0x03030304,
    0x01040302,0x01010101,0x03030101,0x02030303,0x01010202,0x02030101,0x01010100,0x01030202,
    0x03030101,0x01030101,0x01040101,0x02030404,0x01010301,0x01010303,0x04040102,0x03030104,
    0x02020303,0x02030302,0x03040403,0x01010103,0x01010302,0x01030101,0x01020301,0x00010101,
};

const unsigned int bgPal[4] __attribute__((aligned(4)))=
{
    0x14AA0000,0x08640000,0x0000150E
};