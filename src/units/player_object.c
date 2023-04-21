#include "../../include/object_utils.h"
#include "../../include/player_dash.h"

extern PlayerDash player_dash;

/*
Object* create_player_object();
void player_object_action(void *self);
*/

typedef struct PlayerObjectStorage{
    int player_direction_key;
    int player_attack_key;
    int player_change_skill_key;
    int player_use_skill_key;
} PlayerObjectStorage;

static void player_object_action(void *self){
    Object* object = (Object*)self;
    PlayerObjectStorage* storage = (PlayerObjectStorage*)object->storage;
    if(object->config.side == BLUE_TROOP){
        storage->player_direction_key = player_dash.player_1_direction_key;
        storage->player_attack_key = player_dash.player_1_attack_key;
        storage->player_change_skill_key = player_dash.player_1_change_skill_key;
        storage->player_use_skill_key = player_dash.player_1_use_skill_key;
    }else if(object->config.side == RED_TROOP){
        storage->player_direction_key = player_dash.player_2_direction_key;
        storage->player_attack_key = player_dash.player_2_attack_key;
        storage->player_change_skill_key = player_dash.player_2_change_skill_key;
        storage->player_use_skill_key = player_dash.player_2_use_skill_key;
    }
    
}

Object* create_player_object(int side){
    Object* object = (Object*)malloc(sizeof(Object));

    default_set_object_status(object, 100);
    if(side != RED_TROOP && side != BLUE_TROOP){
        printf("Error: side must be RED_TROOP or BLUE_TROOP");
        exit(1);
    }
    set_object_config(object, 100, side, 100, PLAYER_OBJECT_INTERVAL);
    object->storage = (PlayerObjectStorage*)malloc(sizeof(PlayerObjectStorage));

    object->birth = default_object_birth;
    object->action = player_object_action;
    object->death = default_object_death;
    object->hurt = default_object_hurt;
    object->heal = default_object_heal;
    object->freeze = default_object_freeze;
    object->burn = default_object_burn;
    object->defend = default_object_defend;
    object->weak = default_object_weak;
    return object;
}

