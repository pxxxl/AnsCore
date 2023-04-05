#pragma once

#define TRUE 1
#define FALSE 0
#define BOOL int

#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

#define LOOKUP_MAX_RADIUS 200

#define RED_TROOP 1
#define BLUE_TROOP 2
#define RED_BULLET 3
#define BLUE_BULLET 4
#define NEUTRAL 5

#define PLAYER_HP 100
#define PLAYER_SKILL_NUM 6

#define BASE_MAX_X 40                       // x range [0, BASE_MAX_X)
#define BASE_MAX_Y 22                       // y range [0, BASE_MAX_Y)
#define BASE_SIZE 880                       // BASE_MAX_X * BASE_MAX_Y
#define OBJECT_AT_BIRTH_MAX_LENGTH 100      // the max length of the object_at_birth array
#define OBJECT_AT_DEATH_MAX_LENGTH 100      // the max length of the object_at_birth array

#define API_REQUEST_MAX_NUM 100             // the max number of the api request
#define API_REQUEST_MOVE 1                  // move
#define API_REQUEST_TELEPORT 2              // teleport
#define API_REQUEST_FREEZE 3                // freeze
#define API_REQUEST_BURN 4                  // burn
#define API_REQUEST_DEFEND 5                // defend
#define API_REQUEST_WEAK 6                  // weak
#define API_REQUEST_HEAL 7                  // heal
#define API_REQUEST_HURT 8                  // hurt
#define API_REQUEST_LOAD_ANIME 9            // load anime


// Anime
#define ANIME_PACK_TYPE_MOVE_INFO 1
#define ANIME_PACK_TYPE_EFFECT_INFO 2

#define ANIME_PACK_CACHE_MAX_LENGTH 500 
#define ANIME_INFO_MOVE_MAX_LENGTH 1000
#define ANIME_INFO_EFFECT_MAX_LENGTH 1000

#define PIXEL_X_MAX 640
#define PIXEL_Y_MAX 360
#define BLOCK_PIXEL_X 16
#define BLOCK_PIXEL_Y 16


