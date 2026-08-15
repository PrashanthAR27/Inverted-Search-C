#include "inverted.h"

int search_word(mnode *arr[])
{
    char word[50];

    printf("Enter the word need to search : ");
    scanf("%49s", word);

    int index = tolower(word[0]) - 'a';

    if (index < 0 || index > 25)
    {
        index = 26;
    }

    mnode *mtemp = arr[index];

    while (mtemp != NULL)
    {

        if (strcmp(mtemp->word, word) == 0)
        {
            printf("The word \"%s\" is present in %d files\n",
                   word, mtemp->fileCount);

            snode *stemp = mtemp->slink;

            while (stemp != NULL)
            {
                printf("%s -> %d\n",
                       stemp->fileName,
                       stemp->wordCount);

                stemp = stemp->link;
            }

            return SUCCESS;
        }

        mtemp = mtemp->mlink;
    }

    printf("The word \"%s\" is not Found\n", word);

    return SUCCESS;
}