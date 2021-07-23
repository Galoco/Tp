#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

//MACROS
#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define VENTANA_ANCHO 800
#define VENTANA_ALTO 600

#define MIN_X 77
#define MAX_X 721
#define MIN_Y 52
#define MAX_Y 592

#define CANON_X 401
#define CANON_Y 71
#define CANON_LARGO 93
#define CANON_MAX 1.6790669176553528

#define BOLA_RADIO 6
#define BOLA_VI 450

#define JUEGO_FPS 200

#define G 600
#define PLASTICIDAD 0.8
#define ROZAMIENTO 0.9999

#endif // _CONFIG_H_

#define MASK_COLOR 0xC0
#define MASK_MOVIMIENTO 0x30
#define MASK_GEOMETRIA 0x0F

#define SHIFT_COLOR 6
#define SHIFT_MOVIMIENTO 4
#define SHIFT_GEOMETRIA 0



