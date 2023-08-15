#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utills.h"
#include "symbols.h"
#include "error.h"

#define MAX_LINE_LENGTH 81
#define MAX_LABLE_LENGTH 30
#define MAX_MEMORY_SIZE 1024


void first_pass(FILE *am,FILE *ob,char *file_name_am);



#endif