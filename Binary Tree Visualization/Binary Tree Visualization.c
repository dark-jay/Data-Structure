#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

    //displayTree(bst);
    printf("\n");
    int arrLevel[100];
    getGivenLevel(bst, 3, arrLevel);
    for(x; x<nodeCount; x++){
        printf("%d ", arrLevel[x]);
    }

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
                                   SS      DBSS(util)     Q       DBC
              i    n    Lvl    Starting    Difference   Quotes  Difference
                   or          Space(SS)   Between SS   SS+2    Between 2 child
                   h           DBSS(n-1)   DBSS(n-1)*2          SS(n+1)+1
                               *2+SS(n-1)
            """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
              0    1     5   |   0          0            4       3
              1    2     4   |   4          4            6       11
              2    3     3   |   10         6            12      23
              3    4     2   |   22         12           24      47
              4    5     1   |   46         24           48      95
              5    6     0   |   94         48           96      191
*/
void displayTree(Btree root){
    int h = height(root);
    int level = h-1;
    int arr_N[h], arr_SS[h], arr_DBSS[h], arr_Q[h], arr_DBC[h];
    populateArray(arr_N, arr_SS, arr_DBSS, arr_Q, arr_DBC, h);
    printArray(arr_N, arr_SS, arr_DBSS, arr_Q, arr_DBC, h);

    printf("\n\n");

    int ss=0;
    int i, j, k, l;
    // traverse through total number of level
    for(l=0; l<h; l++){
        // number
        int spaceBeforeNode = arr_SS[h-l-1] + arr_Q[h-l-1];
        while(spaceBeforeNode >= 0){
            printf("j");
            spaceBeforeNode--;
        }
        int c, limit=pow(2,l);
        //for(c=1; c<=limit; c++){
            //printf("%d", );
            printGivenLevel(root, l+1); // since in the function level 0 = level 1
        //}

        // quotes

        // pipes

        // new level
        printf("\n");
    }
}

void printArray(int arr_N[], int arr_SS[], int arr_DBSS[], int arr_Q[], int arr_DBC[], int h){
    int i;
    printf("\nh\tlvl\tSS\tDBSS\tQ\tDBC");
    printf("\n\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
    for(i=0; i<h; i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", arr_N[i], h-i-1, arr_SS[i], arr_DBSS[i], arr_Q[i], arr_DBC[i]);
    }
}

void populateArray(int arr_N[], int arr_SS[], int arr_DBSS[], int arr_Q[], int arr_DBC[], int h){
    int i=0;
    if(h==1){
        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBC[i] = 3;
    }
    else if(h==2){
        arr_N[i+1] = 2;
        arr_SS[i+1] = 4;
        arr_DBSS[i+1] = 4;
        arr_Q[i+1] = 6;
        arr_DBC[i+1] = 11;

        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBC[i] = 3;
    }
    else if(h == 3){
        // i = 2
        arr_N[i+2] = 3;
        arr_SS[i+2] = 10;
        arr_DBSS[i+2] = 6;
        arr_Q[i+2] = 12;
        arr_DBC[i+2] = 23;

        // i = 1
        arr_N[i+1] = 2;
        arr_SS[i+1] = 4;
        arr_DBSS[i+1] = 4;
        arr_Q[i+1] = 6;
        arr_DBC[i+1] = 11;

        // i = 0
        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBC[i] = 3;
    }
    else if(h > 3){
        // i = 2
        arr_N[i+1] = 3;
        arr_SS[i+1] = 10;
        arr_DBSS[i+1] = 6;
        arr_Q[i+1] = 12;
        arr_DBC[i+1] = 23;

        // i = 1
        arr_N[i+1] = 2;
        arr_SS[i+1] = 4;
        arr_DBSS[i+1] = 4;
        arr_Q[i+1] = 6;
        arr_DBC[i+1] = 11;

        // i = 0
        arr_N[i] = 1;
        arr_SS[i] = 0;
        arr_DBSS[i] = 0;
        arr_Q[i] = 4;
        arr_DBC[i] = 3;

        // i > 2
        for(i=3; i<h; i++){ // note: i = h-1 or n-1
            int temp_arr_SS;
            arr_N[i] = i+1;
            arr_SS[i] = arr_DBSS[i-1]*2 + arr_SS[i-1];
            arr_DBSS[i] = arr_DBSS[i-1]*2;
            arr_Q[i] = arr_SS[i] + 2;
            temp_arr_SS = arr_DBSS[i]*2 + arr_SS[i]; // arr_ss[i+1]
            arr_DBC[i] = temp_arr_SS + 1;
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
        arrLevel[nodeCount++] = 0;
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



                                   SS      DBSS(util)     Q       DBC
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
