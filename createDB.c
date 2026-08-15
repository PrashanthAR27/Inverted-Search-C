#include "inverted.h"

snode *create_snode(slist *head)
{
    snode *new = malloc(sizeof(snode));

    if (new == NULL)
        return NULL;
    new->wordCount = 1;
    strcpy(new->fileName, head->filename);
    new->link = NULL;
    return new;
}

mnode *create_mnode(char word[], slist *head)
{
    mnode *new = malloc(sizeof(mnode));
    if (new == NULL)
    {
        return NULL;
    }
    new->fileCount = 1;
    new->mlink = NULL;
    strcpy(new->word, word);
    new->slink = create_snode(head);
    return new;
}

int create_db(mnode *arr[], slist *head)
{
    char word[50]; // buffer to store word temporarily

    while (head != NULL)
    {
        FILE *fp = fopen(head->filename, "r");
        if (fp == NULL)
        {
            return FAILURE;
        }

        while (fscanf(fp, "%s", word) != EOF)
        {

            int index = tolower(word[0]) - 'a';
            if (!(index >= 0 && index <= 25))
            {
                index = 26;
            }
            {
                if (arr[index] == NULL)
                {
                    mnode *new = create_mnode(word, head);

                    if (new == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    arr[index] = new;
                }
                else
                {
                    // need to traverse to find whether word is exist or not
                    mnode *mtemp = arr[index];
                    mnode *mprev = NULL;
                    while (mtemp != NULL && strcmp(mtemp->word, word) != 0)
                    {
                        mprev = mtemp;
                        mtemp = mtemp->mlink;
                    }
                    // temp reaches null word not exist
                    if (mtemp == NULL)
                    {
                        mnode *new = create_mnode(word, head);

                        mprev->mlink = new;
                    }
                    // temp not reaches null tehn word exist
                    else
                    {
                        snode *stemp = mtemp->slink;
                        snode *sprev = NULL;
                        while ((stemp != NULL) && (strcmp(head->filename, stemp->fileName) != 0))
                        {
                            sprev = stemp;
                            stemp = stemp->link;
                        }
                        // if temp reaches null and file not exist
                        if (stemp == NULL)
                        {
                            snode *new = create_snode(head);

                            if (new == NULL)
                            {
                                fclose(fp);
                                return FAILURE;
                            }

                            if (sprev == NULL)
                                mtemp->slink = new;
                            else
                                sprev->link = new;

                            mtemp->fileCount++;
                        }
                        // temp not reaches null then file exist
                        else
                        {
                            (stemp->wordCount)++;
                        }
                    }
                }
            }
        }
        fclose(fp);
        head = head->link;
    }

    printf("Create database successfully completed\n");
    return SUCCESS;
}