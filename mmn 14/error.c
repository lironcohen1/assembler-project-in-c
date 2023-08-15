
/*******************************************************

 in this file we are printing all the possible errors

*******************************************************/


#include "error.h"




int x=1;
int *status=&x;


/***Mcro errors***/


/*this function print ERROR if there is extra text after the line (mcro "mcro_name") or after the line(endmcro)*/
void mcro_error(int line_number,char *file_name_as){
    printf("ERROR: %s --> extra text after macro definition (in line number: %d) \n",file_name_as,line_number);
    *status=0;
    
}
/*this function is print ERROR if the mcro name is illegal*/
void mcro_name_error(int line_number,char *file_name_as){
     printf("ERROR: %s --> mcro name is illegal (in line number: %d) \n",file_name_as,line_number);
    *status=0;
    
}

/***Assembler errors***/

/*this function is print ERROR if the length of the line is more than 82 charcter including the \n */
void error_line_length(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> line exceeds max length of 80 characters (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if the memory words are more then 1024 words */
void error_max_memory_size(char *file_name_am){
    printf("ERROR: %s --> .ob file exceeds max memory size of 1024 \n",file_name_am);
    *status=0;

}



/***Lables error***/

/*this function is print ERROR if lable name is not by the rules */
void error_lable_length(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> lable name exceeds max length of 30 characters (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if lable name is not by the rules */
void error_lable_invalid_name(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> lable name must start with letter followed by letters or numbers, and also cannot be an instruction, data or register name (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}
/*this function is print ERROR if the lable defined more than once */
void error_lable_already_defined(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> lable name already exist (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}
/*this function is print ERROR if there was a declartion of lable but he was not defined in the file */
void error_lable_declared_but_not_defined(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> lable name is declared but not defined (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}


/***Instruction errors***/

/*this function is print ERROR if we dont get all the paramters */
void error_missing_paramter(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> missing parameter (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if there are too many paramters */
void error_too_many_paramters(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> too many parameters (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if there is a missing comma */
void error_missing_comma(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> missing comma (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if there is a comma not according the rules */
void error_unexpected_comma(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> unexpected comma (in line number: %d) \n",file_name_am,am_line_number);
        *status=0;
}

/*this function is print ERROR if there is a consecutive commas */
void error_too_many_commas(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> too many commas (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if we dont have a space acorrding to the rules */
void error_missing_space(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> missing space after instruction or data sentence (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if we dont have the instruction or data word*/
void error_missing_sentence(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> missing instruction or data sentence (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if the word is not one of the instruction or data saved word */
void error_unknown_sentence(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> Unknown instruction or data sentence (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if the source paramter is not apropiate to the insturcion or data word */
void error_invalid_source_paramter(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> invalid source paramter (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if the destination paramter is not apropiate to the insturcion or data word */
void error_invalid_destination_paramter(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> invalid destination paramter (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}


/***Data errors***/

/*this function is print ERROR if it is not an integer number */
void error_invalid_number(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> invalid number (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if the number exceeds the maximum or the minimum range he can be */
void error_number_size(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> number size have to be between -2048 to 2047 (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}

/*this function is print ERROR if the string did not start and end with quote */
void error_string_quotes(int am_line_number,char *file_name_am){
    printf("ERROR: %s --> string declarations must start and end with quotes (in line number: %d) \n",file_name_am,am_line_number);
    *status=0;
}











