/**********************************************************************************************************************************
 this file have a various function that help us to interpret the file we get from the user and coding him as necessary
**********************************************************************************************************************************/


#include "utills.h"

/*string that contain the 64 base table*/
char base_64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*this function is open files*/
FILE * open_file(FILE *fd,char file_name[],char s[]){
    if(!(fd=fopen(file_name,s))){
        printf("cannot open file\n");
        exit(0);
    }
    return fd;
}




/*this fumction return the file size (how many charcters he consist)*/
long get_file_size(FILE *as){
    long size;
    fseek(as,0,SEEK_END);
    size=ftell(as);
    fseek(as,0,SEEK_SET);
    size+=2;
    return size;

}





/*this function is skip of white spaces*/
void skip_space(char *line,int *index){
    while (line[*index] == '\t' || line[*index] == ' ') 
        (*index)++;

}

/*this function is get the current word that we want to check*/
void get_word(char *line, char *strcopy, int *index) {
    int i = 0;
    strcopy[0] = '\0';
    
    while (line[*index] != '\t' && line[*index] != ' ' && line[*index] != '\n'){
        strcopy[i] = line[*index];
        (*index)++;
        i++;
    }
    
    strcopy[i] = '\0';  
}

/*this function copy the string to param1 without the quatation marks*/
void get_string(char *line, char *param1,int *index){
    int i = 0;
    (*index)++;/*to skip the open qutation mark*/
    param1[0] = '\0';
    
    while (line[*index] != '\"'){
        param1[i] = line[*index];
        (*index)++;
        i++;
    }

    (*index)++;/*to skip the close qutation mark*/
    
    param1[i] = '\0';  

}


/*this function getting the lable name without the char --> ':' */
void get_lable(char *line,char *current_word,int *index){
    int i = 0;
    current_word[0] = '\0';
    
    while (line[*index] != ':'){
        current_word[i] = line[*index];
        (*index)++;
        i++;
    }
    (*index)++;/*skip the ':'*/
    
    current_word[i] = '\0';  
}

/*in this function we check if the lable name is acoording to the rules*/
int check_lable(char *lable_name,char *word, int am_line_number, char *file_name_am){
    int i=1;
    if(strlen(lable_name)>MAX_LABLE_LENGTH){/*length checking*/
        error_lable_length(am_line_number,file_name_am);
        return 0;
    }
    /*lable name checking*/
    if(!isalpha(lable_name[0])){
        error_lable_invalid_name(am_line_number,file_name_am);
        return 0;
    }
    while(i<strlen(lable_name)){
        if(!isalpha(lable_name[i]) && !isdigit(lable_name[i])){
            error_lable_invalid_name(am_line_number,file_name_am);
            return 0;
        }
        i++;
    }

    if(opcode_check(lable_name)){
        error_lable_invalid_name(am_line_number,file_name_am);
        return 0;
    }
    /*check if lable already defined*/
    if(strcmp(word,".entry")){
        if(check_list(lable_name,h_instruction_lable) || check_list(lable_name,h_data_lable) ||check_list(lable_name,h_extern)){
            error_lable_already_defined(am_line_number,file_name_am);
            return 0;
        }
    }

    return 1;

}




/*this funcion check if the current word is one of the opcodes return 1 if true else return 0*/
int opcode_check(char *current_word){
    int i;
    for(i=0;i<16;i++){
        if(strcmp(current_word,opcodes[i].name)==0)
            return 1;
    }
    return 0;
}

  

/*this function is get the paramters in the instruction sentence */
void get_paramter(char *line, char *param, int *index){
    int i = 0;
    param[0] = '\0';
    
    while (line[*index] != '\t' && line[*index] != ' ' && line[*index] != '\n' && line[*index] != ','){
        param[i] = line[*index];
        (*index)++;
        i++;
    }
    
    param[i] = '\0';  
}

/*this function check if there is only one comma between the two paramters return 1 if true else 0*/
int check_only_one_comma(char *line,int *index,int am_line_number,char *file_name_am){
    skip_space(line,index);
    if(line[*index]!=','){
        error_missing_comma(am_line_number,file_name_am);
        return 0;
    }
    (*index)++;/*skip the ',' */
    skip_space(line,index);
    if(line[*index]==','){
        error_too_many_commas(am_line_number,file_name_am);
        return 0;
    }
    return 1;


}

/*this function check if there was early end if we expected to see more paramters for example and there was not another paramters*/
int early_end(char *line,int index,int am_line_number,char *file_name_am){
    if(line[index]=='\n'){
        error_missing_paramter(am_line_number,file_name_am);
        return 0;
    }
    return 1;

}

/*this function chacking if the paramter is a register*/
int check_if_register(char *param){
    int i;
    for(i=0;i<8;i++){
        if(!strcmp(registers[i].name,param)){
            return 1;
        }
    }
    return 0;

}

/*this function check if the number is according to the rules and also there is one comma between 2 numbers*/
int data_check(char *line,int *index,int am_line_number,char *file_name_am,int *DC){
    if(!valid_number(line,index,am_line_number,file_name_am)){
        return 0;
    }
    skip_space(line,index);
    (*DC)++;
    while(line[*index]!='\n'){
        if(!check_only_one_comma(line,index,am_line_number,file_name_am)){
            return 0;
        }
        skip_space(line,index);
        if(!early_end(line,*index,am_line_number,file_name_am)){
            return 0;
        }
        if(!valid_number(line,index,am_line_number,file_name_am)){
            return 0;
        }
        skip_space(line,index);
        (*DC)++;
        
    }
    return 1;

}

/*this function check if the number we read is an integer number*/
int valid_number(char *line,int *index,int am_line_number,char *file_name_am){
    if(line[*index]=='+' || line[*index]=='-'){/*the number can start with sign '+' or '-' */
        (*index)++;  
    }
    if(line[*index]<'0' || line[*index]>'9'){
            error_invalid_number(am_line_number,file_name_am);
            return 0;
    }
    (*index)++; 
    while(line[*index]!=' ' && line[*index]!='\t' && line[*index]!=',' && line[*index]!='\n'){
        if(line[*index]<'0' || line[*index]>'9'){
            error_invalid_number(am_line_number,file_name_am);
            return 0;
        }

        (*index)++;  

    }

return 1;

}




/*this function is skip on the lable defintion*/
void skip_lable(char *line,int *index){

    while(line[*index]!=':'){
        (*index)++;
    }
    (*index)++;/*skip also the ':'*/

}

/*this function skip whit charcter and a comma*/
void skip_space_and_comma(char *line,int *index){
    while(line[*index]=='\t' || line[*index]==' ' || line[*index]==','){
        (*index)++;
    }
}

/*this function coding the first memory word*/
void first_word_to_binary(char *source_paramter,char *opcode ,char* destination_paramter,char *first_word){

    /***coding the source paramter***/
    /*if we dont have source paramter*/
    if(!strcmp(source_paramter,"")){
        strcpy(first_word,"000");
    }
    /*if it is a lable*/
    else if(check_list(source_paramter,h_instruction_lable) || check_list(source_paramter,h_data_lable) || check_list(source_paramter,h_extern)){
        strcpy(first_word,"011");
    }
    /*if it is a register*/
    else if(check_if_register(source_paramter)){
        strcpy(first_word,"101");
    }
    else {/*if it is a number*/
        strcpy(first_word,"001");
    }
    
    /*coding the opcode*/
    strcat(first_word,get_binary_opcode(opcode));

    /**coding the destination paramter**/
    if(!strcmp(destination_paramter,"")){
        strcat(first_word,"000");
    }
    /*if it is a lable*/
    else if(check_list(destination_paramter,h_instruction_lable) || check_list(destination_paramter,h_data_lable) || check_list(destination_paramter,h_extern)){
        strcat(first_word,"011");
    }
    /*if it is a register*/
    else if(check_if_register(destination_paramter)){
        strcat(first_word,"101");
    }
    else {/*if it is a number*/
        strcat(first_word,"001");
    }

    /*coding the ARE*/
    strcat(first_word,"00");


}


/*this function is coding the second memory word that are paramters are both a registers*/
void two_register_word_to_binary(char *source_paramter,char* destination_paramter,char *second_word){
    strcpy(second_word,get_binary_register(source_paramter));
    strcat(second_word,get_binary_register(destination_paramter));
    strcat(second_word,"00");

}

/*this function is coding the source paramter*/
void source_word_to_binary(char* paramter,char *source_word,FILE *ext,int ob_line_number,int am_line_number,char *file_name_am){
    int num;
    if(check_list(paramter,h_instruction_lable)){/*if it is a lable*/
        num=get_lable_number(paramter,h_instruction_lable);
        int_to_binary_10_bits(num,source_word);
        strcat(source_word,"10");
        
    }
    else if(check_list(paramter,h_data_lable)){/*if it is a lable*/
        num=get_lable_number(paramter,h_data_lable);
        int_to_binary_10_bits(num,source_word);
        strcat(source_word,"10");

    }
    else if(check_list(paramter,h_extern)){/*if it is an extern lable*/
        strcpy(source_word,"000000000001");
        fprintf(ext,"%s %d\n",paramter,ob_line_number);/*printing to the .ext the lable name and the .ob line number he was used*/

    }
    else if(check_if_register(paramter)){/*if it is a register*/
        strcpy(source_word,get_binary_register(paramter));
        strcat(source_word,"0000000");
    }
    /*if it is a number*/
    else{
        num=atoi(paramter);
        if(num>MAX_SIZE_OF_NUMBER || num<MIN_SIZE_OF_NUMBER){/*if the number exceed the range he can be*/
            error_number_size(am_line_number,file_name_am);
        }
        int_to_binary_10_bits(num,source_word);
        strcat(source_word,"00");

    
    }

}

/*this function is coding the destination paramter*/
void destination_word_to_binary(char* paramter,char *destination_word,FILE *ext,int ob_line_number,int am_line_number,char *file_name_am){
    int num;
    if(check_list(paramter,h_instruction_lable)){/*if it is a lable*/
        num=get_lable_number(paramter,h_instruction_lable);
        int_to_binary_10_bits(num,destination_word);
        strcat(destination_word,"10");
        
    }
    else if(check_list(paramter,h_data_lable)){/*if it is a lable*/
        num=get_lable_number(paramter,h_data_lable);
        int_to_binary_10_bits(num,destination_word);
        strcat(destination_word,"10");

    }
    else if(check_list(paramter,h_extern)){/*if it is an extern lable*/
        strcpy(destination_word,"000000000001");
        fprintf(ext,"%s %d\n",paramter,ob_line_number);/*printing to the .ext the lable name and the .ob line number he was used*/

    }
    else if(check_if_register(paramter)){/*if it is a register*/
        strcpy(destination_word,"00000");
        strcat(destination_word,get_binary_register(paramter));
        strcat(destination_word,"00");
    }

    /*if it is a number*/
    else{
        num=atoi(paramter);
        if(num>MAX_SIZE_OF_NUMBER || num<MIN_SIZE_OF_NUMBER){/*if the number exceed the range he can be*/
            error_number_size(am_line_number,file_name_am);
        }
        int_to_binary_10_bits(num,destination_word);
        strcat(destination_word,"00");

    
    }



}

/*this function return the binary presantation of the register number*/
char* get_binary_register(char *paramter){
    int i;
    for(i=0;i<8;i++){
        if(!strcmp(registers[i].name,paramter)){
            return (registers[i].binary);
        }
    }
    return "ERROR";

}

/*getting the line numbee of the lable that he was defined in the .ob file*/
int get_lable_number(char *paramter, ptr h_ptr){
    while(h_ptr){
        if(!(strcmp(h_ptr->words,paramter)))
            return h_ptr->line_number;
        h_ptr=h_ptr->next;
    }
    return 0;

}

/* get the binary presntation of the opcode*/
char* get_binary_opcode(char *opcode){
    int i;
    for(i=0;i<16;i++){
        if(!strcmp(opcodes[i].name,opcode)){
            return opcodes[i].binary;
        }
    }
    return "ERROR";
}

/*this function check if the source paramter is acoording the the rules*/
int check_if_source_paramter_ok(char *word,char *paramter){
    int i=0;
    if(!strcmp(word,"lea")){/*if the instruction word is lea the source paramter could be only a lable*/
        if(check_list(paramter,h_instruction_lable) || check_list(paramter,h_data_lable) || check_list(paramter,h_extern)){
            return 1;
        }
        return 0;
    }

    /*if it is a register*/
    if(check_if_register(paramter)){
        return 1;
    }

    /*if it is a lable*/
    if(check_list(paramter,h_instruction_lable) || check_list(paramter,h_data_lable) || check_list(paramter,h_extern)){
        return 1;
    }

    /*if it is a number*/
    if(paramter[i]=='+' || paramter[i]=='-'){
        i++;
    }
    while(i<strlen(paramter)){
        if(paramter[i]<'0' || paramter[i]>'9'){
            return 0;
        }
        i++;
    }

    return 1;


}


/*this function check if the destination paramter is acoording the the rules*/
int check_if_destination_paramter_ok(char *word,char *paramter){
    int i=0;
    if(check_if_register(paramter)){/*if it is a register*/
        return 1;
    }

    if(check_list(paramter,h_instruction_lable) || check_list(paramter,h_data_lable) || check_list(paramter,h_extern)){/*if it is a lable*/
        return 1;
    }


    /*if the instruction word is cmp or prn the destination paramter could also be a number*/
    if(!strcmp(word,"cmp") || !strcmp(word,"prn")){ 
        if(paramter[i]=='+' || paramter[i]=='-'){
            i++;
        }
        while(i<strlen(paramter)){
            if(paramter[i]<'0' || paramter[i]>'9'){
                return 0;
            }
            i++; 
        }
        return 1;

    }

    return 0;

}




/*this function coding the integer number into a 10 bits of binary*/
void int_to_binary_10_bits(int lable_number, char *word){
    int i;
     for (i=0;i<10;i++) {
       word[9-i] = (lable_number & (1 << i)) ? '1' : '0';
    }
    word[10]='\0';
}

/*this function coding the integer number into a 12 bits of binary*/
void int_to_binary_12_bits(int number, char *word){
    int i;
     for (i=0;i<12;i++) {
       word[11-i] = (number & (1 << i)) ? '1' : '0';
    }
    word[12]='\0';

}

/*help function that caclulate the power*/
int power(int number, int power){
    int i,sum;
    sum=1;
    if(power==0)
        return 1;
    for(i=1;i<=power;i++){
        sum*=number;
    }
    return sum;
}

/*this function get a binary 12 bit word and convert it to base 64*/
void convert_to_base_64(char *word,char *base_64_word){
    int i,sum;
    sum=0;
    for(i=0;i<6;i++){
        sum+=(word[i]-48)*power(2,5-i);/*we have '0' or '1' so we decrease 48 to get the integers 0 or 1*/

    }
    base_64_word[0]=base_64_table[sum];
    sum=0;
    for(i=6;i<12;i++){
        sum+=(word[i]-48)*power(2,11-i);/*we have '0' or '1' so we decrease 48 to get the integers 0 or 1*/
    }
    base_64_word[1]=base_64_table[sum];
    base_64_word[2]='\0';

}

/*this function is write to .ob file*/
void write_to_ob(FILE *ob,char *word){
     char base_64_word[3];
     convert_to_base_64(word,base_64_word);
     fprintf(ob,"%s\n",base_64_word);
 }