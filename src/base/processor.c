#pragma once
#include "processor.h"
#include "base.h"
#include "macros.h"
#include <malloc.h>




// static functions
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

static PlayerDisplayPack processor_player_data_to_anime_player_data(Player* player){
    PlayerDisplayPack pack;
    pack.hp = player->object->status.hp;
    pack.side = player->side;
    pack.skill_num = player->skill_num;
    pack.skill_choice = player->skill_choice;
    int i = 0;
    for(i = 0; i < PLAYER_SKILL_NUM; i++){
        pack.skill_tag[i] = player->skill_tag[i];
    }
    return pack;
}

static void processAPIRequest(Processor *self, ProcessorAPIRequest *request){

}












// init the processor
Processor* init_processor(int length, int height){
    // create the processor
    Processor* self = (Processor*)malloc(sizeof(Processor));
    self->anime_cache_size = 0;
    self->place_object = place_object;
    self->step = step;
    self->export_anime_data = export_anime_data;

    // create the base
    self->base = create_base(length, height);

    // create and place the players
    self->player[0]->object = create_player_object();
    self->player[1]->object = create_player_object();
    self->player[0]->side = RED_TROOP;
    self->player[1]->side = BLUE_TROOP;
    self->player[0]->skill_num = 0;
    self->player[1]->skill_num = 0;
    self->player[0]->skill_choice = -1;
    self->player[1]->skill_choice = -1;
    self->place_object(self, self->player[0]->object, 0, BASE_MAX_Y - 3, 3, 3);
    self->place_object(self, self->player[1]->object, BASE_MAX_X - 3, 0, 3, 3);

    // create the birth object set
    self->object_at_birth_size = 0;
    self->object_at_death_size = 0;

    // create the processor's api
    self->api = (ProcessorAPI*)malloc(sizeof(ProcessorAPI));
    self->api->request_move = request_move;
    self->api->request_teleport = request_teleport;
    self->api->request_freeze = request_freeze;
    self->api->request_burn = request_burn;
    self->api->request_defend = request_defend;
    self->api->request_weak = request_weak;
    self->api->request_heal = request_heal;
    self->api->request_hurt = request_hurt;
    self->api->detect_exist_object = detect_exist_object;
    self->api->get_object = get_object;
    self->api->find_closest_object_in_direction = find_closest_object_in_direction;
    self->api->find_closest_object = find_closest_object;

    return self;
}


// destroy the processor
void destroy_processor(Processor *self){
    destroy_base(self->base);
    free(self->anime_cache);
    free(self->api);
    free(self);
}


// place an object at this place
// return ptr to the object if success, return NULL if failed 
// notice that the object's Block and Processor need not to be set by extern user
Object* place_object(Processor *self, Object* object, int x, int y, int length, int height){
    Block* block = self->base->create_block(self->base, x, y, length, height, UP);
    if(block == NULL){
        return NULL;
    }
    block->any_type = object->config.type;
    block->any = (void*)object;
    object->block = block;
    object->host = self;
    return object;
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
    for(i = 0; i < block_num; i++){
        Object* object = (Object*)blocks[i]->any;
        if(object->status.frozen_degree == 0){
            object->action(object);
        }
    }

    // calculate the state
    for(i = 0; i < block_num; i++){
        Object* object = (Object*)blocks[i]->any;
        if(object->status.frozen_degree > 0){
            object->status.frozen_degree--;
        }
        if(object->status.burning_degree > 0){
            object->status.burning_degree--;
        }
        if(object->status.defending_degree > 0){
            object->status.defending_degree--;
        }
        if(object->status.weak_degree > 0){
            object->status.weak_degree--;
        }
    }

    // all interaction requests of the objects.
    for(i = 0; i < self->request_queue_size; i++){
        processAPIRequest(self, &(self->request_queue[i]));
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
}


// export the anime data
ProcessorAnimeData export_anime_data(Processor *self){
    ProcessorAnimeData data;
    int i;
    for(i = 0; i < self->anime_cache_size; i++){
        data.anime_pack[i] = self->anime_cache[i];
    }
    data.player_display_pack[0] = processor_player_data_to_anime_player_data(self->player[0]);
    data.player_display_pack[1] = processor_player_data_to_anime_player_data(self->player[1]);
    return data;
}


// below are provided to the objects
// objects could only use these functions to interact with the processor or other objects

// request to move the object
void request_move(Processor *host, Object *source, int direction, int step){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_MOVE;
    request->source = source;
    request->ext_1 = direction;
    request->ext_2 = step;
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

// request to load the anime
// NOTICE: USER SHOULD USE MALLOC TO ALLOCATE MEMORY FOR THE PACK, AND DON'T FREE IT
void request_load_anime(Processor *host, AnimePack *pack){
    if(host->request_queue_size >= API_REQUEST_MAX_NUM) return;
    ProcessorAPIRequest* request = &(host->request_queue[host->request_queue_size++]);
    request->type = API_REQUEST_LOAD_ANIME;
    request->ext_3 = pack;
}

// detect if there is an object in the area
// return the object if there is, return NULL if not
// range [x1, x2), [y1, y2)
Object* detect_exist_object(Processor *host, int x1, int y1, int x2, int y2){
    Object* object = host->base->detect_exist_block(host->base, x1, y1, x2, y2)->any;
    return object;
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


