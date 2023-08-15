/******************************************************************************************************************************
 in this file we are checking if the paramters that is in the file are good if not we will print an error messeges.
 if the paramteres are good we will coding to base 64 and write for the .ob .ent .ext as requested.
******************************************************************************************************************************/


#include "second_pass.h"





void second_pass(FILE *ob,FILE *ent,FILE *ext, char *file_name_am){
    char *line;
    char *word;
    char *param1;
    char *param2;
    char *first_word;
    char *source_word;
    char *destination_word;
    int index;
    int am_line_number;
    int ob_line_number=100;
    int num;
   


    /*memory allocation*/
    line = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
    word=(char*)malloc(7*sizeof(char));
    param1 = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
    param2 = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
    first_word=(char*)malloc(SIZE_OF_MEMORY_WORD*sizeof(char));
    source_word=(char*)malloc(SIZE_OF_MEMORY_WORD*sizeof(char));
    destination_word=(char*)malloc(SIZE_OF_MEMORY_WORD*sizeof(char));





    /*we start to interptat the instrucion sentances*/
    while(h_INSTRUCTION!=NULL){
        strcpy(line,h_INSTRUCTION->words);/*get the line*/
        am_line_number=h_INSTRUCTION->line_number;/*get the line number*/
        h_INSTRUCTION=h_INSTRUCTION->next;/*preapring the next line if exists*/
        index=0;
        if(strstr(line,":")!=NULL){/*if there is a lable definiton we skip it*/
            skip_lable(line,&index);
        }
        skip_space(line,&index);
        get_word(line,word,&index);/*get the instrucion word*/

        /*mov case*/
        if(!strcmp(word,"mov")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space_and_comma(line,&index);
            get_paramter(line,param2,&index);/*getting the second paramter*/
            if(!check_if_source_paramter_ok(word,param1)){ /*check if the source paramter is good*/
                error_invalid_source_paramter(am_line_number,file_name_am);
                continue;
            }
            if(!check_if_destination_paramter_ok(word,param2)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            if(check_if_register(param1) && check_if_register(param2)){/*if the two paramteres are registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                two_register_word_to_binary(param1,param2,destination_word);/*coding the second memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number+=2;

                
            }
            else{/*if the two paramters are not both registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                source_word_to_binary(param1,source_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
                write_to_ob(ob,source_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                destination_word_to_binary(param2,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the thired memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                

            }


        }

        /*cmp case*/
        else if(!strcmp(word,"cmp")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space_and_comma(line,&index);
            get_paramter(line,param2,&index);/*getting the second paramter*/
            if(!check_if_source_paramter_ok(word,param1)){ /*check if the source paramter is good*/
                error_invalid_source_paramter(am_line_number,file_name_am);
                continue;
            }
            if(!check_if_destination_paramter_ok(word,param2)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            if(check_if_register(param1) && check_if_register(param2)){/*if the two paramteres are registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                two_register_word_to_binary(param1,param2,destination_word);/*coding the second memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number+=2;

                
            }
            else{/*if the two paramters are not both registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                source_word_to_binary(param1,source_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
                write_to_ob(ob,source_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                destination_word_to_binary(param2,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the thired memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;

            }
        
        }

        /*add case*/
        else if(!strcmp(word,"add")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space_and_comma(line,&index);
            get_paramter(line,param2,&index);/*getting the second paramter*/
            if(!check_if_source_paramter_ok(word,param1)){ /*check if the source paramter is good*/
                error_invalid_source_paramter(am_line_number,file_name_am);
                continue;
            }
            if(!check_if_destination_paramter_ok(word,param2)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            if(check_if_register(param1) && check_if_register(param2)){/*if the two paramteres are registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                two_register_word_to_binary(param1,param2,destination_word);
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number+=2;

                
            }
            else{/*if the two paramters are not both registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                source_word_to_binary(param1,source_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
                write_to_ob(ob,source_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                destination_word_to_binary(param2,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the thired memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;

            }
        
        }

        /*sub case*/
        else if(!strcmp(word,"sub")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space_and_comma(line,&index);
            get_paramter(line,param2,&index);/*getting the second paramter*/
            if(!check_if_source_paramter_ok(word,param1)){ /*check if the source paramter is good*/
                error_invalid_source_paramter(am_line_number,file_name_am);
                continue;
            }
            if(!check_if_destination_paramter_ok(word,param2)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            if(check_if_register(param1) && check_if_register(param2)){/*if the two paramteres are registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                two_register_word_to_binary(param1,param2,destination_word);/*coding the second memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number+=2;

                
            }
            else{/*if the two paramters are not both registers*/
                first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                source_word_to_binary(param1,source_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
                write_to_ob(ob,source_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                destination_word_to_binary(param2,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the thired memory word to binary*/
                write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;

            }
        
        }
        
        

        /*not case*/
        else if(!strcmp(word,"not")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;

            
        
        }

        /*clr case*/
        else if(!strcmp(word,"clr")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }


        /*lea case*/
        else if(!strcmp(word,"lea")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the first paramter*/
            skip_space_and_comma(line,&index);
            get_paramter(line,param2,&index);/*getting the second paramter*/
            if(!check_if_source_paramter_ok(word,param1)){ /*check if the source paramter is good*/
                error_invalid_source_paramter(am_line_number,file_name_am);
                continue;
            }
            if(!check_if_destination_paramter_ok(word,param2)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            /*in this case there alwayas be a 3 memory word*/
            first_word_to_binary(param1,word,param2,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            source_word_to_binary(param1,source_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,source_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param2,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the thired memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }

        
        /*inc case*/
        else if(!strcmp(word,"inc")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;        
        
        }


        /*dec case*/
        else if(!strcmp(word,"dec")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }


        /*jmp case*/
        else if(!strcmp(word,"jmp")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }

        /*bne case*/
        else if(!strcmp(word,"bne")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }


        /*red case*/
        else if(!strcmp(word,"red")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }


        /*prn case*/
        else if(!strcmp(word,"prn")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }

        
        /*jsr case*/
        else if(!strcmp(word,"jsr")){
            skip_space(line,&index);
            get_paramter(line,param1,&index);/*getting the paramter*/
            strcpy(param2,"");
            if(!check_if_destination_paramter_ok(word,param1)){/*check if the destination paramter is good*/
                error_invalid_destination_paramter(am_line_number,file_name_am);
                continue;
            }
            
            first_word_to_binary(param2,word,param1,first_word);/*coding the first memory word to binary*/
            write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
            destination_word_to_binary(param1,destination_word,ext,ob_line_number,am_line_number,file_name_am);/*coding the second memory word to binary*/
            write_to_ob(ob,destination_word);/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }

        
        /*rts case*/
        else if(!strcmp(word,"rts")){
            write_to_ob(ob,"000111000000");/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        
        }

        /*stop case*/
        else if(!strcmp(word,"stop")){
            write_to_ob(ob,"000111100000");/*convert the binary word to base 64 and print it to .ob file*/
            ob_line_number++;
        }

        /*entry case*/
        else if(!strcmp(word,".entry")){
            skip_space(line,&index);
            get_word(line,param1,&index);/*getting the lable name*/
            if(check_list(param1,h_instruction_lable)){/*checking if he is in insturction lable table*/
                fprintf(ent,"%s %d\n",param1,get_lable_number(param1,h_instruction_lable));
                continue;
            }
            else if(check_list(param1,h_data_lable)){/*checking if he is in data lable table*/
                fprintf(ent,"%s %d\n",param1,get_lable_number(param1,h_data_lable));
                continue;
            }
            /*if there was sentance of entry some lable and the lable is not in the lables table*/
            error_lable_declared_but_not_defined(am_line_number,file_name_am);
        
        } 
        
        
    }


    /*after we finiished to interpret the instruction sentences we are now interpret the data sentances*/
    while(h_DATA!=NULL){
        strcpy(line,h_DATA->words);/*get the line*/
        am_line_number=h_DATA->line_number;/*get the line number*/
        h_DATA=h_DATA->next;/*preparing the next line if exists*/
        index=0;
        if(strstr(line,":")!=NULL){/*if there is a lable definition we skip it*/
            skip_lable(line,&index);
        }

        skip_space(line,&index);
        get_word(line,word,&index);/*get the data word*/


        /*data case*/
        if(!strcmp(word,".data")){
            skip_space(line,&index);
            while(line[index]!='\n'){/*we read all the numbers number after number*/
                get_paramter(line,param1,&index);/*getting the current paramter*/
                num=atoi(param1);
                if(num>MAX_SIZE_OF_NUMBER || num<MIN_SIZE_OF_NUMBER){/*check that the number is not exceeds maximum and minimum range*/
                    error_number_size(am_line_number,file_name_am);
                    line[index]='\n';/*if there was an error we will stop to interptat the rest of the line*/
                    continue;
                }
                int_to_binary_12_bits(num,first_word);/*coding the memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                skip_space_and_comma(line,&index);
            }
            

        }

        /*string case*/
        else if(!strcmp(word,".string")){
            skip_space(line,&index);
            get_string(line,param1,&index);/*getting the string without the qutation marks*/
            num=0;
            while(num<strlen(param1)){/*we read all the string char after char*/
                int_to_binary_12_bits(param1[num],first_word);/*coding the memory word to binary*/
                write_to_ob(ob,first_word);/*convert the binary word to base 64 and print it to .ob file*/
                ob_line_number++;
                num++;
            }

            write_to_ob(ob,"000000000000");/* writing also the null terminator '\0' */
            ob_line_number++;
        }

        
        

    }


    

    /*free allocate memory*/
    free(line);
    free(word);
    free(param1);
    free(param2);
    free(first_word);
    free(source_word);
    free(destination_word);

}