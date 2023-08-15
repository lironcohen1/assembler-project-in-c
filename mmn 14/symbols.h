#ifndef SYMBOLS_H
#define SYMBOLS_H




#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*opcode and registers table*/
typedef struct{
    char *name;
    char *binary;
}array;


extern array registers[8];
extern array opcodes[16];

/*lables table*/

typedef struct node * ptr;
typedef struct node {
    char *words;
    int line_number;
    ptr next;
}Node;

extern ptr h_INSTRUCTION;
extern ptr h_DATA;
extern ptr h_instruction_lable;
extern ptr h_data_lable;
extern ptr h_extern;

void add_to_list(char *words,int cnt,ptr *h_ptr);
void freelist(ptr *h_ptr);
int check_list(char *lable,ptr h_ptr);
void add_to_data_lable(int IC,ptr h_ptr);
void free_all_5_lists();



#endif


