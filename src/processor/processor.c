#pragma once
#include "processor.h"
#include "../base/base.h"
#include "../macros.h"
#include "../custom/custom.h"
#include <malloc.h>

PlayerDash player_dash;

void request_place(Processor *host, Object *source, Object *target, int x, int y, int ori);
void request_move(Processor *host, Object *source, int direction, int step);
void request_step(Processor *host, Object *source, int direction);
void request_suiside(Processor *host, Object *source);
void request_teleport(Processor *host, Object *source, int des_x, int des_y);
void request_freeze(Processor *host, Object *source, Object* target, int degree);
void request_burn(Processor *host, Object *source, Object* target, int degree);
void request_defend(Processor *host, Object *source, Object* target, int degree);
void request_weak(Processor *host, Object *source, Object* target, int degree);
void request_heal(Processor *host, Object *source, Object* target, int heal);
void request_hurt(Processor *host, Object *source, Object* target, int damage);
void request_load_anime(Processor *host, AnimePack *pack);
void request_use_skill(Processor *host, Object *source, int skill_id, void* params);
void request_use_skill_player(Processor *host, int player_id, void* params);
void give_skill(Processor *host, Object *source, int skill_id);
void change_skill_choice(Processor *host, int player_id, int right_shift, int left_shift);
void load_static_effect(Processor* host, int x, int y, int tag, int delay);
void load_static_sustaining_effect(Processor* host, int x, int y, int tags[], int length, int delay);
void load_dynamic_effect(Processor* host, int x, int y, int des_x, int des_y, int tag, int delay);
void load_move_effect(Processor* host, int x, int y, int step, int direction, int tag, int delay);
Object* detect_exist_object(Processor *host, int x1, int y1, int x2, int y2);
Object* get_object(Processor *host, int x, int y);
Object* find_closest_object_in_direction(Processor *host, Object* object, int direction);
Object* find_closest_object(Processor *host, Object* object);
Object* find_object_around(Processor *host, Object* object, int radius);
static void pro_generate_distance_list(Processor* host);
static void pro_generate_distance_list_gc(Processor* host);
static void get_distance_list(Processor *host, Object ****distance_list, Object*** object_list, int *length);
static BOOL is_valid_address(Processor *host, int x, int y);
static BOOL cannot_hurt(Processor *host, Object* attacker, Object* defender);
static BOOL at_edge(Processor *host, Object* object);
static BOOL going_out_of_bound(Processor *host, Object* object, int direction);
void step(Processor *self);
void fillin_skill_map(Processor *self, SkillFunc* skill_map, int length);
PlayerDisplayPack processor_player_data_to_anime_player_data(PlayerObject* player);
ProcessorAnimeData export_anime_data(Processor *self);
void processAPIRequest(Processor *self, ProcessorAPIRequest *request);


struct NOTE___Implement_init_and_destory{char A;};

static void init_processor_api(Processor* self){
    self->api = (ProcessorAPI*)malloc(sizeof(ProcessorAPI));
    self->api->request_place = request_place;
    self->api->request_move = request_move;
    self->api->request_step = request_step;
    self->api->request_suiside = request_suiside;
    self->api->request_teleport = request_teleport;
    self->api->request_freeze = request_freeze;
    self->api->request_burn = request_burn;
    self->api->request_defend = request_defend;
    self->api->request_weak = request_weak;
    self->api->request_heal = request_heal;
    self->api->request_hurt = request_hurt;
    self->api->request_use_skill = request_use_skill;
    self->api->request_load_anime = request_load_anime;
    self->api->request_load_static_effect = load_static_effect;
    self->api->request_load_static_sustaining_effect = load_static_sustaining_effect;
    self->api->request_load_dynamic_effect = load_dynamic_effect;
    self->api->request_load_move_effect = load_move_effect;
    self->api->request_use_skill_player = request_use_skill_player;

    self->api->give_skill = give_skill;
    self->api->change_skill_choice = change_skill_choice;
    self->api->detect_exist_object = detect_exist_object;
    self->api->get_object = get_object;
    self->api->find_closest_object_in_direction = find_closest_object_in_direction;
    self->api->find_closest_object = find_closest_object;
    self->api->find_object_around = find_object_around;
    self->api->get_distance_list = get_distance_list;

    self->api->cannot_hurt = cannot_hurt;
    self->api->is_valid_address = is_valid_address;
    self->api->at_edge = at_edge;
    self->api->going_out_of_bound = going_out_of_bound;
}

static void init_processor_player(Processor* self){
    self->player[0].object = create_player_object(BLUE);
    self->player[1].object = create_player_object(RED);
    self->player[0].skill_num = 0;
    self->player[1].skill_num = 0;
    self->player[0].skill_choice = -1;
    self->player[1].skill_choice = -1;
    self->api->request_place(self, NULL, self->player[0].object, 0, 3, UP);
    self->api->request_place(self, NULL, self->player[1].object, 18, 15, DOWN);
}


// init the processor
Processor* init_processor(int length, int height){
    // create the processor
    Processor* self = (Processor*)malloc(sizeof(Processor));

    // init the processor's fields
    self->base = create_base(length, height);
    init_processor_api(self);
    init_processor_player(self);
    self->anime_cache_size = 0;
    self->object_at_birth_size = 0;
    self->object_at_death_size = 0;

    // create the processor's method
    self->step = step;
    self->export_anime_data = export_anime_data;
    self->fillin_skill_map = fillin_skill_map;

    return self;
}


// destroy the processor
void destroy_processor(Processor *self){
    destroy_base(self->base);
    free(self->api);
    free(self);
}













struct NOTE___Implement_step_and_export_anime_data{char A;};

// remove the object from the processor's base
// but not destroy it
static void remove_object_from_processor_base(Processor *self, Object *object){
    self->base->remove_block(self->base, object->block);
}

// destroy the object
static void destroy_object_from_processor(Processor *self, Object *object){
    self->base->destroy_block(self->base, object->block);
    free(object);
}

// step the processor
/* The processor performs a "step" of processing, which includes the following steps:
Scan the entire area to obtain all surviving objects.
Check which objects are added to the processor for the first time, and the processor will call their birth method.
Call the death method of the objects that died in the previous round. Then destroy them.
Call the action method of all objects. (If the object is frozen, it will not be called)
Note that objects interact with each other through the API provided by the processor, and objects cannot directly manipulate each other. If an object wants to interact with another object, it can only use the processor API to send a "request". At this time, the processor only stores their requests and does not make the interaction effective.
Calculate the state.
Make all interaction requests of the objects effective.
Scan the entire area to clear all dead objects. Note that they are only cleaned out of the area and not destroyed because their death method will be called in the next step.
*/
void step(Processor *self){
    int x, y;
    int i, j, k;
    Block* blocks[(BASE_MAX_X + 1)*(BASE_MAX_Y+1)];
    int block_num = 0;
    // scan the entire area to obtain all objects.
    // the processor make sure at the begin of the step, all objects are alive
    BOOL flag = self->base->find_all_blocks(self->base, 0, 0, BASE_MAX_X, BASE_MAX_Y, blocks, &block_num);
    if(!flag) return;       // no objects

    // check which objects are added to the processor for the first time, and the processor will call their birth method.
    for(i = 0; i < self->object_at_birth_size; i++){
        self->object_at_birth[i]->birth(self->object_at_birth[i]);
    }
    self->object_at_birth_size = 0;

    // call the death method of the objects that died in the previous round. Then destroy them.
    for(i = 0; i < self->object_at_death_size; i++){
        self->object_at_death[i]->death(self->object_at_death[i]);
        destroy_object_from_processor(self, self->object_at_death[i]);
    }
    self->object_at_death_size = 0;

    // call the action method of all objects. (If the object is frozen, it will not be called)
    // and call the anime method of all objects
    for(i = 0; i < block_num; i++){
        Object* object = (Object*)blocks[i]->any;
        if(object->status.frozen_degree != 0){
            continue;
        }else if(object->status.clock == 0){
            object->action(object);
            object->status.clock = object->config.interval;
        }else{
            object->status.clock--;
        }
    }

    // calculate the state
    for(i = 0; i < block_num; i++){
        Object* object = (Object*)blocks[i]->any;
        if(object->status.frozen_degree > 0 && object->status.clock == object->config.interval){
            object->status.frozen_degree--;
        }
        if(object->status.burning_degree > 0){
            object->status.burning_degree--;
        }
        if(object->status.weak_degree > 0){
            object->status.weak_degree--;
        }
    }

    // all interaction requests of the objects.
    int request_i;
    for(request_i = 0; request_i < self->request_queue_size; request_i++){
        processAPIRequest(self, &(self->request_queue[request_i]));
    }
    for(i = 0; i < block_num; i++){
        // draw the unmoved && autoload_anime objects
        Object* object = (Object*)blocks[i]->any;
        if(object->status.moving == FALSE && object->config.auto_load_anime == TRUE){
            int image_tag;
            if(object->anime.direction_4){
                image_tag = object->anime.ori_image[object->block->orientation];
            }else{
                image_tag = object->anime.ori_image[NONE];
            }
            self->api->request_load_static_effect(
                self,
                object->block->x,
                object->block->y,
                image_tag,
                0
            );
        }
        object->status.moving = FALSE;
    }
    for(; request_i < self->request_queue_size; request_i++){
        // continue to process the interaction requests
        processAPIRequest(self, &(self->request_queue[request_i]));
    }
    self->request_queue_size = 0;


    // scan the entire area to clear all dead objects. Note that they are only cleaned out of the area and not destroyed because their death method will be called in the next step.
    for(i = 0; i < block_num; i++){
        Object* object = (Object*)blocks[i]->any;
        if(object->status.hp <= 0){
            self->base->remove_block(self->base, blocks[i]);
            self->object_at_death[self->object_at_death_size++] = object;
        }
    }

    //process the distance list
    if(self->distance_list_generated == TRUE){
        pro_generate_distance_list_gc(self);
    }
}


PlayerDisplayPack processor_player_data_to_anime_player_data(PlayerObject* player){
    PlayerDisplayPack pack;
    pack.hp = player->object->status.hp;
    pack.side = player->object->config.side;
    pack.skill_num = player->skill_num;
    pack.skill_choice = player->skill_choice;
    int i = 0;
    for(i = 0; i < PLAYER_SKILL_MAX_NUM; i++){
        pack.skill_tag[i] = player->skill_tag[i];
    }
    return pack;
}

// export the anime data
ProcessorAnimeData export_anime_data(Processor *self){
    ProcessorAnimeData data;
    int* intime_mark = (int*)malloc(sizeof(int)*self->anime_cache_size);
    int intime_mark_size = 0;
    int i, j;
    for(i = 0, j = 0; i < self->anime_cache_size; i++){
        if(self->anime_cache[i].delay == 0){
            data.anime_pack[intime_mark_size] = self->anime_cache[i];
            intime_mark[intime_mark_size++] = i;
        } else{
            self->anime_cache[i].delay--;
        }
    }
    data.anime_pack_size = intime_mark_size;
    while(intime_mark_size > 0){
        if(intime_mark[intime_mark_size-1] == i-1){
            i--;
            intime_mark_size--;
        }else{
            self->anime_cache[intime_mark[intime_mark_size-1]] = self->anime_cache[i-1];
            self->anime_cache_size--;
            i--;
            intime_mark_size--;
        }
    }
    self->anime_cache_size = i;
    data.player_display_pack[0] = processor_player_data_to_anime_player_data(&self->player[0]);
    data.player_display_pack[1] = processor_player_data_to_anime_player_data(&self->player[1]);
    return data;
}











/*
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
#define API_REQUEST_STEP 10                 // step
#define API_REQUEST_PLACE 11                // place

struct ProcessorAPIRequest{
    int type;
    Object* source;
    Object* target;
    int x;
    int y;
    int ext_1;
    int ext_2;
    int ext_3;
    void* ext_4;
};
*/
struct NOTE___Implement_API_Request{char A;};

static void place_object(Processor *self, Object* object, int x, int y, int length, int height, int ori){
    Block* b = self->base->create_block(self->base, x, y, length, height, ori);
    if(b == NULL){
        return;
    }
    b->any = object;
    object->block = b;
    object->host = self;
    object->api = self->api;
    self->object_at_birth[self->object_at_birth_size++] = object;
}

void processAPIRequest(Processor *self, ProcessorAPIRequest *request){
    int success;
    switch(request->type){
        case API_REQUEST_MOVE:
            success = self->base->move_block(self->base, request->source->block, request->ext_1, request->ext_2);
            if(success && request->source->config.auto_load_anime){
                self->api->request_load_move_effect(
                    self,
                    request->source->block->x,
                    request->source->block->y,
                    request->ext_2,
                    request->ext_1,
                    request->source->anime.ori_image[request->source->block->orientation],
                    0
                );
            }
            if(success){
                request->source->status.moving = TRUE;
            }
            if(!success){
                request->source->block->orientation = request->ext_1;
            }
            break;
        case API_REQUEST_TELEPORT:
            success = self->base->teleport_block(self->base, request->x, request->y, request->source->block);
            if(success){
                request->source->status.moving = TRUE;
            }
            break;
        case API_REQUEST_FREEZE:
            request->target->freeze(request->target, request->ext_1);
            break;
        case API_REQUEST_BURN:
            request->target->burn(request->target, request->ext_1);
            break;
        case API_REQUEST_DEFEND:
            request->target->defend(request->target, request->ext_1);
            break;
        case API_REQUEST_WEAK:
            request->target->weak(request->target, request->ext_1);
            break;
        case API_REQUEST_HEAL:
            request->target->heal(request->target, request->ext_1);
            break;
        case API_REQUEST_HURT:
            int hurt = request->ext_1;
            if(request->target->status.defending_degree > 0){
                hurt -= request->target->status.defending_degree;
            }
            if(request->source->status.weak_degree > 0){
                hurt -= request->source->status.weak_degree;
            }
            if(hurt < 0){
                hurt = 0;
            }
            request->target->hurt(request->target, hurt);
            break;
        case API_REQUEST_LOAD_ANIME:
            self->anime_cache[self->anime_cache_size] = *((AnimePack*)request->ext_4);
            self->anime_cache_size++;
            free(request->ext_4);
            break;
        case API_REQUEST_STEP:
            int legacy_x = request->source->block->x;
            int legacy_y = request->source->block->y;
            success = self->base->move_block(self->base, request->source->block, request->ext_1, 1);
            int image_tag;
            if(request->source->anime.direction_4){
                image_tag = request->source->anime.ori_image[request->source->block->orientation];
            }else{
                image_tag = request->source->anime.ori_image[NONE];
            }
            if(success && request->source->config.auto_load_anime){
                self->api->request_load_move_effect(
                    self,
                    legacy_x,
                    legacy_y,
                    1,
                    request->ext_1,
                    image_tag,
                    0
                );
            }
            if(success){
                request->source->status.moving = TRUE;
            }
            if(!success){
                request->source->block->orientation = request->ext_1;
            }
            break;
        case API_REQUEST_PLACE:
            place_object(self, request->target, request->x, request->y, request->ext_1, request->ext_2, request->ext_3);
            break;
        case API_REQUEST_SUISIDE:
            request->source->status.hp = 0;
            break;
        case API_REQUEST_USE_SKILL:
            self->skill_map[request->ext_1](request->source, request->ext_4);
            if(request->ext_4 != NULL)
                free(request->ext_4);
            break;
        default:
            break;
    }
}





















// below are apis that are provided to the objects
// objects could only use these functions to interact with the processor or other objects

// "source" request to place target at x, y
void request_place(Processor *host, Object *source, Object *target, int x, int y, int ori){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_PLACE;
    request->source = source;
    request->target = target;
    request->x = x;
    request->y = y;
    request->ext_1 = target->config.length;
    request->ext_2 = target->config.height;
    request->ext_3 = ori;
}

// request to move the object
void request_move(Processor *host, Object *source, int direction, int step){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_MOVE;
    request->source = source;
    request->ext_1 = direction;
    request->ext_2 = step;
}

// move the object to the direction for 1 block
void request_step(Processor *host, Object *source, int direction){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_STEP;
    request->source = source;
    request->ext_1 = direction;
}

void request_suiside(Processor *host, Object *source){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_SUISIDE;
    request->source = source;
}

// request to teleport the object
void request_teleport(Processor *host, Object *source, int des_x, int des_y){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_TELEPORT;
    request->source = source;
    request->x = des_x;
    request->y = des_y;
}

// request to freeze the object
// freeze: the object will not "action"
// degree-- for each step
void request_freeze(Processor *host, Object *source, Object* target, int degree){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_FREEZE;
    request->source = source;
    request->target = target;
    request->ext_1 = degree;
}

// request to burn the object
// burn: the object will lose hp, hp -= 1
// degree-- for each step
void request_burn(Processor *host, Object *source, Object* target, int degree){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_BURN;
    request->source = source;
    request->target = target;
    request->ext_1 = degree;
}

// request to defend the object
// defend: hurt will be reduced by degree
void request_defend(Processor *host, Object *source, Object* target, int degree){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_DEFEND;
    request->source = source;
    request->target = target;
    request->ext_1 = degree;
}

// request to weaken the object
// weaken: hurt will be increased by degree
void request_weak(Processor *host, Object *source, Object* target, int degree){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_WEAK;
    request->source = source;
    request->target = target;
    request->ext_1 = degree;
}

// request to heal the object
void request_heal(Processor *host, Object *source, Object* target, int heal){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_HEAL;
    request->source = source;
    request->target = target;
    request->ext_1 = heal;
}

// request to hurt the object
void request_hurt(Processor *host, Object *source, Object* target, int damage){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_HURT;
    request->source = source;
    request->target = target;
    request->ext_1 = damage;
}

void request_use_skill(Processor *host, Object *source, int skill_id, void* params){
    /*
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_USE_SKILL;
    request->source = source;
    request->ext_1 = skill_id;
    if(source == host->player[0].object){
        request->ext_2 = PLAYER1;
        request->ext_3 = host->player[0].skill_choice;
    }else{
        request->ext_2 = PLAYER2;
        request->ext_3 = host->player[1].skill_choice;
    }
    request->ext_4 = params;
    */
}

void request_use_skill_player(Processor *host, int player_id, void* params){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;

    PlayerObject* player;
    if(player_id == PLAYER1) player = &host->player[0];
    else if(player_id == PLAYER2) player = &host->player[1];
    else return;
    if(player->skill_choice < 0 || player->skill_choice >= player->skill_num){
        return;
    }

    int target = player->skill_tag[player->skill_choice];
    for(int i = player->skill_choice; i < PLAYER_SKILL_MAX_NUM - 1; i++){
        player->skill_tag[i] = player->skill_tag[i+1];
    }
    player->skill_num = player->skill_num - 1;
    if(player->skill_num == player->skill_choice){
        player->skill_choice -= 1;
    }
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_USE_SKILL;
    request->source = player->object;
    request->ext_1 = target;
    request->ext_4 = params;

}

void give_skill(Processor *host, Object *source, int skill_id){
    if(source->config.type != UNIT_TYPE_PLAYER_OBJECT_A && source->config.type != UNIT_TYPE_PLAYER_OBJECT_B) return;
    PlayerObject* playerA = &host->player[0];
    PlayerObject* playerB = &host->player[1];
    PlayerObject* Player;
    if(playerA->object == source) Player = playerA;
    else if(playerB->object == source) Player = playerB;
    else return;

    if(Player->skill_num >= PLAYER_SKILL_MAX_NUM) return;
    Player->skill_tag[Player->skill_num++] = skill_id;
    if(Player->skill_choice == -1){
        Player->skill_choice = 0;
    }
}

// request to load the anime
// NOTICE: USER SHOULD USE MALLOC TO ALLOCATE MEMORY FOR THE PACK, AND DON'T FREE IT
void request_load_anime(Processor *host, AnimePack *pack){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_LOAD_ANIME;
    request->ext_4 = pack;
}

// detect if there is an object in the area
// return the object if there is, return NULL if not
// range [x1, x2), [y1, y2)
Object* detect_exist_object(Processor *host, int x1, int y1, int x2, int y2){
    Block* detect = host->base->detect_exist_block(host->base, x1, y1, x2, y2);
    if(detect == NULL){
        return NULL;
    }
    return detect->any;
}

// get the object at this place
// return the object if there is, return NULL if not
Object* get_object(Processor *host, int x, int y){
    return host->base->get_block(host->base, x, y)->any;
}

// find the closest object in the direction
// return the closest if there is, return NULL if not
Object* find_closest_object_in_direction(Processor *host, Object* object, int direction){
    return host->base->find_closest_block_in_direction(host->base, object->block, direction)->any;
}

// find the closest object
// return the closest if there is, return NULL if not
Object* find_closest_object(Processor *host, Object* object){
    return host->base->find_closest_block(host->base, object->block)->any;
}

Object* find_object_around(Processor* host, Object* object, int radius){
    return host->base->find_block_around(host->base, object->block, radius)->any;
}

static void pro_generate_distance_list(Processor* host){
    Block*** distance_list;
    Block** blocks;
    int length;
    host->base->generate_distance_list(host->base, &distance_list, &blocks, &length);
    host->distance_list = (Object***)malloc(sizeof(Object**) * length);
    for(int i = 0; i < length; i++){
        host->distance_list[i] = (Object**)malloc(sizeof(Object*) * length);
    }
    host->object_list = (Object**)malloc(sizeof(Object*) * length);
    host->object_list_length = length;
    for(int i = 0; i < length; i++){
        host->object_list[i] = blocks[i]->any;
        for(int j = 0; j < length; j++){
            host->distance_list[i][j] = distance_list[i][j]->any;
        }
    }
    host->base->generate_distance_list_gc(host->base, distance_list, blocks, length);
    host->distance_list_generated = TRUE;
}

static void pro_generate_distance_list_gc(Processor* host){
    host->distance_list_generated = FALSE;
    for(int i = 0; i < host->object_list_length; i++){
        free(host->distance_list[i]);
    }
    free(host->distance_list);
    free(host->object_list);
    host->object_list_length = 0;
}

static void get_distance_list(Processor* host, Object ****distance_list, Object*** object_list, int* object_list_length){
    if(!(host->distance_list_generated)){
        pro_generate_distance_list(host);
    }
    *distance_list = host->distance_list;
    *object_list = host->object_list;
    *object_list_length = host->object_list_length;
    return;
}

static BOOL is_valid_address(Processor* host, int x, int y){
    return host->base->is_valid_address(host->base, x, y);
}


static BOOL cannot_hurt(Processor *host, Object* attacker, Object* defender){
    int attacker_side = attacker->config.side;
    int defender_side = defender->config.side;
    if(attacker_side == defender_side) return TRUE;
    return FALSE;
}


static BOOL at_edge(Processor *host, Object* object){
    return host->base->at_edge(host->base, object->block);
}


BOOL going_out_of_bound(Processor *host, Object* object, int direction){
    return host->base->going_out_of_bound(host->base, object->block, direction);
}

void load_static_effect(Processor* host, int x, int y, int tag, int delay){
    AnimePack* pack = (AnimePack*)malloc(sizeof(AnimePack));
    pack->delay = delay;
    pack->pack_type = ANIME_PACK_TYPE_EFFECT_INFO;
    pack->tag = tag;
    pack->x = x;
    pack->y = y;
    host->api->request_load_anime(host, pack);
}

void load_static_sustaining_effect(Processor* host, int x, int y, int tags[], int length, int delay){
    for(int i = 0; i < length; i++){
        AnimePack* pack = (AnimePack*)malloc(sizeof(AnimePack));
        pack->delay = delay + i;
        pack->pack_type = ANIME_PACK_TYPE_EFFECT_INFO;
        pack->tag = tags[i];
        pack->x = x;
        pack->y = y;
        host->api->request_load_anime(host, pack);
    }
}

void load_dynamic_effect(Processor* host, int x, int y, int des_x, int des_y, int tag, int delay){
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

void clear_player_dash(PlayerDash *player_dash, int side){
    if (side == RED){
        player_dash->player_2_attack_key = FALSE;
        player_dash->player_2_direction_key = NONE;
        player_dash->player_2_change_skill_key = FALSE;
        player_dash->player_2_use_skill_key = FALSE;
    }
    if (side == BLUE){
        player_dash->player_1_attack_key = FALSE;
        player_dash->player_1_direction_key = NONE;
        player_dash->player_1_change_skill_key = FALSE;
        player_dash->player_1_use_skill_key = FALSE;
    }
}

void load_move_effect(Processor* host, int x, int y, int step, int direction, int tag, int delay){
    int des_x = x;
    int des_y = y;
    switch(direction){
        case UP:
            des_y -= step;
            break;
        case DOWN:
            des_y += step;
            break;
        case LEFT:
            des_x -= step;
            break;
        case RIGHT:
            des_x += step;
            break;
    }
    load_dynamic_effect(host, x, y, des_x, des_y, tag, delay);
}

void fillin_skill_map(Processor *self, SkillFunc* skill_map, int length){
    for(int i = 0; i < length; i++){
        self->skill_map[i] = skill_map[i];
    }
    for(int i = length; i < MAX_SKILL_NUM; i++){
        self->skill_map[i] = NULL;
    }
}

void change_skill_choice(Processor *host, int player_id, int right_shift, int left_shift){
    PlayerObject* player;
    if(player_id == 1){
        player = &host->player[0];
    }
    else{
        player = &host->player[1];
    }
    if(player->skill_num == 0) return;
    int shift = right_shift - left_shift;
    int real_shift = shift % player->skill_num;
    if(player->skill_choice + real_shift < player->skill_num){
        player->skill_choice += real_shift;
    }
    else{
        player->skill_choice = player->skill_choice + real_shift - player->skill_num;
    }
}