#include "inverted.h"

int validate_files(int argc, char *argv[], slist **head)
{
    for (int i = 1; i < argc; i++)
    {
      //validate the valid extension
      int len = strlen(argv[i]);
      if(len < 4){
        printf("ERROR : %s is invalid file\n",argv[i]);
        continue;
      }
      if(strcmp((argv[i]+(len-4)), ".txt") != 0){
        printf("ERROR : %s is invalid file\n",argv[i]);
        continue;
      }


      //check file exists or not

      FILE *fptr = fopen(argv[i],"r");
      if(fptr == NULL){
        printf("ERROR : %s is NOT Exist\n",argv[i]);
        continue;
      }
      
      

    //check file is empty or not
     if(fgetc(fptr) == EOF){
        printf("ERROR : %s file is empty\n",argv[i]);
        fclose(fptr);
        continue;
     }
       fclose(fptr);
          
     //check file duplicate or not
     slist *temp = *head;
     while(temp != NULL){
        if(strcmp(temp->filename,argv[i]) == 0){
                printf("ERROR: Duplicate file %s is not allowed\n", argv[i]);
            break;
        }
        temp = temp->link;
     }
     if(temp != NULL)
     continue;

     //insert valid file to the list
     insert_at_last(head, argv[i]);
    }

    return SUCCESS;
}