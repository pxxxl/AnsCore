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
*/

typedef struct AnimePack{
    int pack_type;              //ANIME_PACK_TYPE_MOVE_INFO or ANIME_PACK_TYPE_EFFECT_INFO
    int tag;                    //tag: the tag of the animation, and it is used to get the image
    int x, y;                   //the position of the animation
    int des_x, des_y;           //the destination of the animation(only used in move animation)
    int delay;                  //when the delay is not 0, this pack will not be loaded in this step, and it will decrease by 1 in each step
} AnimePack;


typedef struct PlayerDisplayPack{
    int hp;
    int side;                    // RED_TROOP or BLUE_TROOP
    int skill_tag[SKILL_NUM];    // the tag of the skill
    int skill_num;
    int skill_choice;            // if -1, means no skill is chosen
} PlayerDisplayPack;