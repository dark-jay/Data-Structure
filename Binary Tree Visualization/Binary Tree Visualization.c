#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int TRUE=1, FALSE=0, i = 0, nodeCount=0;

typedef struct node {
    struct node *left;
    int data;
    struct node *right;
}*Btree;

Btree addTree(Btree, int);
void preorderTrav(Btree);
void inorderTrav(Btree);
void postorderTrav(Btree);
void displayTree(Btree);
void getPreorderTravValue(Btree, int[]);
int getLevel(Btree node, int data);
int getLevelUtil(Btree node,  int data, int level);

void printGivenLevel(Btree root, int level);
int height(Btree node);
void printLevelOrder(Btree root);
void getGivenLevel(Btree root, int level, int arrLevel[]);


int main()
{
    int x=0;
    Btree bst = NULL;
    bst = addTree(bst, 5);
    addTree(bst, 9);
    addTree(bst, 2);
    addTree(bst, 1);
    addTree(bst, 7);

    printf("Inorder: ");
    inorderTrav(bst);
    printf("\nPreorder: ");
    preorderTrav(bst);
    printf("\nPostorder: ");
    postorderTrav(bst);
    printf("\n\nDisplay: ");
    //displayTree(bst);

    printf("\n\nLevels are :\n");
    printLevelOrder(bst);

    printf("\n\n");

    displayTree(bst);
    printf("\n");

    //displayTree(bst);

    printf("\n\nEND\n");

    return 0;
}

Btree createNode(){
    Btree root;
    root = (Btree)malloc(sizeof(struct node));
    root->data = 0;
    root->left = NULL;
    root->right = NULL;
    return root;
}

Btree addTree(Btree root, int x){
    if(root == NULL){
        root = (Btree)malloc(sizeof(struct node));
        root->data = x;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else{
        if(x < root->data)
            root->left = addTree(root->left, x);
        else if(x > root->data)
            root->right = addTree(root->right, x);
    }
    return root;
}

void preorderTrav(Btree root){
    Btree temp = root;
    if(temp != NULL){
        printf("%d,", temp->data);
        preorderTrav(temp->left);
        preorderTrav(temp->right);
    }
}

void inorderTrav(Btree root){
    Btree temp = root;
    if(temp != NULL){
        inorderTrav(temp->left);
        printf("%d,", temp->data);
        inorderTrav(temp->right);
    }
}
void postorderTrav(Btree root){
    Btree temp = root;
    if(temp != NULL){
        postorderTrav(temp->left);
        postorderTrav(temp->right);
        printf("%d,", temp->data);
    }
}

void getPreorderTravValue(Btree root, int preOrderArr[]){
    Btree temp = root;
    if(temp != NULL){
        preOrderArr[i] = temp->data;
        i++;
        //printf("\n%d\n", temp->data);
        getPreorderTravValue(temp->left, preOrderArr);
        getPreorderTravValue(temp->right, preOrderArr);
    }
}
/*
         5
    """""" """"""
    |           |
    2           9
"""" """"   """" """"
|           |
1           7

*/
void displayTree(Btree root){
    int arrLevel[100], arrLevel_Temp[100]; // temp array is use to check if the node is NULL or not in advance before heading to the next level NUMBER
    int h = height(root);
    int level = h-1;
    //int const_h = h+1; // we gonna need one extra level info for calculation
    int arr_N[h], arr_SS[h], arr_DBSS[h], arr_Q[h], arr_DBCE[h];
    populateArray(arr_N, arr_SS, arr_DBSS, arr_Q, arr_DBCE, h);
    printArray(arr_N, arr_SS, arr_DBSS, arr_Q, arr_DBCE, h);

    printf("\n\n");

    int ss=0;
    int i, j, k, l, x, n, flag7or3 = 3, tempNodeCount;

    // traverse through total number of level
    for(l=0; l<h; l++){
        n = l+1;

        // NUMBER
        int spaceBeforeNode = arr_SS[h-1-l]; // h-1-l because list is upside down //arr_SS[h-l-1] + arr_Q[h-l-1];
        while(spaceBeforeNode > 0){
            printf(" ");
            spaceBeforeNode--;
        }

        getGivenLevel(root, l+1, arrLevel); // level counting starts from zero
        tempNodeCount = nodeCount;
        // add spaces between childs
        ss = arr_DBCE[h-1-l];
        // traverse every node on a single level and print
        for(x=0; x<tempNodeCount; x++){
            if(arrLevel[x] != -99) // -99 if node is not NULL
                printf("%d", arrLevel[x]);
            else
                printf(" ");

            // this portion is to handle last level quotes since it varies between 7 and 3
            // if last level
            if(l == h-1){
                if(flag7or3 == 3){ // or flag7or3 == ss
                    int c=7;
                    while(c){
                        printf(" ");
                        c--;
                    }
                    flag7or3 = 7;
                }
                else{
                    int c=3;
                    while(c){
                        printf(" ");
                        c--;
                    }
                    flag7or3 = 3;
                }
            }
            // if not last level
            else{
                while(ss){
                    printf(" ");
                    ss--;
                }
            }
        }


        // QUOTES
        printf("\n");
        // if last level
        int spaceBeforeQuotes;
        if(l == h-1)
            spaceBeforeQuotes = 0;
        else
            spaceBeforeQuotes = arr_SS[h-1-l-1]; // h-1-l-1 because we need one level below
        //printf(" j %d ", spaceBeforeQuotes); // delete when done
        while(spaceBeforeQuotes > 0){
            printf(" ");
            spaceBeforeQuotes--;
        }
        // if not at the last level, only then print quotes are edges
        if(l != h-1){
            int quoteTracker = 0;
            int spaceBetQuotes = 0;
            for(x=0; x<tempNodeCount; x++){
                while(quoteTracker < arr_Q[h-1-l-1]){
                    printf("\"");
                    quoteTracker++;
                }
                printf(" ");
                quoteTracker = 0;
                while(quoteTracker < arr_Q[h-1-l-1]){
                    printf("\"");
                    quoteTracker++;
                }
                // space between 2 child edges
                while(spaceBetQuotes < arr_DBCE[h-1-l-1]){
                    printf(" ");
                    spaceBetQuotes++;
                }
                quoteTracker = 0;
                spaceBetQuotes = 0;
            }
        }


        // PIPES
        // traverse every node on a single level to print |
        printf("\n");
        // if last level
        if(l == h-1)
            spaceBeforeQuotes = 0;
        else
            spaceBeforeQuotes = arr_SS[h-1-l-1]; // h-1-l-1 because we need one level below
        //printf(" j %d ", spaceBeforeQuotes); // delete when done
        while(spaceBeforeQuotes > 0){
            printf(" ");
            spaceBeforeQuotes--;
        }
        // if not at the last level, only then print pipes
        if(l != h-1){
            // this will modify the actual nodeCount for now in advance for next level
            nodeCount = 0;
            getGivenLevel(root, l+2, arrLevel_Temp); // get the next level node in advance
            int quoteTracker = 0;
            int spaceBetQuotes = 0;
            int flagFirstPipe = 1; // 0 means false, dont print
            int childCounterForNxtLvl=0, z;
            // traverse through every node on that level
            for(x=0; x<tempNodeCount; x++){
                // distacne of first part of quotes
                while(quoteTracker < arr_Q[h-1-l-1]){
                    if(flagFirstPipe == 1){
                        if(arrLevel_Temp[childCounterForNxtLvl++] != -99) // if node is not NULL
                            printf("|");
                        else
                            printf(" ");

                        flagFirstPipe = 0;
                    }
                    else
                        printf(" ");
                    quoteTracker++;
                }
                // distacne of single gap between quotes pairs
                printf(" ");
                quoteTracker = 0;
                // distacne of second part of quotes
                while(quoteTracker < arr_Q[h-1-l-1]-1){
                    printf(" ");
                    quoteTracker++;
                }

                if(arrLevel_Temp[childCounterForNxtLvl++] != -99) // -99 if node is not NULL
                    printf("|");
                else
                    printf(" ");

                // space between 2 child edges or quotes
                while(spaceBetQuotes < arr_DBCE[h-1-l-1]){
                    printf(" ");
                    spaceBetQuotes++;
                }
                quoteTracker = 0;
                spaceBetQuotes = 0;
                flagFirstPipe = 1;
            }
        }


        // new level
        printf("\n");
        nodeCount = 0;
    }
}
/*
11
7 3 7 3 7
                            SS      DBSS(util)     Q       DBCE         DBC
        i    n    Lvl    Starting    Difference   Quotes  Difference    Difference
             or          Space(SS)   Between SS   SS+2    Between 2     between 2
             h           DBSS(n-1)   DBSS(n-1)*2          child/edges   child
                         *2+SS(n-1)                       SS(n+1)+1     Q(n)*2 - 1
    """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
        0    1     5   |   0          0            4       3            7 or 3 alternatively
        1    2     4   |   4          4            6       11           11
        2    3     3   |   10         6            12      23           23
        3    4     2   |   22         12           24      47           47
        4    5     1   |   46         24           48      95           95
        5    6     0   |   94         48           96      191
*/
void printArray(int arr_N[], int arr_SS[], int arr_DBSS[], int arr_Q[], int arr_DBCE[], int h){
    int i;
    printf("\nh\tlvl\tSS\tDBSS\tQ\tDBC");
    printf("\n\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
    for(i=0; i<h; i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", arr_N[i], h-i-1, arr_SS[i], arr_DBSS[i], arr_Q[i], arr_DBCE[i]);
    }
}

void populateArray(int arr_N[], int arr_SS[], int arr_DBSS[], int arr_Q[], int arr_DBCE[], int h){
    int i=0;
    if(h==1){
        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBCE[i] = 3;
    }
    else if(h==2){
        arr_N[i+1] = 2;
        arr_SS[i+1] = 4;
        arr_DBSS[i+1] = 4;
        arr_Q[i+1] = 6;
        arr_DBCE[i+1] = 11;

        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBCE[i] = 3;
    }
    else if(h == 3){
        // i = 2
        arr_N[i+2] = 3;
        arr_SS[i+2] = 10;
        arr_DBSS[i+2] = 6;
        arr_Q[i+2] = 12;
        arr_DBCE[i+2] = 23;

        // i = 1
        arr_N[i+1] = 2;
        arr_SS[i+1] = 4;
        arr_DBSS[i+1] = 4;
        arr_Q[i+1] = 6;
        arr_DBCE[i+1] = 11;

        // i = 0
        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBCE[i] = 3;
    }
    else if(h > 3){
        // i = 2
        arr_N[i+1] = 3;
        arr_SS[i+1] = 10;
        arr_DBSS[i+1] = 6;
        arr_Q[i+1] = 12;
        arr_DBCE[i+1] = 23;

        // i = 1
        arr_N[i+1] = 2;
        arr_SS[i+1] = 4;
        arr_DBSS[i+1] = 4;
        arr_Q[i+1] = 6;
        arr_DBCE[i+1] = 11;

        // i = 0
        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBCE[i] = 3;

        // i > 2
        for(i=3; i<h; i++){ // note: i = h-1 or n-1
            int temp_arr_SS;
            arr_N[i] = i+1;
            arr_SS[i] = arr_DBSS[i-1]*2 + arr_SS[i-1];
            arr_DBSS[i] = arr_DBSS[i-1]*2;
            arr_Q[i] = arr_SS[i] + 2;
            temp_arr_SS = arr_DBSS[i]*2 + arr_SS[i]; // arr_ss[i+1]
            arr_DBCE[i] = temp_arr_SS + 1;
        }
    }
}

int getLevelUtil(Btree node,  int data, int level) {
    if (node == NULL)
        return 0;

    if (node -> data == data)
        return level;

    int downlevel = getLevelUtil(node -> left,
                                 data, level + 1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(node->right,
                             data, level + 1);
    return downlevel;
}

/* Returns level of given data value */
int getLevel(Btree node, int data) {
    return getLevelUtil(node, data, 1);
}

/* Function to print level
order traversal a tree*/
void printLevelOrder(Btree root) {
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++){
        printGivenLevel(root, i);
        printf("\tlevel=%d\n", i-1);
    }
}


/* Print nodes at a given level */
void printGivenLevel(Btree root, int level)
{
    int tempLevel;

    if (root == NULL){ // Base Case
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

void getGivenLevel(Btree root, int level, int arrLevel[])
{
    //int arrLevel[10], nodeCount=0;
    int tempLevel;

    if (root == NULL){ // Base Case
        arrLevel[nodeCount++] = -99;
        return;
    }
    if (level == 1) {
        //printf("%d ", root->data);
        arrLevel[nodeCount++] = root->data;
    }
    else if (level > 1)
    {
        getGivenLevel(root->left, level-1, arrLevel);
        getGivenLevel(root->right, level-1, arrLevel);
    }
}

/*
          5
    """""" """"""
    |           |
    2           9
"""" """"   """" """"
|           |
1           7
*/

/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(Btree node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight + 1);
        else return(rheight + 1);
    }
}
















//5 2 1 9 7
/*
5               // l=0, S=0
-----------------------------------
  5             // l=0, S=2
 /
2               // l=1, S=0
-----------------------------------
    5             // l=0, S=4
   /
  2               // l=1, S=2
 /
1                 // l=2, S=0
-----------------------------------
    5             // l=0, S=4
   / \
  2   9           // l=1, S=2   l=1, S=6
 /
1                 // l=2, S=0
-----------------------------------
    5             // l=0, S=4
   / \
  2   9           // l=1, S=2   l=1, S=6
 /   /
1   7             // l=2, S=0   l=2, S=4




      5             // l=0, S=4
     / \
    2   9           // l=1, S=2   l=1, S=6
   /   / \
  1   7  10
 / \ / \ / \
0   1   89  11
-----------------------------------
        5             // l=0, S=4
       / \
      /   \
     2     9           // l=1, S=2   l=1, S=6
    /     / \
   /     /   \
  1     7     10
 / \   / \    / \
0   1 8   9  11


           5             // l=0, S=4
          /\
         /  \
        /    \
       /      \
      /        \
     2          9           // l=1, S=2   l=1, S=6
    / \        / \
   /   \      /   \
  1     3    7     10
 / \        / \    / \
0   1      8   9  11




                                         5
                            """"""""""""" """"""""""""""
                            |                           |
                            2                           9
                     """"""" """""""             """"""" """""""
                     |             |             |             |
                     8             15            8             15
                 """" """"     """" """"     """" """"     """" """"
                 |       |     |       |     |       |     |       |
                 8      11     5      20     8      11     5      20






1. gap between 2 subtree of last level = 5




                                              5
                      """""""""""""""""""""""" """"""""""""""""""""""""                             // space = 22 ()
                      |                                               |
                      2                                               9                                  12
          """""""""""" """"""""""""                       """""""""""" """"""""""""                 // space = 10 (2*3)
          |                       |                       |                       |
          8                       15                      8                       15                     6
    """""" """"""           """""" """"""           """""" """"""           """""" """"""           // space = 4  (2*2)
    |           |           |           |           |           |           |           |
    8           11          5           20          8           11          5           20               4
"""" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"       // space = 0  (2*0)
|       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |
0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0


// gap between 2 child = 3 at last level

// Space =






                                                                                              5
                                              """""""""""""""""""""""""""""""""""""""""""""""" """"""""""""""""""""""""""""""""""""""""""""""""                                                 // space = 46
                                              |                                                                                               |
                                              2                                                                                               9
                      """""""""""""""""""""""" """"""""""""""""""""""""                                               """""""""""""""""""""""" """"""""""""""""""""""""                         // space = 22
                      |                                               |                                               |                                               |
                      8                                               15                                              8                                               15
          """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""             // space = 10
          |                       |                       |                       |                       |                       |                       |                       |
          8                       11                      5                       20                      8                       11                      5                       20
    """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""       // space = 4
    |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |
    0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0
"""" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   // space = 0
|       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |
0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0













                                                                                                                                                                                              5
                                                                                              """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""" """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
                                                                                              |                                                                                                                                                                                               |
                                                                                              2                                                                                                                                                                                               9
                                              """""""""""""""""""""""""""""""""""""""""""""""" """"""""""""""""""""""""""""""""""""""""""""""""                                                                                               """""""""""""""""""""""""""""""""""""""""""""""" """"""""""""""""""""""""""""""""""""""""""""""""
                                              |                                                                                               |                                                                                               |                                                                                               |
                                              8                                                                                               15                                                                                              8                                                                                               15
                      """""""""""""""""""""""" """"""""""""""""""""""""                                               """""""""""""""""""""""" """"""""""""""""""""""""                                               """""""""""""""""""""""" """"""""""""""""""""""""                                               """""""""""""""""""""""" """"""""""""""""""""""""
                      |                                               |                                               |                                               |                                               |                                               |                                               |                                               |
                      8                                               11                                              5                                               20                                              8                                               11                                              5                                               20
          """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""                       """""""""""" """"""""""""
          |                       |                       |                       |                       |                       |                       |                       |                       |                       |                       |                       |                       |                       |                       |                       |
          0                       0                       0                       0                       0                       0                       0                       0                       0                       0                       0                       0                       0                       0                       0                       0
    """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""           """""" """"""
    |           |           |           |           |           |           |           |           |           |   |       |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |           |
    0           0           0           0           0           0           0           0           0           0   0       0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0           0
"""" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"   """" """"
|       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |   |       |
0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0   0       0



                                   SS      DBSS(util)     Q       DBCE
                   n    Lvl    Starting    Difference   Quotes  Difference
                               Space(SS)   Between SS   SS+2    Between 2 child
                               DBSS(n-1)   DBSS(n-1)*2          SS(n+1)+1
                               *2+SS(n-1)
                   """"""""""""""""""""""""""""""""""""""""""""""""""""""""""
                   1     5   |   0          0            4       3
                   2     4   |   4          4            6       11
                   3     3   |   10         6            12      23
                   4     2   |   22         12           24      47
                   5     1   |   46         24           48      95
                   6     0   |   94         48           96      191


                   NOTE: n of 1,2,3 are exceptional case, formulas dont apply there




          5
    """""" """"""
    |           |
    2           9
"""" """"   """" """"
|           |
1           7


*/
