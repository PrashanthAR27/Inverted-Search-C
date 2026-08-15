#include "inverted.h"
mnode *arr[27] = {NULL};
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Warning : Input files not given\n");
        return FAILURE;
    }
    slist *head = NULL;
    validate_files(argc, argv, &head);
    print_list(head);
    int db = 0;
    int choice;
    do
    {
        printf("\n");
        printf("╔═════════════════════════════════════════════════════════════╗\n");
        printf("║                 INVERTED SEARCH PROJECT                     ║\n");
        printf("╠═════════════════════════════════════════════════════════════╣\n");
        printf("║ 1. Create Database                                          ║\n");
        printf("║ 2. Display Database                                         ║\n");
        printf("║ 3. Search Word                                              ║\n");
        printf("║ 4. Save Database                                            ║\n");
        printf("║ 5. Update Database                                          ║\n");
        printf("║ 6. Restore Database                                         ║\n");
        printf("║ 7. Exit                                                     ║\n");
        printf("╚═════════════════════════════════════════════════════════════╝\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            if (db == 0)
            {
                /* First-time Create */
                create_db(arr, head);
                db = 1;
            }
            else if (db == 1)
            {
                /* Already created normally */
                printf("Database already created.\n");
            }
            else if (db == 2)
            {
                if (update_database(arr, &head) == SUCCESS)
                {
                    db = 1;
                }
            }

            break;
        case 2:
            if (db == 0)
            {
                printf("ERROR : Database is not created.\n");
            }
            else
            {
                displayDB(arr);
            }

            break;
        case 3:

            if (db == 0)
            {
                printf("ERROR : Database is not created.\n");
            }
            else
            {
                search_word(arr);
            }
            break;
        case 4:
            if (db == 0)
            {
                printf("ERROR : Database is not created.\n");
            }
            else
            {
                if (saveDB(arr) == FAILURE)
                {
                    printf("ERROR : Save failed.\n");
                }
            }

            break;
        case 5:

            if (db == 0)
            {
                printf("ERROR : Database is not created.\n");
            }
            else
            {
                if (update_database(arr, &head) == FAILURE)
                {
                    printf("ERROR : Update failed.\n");
                }
            }

            break;
        case 6:

            if (db == 0)
            {
                if (restoreDB(arr, &head) == SUCCESS)
                {
                    db = 2;
                }
            }
            else
            {
                printf("ERROR : Database already created.\n");
            }

            break;
        case 7:
            printf("Exiting...\n");
            break;
        }
    } while (choice != 7);
}