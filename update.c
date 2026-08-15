#include "inverted.h"

int validate_single_file(char *filename, slist *head)
{
    int len = strlen(filename);
    if (len < 4)
    {
        printf("ERROR : %s is invalid file\n", filename);
        return FAILURE;
    }
    if (strcmp(filename + len - 4, ".txt") != 0)
    {
        printf("ERROR : %s is invalid file\n", filename);
        return FAILURE;
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("ERROR : %s does not exist\n", filename);
        return FAILURE;
    }
   

    char ch = fgetc(fp);
    

    if (ch == '#')
    {
        printf("ERROR : Backup file cannot be updated.\n");
        return FAILURE;
    }
    if (fgetc(fp) == EOF)
    {
        printf("ERROR : %s is empty\n", filename);
        fclose(fp);
        return FAILURE;
    }
    fclose(fp);
    slist *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            printf("ERROR : Duplicate file %s\n", filename);
            return FAILURE;
        }
        temp = temp->link;
    }

    return SUCCESS;
}

int update_database(mnode *arr[], slist **head)
{
    char filename[25];
    char choice = 'y';
    slist *last = *head;
    slist *first_new_node = NULL;

    // Find the last node
    if (last != NULL)
    {
        while (last->link != NULL)
        {
            last = last->link;
        }
    }

    do
    {
        printf("Enter filename : ");
        scanf("%24s", filename);

        // Validate file
        if (validate_single_file(filename, *head) == FAILURE)
        {
            printf("Do you want to enter another file? (y/n) : ");
            scanf(" %c", &choice);
            continue;
        }

        // Insert at last
        if (insert_at_last(head, filename) == FAILURE)
        {
            printf("ERROR : Unable to insert file\n");

            printf("Do you want to enter another file? (y/n) : ");
            scanf(" %c", &choice);
            continue;
        }
        // Save first newly inserted node
        if (first_new_node == NULL)
        {
            if (last == NULL)
                first_new_node = *head;
            else
                first_new_node = last->link;
        }

        // Move last pointer
        if (last == NULL)
            last = *head;
        else
            last = last->link;

        printf("File Added Successfully\n");

        printf("Do you want to add another file? (y/n) : ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    // Create database only for new files
    if (first_new_node != NULL)
    {
        if (create_db(arr, first_new_node) == FAILURE)
        {
            printf("ERROR : Failed to update database\n");
            return FAILURE;
        }
    }
    else
    {
        printf("No new files were added.\n");
        return FAILURE;
    }

    printf("Database Updated Successfully\n");

    return SUCCESS;
}