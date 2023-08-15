#ifndef PRE_PROCESSOR_H
#define PRE_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "symbols.h"
#include "hashmap.h"
#include "utills.h"





void pre_processor(FILE *as,FILE *am,char* file_name_as);


void is_mcro(char *line,char *strcopy,char *str_mcro,char *mcro_name,int *flag,HashMap* mcro,int line_number,char *file_name_as);
void get_line(char *line,char *strcopy,char *mcro_name,int *flag,HashMap* mcro,FILE *am,int line_number,char *file_name_as);








#endif

