/**********************************************************************************
  
 This is the main function that calls all the function in our program.
 in the main we are opening the files for write (for example the .ob file etc).
 we are calling the functions that are coding the file if is correct, 
 or will get an error messeges to the stdout if is not.

 Liron Cohen - 206350399
 Elad Harel - 319009643 

**********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "pre_processor.h"
#include "utills.h"
#include "symbols.h"
#include "first_pass.h"
#include "error.h"
#include "second_pass.h"




int main(int argc,char *argv[]){
    FILE *as,*am,*ent,*ext,*ob;
    char original_file_name[81]="";
    char file_name_as[81]="";
    char file_name_am[81]="";
    char file_name_ob[81]="";
    char file_name_ent[81]="";
    char file_name_ext[81]="";
    int i;
   
  
    if(argc==1){/*if the user dont entered any file name*/
        printf("cannot find file\n");
        exit(0);
    }
    for(i=1;i<argc;i++){
        *status=1;
        strcpy(original_file_name,argv[i]);
        strcpy(file_name_as,original_file_name);
        strcat(file_name_as,".as");
        as=open_file(as,file_name_as,"r");/*open file for reading*/

        strcpy(file_name_am,original_file_name);
        strcat(file_name_am,".am");
        am=open_file(am,file_name_am,"w+");/*open file for writing and reading*/

        pre_processor(as,am,file_name_as);/*the pre proccessor pass*/

        if(!(*status)){/*if there was any errors in the pre processor*/
            remove(file_name_am);/*remove the .am file*/
            fclose(as);/*close .as file*/
            continue;

        }

        strcpy(file_name_ob,original_file_name);
        strcat(file_name_ob,".ob");
        ob=open_file(ob,file_name_ob,"w");/*open file for writing */

        first_pass(am,ob,file_name_am);/*the first pass*/

        strcpy(file_name_ent,original_file_name);
        strcat(file_name_ent,".ent");
        ent=open_file(ent,file_name_ent,"w");/*open file for writing */
        strcpy(file_name_ext,original_file_name);
        strcat(file_name_ext,".ext");
        ext=open_file(ext,file_name_ext,"w");/*open file for writing */


        second_pass(ob,ent,ext,file_name_am);/*the second pass*/

        if(!(*status)){/* if there was any errors in the first or the second pass*/
            remove(file_name_ob);
            remove(file_name_ent);
            remove(file_name_ext);
            fclose(as);
            fclose(am);
            free_all_5_lists();/*free the allocate memory of the lists*/
            continue;

        }   

        if(get_file_size(ent)==2){/*if the file is empty we delete him*/
            remove(file_name_ent);
        }
        else{
            fclose(ent);
        }
        if(get_file_size(ext)==2){/*if the file is empty we delete him*/
            remove(file_name_ext);
        }
        else{
            fclose(ext);
        }
        
        fclose(as);
        fclose(am);
        fclose(ob);  
        free_all_5_lists();/*free the allocate memory of the lists*/

    


    }
    
return 0;

}
