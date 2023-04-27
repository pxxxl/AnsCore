#pragma once

#define TRUE 1
#define FALSE 0
#define BOOL int

#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define NONE 0

#define LOOKUP_MAX_RADIUS 200

#define RED_TROOP 1
#define BLUE_TROOP 2
#define RED_BULLET 3
#define BLUE_BULLET 4
#define NEUTRAL 5



#define BASE_MAX_X 40                       // x range [0, BASE_MAX_X)
#define BASE_MAX_Y 22                       // y range [0, BASE_MAX_Y)
#define BASE_SIZE 880                       // BASE_MAX_X * BASE_MAX_Y
#define OBJECT_AT_BIRTH_MAX_LENGTH 1000      // the max length of the object_at_birth array
#define OBJECT_AT_DEATH_MAX_LENGTH 1000      // the max length of the object_at_birth array

// Anime
#define ANIME_PACK_TYPE_MOVE_INFO 1
#define ANIME_PACK_TYPE_EFFECT_INFO 2

#define ANIME_PACK_CACHE_MAX_LENGTH 5000
#define ANIME_INFO_MOVE_MAX_LENGTH 10000
#define ANIME_INFO_EFFECT_MAX_LENGTH 10000

#define PIXEL_X_MAX 640
#define PIXEL_Y_MAX 360
#define BLOCK_PIXEL_X 16
#define BLOCK_PIXEL_Y 16

#define ABS(x) ((x) > 0 ? (x) : -(x))


