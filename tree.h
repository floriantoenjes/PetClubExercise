#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>
#include "list.h"

typedef struct item {
    char petname[20];
    List petkinds;
} TreeItem;

#define MAXITEMS 10

typedef struct trnode {
    TreeItem item;
    struct trnode * left;
    struct trnode * right;
} Trnode;

typedef struct tree {
    Trnode * root;
    int size;
} Tree;

void InitializeTree(Tree * ptree);

bool TreeIsEmpty(const Tree * ptree);

bool TreeIsFull(const Tree * ptree);

int TreeItemCount(const Tree * ptree);

bool AddTreeItem(const TreeItem * pi,const ListItem * li,  Tree * ptree);

bool InTree(const TreeItem * pi, const Tree * ptree);

bool InTreeList(const TreeItem * pi, const ListItem * li, const Tree *ptree);

bool DeleteTreeItem(const TreeItem * pi, const ListItem * li, Tree * ptree);

void TraverseTree(const Tree * ptree, void (* pfun)(TreeItem item1));

void DeleteAllInTree(Tree * ptree);

#endif

