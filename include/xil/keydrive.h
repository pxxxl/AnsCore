#include "xgpio.h"
#include "xparameters.h"
#include "xil_io.h"
#include "stdlib.h"
#include "xintc_l.h"
#include "xtmrctr_l.h"
#include "mb_interface.h"

u8 scancode[256];
void scancode_ascii();
void key_interrupt();
int write_index = 0;

u8 key[256][2] = {
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

u8 key[256][2] = {
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

void key_interrupt(){
    scancode[write_index] = (u8)(Xil_In32(XPAR_PS2_0_S00_AXI_BASEADDR) & 0xff);
    write_index++;
    if(write_index == 256){
        write_index = 0;
    }
    Xil_Out32(
        XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET,
        Xil_In32(XPAR_INTC_0_BASEADDR + XIN_ISR_OFFSET)
    );
}

void scancode_Ascii(){
    int read_index = 0;
    int release = 0;
    while(1){
        if(read_index != write_index){
            switch(scancode[read_index]){
                case 0xf0:
                    release = 1;
                    break;
                default:
                    if(release == 0){
                        
                    } else {
                        release = 0;
                    }
            }
            read_index++;
            if(read_index == 256){
                read_index = 0;
            }
        }
    }
}