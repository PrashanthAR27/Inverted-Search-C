
#include"inverted.h"

void print_list(slist *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    printf("\nValid Files:\n");

    while (head != NULL)
    {
        printf("%s -> ", head->filename);
        head = head->link;
    }

    printf("NULL\n");
}
int insert_at_last(slist **head, char *filename)
{
    slist *new = malloc(sizeof(slist));
    if(new == NULL){
        return FAILURE;
    }
    strcpy(new->filename, filename);
    new->link = NULL;
   if(*head == NULL){
    *head = new;
    return SUCCESS;
   }
   slist *temp = *head;
   while(temp->link != NULL){
    temp = temp->link;
   }
   temp->link = new;
   return SUCCESS;

}