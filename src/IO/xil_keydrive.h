#include "xgpio.h"
#include "xparameters.h"
#include "xil_io.h"
#include "stdlib.h"
#include "xintc_l.h"
#include "xtmrctr_l.h"
#include "mb_interface.h"
#include "../player_dash.h"

u8 scancode[256];
u8 key_queue_A[1000];
u8 key_queue_B[1000];
u8 key_pressing_A = 0;
u8 key_pressing_B = 0;
int key_queue_A_length = 0;
int key_queue_B_length = 0;
void scancode_ascii();
void key_interrupt();
int write_index = 0;
extern PlayerDash player_dash;

u8 key_to_char[256][2] = {
    {0x15, 'q'},
    {0x1d, 'w'},
    {0x24, 'e'},
    {0x2d, 'r'},
    {0x2c, 't'},
    {0x35, 'y'},
    {0x3c, 'u'},
    {0x43, 'i'},
    {0x44, 'o'},
    {0x4d, 'p'},
    {0x1c, 'a'},
    {0x1b, 's'},
    {0x23, 'd'},
    {0x2b, 'f'},
    {0x34, 'g'},
    {0x33, 'h'},
    {0x3b, 'j'},
    {0x42, 'k'},
    {0x4b, 'l'},
    {0x12, 'z'},
    {0x22, 'x'},
    {0x21, 'c'},
    {0x2a, 'v'},
    {0x32, 'b'},
    {0x31, 'n'},
    {0x3a, 'm'}
};

u8 char_to_key[256][2] = {
{'q', 0x15},
{'w', 0x1d},
{'e', 0x24},
{'r', 0x2d},
{'t', 0x2c},
{'y', 0x35},
{'u', 0x3c},
{'i', 0x43},
{'o', 0x44},
{'p', 0x4d},
{'a', 0x1c},
{'s', 0x1b},
{'d', 0x23},
{'f', 0x2b},
{'g', 0x34},
{'h', 0x33},
{'j', 0x3b},
{'k', 0x42},
{'l', 0x4b},
{'z', 0x12},
{'x', 0x22},
{'c', 0x21},
{'v', 0x2a},
{'b', 0x32},
{'n', 0x31},
{'m', 0x3a}
};

char read_char_from_terminal(){
    static last_inp = 0;
    char inp;
    while(1){
        inp = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
        if(inp == last_inp){
            continue;
        }
    	if(inp != 13){
    		break;
    	}
        last_inp = inp;
    }
    return inp;
}

void uart_interrupt(){
    scancode[write_index] = (u8)read_char_from_terminal();
    write_index++;
    if(write_index == 256){
        write_index = 0;
    }
}

char read_char(int read_index, char* release){
    char cha = read_char_from_terminal();
    switch(cha){
        case 'q':player_dash.player_1_use_skill_key = TRUE; break;
        case 'w':player_dash.player_1_direction_key = UP; key_pressing_A = UP; break;
        case 'e':player_dash.player_1_change_skill_key = LEFT; break;
        case 'r':player_dash.player_1_attack_key = TRUE; break;
        case 't':player_dash.player_1_change_skill_key = RIGHT; break;
        case 's':player_dash.player_1_direction_key = DOWN; key_pressing_A = DOWN; break;
        case 'a':player_dash.player_1_direction_key = LEFT; key_pressing_A = LEFT; break;
        case 'd':player_dash.player_1_direction_key = RIGHT; key_pressing_A = RIGHT; break;

        case 'y':player_dash.player_2_use_skill_key = TRUE; break;
        case 'u':player_dash.player_2_direction_key = UP; key_pressing_B = UP; break;
        case 'i':player_dash.player_2_change_skill_key = LEFT; break;
        case 'o':player_dash.player_2_attack_key = TRUE; break;
        case 'p':player_dash.player_2_change_skill_key = RIGHT; break;
        case 'j':player_dash.player_2_direction_key = DOWN; key_pressing_B = DOWN; break;
        case 'h':player_dash.player_2_direction_key = LEFT; key_pressing_B = LEFT; break;
        case 'k':player_dash.player_2_direction_key = RIGHT; key_pressing_B = RIGHT; break;

        case 'W': key_pressing_A = NONE; break;
        case 'S': key_pressing_A = NONE; break;
        case 'A': key_pressing_A = NONE; break;
        case 'D': key_pressing_A = NONE; break;
        case 'U': key_pressing_B = NONE; break;
        case 'J': key_pressing_B = NONE; break;
        case 'H': key_pressing_B = NONE; break;
        case 'K': key_pressing_B = NONE; break;
    }
}

void key_step(){
    if(key_pressing_A == UP){
        player_dash.player_1_direction_key = UP;
    }
    else if(key_pressing_A == DOWN){
        player_dash.player_1_direction_key = DOWN;
    }
    else if(key_pressing_A == LEFT){
        player_dash.player_1_direction_key = LEFT;
    }
    else if(key_pressing_A == RIGHT){
        player_dash.player_1_direction_key = RIGHT;
    }
    if(key_pressing_B == UP){
        player_dash.player_2_direction_key = UP;
    }
    else if(key_pressing_B == DOWN){
        player_dash.player_2_direction_key = DOWN;
    }
    else if(key_pressing_B == LEFT){
        player_dash.player_2_direction_key = LEFT;
    }
    else if(key_pressing_B == RIGHT){
        player_dash.player_2_direction_key = RIGHT;
    }
}

void loop(){
    int read_index = 0;
    char release = 0;
    while(1){
        read_char(read_index, &release);
    }
}
