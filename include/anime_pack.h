#pragma once
#include "macros.h"
/*
    * AnimePack
    * 
    * This struct is used to store the information of
    * the animation.
    * 
    * pack_type: the type of the animation
    * if pack_type == ANIME_PACK_TYPE_MOVE_INFO:
    *   the animation is a move animation
    * if pack_type == ANIME_PACK_TYPE_EFFECT_INFO:
    *   the animation is a effect animation
    *
    * tag: the tag of the animation, and it is used to get the image
    * 
    * x, y: the position of the animation
    * des_x, des_y: the destination of the animation(only used in move animation)
    * delay: when the delay is not 0, this pack will not be loaded in this step, 
    *   and it will decrease by 1 in each step
*/

typedef struct AnimePack{
    // ANIME_PACK_TYPE_MOVE_INFO or
    // ANIME_PACK_TYPE_EFFECT_INFO
    int pack_type;

    int tag;

    int x, y;
    int des_x, des_y;

    int delay;
} AnimePack;


typedef struct PlayerDisplayPack{
    int hp;
    int side;

    int skill_tag[PLAYER_SKILL_NUM];
    int skill_num;

    // if -1, means no skill is chosen
    int skill_choice;
} PlayerDisplayPack;

typedef struct ProcessorAnimeData{
    AnimePack anime_pack[ANIME_PACK_CACHE_MAX_LENGTH];
    int anime_pack_size;

    PlayerDisplayPack player_display_pack[2];
} ProcessorAnimeData;
