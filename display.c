#include "inverted.h"

void displayDB(mnode *arr[])
{
    int headerPrinted = 0;
    int firstRow = 1;

    for (int i = 0; i < 27; i++)
    {
        if (arr[i] != NULL)
        {
            mnode *temp = arr[i];

            while (temp != NULL)
            {
                if (!headerPrinted)
                {
                    printf("\n");
                    printf("┌───────────────────────────────────────────────────────────────────────────────────────┐\n");
                    printf("│                               INVERTED SEARCH DATABASE                                │\n");
                    printf("├───────┬──────────────────────┬────────────┬────────────────────────────┬──────────────┤\n");
                    printf("│ %-5s │ %-20s │ %-10s │ %-26s │ %-12s │\n", "Index", "Word", "File Count", "File Name", "Word Count");
                    printf("├───────┼──────────────────────┼────────────┼────────────────────────────┼──────────────┤\n");

                    headerPrinted = 1;
                }
                /* Print separator before every row except the first */
                if (!firstRow)
                {
                    printf("├───────┼──────────────────────┼────────────┼────────────────────────────┼──────────────┤\n");
                }
                firstRow = 0;

                snode *subTemp = temp->slink;

                /* First file */
                printf("│ %-5d │ %-20s │ %-10d │ %-26s │ %-12d │\n",i,temp->word,temp->fileCount,
                       subTemp->fileName,subTemp->wordCount);
                subTemp = subTemp->link;
                /* Remaining files */
                while (subTemp != NULL)
                {
                    printf("│ %-5s │ %-20s │ %-10s │ %-26s │ %-12d │\n", "", "", "", subTemp->fileName, subTemp->wordCount);
                    subTemp = subTemp->link;
                }
                temp = temp->mlink;
            }
        }
    }

    if (headerPrinted)
    {
        printf("└───────────────────────────────────────────────────────────────────────────────────────┘\n");
    }
    else
    {
        printf("\n[INFO] Database is empty. Please create the database.\n");
    }
}