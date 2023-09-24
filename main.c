#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COUNT 10

#define WINDOWS

typedef struct db
{
    char name[47];
    char phone[16];
    char email[33];
} db;

typedef struct tree
{
    db data;
    struct tree *left;
    struct tree *right;
} tree;

// external file function
tree *readExternal(tree *root); // read external file.txt to restore data
void writeExternal(tree *root); // write external file.txt to backup data

// setting function
void changeWriteMode();   // change write external 3 modes (pre, in, post order)
void changeDisplayMode(); // change table in 3 modes (pre, in, post order)

// support function
void adjustString(char string[], int mode); // adjust string to produce better table
tree *find_tree2(tree *root, char name[]);  // find tree for validating record
tree *findminval(tree *root);               // find minimal value
void treeToArray(tree *root);               // convert tree to array
int heightCount(tree *root);                // count tree heights
void printTable(tree *root, int mode);      // print table
void printData(tree *root, int mode);       // print data in selected 3 modes (pre, in, post order)
void pauseScreen();                         // pause screen
void clearScreen();                         // clear screen
int findInArray(char string[], int mode);   // validate record in array
tree *visualizeTree(tree *root);            // make tree visualization
void printTree(tree *t, int space);         // print tree visualization

// main function
tree *create_tree(db dbTemp);                  // add new tree
tree *delete_node(tree *root, char name[]);    // delete tree
tree *askDataAdd(tree *root);                  // ask data to add a tree
tree *askDataDeleteFind(tree *root, int mode); // ask data to delete or find a tree
tree *find_tree(tree *root, db dbTemp);        // find tree for add new tree
tree *freee(tree *root);                       // free all data
void display(tree *root);                      // display all record

int count;           // for counting table number
char tempName[47];   // temp for name
char tempEmail[30];  // temp for email
char tempPhone[16];  // temp for phone
int writeMode = 1;   // write mode setting
int displayMode = 4; // table mode setting
db tempp[100];       // for temp array used in treetoarray
int x;               // for counting other function

int main(void)
{
    clearScreen();
    int option = 0;
    struct tree *root = NULL;

    if (root == NULL)
    {
        root = readExternal(root);
    }
backMenu:

    clearScreen();
    printf("Phonebook Record Data Using Binary Search Tree\n\n");
    display(root); // print table
    printf("\n1. Record Data\n");
    printf("2. Delete Record\n");
    printf("3. Search Record\n");
    printf("4. Visualize Tree\n");
    printf("7. Change Write Method\n");
    printf("8. Change Display Method\n");
    printf("9. Quit\n");

    printf("\nPlease select an option: ");
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        root = askDataAdd(root);
        break;

    case 2:
        if (root == NULL)
        {
            printf("\e[0;31m \nData still Empty. You need to insert first Tree!\x1b[0m");
            pauseScreen();
        }
        else
        {
            root = askDataDeleteFind(root, 1);
        }
        break;

    case 3:
        if (root == NULL)
        {
            printf("\e[0;31m \nData still Empty. You need to insert first Tree!\x1b[0m");
            pauseScreen();
        }
        else
        {
            askDataDeleteFind(root, 2);
        }
        break;

    case 4:
        visualizeTree(root);
        break;

    case 7:
        changeWriteMode();
        writeExternal(root);
        break;

    case 8:
        changeDisplayMode();
        writeExternal(root);
        break;

    case 9:
        printf("\nAhmad Mudhiya Ananta Rahman      - 2502010906");
        printf("\nAhmad Naufal Abdurrohman Alfadli - 2502014652");
        printf("\nMarchel Christhoper Wuisang      - 2501991611\n\n");
        freee(root);
        exit(0);

    default:
        printf("\e[0;31m\nInvalid Input!. Please Try Again!\x1b[0m");
        pauseScreen();
    }

    goto backMenu;
}

tree *visualizeTree(tree *root)
{
    clearScreen();
    printf("NOTES! \n");
    printf("Visualize Tree From Right to Left \e[0;31m(Not From Up to Bottom)\x1b[0m \n");
    printf("\nThe Format: \n\n");
    printf("----------------------------------------------------------------------\n");
    printf("\t   right child node \n\n");
    printf("root node\n\n");
    printf("\t   left child node \n\n");
    printf("----------------------------------------------------------------------\n");
    printf("\nTree Height    : %d\n", heightCount(root));
    printf("\nPhonebook Tree : \n");
    if (root == NULL)
    {
        printf("\nTree is Empty!");
    }
    else
    {
        printTree(root, 0);
    }
    printf("\n");
    pauseScreen();
}

void display(tree *root)
{
    if (root == NULL)
    {
        printf("Data Is Empty\n\n");
    }
    else
    {
        if (displayMode == 4)
        {
            printf("Display Method: Pre Order\n");
            printTable(root, 1);
            printf("\n\nDisplay Method: In Order\n");
            printTable(root, 2);
            printf("\n\nDisplay Method: Post Order\n");
            printTable(root, 3);
        }
        else
        {
            if (displayMode == 1)
            {
                printf("Display Method: Pre Order\n");
            }
            else if (displayMode == 2)
            {
                printf("Display Method: In Order\n");
            }
            else if (displayMode == 3)
            {
                printf("Display Method: Post Order\n");
            }
            printTable(root, displayMode);
        }
    }
}

void printTable(tree *root, int mode)
{
    count = 1;
    printf("_____________________________________________________________________________________________________\n");
    printf(" No |                     Name                     |    Phone      |             E-Mail             |\n");
    printf("_____________________________________________________________________________________________________\n");
    printData(root, mode);
    printf("_____________________________________________________________________________________________________\n");
}

void adjustString(char string[], int mode)
{
    int lenght = strlen(string);
    int target;

    if (mode == 1) // name
    {
        strcpy(tempName, string);
        target = 44;
    }
    else if (mode == 2) // email
    {
        strcpy(tempEmail, string);
        target = 30;
    }
    else // phone
    {
        strcpy(tempPhone, string);
        target = 13;
    }

    if (lenght != target)
    {
        for (int i = lenght; i < target; i++)
        {
            if (mode == 1) // name
            {
                strcat(tempName, " ");
            }
            else if (mode == 2) // email
            {
                strcat(tempEmail, " ");
            }
            else // phone
            {
                strcat(tempPhone, " ");
            }
        }
    }
}

void printData(tree *root, int mode)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        if (mode == 1) // pre order
        {
            adjustString(root->data.name, 1);
            adjustString(root->data.email, 2);
            adjustString(root->data.phone, 3);
            printf(" %.2d | %s | %s | %s |\n", count++, tempName, tempPhone, tempEmail);
            printData(root->left, mode);
            printData(root->right, mode);
        }
        else if (mode == 2) // in order
        {
            printData(root->left, mode);
            adjustString(root->data.name, 1);
            adjustString(root->data.email, 2);
            adjustString(root->data.phone, 3);
            printf(" %.2d | %s | %s | %s |\n", count++, tempName, tempPhone, tempEmail);
            printData(root->right, mode);
        }
        else // post order
        {
            printData(root->left, mode);
            printData(root->right, mode);
            adjustString(root->data.name, 1);
            adjustString(root->data.email, 2);
            adjustString(root->data.phone, 3);
            printf(" %.2d | %s | %s | %s |\n", count++, tempName, tempPhone, tempEmail);
        }
    }
}

tree *askDataDeleteFind(tree *root, int mode)
{
askDelete:
    clearScreen();
    if (mode == 1)
    {
        printf("Delete Record \n\n");
    }
    else
    {
        printf("Find Record \n\n");
    }
    display(root);
    int option;
    tree *found = NULL;

    printf("\n1. From Name\n");
    printf("2. From E-mail\n");
    printf("3. From Phone\n");
    if (mode == 1)
    {
        printf("4. ALL DATA\n");
    }
    printf("9. Exit\n\n");
    printf("Select Input     : ");
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
    name:
        printf("\nEnter -99 to Exit\n"); // exit
        printf("Enter the name   : ");   // insert name

        scanf("%[^\n]", &tempName);
        getchar();

        // exit checker
        if (strcmp(tempName, "-99") == 0)
        {
            main();
        }

        // validate record
        found = find_tree2(root, tempName);

        if (found == NULL) // data not found
        {
            printf("\e[0;31m\nData Not Found!\x1b[0m");
            pauseScreen();
            goto name;
        }
        else
        {
            if (mode == 1) // delete mode
            {
                root = delete_node(root, tempName); // delete record
            }
        }
        break;

    case 2:
    email:
        x = 0;
        printf("\nEnter -99 to Exit\n"); // exit
        printf("Enter the E-mail : ");   // insert email

        scanf("%[^\n]", &tempEmail);
        getchar();

        // exit checker
        if (strcmp(tempEmail, "-99") == 0)
        {
            main();
        }

        // validate record
        treeToArray(root);         // convert tree to array
        findInArray(tempEmail, 1); // find data in converted array

        if (strcmp(tempName, "-999") == 0) // data not found
        {
            printf("\e[0;31m\nData Not Found!\n\x1b[0m");
            pauseScreen();
            goto email;
        }
        else
        {
            if (mode == 1) // delete mode
            {
                root = delete_node(root, tempName); // delete
            }
            else // find mode
            {
                found = find_tree2(root, tempName); // find data to show
            }
        }

        break;

    case 3:
    phone:
        x = 0;
        printf("\nEnter -99 to Exit\n"); // insert name
        printf("Enter the Phone  : ");   // insert phone
        scanf("%[^\n]", &tempPhone);
        getchar();

        // exit checker
        if (strcmp(tempPhone, "-99") == 0)
        {
            main();
        }

        treeToArray(root);         // convert tree to array
        findInArray(tempPhone, 2); // validate record

        // check data
        if (strcmp(tempName, "-999") == 0)
        {
            printf("\e[0;31m\nData Not Found!\n\x1b[0m");
            pauseScreen();
            goto phone;
        }
        else
        {
            if (mode == 1) // delete mode
            {
                root = delete_node(root, tempName); // delete
            }
            else // find mode
            {
                found = find_tree2(root, tempName); // find record to show
            }
        }

        break;

    case 4:
        if (mode == 1)
        {
            root = freee(root);
        }
        else
        {
            printf("\e[0;31m\nWrong Input!\x1b[0m");
            pauseScreen();
            goto askDelete;
        }

        break;

    case 9:
        main();
    default:
        printf("\e[0;31m\nWrong Input!\n\x1b[0m");
        pauseScreen();
        goto askDelete;
    }

    if (mode == 1)
    {
        printf("\nRecord deleted successfully\n\n");
        writeExternal(root);
    }
    else if (mode == 2)
    {
        clearScreen();
        printf("Record Found!\n\n");
        printf("Name   : %s\n", found->data.name);
        printf("Phone  : %s\n", found->data.phone);
        printf("E-Mail : %s\n", found->data.email);
        pauseScreen();
    }
    return root;
}

int findInArray(char string[], int mode)
{
    for (int i = 0; i < x; i++)
    {
        if (mode == 1) // email
        {
            if (strcmp(string, tempp[i].email) == 0) // data found
            {
                strcpy(tempName, tempp[i].name);
                return 0;
            }
        }
        else // phone
        {
            if (strcmp(string, tempp[i].phone) == 0) // data found
            {
                strcpy(tempName, tempp[i].name);
                return 0;
            }
        }
    }

    // not found
    strcpy(tempName, "-999");
}

void treeToArray(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    db *newTree = NULL;
    if (writeMode == 1) // pre order
    {
        strcpy(tempp[x].name, root->data.name);
        strcpy(tempp[x].email, root->data.email);
        strcpy(tempp[x++].phone, root->data.phone);
        treeToArray(root->left);
        treeToArray(root->right);
    }
    else if (writeMode == 2) // in order
    {
        treeToArray(root->left);
        strcpy(tempp[x].name, root->data.name);
        strcpy(tempp[x].email, root->data.email);
        strcpy(tempp[x++].phone, root->data.phone);
        treeToArray(root->right);
    }
    else // post order
    {
        treeToArray(root->left);
        treeToArray(root->right);
        strcpy(tempp[x].name, root->data.name);
        strcpy(tempp[x].email, root->data.email);
        strcpy(tempp[x++].phone, root->data.phone);
    }
}

tree *askDataAdd(tree *root)
{
    clearScreen();

    tree *found = NULL; // found tree for validation
    db dbTemp;          // temporary data
    int len;            // phone lenght checker
    int ascii;          // numerical checker in phone
    int v1 = 0, v2 = 0; // email validation checker
    int mailCheck1 = 0; // @ checker in email
    int mailCheck2 = 0; // . checker in email

    printf("Add Phonebook Data \n");
    printf("Type -99 to cancel \n");

name:
    printf("\nEnter Name           : ");
    scanf("%[^\n]", &dbTemp.name);
    getchar();

    // back to menu checker
    if (strcmp(dbTemp.name, "-99") == 0)
    {
        main();
    }

    // name lenght checker
    len = strlen(dbTemp.name);
    if (len <= 0 || len > 44)
    {
        printf("\e[0;31mPlease Enter 1-44 Character!\n\x1b[0m");
        goto name;
    }

    // validate record
    if (root != NULL)
    {
        found = find_tree2(root, dbTemp.name);
        if (found != NULL)
        {
            printf("\e[0;31mData already found with\x1b[0m E-mail %s and phone %s\n", found->data.email, found->data.phone);
            goto name;
        }
    }

phone:
    printf("\nEnter Phone Number   : ");
    scanf("%[^\n]", &dbTemp.phone);
    getchar();

    // back to menu checker
    if (strcmp(dbTemp.phone, "-99") == 0)
    {
        main();
    }

    // phone digit checker
    len = strlen(dbTemp.phone);
    if (len < 10 || len > 13)
    {
        printf("\e[0;31mPlease Enter 10-13 Digit\n\x1b[0m");
        goto phone;
    }

    // numerical value checker
    for (int i = 0; i < len; i++)
    {
        ascii = dbTemp.phone[i];
        if (ascii < 48 || ascii > 57)
        {
            printf("\e[0;31mPlease Enter Valid Numerical Value (0-9) !\n\x1b[0m");
            goto phone;
        }
    }

    if (root != NULL)
    {
        // validate record
        treeToArray(root);            // convert tree to array
        findInArray(dbTemp.phone, 0); // find data in converted array

        if (strcmp(tempName, "-999") != 0) // data found
        {
            found = find_tree2(root, tempName); // find record to show
            printf("\e[0;31mData already found with\x1b[0m name %s and E-mail %s\n", found->data.name, found->data.email);
            goto phone;
        }
    }

    while (v1 != 1 && v2 != 1)
    {
        do
        {
        email:
            printf("\nEnter E-mail Address : ");
            scanf("%[^\n]", &dbTemp.email);
            getchar();

            // back to menu checker
            if (strcmp(dbTemp.email, "-99") == 0)
            {
                main();
            }

            len = strlen(dbTemp.email);
            if (len <= 0 || len > 30)
            {
                printf("\e[0;31mPlease Enter 1-30 Character!\n\x1b[0m");
            }

        } while (len <= 0 || len > 30);

        // email validity checker

        for (int i = 0; i < len; i++)
        {
            if (dbTemp.email[i] == '@') //@ checker
            {
                mailCheck1 = i;
            }
            if (dbTemp.email[i] == '.') //. checker
            {
                mailCheck2 = i;
            }
        }
        if (mailCheck1 > 3 && (mailCheck2 - mailCheck1) > 3) //@ and . should have minimum 3 char distance
        {
            v1 = 1;
            v2 = 1;
        }
        else
        {
            printf("\e[0;31mInvalid E-mail adrress!\n\x1b[0m");
        }
    }

    if (root != NULL)
    {
        // validate record
        findInArray(dbTemp.email, 1); // find data in converted array

        if (strcmp(tempName, "-999") != 0) // data found
        {
            found = find_tree2(root, tempName); // find record to show
            printf("\e[0;31mData already found with\x1b[0m name %s and phone %s\n", found->data.name, found->data.phone);
            goto email;
        }
    }

    // add tree
    root = find_tree(root, dbTemp);

    printf("\nPhonebook added successfully!\n\n");
    writeExternal(root); // save to external file

    return root;
}

tree *find_tree(tree *root, db dbTemp)
{
    if (root == NULL) // null. lets add new tree
    {

        root = create_tree(dbTemp);
    }
    else // find left or right
    {

        if (strcmp(dbTemp.name, root->data.name) < 0) // go to left tree
        {
            root->left = find_tree(root->left, dbTemp);
        }

        else if (strcmp(dbTemp.name, root->data.name) > 0) // go to right tree
        {

            root->right = find_tree(root->right, dbTemp);
        }
    }

    return root;
}

tree *find_tree2(tree *root, char name[])
{

    if (root == NULL) // empty. data not found
    {
        return NULL;
    }
    else
    {
        // for find tree
        if (strcmp(root->data.name, name) == 0) // data found. return it
        {
            return root;
        }

        // for add tree
        if (strcmp(name, root->data.name) < 0) // go to left tree
        {
            find_tree2(root->left, name);
        }

        else if (strcmp(name, root->data.name) > 0) // go to right tree
        {

            find_tree2(root->right, name);
        }
    }
}

struct tree *create_tree(db dbTemp)
{
    struct tree *newnode;
    newnode = (struct tree *)(malloc(sizeof(struct tree))); // memory allocation
    newnode->data = dbTemp;                                 // send db temp to data
    newnode->left = NULL;                                   // null as new left node
    newnode->right = NULL;                                  // null as new right node
    return newnode;
}
 
tree *delete_node(tree *root, char name[])
{

    if (root == NULL) // empty tree
    {
        return NULL;
    }

    if (strcmp(name, root->data.name) < 0) // go to left tree
    {

        root->left = delete_node(root->left, name);
    }

    else if (strcmp(name, root->data.name) > 0) // go to right tree
    {

        root->right = delete_node(root->right, name);
    }
    else // tree found. Let's delete it!
    {

        if (root->left == NULL && root->right == NULL) // tree has no child
        {
            root = NULL;
        }

        else if (root->left == NULL) // tree has only right child
        {

            root = root->right;
        }

        else if (root->right == NULL) // tree has only left child
        {
            root = root->left;
        }
        else // tree has two children
        {
            tree *tempNode = findminval(root->right);
            root->data = tempNode->data;
            root->right = delete_node(root->right, tempNode->data.name);
        }
    }

    return root;
}

tree *findminval(tree *root)
{
    if (root->left == NULL)
    {
        return root;
    }

    return findminval(root->left);
}

void changeWriteMode()
{
    clearScreen();
    printf("Change Write External Mode\n");
    printf("\n\n1. Pre Order Mode\n");
    printf("2. In Order Mode\n");
    printf("3. Post Order Mode\n\n");

    printf("Select Mode: ");
    scanf("%d", &writeMode);
    getchar();
    printf("\nWrite Mode Successfully Changed!\n");
}

void changeDisplayMode()
{
    clearScreen();
    printf("Change Display Mode\n");
    printf("\n\n1. Pre Order Mode\n");
    printf("2. In Order Mode\n");
    printf("3. Post Order Mode\n");
    printf("4. All Mode\n\n");

    printf("Select Mode: ");
    scanf("%d", &displayMode);
    getchar();
    printf("\nDisplay Mode Successfully Changed!\n");
}

tree *readExternal(tree *root)
{
    db dbTemp;

    FILE *data = fopen("file.txt", "r");
    fscanf(data, "%d\n", &writeMode);                                                               // write mode
    fscanf(data, "%d\n", &displayMode);                                                             // display mode
    while (fscanf(data, "%[^|]|%[^|]|%[^\n]\n", &dbTemp.name, &dbTemp.phone, &dbTemp.email) != EOF) // records data
    {
        root = find_tree(root, dbTemp);
    }
    return root;
}

void writeExternal(tree *root)
{
    printf("\nUpdating External Database. Please Wait!\n");
    FILE *data = fopen("file.txt", "w");

    x = 0;

    // save write and display setting to external file
    fprintf(data, "%d\n", writeMode);
    fprintf(data, "%d\n", displayMode);

    treeToArray(root); // convert tree to array

    // save records to external file
    for (int i = 0; i < x; i++)
    {
        fprintf(data, "%s|%s|%s\n", tempp[i].name, tempp[i].phone, tempp[i].email);
    }

    fclose(data);

    if (writeMode == 1)
    {
        printf("Data Successly Saved with Pre Order!\n\n");
    }
    else if (writeMode == 2)
    {
        printf("Data Successly Saved with In Order!\n\n");
    }
    else
    {
        printf("Data Successly Saved with Post Order!\n\n");
    }
    pauseScreen();
}

void pauseScreen()
{
    printf("\n\nPress Enter To Continue!");
    getchar();
}

void clearScreen(){
#ifdef WINDOWS // Windows
    {system("CLS");
}
#else // Linux / Mac
    {system("clear");
}
#endif
}

tree *freee(tree *root)
{
    tree *o, *l = root;
    for (; root; free(o))
    {
        for (; l->left; l = l->left)
            ;
        l->left = root->right;
        o = root;
        root = root->left;
    }
    return root;
}

int heightCount(tree *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        /* compute the depth of each subtree */
        int lDepth = heightCount(root->left);
        int rDepth = heightCount(root->right);

        /* use the larger one */
        if (lDepth > rDepth)
        {
            return (lDepth + 1);
        }
        else
        {
            return (rDepth + 1);
        }
    }
}

void printTree(tree *t, int space)
{
    if (t == NULL)
    {
        return;
    }

    space += COUNT;

    // Process right child first
    printTree(t->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
    {
        printf("  ");
    }

    printf("(%s)\n", t->data.name);

    printTree(t->left, space);
}
