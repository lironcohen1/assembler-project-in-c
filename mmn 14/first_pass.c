/*********************************************************************************************
 in this file we are building the lables table and the instruction and the data table
 and also we are checking if the lines that entered in the file are acorrding the rules
*********************************************************************************************/


#include "first_pass.h"



void first_pass(FILE *am,FILE *ob,char *file_name_am){
    char *line; 
    char *current_word;
    char *param1;
    char *param2;
    char *lable_name;
    long fileSize;
    int am_line_number=0;
    int index;
    int IC=100;
    int DC=0;
    


    fileSize=get_file_size(am);

    /*memory allocation*/
    line = (char*)malloc(fileSize*sizeof(char));
    current_word = (char *)malloc(fileSize*sizeof(char));
    lable_name = (char *)malloc(fileSize*sizeof(char));
    param1 = (char *)malloc(fileSize*sizeof(char));
    param2 = (char *)malloc(fileSize*sizeof(char));

    

    while(fgets(line,fileSize,am)!=NULL){ /*we reading line after line*/
        am_line_number++;
        index=0;
        
        if(strlen(line)>MAX_LINE_LENGTH){/* if the line exceeds 81 charcters*/
            error_line_length(am_line_number,file_name_am);
            continue;
        }
        
        skip_space(line,&index);/*skip on white charcters*/

        /*lable check*/
        
        if(strstr(line,":")!=NULL){/*if there is a defintion of lable*/
            get_lable(line,lable_name,&index);
            if(check_lable(lable_name,"",am_line_number,file_name_am)==0){
                continue;
            }
        }

        /*if we get here the lable name is good or the line do not start with lable command*/
        
        skip_space(line,&index);
        if(!early_end(line,index,am_line_number,file_name_am)){
            continue;
        }

        get_word(line,current_word,&index);/*getting the instruction or data word or .entry or .extern*/

        /*check that the lable name that we find in line 50 is not exist */
        if(check_list(lable_name,h_instruction_lable) || check_list(lable_name,h_data_lable)|| check_list(lable_name,h_extern)){
            error_lable_already_defined(am_line_number,file_name_am);
            continue;
        }
        
        /*if it is an instruction word and there was a lable defintion before so we add the lable to the instruction lable table*/
        if(opcode_check(current_word)){
            if(strlen(lable_name)>0){
                add_to_list(lable_name,IC,&h_instruction_lable);
                strcpy(lable_name,"");
            }
        }

        /*if it is an data word and there was a lable defintion before so we add the lable to the data lable table*/
        else if(strcmp(current_word,".string")==0 || strcmp(current_word,".data")==0){
            if(strlen(lable_name)>0){
                add_to_list(lable_name,DC,&h_data_lable);
                strcpy(lable_name,"");
            }
        }
        else{
            /*if the word is .entry or .extern we ignore the lable defintion(if it was)*/
            if(strcmp(current_word,".entry")!=0 && strcmp(current_word,".extern")!=0){
                error_unknown_sentence(am_line_number,file_name_am);/*if the word was not an instruction or data or .exteren or .entry word*/
                continue;
            }
        }


        /*if we get here so the current word is instruction or data or .entery or .extern word*/
        /*checking that there is a space after the current word*/
        if(line[index]!=' ' && line[index]!='\t' && line[index]!='\n'){
            error_missing_space(am_line_number,file_name_am);
            continue;
        }


        /*mov case*/
        if(!strcmp(current_word,"mov")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }

            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }

            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space(line,&index);    
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            if(!check_only_one_comma(line,&index,am_line_number,file_name_am)){/*checking there is only one comma between the two paramters*/
                continue;
            }
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            get_paramter(line,param2,&index);/*getting the second paramter*/

            /*if the two paramters are registers than the memory picture have a 2 memory word else there is 3*/
            if(check_if_register(param1) && check_if_register(param2)){
                IC+=2;
            }
            else{
                IC+=3;
            }
                 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;

        }

        /*cmp case*/
        else if(!strcmp(current_word,"cmp")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space(line,&index);    
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            if(!check_only_one_comma(line,&index,am_line_number,file_name_am)){/*checking there is only one comma between the two paramters*/
                continue;
            }
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            get_paramter(line,param2,&index);/*getting the second paramter*/

            /*if the two paramters are registers than the memory picture have a 2 memory word else there is 3*/
            if(check_if_register(param1) && check_if_register(param2)){
                IC+=2;
            }
            else{
                IC+=3;
            }
                 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;

        }

        /*add case*/
        else if(!strcmp(current_word,"add")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space(line,&index);    
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            if(!check_only_one_comma(line,&index,am_line_number,file_name_am)){/*checking there is only one comma between the two paramters*/
                continue;
            }
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            get_paramter(line,param2,&index);/*getting the second paramter*/

            /*if the two paramters are registers than the memory picture have a 2 memory word else there is 3*/
            if(check_if_register(param1) && check_if_register(param2)){
                IC+=2;
            }
            else{
                IC+=3;
            }
                 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*sub case*/
        else if(!strcmp(current_word,"sub")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space(line,&index);    
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            if(!check_only_one_comma(line,&index,am_line_number,file_name_am)){/*checking there is only one comma between the two paramters*/
                continue;
            }
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            get_paramter(line,param2,&index);/*getting the second paramter*/

            /*if the two paramters are registers than the memory picture have a 2 memory word else there is 3*/
            if(check_if_register(param1) && check_if_register(param2)){
                IC+=2;
            }
            else{
                IC+=3;
            }
                 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
        }

        /*not case*/
        else if(!strcmp(current_word,"not")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/   
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*clr case*/
        else if(!strcmp(current_word,"clr")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/ 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*lea case*/
        else if(!strcmp(current_word,"lea")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space(line,&index);    
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            if(!check_only_one_comma(line,&index,am_line_number,file_name_am)){/*checking there is only one comma between the two paramters*/
                continue;
            }
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){
                continue;
            }
            get_paramter(line,param2,&index); /*getting the second paramter*/
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            IC+=3;/*in this case there is alwayas a 3 memory word*/
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*inc case*/
        else if(!strcmp(current_word,"inc")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/   
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*dec case*/
        else if(!strcmp(current_word,"dec")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){
                error_unexpected_comma(am_line_number,file_name_am);/*if there was a comma before the first paramter*/
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/    
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*jmp case*/
        else if(!strcmp(current_word,"jmp")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/    
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*bne case*/
        else if(!strcmp(current_word,"bne")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/   
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*red case*/
        else if(!strcmp(current_word,"red")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/     
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*prn case*/
        else if(!strcmp(current_word,"prn")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/   
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*jsr case*/
        else if(!strcmp(current_word,"jsr")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }
            get_paramter(line,param1,&index);/*getting the paramter*/
            IC+=2;/*in this case there is alwayas a 2 memory word*/   
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments after the the last paramter*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*rts case*/
        else if(!strcmp(current_word,"rts")){
            IC+=1;/*in this case there is alwayas one memory word*/ 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;

            
        }

        /*stop case*/
        else if(!strcmp(current_word,"stop")){
            IC+=1;/*in this case there is alwayas one memory word*/ 
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;

            
        }

        /*data case*/
        else if(!strcmp(current_word,".data")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]==','){/*if there was a comma before the first paramter*/
                error_unexpected_comma(am_line_number,file_name_am);
                continue;
            }

            data_check(line,&index,am_line_number,file_name_am,&DC);/*checking that the numbers are good*/
            add_to_list(line,am_line_number,&h_DATA);/*insert the line to the data sentance table*/
            continue;

            
        }

        /*string case*/
        else if(!strcmp(current_word,".string")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            if(line[index]!='\"'){/*if the string dont start with a quotation marks*/
                error_string_quotes(am_line_number,file_name_am);
                continue;
            }
            index++;/*skipping the open -->  "  */
            while(line[index]!='\"' && line[index]!='\n'){
                DC++;
                index++;
            }
            DC++;/*DC +1 for the '\0' char*/
            if(line[index]!='\"'){/*if the string dont end with a quotation marks*/
                error_string_quotes(am_line_number,file_name_am);
                continue;
            }
            index++;/*skipping the close -->  "  */
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments*/
                error_too_many_paramters(am_line_number,file_name_am);
                continue;
            }
            add_to_list(line,am_line_number,&h_DATA);/*insert the line to the data sentance table*/
            continue;

            
        }

        /*entry case*/
        else if(!strcmp(current_word,".entry")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            get_word(line,current_word,&index);/*getting the lable name*/
            if(!check_lable(current_word,".entry",am_line_number,file_name_am)){/*checking that the name is good according to the rules*/
                continue;
            }
            
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            add_to_list(line,am_line_number,&h_INSTRUCTION);/*insert the line to the instruction sentance table*/
            continue;
            
        }

        /*extern case*/
        else if(!strcmp(current_word,".extern")){
            skip_space(line,&index);
            if(!early_end(line,index,am_line_number,file_name_am)){/*if paramters are missing */
                continue;
            }
            get_word(line,current_word,&index);/*getting the lable name*/
            if(!check_lable(current_word,".extern",am_line_number,file_name_am)){/*checking that the name is good according to the rules*/
                continue;
            }
            add_to_list(current_word,0,&h_extern);/*add the extern lable to the external lable table*/
            skip_space(line,&index);
            if(line[index]!='\n'){/*if there is more arguments*/
                error_too_many_paramters(am_line_number,file_name_am);
            }
            continue;
            
        }


    }/*end of reading from .am file*/

    if(IC+DC-1>MAX_MEMORY_SIZE){/*if the memory word exceed max memory size*/
        error_max_memory_size(file_name_am);
    }

    add_to_data_lable(IC,h_data_lable);/*adding to the DC line number the IC number*/
    fprintf(ob,"%d %d\n",IC-100,DC);/*printing to the ob file the number of instruction word and data word*/

    /*free the memory that was allocate*/
    free(line);
    free(current_word);
    free(lable_name);
    free(param1);
    free(param2);






}

  






