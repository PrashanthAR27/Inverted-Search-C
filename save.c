#include "inverted.h"

int saveDB(mnode *arr[])
{
    char fileName[25];

    printf("Enter the filename : ");
    scanf("%s", fileName);

    // Validate file extension
    int len = strlen(fileName);

    if (len < 4)
    {
        printf("ERROR : %s is invalid file\n", fileName);
        return FAILURE;
    }

    if (strcmp(fileName + (len - 4), ".txt") != 0)
    {
        printf("ERROR : %s is invalid file\n", fileName);
        return FAILURE;
    }

    FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("ERROR : Unable to create file\n");
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        if (arr[i] == NULL)
        {
            continue;
        }

        mnode *mtemp = arr[i];

        while (mtemp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;", i, mtemp->word, mtemp->fileCount);

            snode *stemp = mtemp->slink;

            while (stemp != NULL)
            {
                fprintf(fp, "%s;%d;", stemp->fileName, stemp->wordCount);
                stemp = stemp->link;
            }

            fprintf(fp, "#\n");
            mtemp = mtemp->mlink;
        }
    }

    fclose(fp);
    printf("Database is successfully stored in %s file.\n", fileName);

    return SUCCESS;
}