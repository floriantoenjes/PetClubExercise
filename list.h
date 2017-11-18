#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

#define KINDSIZE 20
struct petkind {
    char kind[KINDSIZE];
};

typedef struct petkind ListItem;

typedef struct node {
    ListItem item;
    struct node * next;
} Node;

typedef struct list {
    Node * head;
    Node * end;
} List;

void InitializeList(List * plist);

bool ListIsEmpty(const List * plist);

bool ListIsFull(const List * plist);

unsigned int ListItemCount(const List * plist);

bool AddListItem(ListItem item, List * plist);

void TraverseList(const List * plist, void (* pfun)(ListItem item));

void EmptyTheList(List * plist);

Node ** GetListItem(const ListItem * li, const List *plist);

bool RemoveListItem(const ListItem * item, List * plist);

#endif