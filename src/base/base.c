#include "base.h"

#include <stdlib.h>

Block* detect_exist_block(Base *self, int x1, int y1, int x2, int y2);
Block* get_block(Base *self, int x, int y);
Block* create_block(Base *self, int x, int y, int length, int height, int orientation);
BOOL teleport_block(Base *self, int des_x, int des_y, Block *block);
BOOL move_block(Base *self, Block *block, int direction, int step);
void orientate_block(Block *block, int orientation);
void remove_block(Base *self, Block *block);
void destroy_block(Base *self, Block *block);
void del_block(Base *self, Block *block);
void assign_data(Base* self, Block *block, void *any);
Block* find_closest_block_around(Base *self, Block *block, int radius);
Block* find_closest_block_in_direction(Base *self, Block *block, int direction);
Block* find_closest_block(Base *self, Block *block);
BOOL find_all_blocks(Base *self, int x1, int y1, int x2, int y2, Block **blocks, int *length);
void generate_distance_list(Base *self, Block ****distance_list, Block*** block_list, int *length);
void generate_distance_list_gc(Base *self, Block ***distance_list, Block** blocks, int length);
BOOL is_valid_address(Base *self, int x, int y);
BOOL at_edge(Base *self, Block* block);
BOOL going_out_of_bound(Base *self, Block* block, int direction);


// verify if the address is valid
BOOL is_valid_address(Base *self, int x, int y){
    if(x < 0 || x >= self->length || y < 0 || y >= self->height){
        return FALSE;
    }
    return TRUE;
}
// check if the address is in the board
static BOOL check_address_bound(char* function_name, Base *self, int x, int y){
    if(!is_valid_address(self, x, y)){
        //printf("ERROR: invalid address in %s, x = %d, y = %d", function_name, x, y);
        return FALSE;
    }
    return TRUE;
}


// check if the 2 address is in the board
// check the sequence of the address
static BOOL check_two_address_bound(char* function_name, Base *self, int x1, int y1, int x2, int y2){
    int is_valid = 1;
    if(!is_valid_address(self, x1, y1)){
        //printf("ERROR: invalid address in %s, x1 = %d, y1 = %d", function_name, x1, y1);
        is_valid = 2;
    }
    if(!is_valid_address(self, x2, y2)){
        //printf("ERROR: invalid address in %s, x2 = %d, y2 = %d", function_name, x2, y2);
        is_valid = 3;
    }
    if(x1 > x2){
        //printf("ERROR: non logical address in %s, x1 = %d, x2 = %d", function_name, x1, x2);
        is_valid = 4;
    }
    if(y1 > y2){
        //printf("ERROR: non logical address in %s, y1 = %d, y2 = %d", function_name, y1, y2);
        is_valid = 5;
    }
    if(is_valid != 1){
        return FALSE;
    }
    return TRUE;
}
static void check_null_base_pointer(char* function_name, Base *pointer){
    if(pointer == NULL){
        //printf("ERROR: NULL base pointer in %s", function_name);
        exit(2);
    }
}
static void check_null_block_pointer(char* function_name, Block *pointer){
    if(pointer == NULL){
        //printf("ERROR: NULL block pointer in %s", function_name);
        exit(3);
    }
}

// create a base
Base* create_base(int length, int height){
    Base *self = (Base*)malloc(sizeof(Base));
    self->base = (Block***)malloc(sizeof(Block*) * height);
    self->length = length;
    self->height = height;
    int i, j;
    for(i = 0; i < height; i++){
        self->base[i] = (Block**)malloc(sizeof(Block) * length);
    }
    for(i = 0; i < height; i++){
        for(j = 0; j < length; j++){
            self->base[i][j] = NULL;
        }
    }
    self->detect_exist_block = detect_exist_block;
    self->get_block = get_block;
    self->create_block = create_block;
    self->teleport_block = teleport_block;
    self->move_block = move_block;
    self->orientate_block = orientate_block;
    self->remove_block = remove_block;
    self->destroy_block = destroy_block;
    self->delete_block = del_block;
    self->assign_data = assign_data;
    self->find_block_around = find_closest_block_around;
    self->find_closest_block_in_direction = find_closest_block_in_direction;
    self->find_closest_block = find_closest_block;
    self->find_all_blocks = find_all_blocks;
    self->generate_distance_list = generate_distance_list;
    self->generate_distance_list_gc = generate_distance_list_gc;
    self->is_valid_address = is_valid_address;
    self->at_edge = at_edge;
    self->going_out_of_bound = going_out_of_bound;
    return self;
}

// delete a base
void destroy_base(Base *self){
    check_null_base_pointer("destroy_base", self);
    int i, j;
    for(i = 0; i < self->height; i++){
        for(j = 0; j < self->length; j++){
            Block *block = self->base[i][j];
            if(block != NULL){
                self->delete_block(self, block);
            }
        }
    }
    for(i = 0; i < self->height; i++){
        free(self->base[i]);
    }
    free(self);
}



// detect if there is an block in the area, return NULL if not, return the first block if there is
// [x1 x2), [y1 y2)
Block* detect_exist_block(Base *self, int x1, int y1, int x2, int y2){
    int i, j;
    for(i = y1; i < y2; i++){
        for(j = x1; j < x2; j++){
            if(self->is_valid_address(self, j, i)){
                if(self->base[i][j] != NULL){
                    return self->base[i][j];
                }
            }
        }
    }
    return NULL;
}

// get the block at this place
// return NULL if there is no block
Block* get_block(Base *self, int x, int y){
    check_null_base_pointer("get_block", self);
    if(!check_address_bound("get_block", self, x, y)){
        return NULL;
    }
    return self->base[y][x];
}

// create an block at this place, the place is up left corner
Block* create_block(Base *self, int x, int y, int length, int height, int orientation){
    check_null_base_pointer("create_block", self);
    if(!is_valid_address(self, x, y) || !is_valid_address(self,x+length-1, y+height-1)){
        return NULL;
    }
    if(detect_exist_block(self, x, y, x+length, y+height) != NULL){
        return NULL;
    }
    Block *block = (Block*)malloc(sizeof(Block));
    block->x = x;
    block->y = y;
    block->length = length;
    block->height = height;
    block->orientation = orientation;
    block->any = NULL;
    int i, j;
    for(i = y; i < y+height; i++){
        for(j = x; j < x+length; j++){
            self->base[i][j] = block;
        }
    }
    return block;
}

// teleport the block, the place is up left corner
// the path do not need to be empty
// if success, return the block, else return NULL
BOOL teleport_block(Base *self, int des_x, int des_y, Block *block){
    check_null_base_pointer("teleport_block", self);
    check_null_block_pointer("teleport_block", block);
    BOOL res1 = check_address_bound("teleport_block", self, des_x, des_y);
    BOOL res2 = check_address_bound("teleport_block", self, des_x+block->length-1, des_y+block->height-1);
    if(!res1 || !res2){
        return FALSE;
    }
    if(detect_exist_block(self, des_x, des_y, des_x+block->length, des_y+block->height) != NULL){
        return FALSE;
    }
    if(block == NULL){
        //printf("ERROR: NULL block in teleport_block");
        return FALSE;
    }
    int i, j;
    for(i = block->y; i < block->y+block->height; i++){
        for(j = block->x; j < block->x+block->length; j++){
            self->base[i][j] = NULL;
        }
    }
    block->x = des_x;
    block->y = des_y;
    for(i = block->y; i < block->y+block->height; i++){
        for(j = block->x; j < block->x+block->length; j++){
            self->base[i][j] = block;
        }
    }
    return TRUE;
}

// move the block, the anchor point is up left corner
// the path need to be empty
// if success, return the block, else return NULL
BOOL move_block(Base *self, Block *block, int direction, int step){
    check_null_base_pointer("move_block", self);
    check_null_block_pointer("move_block", block);
    if(step == 0){
        return TRUE;
    }
    int des_x = block->x;
    int des_y = block->y;
    int empty_zone_x1, empty_zone_y1, empty_zone_x2, empty_zone_y2;
    switch(direction){
        case UP:
            des_y -= step;
            empty_zone_x1 = block->x;
            empty_zone_y1 = des_y;
            empty_zone_x2 = block->x + block->length;
            empty_zone_y2 = block->y;
            break;
        case DOWN:
            des_y += step;
            empty_zone_x1 = block->x;
            empty_zone_y1 = block->y + block->height;
            empty_zone_x2 = block->x + block->length;
            empty_zone_y2 = des_y + block->height;
            break;
        case LEFT:
            des_x -= step;
            empty_zone_x1 = des_x;
            empty_zone_y1 = block->y;
            empty_zone_x2 = block->x;
            empty_zone_y2 = block->y + block->height;
            break;
        case RIGHT:
            des_x += step;
            empty_zone_x1 = block->x + block->length;
            empty_zone_y1 = block->y;
            empty_zone_x2 = des_x + block->length;
            empty_zone_y2 = block->y + block->height;
            break;
        default:
            //printf("ERROR: invalid direction in move_block");
            return FALSE;
    }
    if(detect_exist_block(self, empty_zone_x1, empty_zone_y1, empty_zone_x2, empty_zone_y2) != NULL){
        return FALSE;
    }
    if(!is_valid_address(self, des_x, des_y) ||    // up left corner
       !is_valid_address(self, des_x+block->length-1, des_y+block->height-1)){    // down right corner
        return FALSE;
    }
    int i, j;
    for(i = block->y; i < block->y+block->height; i++){
        for(j = block->x; j < block->x+block->length; j++){
            self->base[i][j] = NULL;
        }
    }
    block->x = des_x;
    block->y = des_y;
    for(i = block->y; i < block->y+block->height; i++){
        for(j = block->x; j < block->x+block->length; j++){
            self->base[i][j] = block;
        }
    }
    switch(direction){
        case UP:block->orientation = UP;break;
        case DOWN:block->orientation = DOWN;break;
        case LEFT:block->orientation = LEFT;break;
        case RIGHT:block->orientation = RIGHT;break;
        }
    return TRUE;
}

// orientate the block
void orientate_block(Block *block, int orientation){
    check_null_block_pointer("orientate_block", block);
    block->orientation = orientation;
}

// remove the block from the base, but not free it
void remove_block(Base *self, Block *block){
    check_null_base_pointer("remove_block", self);
    check_null_block_pointer("remove_block", block);
    int i, j;
    for(i = block->y; i < block->y+block->height; i++){
        for(j = block->x; j < block->x+block->length; j++){
            self->base[i][j] = NULL;
        }
    }
}

// destroy the block, just free it, use with remove_block
void destroy_block(Base *self, Block *block){
    check_null_base_pointer("destroy_block", self);
    check_null_block_pointer("destroy_block", block);
    free(block);
}

// delete the block, behave like remove_block + destroy_block 
void del_block(Base* self, Block* block){
    check_null_base_pointer("delete_block", self);
    check_null_block_pointer("delete_block", block);
    int i, j;
    for(i = block->y; i < block->y+block->height; i++){
        for(j = block->x; j < block->x+block->length; j++){
            self->base[i][j] = NULL;
        }
    }
    free(block);
}

// assign data to data field of block
void assign_data(Base* self, Block *block, void *any){
    check_null_base_pointer("assign_data", self);
    check_null_block_pointer("assign_data", block);
    block->any = any;
}

// x1 == x2 or y1 == y2, if x1 == x2 && y1 == y2, return -1
// assume x1 == x2, then scan from y1 to y2, range [y1, y2)
// if detected block, return yn, else return -1
static int path_detect(Base* self, int x1, int y1, int x2, int y2){
    check_null_base_pointer("path_detect", self);
    if(x1 == x2 && y1 == y2){
        return -1;
    }
    if(x1 == x2 && y1 != y2){
        int i;
        if(y1 < y2){
            for(i = y1; i < y2; i++){
                if(self->base[i][x1] != NULL){
                    return i;
                }
            }
        }else{
            for(i = y1; i > y2; i--){
                if(self->base[i][x1] != NULL){
                    return i;
                }
            }
        }
        return -1;
    }else if(x1 != x2 && y1 == y2){
        int i;
        if(x1 < x2){
            for(i = x1; i < x2; i++){
                if(self->base[y1][i] != NULL){
                    return i;
                }
            }
        }else{
            for(i = x1; i > x2; i--){
                if(self->base[y1][i] != NULL){
                    return i;
                }
            }
        }
        return -1;
    }
    return -1;
}

// find the closest block in the direction
// if success, return the block, else return NULL
Block* find_closest_block_in_direction(Base *self, Block *block, int direction){
    check_null_base_pointer("find_closest_block_in_direction", self);
    check_null_block_pointer("find_closest_block_in_direction", block);
    if(direction != UP && direction != DOWN && direction != LEFT && direction != RIGHT){
        return NULL;
    }
    int i, j;
    int* touch_position;
    int des_x;
    int des_y;
    int pos;
    int expect;
    int expect_pos;
    switch(direction){
        case UP:
            touch_position = (int*)malloc(sizeof(int)*block->length);
            for(i = block->x; i < block->x + block->length; i++){
                pos = path_detect(self, i, block->y - 1, i, -1);
                touch_position[i] = pos;
            }
            expect = -1;
            expect_pos = -1;
            for(i = block->x; i < block->x + block->length; i++){
                if(touch_position[i] != -1 && touch_position[i] > expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect_pos;
            des_y = expect;
            free(touch_position);
            break;
        case DOWN:
            touch_position = (int*)malloc(sizeof(int)*block->length);
            for(i = block->x; i < block->x + block->length; i++){
                pos = path_detect(self, i, block->y + block->height, i, self->height);
                touch_position[i] = pos;
            }
            expect = self->height;
            expect_pos = -1;
            for(i = block->x; i < block->x + block->length; i++){
                if(touch_position[i] != -1 && touch_position[i] < expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect_pos;
            des_y = expect;
            free(touch_position);
            break;
        case LEFT:
            touch_position = (int*)malloc(sizeof(int)*block->height);
            for(i = block->y; i < block->y + block->height; i++){
                pos = path_detect(self, block->x - 1, i, -1, i);
                touch_position[i] = pos;
            }
            expect = -1;
            expect_pos = -1;
            for(i = block->y; i < block->y + block->height; i++){
                if(touch_position[i] != -1 && touch_position[i] > expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect;
            des_y = expect_pos;
            free(touch_position);
            break;
        case RIGHT:
            touch_position = (int*)malloc(sizeof(int)*block->height);
            for(i = block->y; i < block->y + block->height; i++){
                int pos;
                pos = path_detect(self, block->x+block->length, i, self->length, i);
                touch_position[i] = pos;
            }
            expect = self->length;
            expect_pos = -1;
            for(i = block->y; i < block->y + block->height; i++){
                if(touch_position[i] != -1 && touch_position[i] < expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect;
            des_y = expect_pos;
            free(touch_position);
            break;
    }
    if(is_valid_address(self, des_x, des_y)){
        return self->base[des_y][des_x];
    }
    return NULL;
}

// scan the around of the block
// if success, return the block, else return NULL
Block* find_closest_block_around(Base *self, Block *block, int radius){
    check_null_base_pointer("find_closest_block_around", self);
    check_null_block_pointer("find_closest_block_around", block);
    int i, j;
    int x1, x2, y1, y2;
    // now the range is [x1, x2), [y1, y2)
    x1 = block->x - radius;
    x2 = block->x + block->length + radius;
    y1 = block->y - radius;
    y2 = block->y + block->height + radius;
    for(i = y1; i < y2; i++){
        if(!is_valid_address(self, x1, i)) continue;
        if(self->base[i][x1] != NULL){
            return self->base[i][x1];
        }
    }
    for(i = y1; i < y2; i++){
        if(!is_valid_address(self, x2 - 1, i)) continue;
        if(self->base[i][x2 - 1] != NULL){
            return self->base[i][x2 - 1];
        }
    }
    for(i = x1; i < x2; i++){
        if(!is_valid_address(self, i, y1)) continue;
        if(self->base[y1][i] != NULL){
            return self->base[y1][i];
        }
    }
    for(i = x1; i < x2; i++){
        if(!is_valid_address(self, i, y2 - 1)) continue;
        if(self->base[y2 - 1][i] != NULL){
            return self->base[y2 - 1][i];
        }
    }
    return NULL;
}

// find the closest block
// if success, return the block, else return NULL
Block* find_closest_block(Base *self, Block *block){
    check_null_base_pointer("find_closest_block", self);
    check_null_block_pointer("find_closest_block", block);
    int i;
    for(i = 1; i < LOOKUP_MAX_RADIUS; i++){
        Block *result = find_closest_block_around(self, block, i);
        if(result != NULL){
            return result;
        }
    }
    return NULL;
}

//find blocks in [x1, x2), [y1, y2) 
BOOL find_all_blocks(Base *self, int x1, int y1, int x2, int y2, Block **blocks, int *length){
    check_null_base_pointer("find_all_blocks", self);
    BOOL res = check_two_address_bound("find_all_block", self, x1, y1, x2-1, y2-1);
    if(res == FALSE){
        return FALSE;
    }
    int i, j, k, valid;
    int count = 0;
    for(i = y1; i < y2; i++){
        for(j = x1; j < x2; j++){
            if(self->base[i][j] != NULL){
                valid = 1;
                for(k = 0; k < count; k++){
                    if(blocks[k] == self->base[i][j]){
                        valid = 0;
                        break;
                    }
                }
                if(valid) blocks[count++] = self->base[i][j];
            }
        }
    }
    *length = count;
    return TRUE;
}

// this function first generate a list of existing blocks, and keep their x, y, Block* in a list
// then generate a 2d array of n * n, n is the length of the list
// the array is used to store the distance between the block and the target block
// then sort the array by the distance
// get a plain Block**** and Block*** and int*, they are for the return value
// after call, the distance list and the block list is mallocd.
// distance_list is a 2d array of Block*, block_list is a 1d array of Block*
void generate_distance_list(Base *self, Block ****distance_list, Block*** block_list, int *length){
    (*block_list) = (Block**)malloc(sizeof(Block*) * self->length * self->height); 
    int list_length = 0;
    find_all_blocks(self, 0, 0, self->length, self->height, (*block_list), &list_length);
    float **dist_list = (float**)malloc(sizeof(float*) * list_length);
    (*distance_list) = (Block***)malloc(sizeof(Block*) * list_length);
    for (int i = 0; i < list_length; i++){
        dist_list[i] = (float*)malloc(sizeof(float) * list_length);
        (*distance_list)[i] = (Block**)malloc(sizeof(Block*) * list_length);
    }
    for (int i = 0; i < list_length; i++){
        for (int j = 0; j < list_length; j++){
            dist_list[i][j] = ((*block_list)[i]->x - (*block_list)[j]->x)*((*block_list)[i]->x - (*block_list)[j]->x) + ((*block_list)[i]->y - (*block_list)[j]->y)*((*block_list)[i]->y - (*block_list)[j]->y);
        }
    }

    // then according to the distance list, place the blocks in the blocks 2d array, each line in the 2d array is a list of blocks which are sorted by the distance
    for (int i = 0; i < list_length; i++){
        for(int j = 0; j < list_length; j++){
            // now fill the blocks for BLOCK* : blocks[i]
            // find the min distance
            float min = 100000000;
            int min_index = 0;
            for (int k = 0; k < list_length; k++){
                if (dist_list[i][k] < min){
                    min = dist_list[i][k];
                    min_index = k;
                }
            }
            // fill the min_index block
            (*distance_list)[i][j] = (*block_list)[min_index];
            // set the distance to a big number
            dist_list[i][min_index] = 100000000;
        }
    }
    //return the list and the length
    *length = list_length;

    // free the dist list
    for (int i = 0; i < list_length; i++){
        free(dist_list[i]);
    }
    free(dist_list);
}

void generate_distance_list_gc(Base *self, Block ***distance_list, Block** blocks, int length){
    for(int i = 0; i < length; i++){
        free(distance_list[i]);
    }
    free(distance_list);
    free(blocks);
}

BOOL at_edge(Base *self, Block* block){
    check_null_base_pointer("at_edge", self);
    check_null_block_pointer("at_edge", block);
    int upper_bound = block->y;
    int lower_bound = block->y - block->height + 1;
    int left_bound = block->x;
    int right_bound = block->x + block->length - 1;
    if(upper_bound == 0 || lower_bound == self->height - 1 || left_bound == 0 || right_bound == self->length - 1){
        return TRUE;
    }
    return FALSE;
}

BOOL going_out_of_bound(Base *self, Block* block, int direction){
    check_null_base_pointer("going_out_of_bound", self);
    check_null_block_pointer("going_out_of_bound", block);
    int upper_bound = block->y;
    int lower_bound = block->y - block->height + 1;
    int left_bound = block->x;
    int right_bound = block->x + block->length - 1;
    if(direction == UP){
        if(upper_bound == 0){
            return TRUE;
        }
    }
    else if(direction == DOWN){
        if(lower_bound == self->height - 1){
            return TRUE;
        }
    }
    else if(direction == LEFT){
        if(left_bound == 0){
            return TRUE;
        }
    }
    else if(direction == RIGHT){
        if(right_bound == self->length - 1){
            return TRUE;
        }
    }
    return FALSE;
}