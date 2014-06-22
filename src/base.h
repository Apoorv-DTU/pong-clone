#ifndef _base_h_
#define _base_h_

#include <stdint.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

#define BAT_SPEED 5
#define BALL_SPEED 2

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Color;

#endif
