#ifndef UTILLS_H
#define UTILLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "symbols.h"
#include "error.h"

#define MAX_LABLE_LENGTH 30
#define MIN_SIZE_OF_NUMBER -2048
#define MAX_SIZE_OF_NUMBER 2047



FILE* open_file(FILE *fd,char file_name[],char s[]);
long get_file_size(FILE *as);

void skip_space(char *line,int *index);
void get_word(char *line, char *strcopy, int *index);

void get_lable(char *line,char *current_word,int *index);
int check_lable(char *lable_name,char *word, int am_line_number, char *file_name_am);

int opcode_check(char *current_word);

/*instruction and data help function*/
void get_paramter(char *line, char *param, int *index); 
int check_only_one_comma(char *line,int *index,int am_line_number,char *file_name_am);
int early_end(char *line,int index,int am_line_number,char *file_name_am);
int check_if_register(char *param);
int data_check(char *line,int *index,int am_line_number,char *file_name_am,int *DC);
int valid_number(char *line,int *index,int am_line_number,char *file_name_am);
            



void skip_lable(char *line,int *index);
void skip_space_and_comma(char *line,int *index);


/*second pass help function*/
void first_word_to_binary(char *source_paramter,char *opcode ,char* destination_paramter,char *first_word);
void two_register_word_to_binary(char *source_paramter,char* destination_paramter,char *second_word);
void source_word_to_binary(char* paramter,char *source_word,FILE *ext,int ob_line_number,int am_line_number,char *file_name_am);
void destination_word_to_binary(char* paramter,char *destination_word,FILE *ext,int ob_line_number,int am_line_number,char *file_name_am);
char* get_binary_register(char *paramter);
int get_lable_number(char *paramter,ptr h_ptr);
char* get_binary_opcode(char *opcode);
int check_if_source_paramter_ok(char *word,char *paramter);
int check_if_destination_paramter_ok(char *word,char *paramter);
void int_to_binary_10_bits(int lable_number, char *word);
void int_to_binary_12_bits(int number, char *word);
void write_to_ob(FILE *ob,char *word);
void convert_to_base_64(char *word,char *base_64_word);
int power(int number, int power);
void get_string(char *line, char *param1,int *index);



#endif