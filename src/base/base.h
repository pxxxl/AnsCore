#pragma once

#include "../macros.h"

typedef struct Block{               // Position : up left corner
    int x;
    int y;
    int length;                     // length : x
    int height;                     // height : y
    int orientation;                // UP, DOWN, LEFT, RIGHT
    void* any;                      // this module did not release the "any" pointer
} Block;

struct Base;
typedef struct Base Base;


typedef struct Base
{
    Block ***base;
    int length;
    int height;

    // methods
    
    // detect if there is an block in the area, return NULL if not, return the first block if there is
    // [x1 x2), [y1 y2)
    Block* (*detect_exist_block)(Base *self, int x1, int y1, int x2, int y2);

    // get the block at this place
    // return NULL if there is no block
    Block* (*get_block)(Base *self, int x, int y);

    // create an block at this place, the place is up left corner
    Block* (*create_block)(Base *self, int x, int y, int length, int height, int orientation);

    // teleport the block, the place is up left corner
    // the path do not need to be empty
    // if success, return true, else return false
    BOOL (*teleport_block)(Base *self, int des_x, int des_y, Block *block);

    // move the block, the anchor point is up left corner
    // the path need to be empty
    // if success, return the true, else return false
    BOOL (*move_block)(Base *self, Block *block, int direction, int step);

    // orientate the block
    void (*orientate_block)(Block *block, int orientation);

    // remove the block from the base, but not free it
    void (*remove_block)(Base *self, Block *block);

    // destroy the block, (just free it, use with remove_block)
    void (*destroy_block)(Base *self, Block *block);

    // delete the block, behave like remove_block + destroy_block 
    void (*delete_block)(Base *self, Block *block);

    // assign the data to the block
    void (*assign_data)(Base* self, Block *block, void *any);

    // find block around at a radius
    Block* (*find_block_around)(Base *self, Block *block, int radius);

    // find the closest block in the direction
    // if success, return the block, else return NULL
    Block* (*find_closest_block_in_direction)(Base *self, Block *block, int direction);

    // find the closest block
    // if success, return the block, else return NULL
    Block* (*find_closest_block)(Base *self, Block *block);

    //find blocks in [x1, x2), [y1, y2) 
    BOOL (*find_all_blocks)(Base *self, int x1, int y1, int x2, int y2, Block **blocks, int *length);

    // get a plain Block**** and Block*** and int*, they are for the return value
    // after call, the distance list and the block list is mallocd.
    // distance_list is a 2d array of Block*, block_list is a 1d array of Block*
    // the block in block list are all the blocks in the base
    // the distance list's row is the blocks in the block list, the column block is sorted by distance
    void (*generate_distance_list)(Base *self, Block ****distance_list, Block*** blocks, int *length);
    void (*generate_distance_list_gc)(Base *self, Block ***distance_list, Block** blocks, int length);

    BOOL (*is_valid_address)(Base *self, int x, int y);
    BOOL (*at_edge)(Base *self, Block* block);
    BOOL (*going_out_of_bound)(Base *self, Block* block, int direction);
} Base;

// create a base
Base* create_base(int length, int height);

// delete a base
void destroy_base(Base *self);