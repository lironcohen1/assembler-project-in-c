/*****************************************
 in this file we are spreading the mcros
*****************************************/


#include "pre_processor.h"



/* this function is the pre_processor stage when the assembler interprets the mcros*/
void pre_processor(FILE *as,FILE *am,char* file_name_as){
HashMap mcro;
char *line;
char* str_mcro;
char* mcro_name;
char *strcopy;
int flag=0;
long fileSize;
int line_number=0;

initializeHashMap(&mcro);

fileSize=get_file_size(as);

    

line = (char*)malloc(fileSize*sizeof(char));
strcopy = (char *)malloc(fileSize*sizeof(char));
str_mcro = (char*)malloc(fileSize*sizeof(char));
mcro_name = (char*)malloc(fileSize*sizeof(char));

while(fgets(line,fileSize,as)!=NULL){ /*we reading line after line*/
    if(feof(as)){/* we are adding the /n charcter to the last line in the file*/
            strcat(line,"\n");
    }
    line_number++;
    if(flag==0){/*we are not in a mcro definition*/
        get_line(line,strcopy,mcro_name,&flag,&mcro,am,line_number,file_name_as);
       
   }
    else if(flag==1){ /*we are in a mcro defintion*/
        is_mcro(line,strcopy,str_mcro,mcro_name,&flag,&mcro,line_number,file_name_as);
    }

 
 
    
}
/*free the aloocate memory*/
free(line);
free(strcopy);
free(mcro_name);
free(str_mcro);
freeHashMap(&mcro);




}



/**********************************************************************
this function is reading the next line from the file 
and decide if this is a start of a mcro definition or a regular line
**********************************************************************/
void get_line(char *line,char *strcopy,char *mcro_name,int *flag,HashMap* mcro,FILE *am,int line_number,char *file_name_as){
    int index=0;

    skip_space(line,&index);

    if(line[index]=='\n'){/*if its an empty line we do not copy it to .am file*/
        return;
    }

    get_word(line,strcopy,&index);

    if(strncmp(strcopy,";",1)==0){/*if its a comment line we do not copy it to .am file*/
        return;
    }

  
    if(strcmp(strcopy,"mcro")==0){/* if this is a line that we define a mcro*/
        *flag=1;/*update the flag that tell us that we are in a mcro definition*/
        skip_space(line,&index);
        get_word(line,strcopy,&index);
        strcpy(mcro_name,strcopy);/*we are saving the mcro name in - mcro_name*/

        if(getValue(mcro,mcro_name)!=NULL){/*if the new mcro name is alrady exist in the mcro table*/
            mcro_name_error(line_number,file_name_as);
        }
        if(!((mcro_name[0]>='a' && mcro_name[0]<='z') || (mcro_name[0]>='A' && mcro_name[0]<='Z')))/*if the mcro name dont start in a letter its not legal*/
            mcro_name_error(line_number,file_name_as);

        if(opcode_check(mcro_name)){/*if the mcro name is the same has the opcode name*/
            mcro_name_error(line_number,file_name_as);
        }

        skip_space(line,&index);
        if(!(line[index]=='\n'))/*if there is extra text after start definition of mcro*/
            mcro_error(line_number,file_name_as);

        return;
    }
    
    

    if(getValue(mcro, strcopy)!=NULL){/*if this is a mcro name we will copy to .am file the body of the mcro name*/
            fprintf(am,"%s",getValue(mcro, strcopy));
            skip_space(line,&index);
            if(line[index]!='\n'){/* if after the mcro name there is more arguments we will copy it to*/
                fprintf(am,"%s",line+index);
            }
            
            
    }
    else
        fprintf(am,"%s",line);/*if its not a mcro defintion we copy the all line as is*/
    


    

}


/* if we are in a mcro definiton this function is resopnsable to enter the mcro name and body of the mcro to the hasmap*/
void is_mcro(char *line,char *strcopy,char *str_mcro,char *mcro_name,int *flag,HashMap* mcro,int line_number,char *file_name_as){

    int index=0;
    
    skip_space(line,&index);
      if(line[index]=='\n'){/*if its an empty line we do not copy it to .am file*/
        return;
    }
    get_word(line,strcopy,&index);
    if(strncmp(strcopy,";",1)==0){/*if its a comment line we do not copy it to .am file*/
        return;
    }
    if(strcmp(strcopy,"endmcro")==0){/*if this is the end of a mcro definition*/
        *flag=0;/*update the flag that we are finish the mcro definiton*/

        insertElement(mcro, mcro_name, str_mcro);/*insert to the hash*/
        
        skip_space(line,&index);
        
        if(!(line[index]=='\n')){/*if there is extra text after  end  definition of mcro*/
            mcro_error(line_number,file_name_as);
        
        }
        strcpy(str_mcro,"");
        strcpy(mcro_name,"");

        return;
    }


    else{
      
        strcat(str_mcro,line);/*if we still in a mcro definition we copy the line as is to the mcro body*/
        
    }

}








