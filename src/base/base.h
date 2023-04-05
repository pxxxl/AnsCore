#pragma once
#include "macros.h"


typedef struct Block{
    // Position : up left corner
    int x;
    int y;

    // length : x
    // height : y
    int length;
    int height;
    
    int orientation;

    // this module did not release the "any" pointer
    void* any;
    int any_type;
} Block;

struct Base;
typedef struct Base Base;
struct Base
{
    Block ***base;
    int length;
    int height;

    Block* (*detect_exist_block)(Base *self, int x1, int y1, int x2, int y2);
    Block* (*get_block)(Base *self, int x, int y);
    Block* (*create_block)(Base *self, int x, int y, int length, int height, int orientation);
    BOOL (*teleport_block)(Base *self, int des_x, int des_y, Block *block);
    BOOL (*move_block)(Base *self, Block *block, int direction, int step);
    void (*orientate_block)(Block *block, int orientation);
    void (*remove_block)(Base *self, Block *block);
    void (*destroy_block)(Base *self, Block *block);
    void (*delete_block)(Base *self, Block *block);
    void (*assign_data)(Base* self, Block *block, void *any, int any_type);
    Block* (*find_closest_block_in_direction)(Base *self, Block *block, int direction);
    Block* (*find_closest_block)(Base *self, Block *block);
    BOOL (*find_all_blocks)(Base *self, int x1, int y1, int x2, int y2, Block **blocks, int *length);

};

// create a base
Base* create_base(int length, int height);

// delete a base
void destroy_base(Base *self);

// NOTICE: varieble range: [x1, x2), [y1, y2)

// detect if there is an block in the area, return NULL if not, return the first block if there is
Block* detect_exist_block(Base *self, int x1, int y1, int x2, int y2);

// get the block at this place
Block* get_block(Base *self, int x, int y);

// create an block at this place, the place is up left corner
Block* create_block(Base *self, int x, int y, int length, int height, int orientation);

// teleport the block, the place is up left corner
// the path do not need to be empty
// if success, return TRUE
BOOL teleport_block(Base *self, int des_x, int des_y, Block *block);

// move the block, the anchor point is up left corner
// the path need to be empty
// if success, return the block, else return NULL
// will change the block's orientation automatically
BOOL move_block(Base *self, Block *block, int direction, int step);

// orientate the block
void orientate_block(Block *block, int orientation);

// remove the block from the base, but not free it
void remove_block(Base *self, Block *block);

// destroy the block, just free it, use with remove_block
// notice it does not free the "any" pointer
void destroy_block(Base *self, Block *block);

// delete the block, same to {remove_block and destroy_block}
// notice it does not free the "any" pointer
void delete_block(Base* self, Block* block);

// assign the any pointer
void assign_data(Base* self, Block* block, void* any, int any_type);

// find the closest block in the direction
// if success, return the block, else return NULL
Block* find_closest_block_in_direction(Base *self, Block *block, int direction);

// find the closest block
// if success, return the block, else return NULL
Block* find_closest_block(Base *self, Block *block);

// find all blocks in the area
// if find at least 1, return TRUE, else return FALSE
BOOL find_all_blocks(Base *self, int x1, int y1, int x2, int y2, Block **blocks, int *length);



