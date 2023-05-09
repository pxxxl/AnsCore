#include "../custom.h"

void defend_sheild(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int center_x = x + self->block->length / 2;
    int center_y = y + self->block->height / 2;
    int min_x = center_x - DEFEND_SHIELD_HALF_LENGTH;
    int min_y = center_y - DEFEND_SHIELD_HALF_HEIGHT;
    int max_x = center_x + DEFEND_SHIELD_HALF_LENGTH;
    int max_y = center_y + DEFEND_SHIELD_HALF_HEIGHT;
    for(int i = min_x; i <= max_x; i++){
        for(int j = min_y; j <= max_y; j++){
            Object* block = self->api->get_object(self->host, i, j);
            if(block != NULL){
                self->api->request_defend(self->host, self, block, 1);
            }
        }
    }
}