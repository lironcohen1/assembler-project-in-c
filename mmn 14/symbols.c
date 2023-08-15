/****************************************************************************************
  in this file there is method that help us to create and check the lables table
****************************************************************************************/

#include "symbols.h"



array registers[8]={
    {"@r0","00000"},
    {"@r1","00001"},
    {"@r2","00010"},
    {"@r3","00011"},
    {"@r4","00100"},
    {"@r5","00101"},
    {"@r6","00110"},
    {"@r7","00111"}
};

array opcodes[16]=
{
    {"mov","0000"},
    {"cmp","0001"},
    {"add","0010"},
    {"sub","0011"},
    {"not","0100"},
    {"clr","0101"},
    {"lea","0110"},
    {"inc","0111"},
    {"dec","1000"},
    {"jmp","1001"},
    {"bne","1010"},
    {"red","1011"},
    {"prn","1100"},
    {"jsr","1101"},
    {"rts","1110"},
    {"stop","1111"}

};

ptr h_INSTRUCTION= NULL;
ptr h_DATA= NULL;
ptr h_instruction_lable= NULL;
ptr h_data_lable= NULL;
ptr h_extern= NULL;

/*in this function we are adding node to the list*/
void add_to_list(char *words,int cnt,ptr *h_ptr){

    ptr p1 ,p2;
    ptr t;
    t=(ptr)malloc(sizeof(Node));
    if(!t){
        printf("\n cannot build list \n");
        exit(0);
    }
    t->words = (char *)malloc(strlen(words) + 1); 
    if (!t->words) {
        printf("\n cannot build list \n");
        free(t);
        exit(0);
    }

    strcpy(t->words, words);
    t->line_number=cnt;

    p1=*h_ptr;
    while(p1){
        p2=p1;
        p1=p1->next;
    }
    if(p1==*h_ptr){
        *h_ptr=t;
        t->next=p1;
    }
    else{
        p2->next=t;
        t->next=p1;
    }



}

/*in this function we free the allocat memory each node one after one*/
void freelist(ptr *h_ptr){
    ptr p;
    while(*h_ptr){
        p=*h_ptr;
        *h_ptr=(*h_ptr)->next;
        free(p);
    }
}

/*this funcion is free the 5 list that we used in our program*/
void free_all_5_lists(){
    freelist(&h_INSTRUCTION);
    freelist(&h_DATA);
    freelist(&h_instruction_lable);
    freelist(&h_data_lable);
    freelist(&h_extern);

}

/*this program is check if the lable name is found in the list return 1 if true else return 0*/
int check_list(char *lable,ptr h_ptr){
    while(h_ptr){
        if(!(strcmp(h_ptr->words,lable)))
            return 1;
        h_ptr=h_ptr->next;
    }
    return 0;

}

/*in this function we add a new node to the list*/
void add_to_data_lable(int IC,ptr h_ptr){

    while(h_ptr!=NULL){
        h_ptr->line_number+=IC;
        h_ptr=h_ptr->next;
    }

}









