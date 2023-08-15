#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*status is a flag that tell us if there was any error in the file or not*/
extern int *status;

/***Mcro errors***/
void mcro_error(int line_number,char *file_name_as);
void mcro_name_error(int line_number,char *file_name_as);

/***Assmbler errors***/

void error_line_length(int am_line_number,char *file_name_am);
void error_max_memory_size(char *file_name_am);

/*Lables error*/
void error_lable_length(int am_line_number,char *file_name_am);
void error_lable_invalid_name(int am_line_number,char *file_name_am);
void error_lable_already_defined(int am_line_number,char *file_name_am);
void error_lable_declared_but_not_defined(int am_line_number,char *file_name_am);


/* Instruction errors   */

void error_missing_paramter(int am_line_number,char *file_name_am);
void error_too_many_paramters(int am_line_number,char *file_name_am);
void error_missing_comma(int am_line_number,char *file_name_am);
void error_unexpected_comma(int am_line_number,char *file_name_am);
void error_too_many_commas(int am_line_number,char *file_name_am);
void error_missing_space(int am_line_number,char *file_name_am);
void error_missing_sentence(int am_line_number,char *file_name_am);
void error_unknown_sentence(int am_line_number,char *file_name_am);
void error_invalid_source_paramter(int am_line_number,char *file_name_am);
void error_invalid_destination_paramter(int am_line_number,char *file_name_am);

/*Data errors*/

void error_invalid_number(int am_line_number,char *file_name_am);
void error_number_size(int am_line_number,char *file_name_am);
void error_string_quotes(int am_line_number,char *file_name_am);








#endif




