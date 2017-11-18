#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

typedef struct pair {
    Trnode * parent;
    Trnode * child;
} Pair;

static Trnode * MakeNode(const TreeItem * pi);
static bool ToLeft(const TreeItem * i1, const TreeItem * i2);
static bool ToRight(const TreeItem * i1, const TreeItem * i2);
static void AddNode(Trnode * new_node, Trnode * root);
static void InOrder(const Trnode * root, void (* pfun)(TreeItem item));
static Pair SeekTreeItem(const TreeItem *pi, const Tree *ptree);
static Pair SeekListItem(const TreeItem *pi, const ListItem *li, const Tree *ptree);
static void DeleteNode(Trnode **ptr);
static void DeleteAllNodes(Trnode * root);


void InitializeTree(Tree * ptree) {
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree) {
    if (ptree->root == NULL) {
        return true;
    } else {
        return false;
    }
}

bool TreeIsFull(const Tree * ptree) {
    if (ptree->size == MAXITEMS) {
        return true;
    } else {
        return false;
    }
}

int TreeItemCount(const Tree * ptree) {
    return ptree->size;
}

bool AddTreeItem(const TreeItem * pi, const ListItem * li, Tree * ptree) {
    Trnode * new_node;
    Trnode * result;

    if (TreeIsFull(ptree)) {
        fprintf(stderr, "Tree is full\n");
        return false;
    }

    if ((result = SeekTreeItem(pi, ptree).child) != NULL) {
        AddListItem(*li, &result->item.petkinds);

        ptree->size++;
        return true;
    }

    new_node = MakeNode(pi);
    if (new_node == NULL) {
        fprintf(stderr, "Couldn't create node\n");
        return false;
    }
    AddListItem(*li, &new_node->item.petkinds);

    ptree->size++;

    if (ptree->root == NULL) {
        ptree->root = new_node;
    } else {
        AddNode(new_node, ptree->root);
    }

    return true;
}

bool InTree(const TreeItem * pi, const Tree *ptree) {
    return (SeekTreeItem(pi, ptree).child == NULL) ? false : true;
}

bool InTreeList(const TreeItem * pi, const ListItem * li, const Tree *ptree) {
    return (SeekListItem(pi, li, ptree).child == NULL) ? false : true;
}

bool DeleteTreeItem(const TreeItem * pi, const ListItem * li, Tree * ptree) {
    Pair look;

    look = SeekListItem(pi, li, ptree);
    if (look.child == NULL) {
        return false;
    }

    if (ListItemCount(&look.child->item.petkinds) > 1) {
        RemoveListItem(li, &look.child->item.petkinds);
        ptree->size--;
        return true;
    }

    if (look.parent == NULL) {
        DeleteNode(&ptree->root);
    } else if (look.parent->left == look.child) {
        DeleteNode(&look.parent->left);
    } else {
        DeleteNode(&look.parent->right);
    }
    ptree->size--;

    return true;
}

void TraverseTree(const Tree * ptree, void (* pfun)(TreeItem item)) {
    if (ptree != NULL) {
        InOrder(ptree->root, pfun);
    }
}

void DeleteAllInTree(Tree * ptree) {
    if (ptree->root != NULL) {
        DeleteAllNodes(ptree->root);
    }
    ptree->root = NULL;
    ptree->size = 0;
}

static void InOrder(const Trnode * root, void (* pfun)(TreeItem item)) {
    if (root != NULL) {
        InOrder(root->left, pfun);
        (*pfun)(root->item);
        InOrder(root->right, pfun);
    }
}

static void DeleteAllNodes(Trnode * root) {
    Trnode * pright;

    if (root != NULL) {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}

static void AddNode(Trnode * new_node, Trnode * root) {
    if (ToLeft(&new_node->item, &root->item)) {
        if (root->left == NULL) {
            root->left = new_node;
        } else {
            AddNode(new_node, root->left);
        }
    } else if (ToRight(&new_node->item, &root->item)) {
        if (root->right == NULL) {
            root->right = new_node;
        } else {
            AddNode(new_node, root->right);
        }
    } else {
        fprintf(stderr, "location error in AddNode()\n");
        exit(1);
    }
}

static bool ToLeft(const TreeItem * i1, const TreeItem * i2) {
    int comp1;

    if ((comp1 = strcmp(i1->petname, i2->petname)) < 0) {
        return true;
    } else {
        return false;
    }
}

static bool ToRight(const TreeItem * i1, const TreeItem * i2) {
    int comp1;

    if ((comp1 = strcmp(i1->petname, i2->petname)) > 0) {
        return true;
    } else {
        return false;
    }
}

static Trnode * MakeNode(const TreeItem * pi) {
    Trnode * new_node;

    new_node = (Trnode *) malloc(sizeof(Trnode));

    if (new_node != NULL) {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

static Pair SeekTreeItem(const TreeItem *pi, const Tree *ptree) {
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL) {
        return look;
    }

    while (look.child != NULL) {
        if (ToLeft(pi, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->left;
        } else if (ToRight(pi, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->right;
        } else {
            break;
        }
    }

    return look;
}

static Pair SeekListItem(const TreeItem *pi, const ListItem *li, const Tree *ptree) {
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL) {
        return look;
    }

    while (look.child != NULL) {
        if (ToLeft(pi, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->left;
        } else if (ToRight(pi, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->right;
        } else {
            if (GetListItem(li, &look.child->item.petkinds) == NULL) {
                look.child = NULL;
            }
            break;
        }
    }

    return look;
}

static void DeleteNode(Trnode **ptr) {
    Trnode * temp;

    if ((*ptr)->left == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    } else if ((*ptr)->right == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    } else {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right) {
            continue;
        }
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}