#include "../custom.h"


extern PlayerDash player_dash;
extern ini PlayerObjectBIni;
extern ini PlayerObjectAIni;

/*
Object* create_player_object();
void player_object_action(void *self);
*/



static void player_object_action(Object *self){
    Object* object = (Object*)self;
    PlayerObjectStorage* storage = (PlayerObjectStorage*)object->storage;
    if(storage->attack_interval != 0){
        storage->attack_interval--;
    }
    if(storage->skill_interval != 0){
        storage->skill_interval--;
    }
    if(object->config.side == BLUE){
        storage->player_direction_key = player_dash.player_1_direction_key;
        storage->player_attack_key = player_dash.player_1_attack_key;
        storage->player_change_skill_key = player_dash.player_1_change_skill_key;
        storage->player_use_skill_key = player_dash.player_1_use_skill_key;
        clear_player_dash(&player_dash, BLUE);
    }else if(object->config.side == RED){
        storage->player_direction_key = player_dash.player_2_direction_key;
        storage->player_attack_key = player_dash.player_2_attack_key;
        storage->player_change_skill_key = player_dash.player_2_change_skill_key;
        storage->player_use_skill_key = player_dash.player_2_use_skill_key;
        clear_player_dash(&player_dash, RED);
    }
    if(storage->player_direction_key != NONE){
        object->api->request_step(object->host, object, storage->player_direction_key);
    }
    if(storage->player_attack_key != NONE){
        if(storage->attack_interval == 0){
            if(storage->spetial_bullet_remain > 0){
                switch(storage->spetial_bullet_type){
                    case UNIT_TYPE_FREEZE_BULLET:
                        player_shoot_freeze(object, NULL);
                        storage->spetial_bullet_remain--;
                        break;
                    case UNIT_TYPE_FIRE_BULLET:
                        player_shoot_burning(object, NULL);
                        storage->spetial_bullet_remain--;
                        break;
                    case UNIT_TYPE_WEAKENING_BULLET:
                        player_shoot_weaking(object, NULL);
                        storage->spetial_bullet_remain--;
                        break;
                }
            }else{
                player_shoot(object, NULL);
                storage->attack_interval = 10;
            }

        }
    }
    if(storage->player_use_skill_key != NONE){
        if(storage->attack_interval == 0){
            if(object->config.side == BLUE){
                object->api->request_use_skill_player(object->host, PLAYER1, NULL);
            }else{
                object->api->request_use_skill_player(object->host, PLAYER2, NULL);
            }
        }
    }
    if(storage->player_change_skill_key != NONE){
        if(object->config.side == BLUE){
            object->api->change_skill_choice(object->host, PLAYER1, 1, 0);
        }else{
            object->api->change_skill_choice(object->host, PLAYER2, 1, 0);
        }
        
    }
}

Object* create_player_object(int side){
    Object* object;
    if(side == BLUE){
        object = init_object(PlayerObjectAIni, side);
    }else{
        object = init_object(PlayerObjectBIni, side);
    }
    object->storage = malloc(sizeof(PlayerObjectStorage));
    ((PlayerObjectStorage*)object->storage)->attack_interval = 0;
    ((PlayerObjectStorage*)object->storage)->skill_interval = 0;
    ((PlayerObjectStorage*)object->storage)->spetial_bullet_type = 0;
    ((PlayerObjectStorage*)object->storage)->spetial_bullet_remain = 0;   

    object->action = player_object_action;

    return object;
}

