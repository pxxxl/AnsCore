#include "../include/anime.h"

void add_fixed_effect(Processor* host, int x, int y, int tag, int delay){
    AnimePack* pack = (AnimePack*)malloc(sizeof(AnimePack));
    pack->delay = delay;
    pack->pack_type = ANIME_PACK_TYPE_EFFECT_INFO;
    pack->tag = tag;
    pack->x = x;
    pack->y = y;
    host->api->request_load_anime(host, pack);
}

void add_fixed_sustaining_effect(Processor* host, int x, int y, int tags[], int length){
    for(int i = 0; i < length; i++){
        AnimePack* pack = (AnimePack*)malloc(sizeof(AnimePack));
        pack->delay = i;
        pack->pack_type = ANIME_PACK_TYPE_EFFECT_INFO;
        pack->tag = tags[i];
        pack->x = x;
        pack->y = y;
        host->api->request_load_anime(host, pack);
    }
}

void add_move_effect(Processor* host, int x, int y, int des_x, int des_y, int tag, int delay){
    AnimePack* pack = (AnimePack*)malloc(sizeof(AnimePack));
    pack->delay = delay;
    pack->pack_type = ANIME_PACK_TYPE_MOVE_INFO;
    pack->tag = tag;
    pack->x = x;
    pack->y = y;
    pack->des_x = des_x;
    pack->des_y = des_y;
    host->api->request_load_anime(host, pack);
}