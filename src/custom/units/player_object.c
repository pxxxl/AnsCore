#include "../custom.h"


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
    int attack_interval;
    int skill_interval;
} PlayerObjectStorage;

static void player_object_action(void *self){
    Object* object = (Object*)self;
    PlayerObjectStorage* storage = (PlayerObjectStorage*)object->storage;
    if(storage->attack_interval != 0){
        storage->attack_interval--;
    }
    if(storage->skill_interval != 0){
        storage->skill_interval--;
    }
    if(object->config.side == BLUE_TROOP){
        storage->player_direction_key = player_dash.player_1_direction_key;
        storage->player_attack_key = player_dash.player_1_attack_key;
        storage->player_change_skill_key = player_dash.player_1_change_skill_key;
        storage->player_use_skill_key = player_dash.player_1_use_skill_key;
        clear_player_dash(&player_dash, BLUE_TROOP);
    }else if(object->config.side == RED_TROOP){
        storage->player_direction_key = player_dash.player_2_direction_key;
        storage->player_attack_key = player_dash.player_2_attack_key;
        storage->player_change_skill_key = player_dash.player_2_change_skill_key;
        storage->player_use_skill_key = player_dash.player_2_use_skill_key;
        clear_player_dash(&player_dash, RED_TROOP);
    }
    if(storage->player_direction_key != NONE){
        object->api->request_step(object->host, object, storage->player_direction_key);
    }
    if(storage->player_attack_key != NONE){
        if(storage->attack_interval == 0){
            player_shoot(object, 106);
            storage->attack_interval = 10;
        }
    }
    if(storage->player_use_skill_key != NONE){
        if(storage->skill_interval == 0){
            place_tesla(object);
            storage->skill_interval = 100;
        }
    }
}

Object* create_player_object(int side){
    Object* object = (Object*)malloc(sizeof(Object));

    set_object_status(object, 500);
    if(side != RED_TROOP && side != BLUE_TROOP){
        printf("Error: side must be RED_TROOP or BLUE_TROOP");
        exit(1);
    }
    set_object_config(object, 500, side, 100, 3, 3, PLAYER_OBJECT_INTERVAL, TRUE);
    if(side == BLUE_TROOP){
        set_object_anime(object, TRUE, 207, 205, 206, 204, 207);
    }else{
        set_object_anime(object, TRUE, 211, 209, 210, 208, 211);
    }

    object->storage = malloc(sizeof(PlayerObjectStorage));
    ((PlayerObjectStorage*)object->storage)->attack_interval = 0;
    ((PlayerObjectStorage*)object->storage)->skill_interval = 0;

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

