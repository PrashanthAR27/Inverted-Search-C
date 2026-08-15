#ifndef INVERTED_H
#define INVERTED_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int Status;
#define SUCCESS 0
#define FAILURE 1
#define TABLE_EMPTY 2


typedef struct mainnode
{
    char word[25];
    int fileCount;
    struct mainnode *mlink;
    struct subnode *slink;
}mnode;

extern mnode *arr[27];

typedef struct subnode
{
 int wordCount;
 char fileName[25];
 struct subnode *link;
}snode;

typedef struct fileNode
{
    char filename[25];
    struct fileNode *link;
}slist;

int insert_at_last(slist **head, char *filename);
int validate_files(int argc, char *argv[], slist **head);
void print_list(slist *head);
int create_db(mnode *arr[],slist *head);
snode *create_snode(slist *head);
mnode *create_mnode(char word[],slist *head);
void displayDB(mnode *arr[]);
int search_word(mnode *arr[]);
int saveDB(mnode *arr[]);
int restoreDB(mnode *arr[], slist **head);
int update_database(mnode *arr[], slist **head);
int validate_single_file(char *filename, slist *head);

#endif