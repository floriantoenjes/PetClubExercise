#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

#define SLEN 50

char menu(void);
void addpet(Tree * pt);
void droppet(Tree * pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(TreeItem item);
void printListItem(ListItem item);
void uppercase(char * str);
char * s_gets(char * st, int n);

int main(void) {
    Tree pets;
    char choice;

    InitializeTree(&pets);
    while ((choice = menu()) != 'q') {
        switch (choice) {
            case 'a':
                addpet(&pets);
                break;

            case 'l':
                showpets(&pets);
                break;

            case 'f':
                findpet(&pets);
                break;

            case 'n':
                printf("%d pets in club\n", TreeItemCount(&pets));
                break;

            case 'd':
                droppet(&pets);
                break;

            default:
                puts("Switching error");
        }
    }
    DeleteAllInTree(&pets);
    puts("Bye.");

    return 0;
}

char menu(void) {
    int ch;

    puts("Nerfville Pet Club Membership Program");
    puts("Enter the letter corresponding to your choice:");
    puts("a) add a pet         l) show list of pets");
    puts("n) number of pets    f) find pets");
    puts("d) delete a pet      q) quit");
    while ((ch = getchar()) != EOF) {

        while (getchar() != '\n') {
            continue;
        }

        ch = tolower(ch);
        if (strchr("alfndq", ch) == NULL) {
            puts("Please enter an a, l, f, n, d, or q:");
        } else {
            break;
        }
    }

    if (ch == EOF) {
        ch = 'q';
    }

    return ch;
}

void addpet(Tree * pt) {
    TreeItem temp;
    ListItem li;
    InitializeList(&temp.petkinds);

    if (TreeIsFull(pt)) {
        puts("No room in the club!");
    } else {
        puts("Please enter name of pet:");
        s_gets(temp.petname, SLEN);
        puts("Please enter pet kind:");
        s_gets(li.kind, SLEN);
        uppercase(temp.petname);
        uppercase(li.kind);
        AddTreeItem(&temp, &li, pt);
    }
}

void showpets(const Tree * pt) {
    if (TreeIsEmpty(pt)) {
        puts("No entries!");
    } else {
        TraverseTree(pt, printitem);
    }
}

void printitem(TreeItem item) {
    printf("Pet: %-19s\n", item.petname);
    TraverseList(&item.petkinds, printListItem);
}

void printListItem(ListItem item) {
    printf("Kind: %-19s\n", item.kind);
}

void findpet(const Tree * pt) {
    TreeItem temp;
    ListItem li;

    InitializeList(&temp.petkinds);

    if (TreeIsEmpty(pt)) {
        puts("No entries!");
        return;
    }

    puts("Please enter name of the pet you wish to find:");
    s_gets(temp.petname, SLEN);
    puts("Please enter pet kind:");
    s_gets(li.kind, SLEN);
    uppercase(temp.petname);
    uppercase(li.kind);
    printf("%s the %s ", temp.petname, li.kind);
    if (InTreeList(&temp, &li, pt)) {
        printf("is a member.\n");
    } else {
        printf("is not a member .\n");
    }
}

void droppet(Tree * pt) {
    TreeItem temp;
    ListItem li;

    if (TreeIsEmpty(pt)) {
        puts("No entries!");
        return;
    }

    puts("Please enter name of pet you wish to delete:");
    s_gets(temp.petname, SLEN);
    puts("Please enter pet kind:");
    s_gets(li.kind, SLEN);
    uppercase(temp.petname);
    uppercase(li.kind);
    printf("%s the %s ", temp.petname, li.kind);
    if (DeleteTreeItem(&temp, &li, pt)) {
        printf("is dropped from the club.\n");
    } else {
        printf("is not a member\n");
    }
}

void uppercase(char * str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

char * s_gets(char * st, int n) {
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(ret_val, '\n');
        if (find) {
            *find = '\0';
        } else {
            while (getchar() != '\n') {
                continue;
            }
        }
    }
    return ret_val;
}