#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static void CopyToNode(ListItem item, Node * pnode);

void InitializeList(List * plist) {
    plist->head = NULL;
    plist->end = NULL;
}

bool ListIsEmpty(const List * plist) {
    if (plist->head == NULL) {
        return true;
    } else {
        return false;
    }
}

bool ListIsFull(const List * plist) {
    Node * pt;
    bool full;

    pt = (Node *) malloc(sizeof(Node));
    if (pt == NULL) {
        full = true;
    } else {
        full = false;
    }

    free(pt);

    return full;
}

unsigned int ListItemCount(const List * plist) {
    unsigned int count = 0;
    Node * pnode = plist->head;

    while (pnode != NULL) {
        ++count;
        pnode = pnode->next;
    }

    return count;
}

bool AddListItem(ListItem item, List * plist) {
    Node * pnew;

    pnew = (Node *) calloc(1, sizeof(Node));
    if (pnew == NULL) {
        return false;
    }

    CopyToNode(item, pnew);
    if (plist->head == NULL) {
        plist->head = pnew;
        plist->end = pnew;
    } else {
        plist->end->next = pnew;
        plist->end = pnew;
    }

    return true;
}

void TraverseList(const List * plist, void (* pfun)(ListItem item)) {
    Node * pnode = plist->head;

    while (pnode != NULL) {
        (*pfun)(pnode->item);
        pnode = pnode->next;
    }
}

void EmptyTheList(List * plist) {
    Node * pnode = plist->head;
    Node * psave;

    while (pnode != NULL) {
        psave = pnode;
        free(pnode);
        pnode = psave->next;
    }
}

Node ** GetListItem(const ListItem * li, const List *plist) {
    Node ** pnode = &plist->head;
    while (pnode != NULL) {
        if (strcmp((*pnode)->item.kind, li->kind) == 0) {
            return pnode;
        }
        pnode = &(*pnode)->next;
    }

    return NULL;
}

bool RemoveListItem(const ListItem * item, List * plist) {
    Node ** pnode;
    Node * psave;
    if ((pnode = GetListItem(item, plist)) == NULL) {
        return false;
    } else {
        psave = *pnode;
        *pnode = (*pnode)->next;
        free(psave);
    }
}

static void CopyToNode(ListItem item, Node * pnode) {
    pnode->item = item;
}