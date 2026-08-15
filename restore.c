#include "inverted.h"

mnode *create_restore_mnode(char word[], int fileCount)
{
    mnode *new = malloc(sizeof(mnode));

    if (new == NULL)
    {
        return NULL;
    }

    strcpy(new->word, word);
    new->fileCount = fileCount;
    new->mlink = NULL;
    new->slink = NULL;

    return new;
}

snode *create_restore_snode(char filename[], int wordCount)
{
    snode *new = malloc(sizeof(snode));

    if (new == NULL)
    {
        return NULL;
    }

    strcpy(new->fileName, filename);
    new->wordCount = wordCount;
    new->link = NULL;

    return new;
}

int restoreDB(mnode *arr[], slist **head)
{
    char backUpFile[25];
    printf("Enter the filename : ");
    scanf("%s", backUpFile);

    // validate whether the file is actually backup file?
    int len = strlen(backUpFile);
    if (len < 4)
    {
        printf("ERROR : %s is invalid file\n", backUpFile);
        return FAILURE;
    }

    if (strcmp(backUpFile + (len - 4), ".txt") != 0)
    {
        printf("ERROR : %s is invalid file\n", backUpFile);
        return FAILURE;
    }

    FILE *fp = fopen(backUpFile, "r");
    if (fp == NULL)
    {
        printf("ERROR : File not exist\n");
        return FAILURE;
    }

    char first = fgetc(fp);

    // Move to last character of the file
    fseek(fp, -2, SEEK_END);
    char last = fgetc(fp);

    if (first != '#' || last != '#')
    {
        printf("Invalid backup file\n");
        fclose(fp);
        return FAILURE;
    }

    rewind(fp);

    for (int i = 0; i < 27; i++)
    {
        if (arr[i] != NULL)
        {
            printf("Database is not empty..!\nRestore is not possible...\n");
            fclose(fp);
            return FAILURE;
        }
    }

    char line[300];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *token = strtok(line, ";#");

        int index = atoi(token);

        token = strtok(NULL, ";#");
        char word[50];
        strcpy(word, token);

        token = strtok(NULL, ";#");
        int filecount = atoi(token);

        mnode *new = create_restore_mnode(word, filecount);
        if (new == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        snode *prev = NULL;

        for (int i = 0; i < filecount; i++)
        {
            token = strtok(NULL, ";#");
            char filename[25];
            strcpy(filename, token);
            slist *temp = *head;

            int found = 0;

            while (temp != NULL)
            {
                if (strcmp(temp->filename, filename) == 0)
                {
                    found = 1;
                    break;
                }

                temp = temp->link;
            }

            if (!found)
            {
                insert_at_last(head, filename);
            }
            token = strtok(NULL, ";#");
            int wordcount = atoi(token);

            snode *snew = create_restore_snode(filename, wordcount);
            if (snew == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            if (new->slink == NULL)
            {
                new->slink = snew;
                prev = snew;
            }
            else
            {
                prev->link = snew;
                prev = snew;
            }
        }

        if (arr[index] == NULL)
        {
            arr[index] = new;
        }
        else
        {
            mnode *temp = arr[index];

            while (temp->mlink != NULL)
            {
                temp = temp->mlink;
            }

            temp->mlink = new;
        }
    }

    fclose(fp);
    printf("Restore database successfull\n");
    return SUCCESS;
}