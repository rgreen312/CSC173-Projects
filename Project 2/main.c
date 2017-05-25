#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"

/*
***************************************************
LINKED LIST IMPLEMENTATION
***************************************************
*/
/**
 * Toplevel LinkedList structure.
 */
struct LinkedList {
    struct LinkedListNode *first;
    struct LinkedListNode *last;
};

/**
 * Structure for each element of a doubly-linked LinkedList.
 */
typedef struct LinkedListNode {
    char data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

/**
 * Allocate, initialize and return a new (empty) LinkedList.
 */
LinkedList *
LinkedList_new() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->first = list->last = NULL;
    return list;
}

static LinkedListNode *
LinkedListNode_new(char data) {
    LinkedListNode *node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
    abort();
    }
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}

/**
 * Free the memory used for the given LinkedList.
 * If boolean free_data_also is true, also free the data associated with
 * each element.
 */
void
LinkedList_free(LinkedList *list, bool free_data_also) {
    // Free the elements
    LinkedListNode *elt = list->first;
    while (elt != NULL) {
    LinkedListNode *next = elt->next;
    free(elt);
    elt = next;
    }
    // Free the list itself
    free(list);
}

/**
 * Return true if the given LinkedList is empty.
 */
bool
LinkedList_is_empty(const LinkedList *list) {
    return list->first == NULL;
}

/**
 * Add the given char value at the front of the given LinkedList.
 */
void
LinkedList_push(LinkedList *list, char data) {
    LinkedListNode *node = LinkedListNode_new(data);
    node->next = list->first;
    if (list->first != NULL) {
    list->first->prev = node;
    }
    list->first = node;
    if (list->last == NULL) {
    list->last = node;
    }
}

/**
 * Add the given chars to the stack in order
 */
void LinkedList_push_str(LinkedList* list, char* data) {
    for(int i = 0; data[i] != '\0'; i++) {
        LinkedList_push(list, data[i]);
    }
}

/**
 * Remove the given void* value from the given LinkedList if it is there.
 * Note that this does not free the data associated with the element.
 */
void
LinkedList_remove(LinkedList *list, char data) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
    if (node->data == data) {
        if (node == list->first) {
        list->first = node->next;
        }
        if (node == list->last) {
        list->last = node->prev;
        }
        if (node->prev != NULL) {
        node->prev->next = node->next;
        }
        if (node->next != NULL) {
        node->next->prev = node->prev;
        }
        free(node);
        return;
    }
    }
}

/**
 * Return the void* value at the given index in the given LinkedList, or
 * NULL if there is no such.
 * Note that this means you can't store NULL in a LinkedList. C'est la vie.
 */
char
LinkedList_element_at(LinkedList *list, int index) {
    int i = 0;
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
    if (i == index) {
        return node->data;
    }
    i += 1;
    }
    return '\0';
}

/**
 * Remove and return the first element from the given LinkedList.
 * Returns NULL if the list is empty.
 */
char
LinkedList_pop(LinkedList *list) {
    char data = LinkedList_element_at(list, 0);
    if (data != '\0') {
    LinkedList_remove(list, data); // Removes first occurrence
    }
    return data;
}

/**
 * Call the given function on each element of given LinkedList, passing the
 * void* value to the function.
 */
void
LinkedList_iterate(const LinkedList *list, void (*func)(char)) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
    func(node->data);
    }
}

/**
 * Return an LinkedListIterator for the given LinkedList.
 * Don't forget to free() this when you're done iterating.
 */
LinkedListIterator *
LinkedList_iterator(const LinkedList *list) {
    LinkedListIterator *iterator = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));
    *iterator = list->first;
    return iterator;
}

/**
 * Return true if the given LinkedListIterator will return another element
 * if LinkedListIterator_next() is called.
 */
bool
LinkedListIterator_has_next(const LinkedListIterator *iterator) {
    return iterator != NULL && *iterator != NULL;
}

/**
 * Return the next value from the given LinkedListIterator and increment it
 * to point to the next element.
 * Will return NULL if there is no such element.
 * This means that you can't store NULL in a LinkedList. C'est la vie.
 * It would be easy to allow it and signal `no such element' some other way...
 */
char
LinkedListIterator_next(LinkedListIterator *iterator) {
    if (iterator == NULL || *iterator == NULL) {
    return '\0';
    } else {
    char data = (*iterator)->data;
    *iterator = (*iterator)->next;
    return data;
    }
}

/**
 * Print the given LinkedList to stdout, assuming that the values are
 * all null-terminated strings.
 */
void
LinkedList_print_string_list(LinkedList *list) {
    printf("Top: ");
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
    printf("%c", node->data);
    if (node->next != NULL) {
        printf(" ");
    }
    }
    printf("\n");
}
/*
***************************************************
TREE IMPLEMENTATION
***************************************************
*/

//Define functions
typedef struct NODE *PNODE;
PNODE E();
PNODE TT();
PNODE T();
PNODE FT();
PNODE F();
PNODE N();
PNODE NT();
PNODE D();
char* evaluateNode(PNODE leftnode, PNODE centernode, PNODE rightnode);
void evaluate_tree(PNODE root);

/*
 * Creates the NODE structure that holds a string, terminal (boolean, always 0 or 1)
 * The node uses leftchild and rightsibling structure for the tree
*/
struct NODE {
    char* character;
    int terminal;
    PNODE leftChild;
    PNODE rightSibling;
};

/*
 * Create a new Node with a string as input and terminal value stating
 * 0 for non-terminal and 1 for terminal in the Node.
*/
PNODE createNewNode(char* c, int terminal) {
    PNODE newNode;
    newNode = (PNODE) malloc(sizeof(struct NODE));
    newNode->character = c;
    newNode->terminal = terminal;
    newNode->rightSibling = NULL;
    newNode->leftChild = NULL;
    return newNode;
}
/*
 * Adds a child to a passed in Parent Node. It creates a new Node based on a string pased in
 * with a terminal passed in as well.
*/
PNODE addChild(char* c, int terminal, PNODE parent) {
    PNODE child = createNewNode(c, terminal);
    parent->leftChild = child;

    return child;
}
/*
 * This takes in two existing Nodes and sets one as the parents of the other.
*/
PNODE addChildTree(PNODE child, PNODE parent) {
     parent->leftChild = child;

     return parent;
}

/*
 * This takes in two existing Nodes and makes on the sibling of the other.
*/
PNODE addSiblingTree(PNODE sibling, PNODE parent) {
    parent->rightSibling = sibling;

    return parent;
}

/*
 * Creates a new node and sets it to be a sibling of a passed in Node. Defines the string and
 * terminal value of the new Node created.
*/
PNODE addSibling(char* c, int terminal, PNODE leftSibling) {
    PNODE newRightSibling = createNewNode(c, terminal);
    leftSibling->rightSibling = newRightSibling;

    return newRightSibling;
}
/*
 * This prints the tree output to the terminal, takes in depth as 0 originally and
 * recursively prints the tree how it was asked to be printed.
*/
void printTree(PNODE root, int depth) {
    for (int i=0; i < depth; i++) {
        printf("   ");
    }

    char* toPrint;
    toPrint = root->character;

    printf("%s\n", toPrint);

    if ((root->leftChild) != NULL) {
        printTree((root->leftChild), depth+1);
    }

    if ((root->rightSibling) != NULL) {
        printTree((root->rightSibling), depth);
    }
}

char* terminal; //input
PNODE rootTree2; //actual RESULT


/*
***************************************************
STACK IMPLEMENTATION
***************************************************
*/

/*
 * Defines a new Node with data as a PNODE and a connection to the next node.
*/
typedef struct node{
    PNODE data;
    struct node* next;
}node;

/*
 * Defines nodeStack with head.
*/
typedef struct nodeStack{
    node* head;
}nodeStack;

/*
 * Declars the functions of Stack and evaluateNode and evaluateTree.
*/
node* node_new(PNODE data);
void node_free(node* kill);
nodeStack* nodeStack_new();
void nodeStack_push(nodeStack* stack, PNODE data);
PNODE nodeStack_pop(nodeStack* stack);
PNODE nodeStack_peek(nodeStack* stack);
char* evaluateNode(PNODE leftnode, PNODE centernode, PNODE rightnode);
void evaluate_tree(PNODE root);

/*
 * Creates a new node  for stack implementation
 * and mallocs the size of it. Sets the data passed in as well.
*/
node* node_new(PNODE data){
    node* out = (node*)(malloc(sizeof(node*)));
    out->data = data;
    return out;
}

/*
 * Free the stack nodes.
*/
void node_free(node* kill){
    free(kill->data);
    free(kill);
}

/*
 * Create a new Node stack.
*/
nodeStack* nodeStack_new(){
    nodeStack* out  = (nodeStack*)(malloc(sizeof(nodeStack*)));
    return out;
}

/*
 * Push unto the nodeStack with given data passed in.
*/
void nodeStack_push(nodeStack* stack, PNODE data) {
    node* new = node_new(data);
    new->next = stack->head;
    stack->head = new;
}

/*
 * Pop off of the nodeStack and return data;
*/
PNODE nodeStack_pop(nodeStack* stack) {
    PNODE out = stack->head->data;
    if(stack->head->next == NULL) {
        stack->head = NULL;
        return out;
    }
    stack->head = stack->head->next;
    return out;
}

/*
 * Peek at the top value of the stack and return value;
*/
PNODE nodeStack_peek(nodeStack* stack) {
    return stack->head->data;
}

/*
***************************************************
RECURSIVE DESCENT PARSER IMPLEMENTATION
***************************************************
*/

/*
 * This is the E function in the grammar given.
*/
PNODE E() {
    //*terminal is input character
    PNODE recT, recTT;

    //Call <T>
    recT = T();
    if (recT == NULL) { //T call failed test
        printf("%s\n", "Parse Failed on Call T in E");
        return NULL;
    }

    //Call <TT>
    recTT = TT();
    if (recTT == NULL) { //TT call failed test
        printf("%s\n", "Parse Failed on TT in E");
        return NULL;
    }

    //T and TT passed
    PNODE newNode = createNewNode("E", 0);
    addChildTree(recT, newNode);
    addSiblingTree(recTT, recT);
    return newNode;


}

/*
 * This is the TT function in the grammar given.
*/
PNODE TT() {
    PNODE recT, recTT;
    //Check terminal has a + or - as first character
    if (*terminal == '+' || *terminal == '-') {
    	char saved[2];
    	saved[1] = '\0';
        saved[0] = *terminal; //+ or -

        char* temp2 = malloc(2*sizeof(char*));
        strncpy(temp2, saved, 2);
        terminal++;

        //Needs to pass T
        recT = T();
        if (recT == NULL) {
            return NULL;
        }

        //Needs to pass TT
        recTT = TT();
        if (recTT == NULL) {
            return NULL;
        }

        //Made it the whole way
        //Add Nodes and create nodes to add to tree.

        PNODE newNode = createNewNode("t", 0);
        PNODE child = addChild(temp2, 1, newNode); //add +/-
        addSiblingTree(recT, child); //add recT
        addSiblingTree(recTT, recT); //add recTT
        return newNode;

    } else {
        //If terminal does not have a + or - as first character, return t going to empty.
        PNODE newNode = createNewNode("t", 0);
        return addChildTree(createNewNode("e", 1), newNode);
    }
}

/*
 * This is the T function in the grammar given.
*/
PNODE T() {
    PNODE recF, recFT;

    //Needs to pass F
    recF = F();
    if (recF == NULL) {
        return NULL;
    }

    //Needs to pass FT
    recFT = FT();
    if (recFT == NULL) {
        return NULL;
    }

    PNODE newNode = createNewNode("T", 0);
    addChildTree(recF, newNode);
    addSiblingTree(recFT, recF);

    return newNode;
}

/*
 * This is the FT function in the grammar given.
*/
PNODE FT() {
    PNODE recF, recFT;
    if (*terminal == '*' || *terminal == '/') {
    	char saved[2];
    	saved[1] = '\0';
        saved[0] = *terminal; //* or /
        char* temp2 = malloc(2*sizeof(char*));
        strncpy(temp2, saved, 2);
        terminal++;

        //Needs to pass F
        recF = F();
        if (recF == NULL) {
            return NULL;
        }

        //Needs to pass FT
        recFT = FT();
        if (recFT == NULL) {
            return NULL;
        }

        //Made it the whole way
        PNODE newNode = createNewNode("t", 0);
        PNODE child = addChild(temp2, 1, newNode); //add * or /
        addSiblingTree(recF, child); //add recF
        addSiblingTree(recFT, recF); //add recFT
        return newNode;

    } else {
        PNODE newNode = createNewNode("f", 0);
        return addChildTree(createNewNode("e", 1), newNode);
    }
}

/*
 * This is the F function in the grammar given.
*/
PNODE F() {
    if (*terminal == '(') {
        terminal++;
        PNODE recE = E();
        if (recE == NULL) {
            return NULL;
        }

        if (*terminal == ')') {
            terminal++;
            PNODE newNode = createNewNode("F", 0);
            PNODE child = addChild("(", 1, newNode);
            addSiblingTree(recE, child);
            addSibling(")", 1, recE);
            return newNode;
        }
    } else {
        PNODE recN = N();
        if (recN == NULL) {
            return NULL;
        }

        PNODE newNode = createNewNode("F", 0);
        addChildTree(recN, newNode);
        return newNode;
    }
    return NULL;
}

/*
 * This is the N function in the grammar given.
*/
PNODE N() {
    PNODE recD, recNT;

    //Needs to pass D
    recD = D();
    if (recD == NULL) {
        return NULL;
    }

    //Needs to pass NT
    recNT = NT();
    if (recNT == NULL) {
        return NULL;
    }

    PNODE newNode = createNewNode("N", 0);
    addChildTree(recD, newNode);
    addSiblingTree(recNT, recD);

    return newNode;
}

/*
 * This is the NT function in the grammar given.
*/
PNODE NT() {
    PNODE recN;

    recN = N();
    if (recN == NULL) {
        PNODE newNode = createNewNode("n", 0);
        addChild("e", 1, newNode);

        return newNode;

    } else {
        PNODE newNode = createNewNode("n", 0);
        addChildTree(recN, newNode);

        return newNode;
    }

}

/*
 * This is the F function in the grammar given.
*/
PNODE D() {
    if (isdigit(*terminal)) {
        PNODE newNode = createNewNode("D", 0);
        char temp[2];
        temp[1] = '\0';
        temp[0] = *terminal;
        char* temp2 = malloc(2*sizeof(char*));
        strncpy(temp2, temp, 2);
        addChild(temp2, 1, newNode);
        terminal++;
        return newNode;
    } else {
        return NULL;
    }
}

/*
***************************************************
TABLE DRIVEN PARSER IMPLEMENTATION
***************************************************
*/

typedef struct parseTable{
    char* heads;
    char** bodies;
}parseTable;

parseTable* parseTable_new(int productionNum){
    parseTable* out = (parseTable*)malloc(sizeof(parseTable*));
    out->bodies = malloc(productionNum * sizeof(char*));
    return out;
}

void parseTable_set_heads(parseTable* table, char* headList) {
    table->heads = headList;
}

void parseTable_set_body(parseTable* table, int productionNum, char* body) {
    table->bodies[productionNum] = body;
}

char* parseTable_get_body(parseTable* table, int productionNum) {
    return table->bodies[productionNum];
}

void parseTable_print(parseTable* table) {
    for(int i = 0; table->heads[i] != '\0'; i++) {
        printf("%d) <%c>->", i, table->heads[i]);
        printf("%s", table->bodies[i]);
        printf("\n");
    }
}
void tableDrivenParse(char* terminal) {
    //Create the parse table
    parseTable* arithmeticTable = parseTable_new(22);
    parseTable_set_heads(arithmeticTable, "EtttTfffFFNnnDDDDDDDDDD");
    /* The productions:
    0) <E>->Tt
    1) <t>->+Tt
    2) <t>->-Tt
    3) <t>->
    4) <T>->Ff
    5) <f>->*Ff
    6) <f>->/Ff
    7) <f>->
    8) <F>->N
    9) <F>->(E)
    10) <N>->Dn
    11) <n>->N
    12) <n>->
    13) <D>->0
    14) <D>->1
    15) <D>->2
    16) <D>->3
    17) <D>->4
    18) <D>->5
    19) <D>->6
    20) <D>->7
    21) <D>->8
    22) <D>->9
    */
    //The productions are stored backwards to facilitate pushing to the stack in the correct order
    parseTable_set_body(arithmeticTable, 0, "tT");
    parseTable_set_body(arithmeticTable, 1, "tT+");
    parseTable_set_body(arithmeticTable, 2, "tT-");
    parseTable_set_body(arithmeticTable, 3, "");
    parseTable_set_body(arithmeticTable, 4, "fF");
    parseTable_set_body(arithmeticTable, 5, "fF*");
    parseTable_set_body(arithmeticTable, 6, "fF/");
    parseTable_set_body(arithmeticTable, 7, "");
    parseTable_set_body(arithmeticTable, 8, "N");
    parseTable_set_body(arithmeticTable, 9, ")E(");
    parseTable_set_body(arithmeticTable, 10, "nD");
    parseTable_set_body(arithmeticTable, 11, "N");
    parseTable_set_body(arithmeticTable, 12, "");
    parseTable_set_body(arithmeticTable, 13, "0");
    parseTable_set_body(arithmeticTable, 14, "1");
    parseTable_set_body(arithmeticTable, 15, "2");
    parseTable_set_body(arithmeticTable, 16, "3");
    parseTable_set_body(arithmeticTable, 17, "4");
    parseTable_set_body(arithmeticTable, 18, "5");
    parseTable_set_body(arithmeticTable, 19, "6");
    parseTable_set_body(arithmeticTable, 20, "7");
    parseTable_set_body(arithmeticTable, 21, "8");
    parseTable_set_body(arithmeticTable, 22, "9");
    printf("\n-------- Printing Grammar: --------\n");
    parseTable_print(arithmeticTable);
    printf("\n");


    //Create the stack that stores production heads and terminals
    LinkedList* stack = LinkedList_new();
    LinkedList_push(stack, 'E');
    int parseCheck = 1; //speeds up the process of failing a parse (catches invalid chars)

    //Create the parse tree corresponding to the parse
    PNODE parseTree = createNewNode("E",0);
    LinkedList* nodeStack = LinkedList_new();

    //Create a stack to allow for top-down construction of the tree
    struct nodeStack* nstack = nodeStack_new();
    nodeStack_push(nstack, parseTree);//push the root of the initialized parse tree to the stack
    printf("\n-------- Print Steps of Table Driven Parse: --------\n");
    while (!LinkedList_is_empty(stack) && parseCheck == 1) {
        LinkedList_print_string_list(stack);//prints what's currently on the stack
        char current = LinkedList_pop(stack); //pops the top character of the stack
        PNODE nodeCurrent = nodeStack_pop(nstack); //pops the top node on the node stack
        //printf("current: %c\n", *terminal);

        //checks whether the top of the stack was a production head
        if (current == 'E') {
            LinkedList_push_str(stack, arithmeticTable->bodies[0]); //adds the body of the production to the parsing stack
            addChild("T",0, nodeCurrent); //adds children to the parse tree
            addSibling("t",0, nodeCurrent->leftChild); //adds children to the parse tree
            nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling); //stores the children in the node stack to correspond to the parser
            nodeStack_push(nstack, nodeCurrent->leftChild);
            //this process is more or less the same for all productions and production heads
        } else if (current == 't') {
            switch (*terminal) { //switch statement on lookahead necessary to eliminate ambiguity on the correct production
            case '+':
                LinkedList_push_str(stack, arithmeticTable->bodies[1]);
                addChild("+",1, nodeCurrent);
                addSibling("T",0, nodeCurrent->leftChild);
                addSibling("t", 0,nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '-':
                LinkedList_push_str(stack, arithmeticTable->bodies[2]);
                addChild("-",1, nodeCurrent);
                addSibling("T",0, nodeCurrent->leftChild);
                addSibling("t",0, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            default:
                LinkedList_push_str(stack, arithmeticTable->bodies[3]);
                addChild("e",1, nodeCurrent);
                break;
            }
        } else if (current == 'T') {
            LinkedList_push_str(stack, arithmeticTable->bodies[4]);
            addChild("F",0, nodeCurrent);
            addSibling("f", 0, nodeCurrent->leftChild);
            nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
            nodeStack_push(nstack, nodeCurrent->leftChild);
        } else if (current == 'f') {
            switch (*terminal) {
            case '*':
                LinkedList_push_str(stack, arithmeticTable->bodies[5]);
                addChild("*", 1, nodeCurrent);
                addSibling("F",0, nodeCurrent->leftChild);
                addSibling("f", 0, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '/':
                LinkedList_push_str(stack, arithmeticTable->bodies[6]);
                addChild("/",1, nodeCurrent);
                addSibling("F",0, nodeCurrent->leftChild);
                addSibling("f",0, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            default:
                LinkedList_push_str(stack, arithmeticTable->bodies[7]);
                addChild("e",1, nodeCurrent);
                break;
            }
        } else if (current == 'F') {
            if (*terminal == '(') {
                LinkedList_push_str(stack, arithmeticTable->bodies[9]);
                addChild("(",1, nodeCurrent);
                addSibling("E",0, nodeCurrent->leftChild);
                addSibling(")",1, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
                nodeStack_push(nstack, nodeCurrent->leftChild);
            } else {
                LinkedList_push_str(stack, arithmeticTable->bodies[8]);
                addChild("N",0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
            }
        } else if (current == 'N') {
            LinkedList_push_str(stack, arithmeticTable->bodies[10]);
            addChild("D", 0, nodeCurrent);
            addSibling("n",0, nodeCurrent->leftChild);
            nodeStack_push(nstack, nodeCurrent->leftChild->rightSibling);
            nodeStack_push(nstack, nodeCurrent->leftChild);

        } else if (current == 'n') {
            switch (*terminal) {
            case '0':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N",0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '1':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N",0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '2':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N",0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '3':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '4':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '5':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '6':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '7':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '8':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '9':
                LinkedList_push_str(stack, arithmeticTable->bodies[11]);
                addChild("N", 0, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            default:
                LinkedList_push_str(stack, arithmeticTable->bodies[12]);
                addChild("e", 1, nodeCurrent);
                break;
            }
        } else if (current == 'D') {
            switch (*terminal) {
            case '0':
                LinkedList_push_str(stack, arithmeticTable->bodies[13]);
                addChild("0",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '1':
                LinkedList_push_str(stack, arithmeticTable->bodies[14]);
                addChild("1",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '2':
                LinkedList_push_str(stack, arithmeticTable->bodies[15]);
                addChild("2",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '3':
                LinkedList_push_str(stack, arithmeticTable->bodies[16]);
                addChild("3",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '4':
                LinkedList_push_str(stack, arithmeticTable->bodies[17]);
                addChild("4",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '5':
                LinkedList_push_str(stack, arithmeticTable->bodies[18]);
                addChild("5", 1,nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '6':
                LinkedList_push_str(stack, arithmeticTable->bodies[19]);
                addChild("6", 1,nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '7':
                LinkedList_push_str(stack, arithmeticTable->bodies[20]);
                addChild("7",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '8':
                LinkedList_push_str(stack, arithmeticTable->bodies[21]);
                addChild("8",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            case '9':
                LinkedList_push_str(stack, arithmeticTable->bodies[22]);
                addChild("9",1, nodeCurrent);
                nodeStack_push(nstack, nodeCurrent->leftChild);
                break;
            default:
                parseCheck = 0;
                printf("parse failed on \"%c\"\n", *terminal);
                break;
            }
        } else {
            //checks if the character is a terminal accepted by the grammar
            if (current == *(terminal)) {
                printf("consumed: \"%c\"\n", *terminal);
                terminal++;
            } else {
                //if not, report that the parse failed and exit.
                printf("%s\n", "fail (grammar violation)");
                parseCheck = 0;
                break;
            }
        }
    }

    printf("%s\n", "Finished parsing");
    //must check if input was fully consumed
    if (parseCheck == 1 && (*terminal == '\0' || *terminal == '\n')) {
        printf("Parse successful\n");
        printf("\n-------- Print ParseTree: --------\n");
        printTree(parseTree, 0);
        printf("\n-------- Print Result: --------\n");
        evaluate_tree(parseTree);
        printf("%s\n", parseTree->character);

    }
    else if (*terminal != '\0') {
        printf("Parse failed (input was not fully consumed)\n");
    }
}

/*
***************************************************
EVALUATING PARSE TREE IMPLEMENTATION
***************************************************
*/
void evaluate_tree(PNODE root) {
    PNODE left = (PNODE)malloc(20*sizeof(PNODE));
    PNODE center = (PNODE)malloc(20*sizeof(PNODE));
    PNODE right = (PNODE)malloc(20*sizeof(PNODE));
    int terminalChildren = 0;
    int nonTerminalChildren = 0;


    //Get all of the children of the current node
    //Center only exists if left is not null, and right only exists if center is not null
    if (root==NULL)
        printf("%s\n", "something went wrong");;
    if (root->leftChild == NULL)
        left=NULL;
    else
        left = root->leftChild;
    if (left != NULL)
        center = left->rightSibling;
    else
        center=NULL;
    if (center != NULL)
        right = center->rightSibling;
    else
        right=NULL;

    //Recursively call evaluate node on the children of this node if they are not terminals
    if (left != NULL && left->terminal == 0) {
        evaluate_tree(left);
    }
    if (center != NULL && center->terminal == 0) {
        evaluate_tree(center);
    }
    if (right != NULL && right->terminal == 0) {
        evaluate_tree(right);
    }

    //check if any of the children are the empty string, and if so remove that child
    if (right != NULL && strcmp(right->character, "e")==0) {

        right=NULL;
        root->leftChild->rightSibling->rightSibling = NULL;
    }
    if (center != NULL && strcmp(center->character, "e")==0) {

        center=NULL;
        root->leftChild->rightSibling = NULL;

    }
    if (left != NULL && strcmp(left->character, "e")==0) {

        left=NULL;
        root->leftChild = NULL;

    }

    //get the number of terminal and non terminal children of the current node
    if (left != NULL && left->terminal == 1) {
        terminalChildren++;
    }
    else if (left != NULL && left->terminal == 0) {
        nonTerminalChildren++;
    }
    if (center != NULL && center->terminal == 1) {
        terminalChildren++;
    }
    else if (center != NULL && center->terminal == 0) {
        nonTerminalChildren++;
    }
    if (right != NULL && right->terminal == 1) {
        terminalChildren++;
    }
    else if (right != NULL && right->terminal == 0){ 
        nonTerminalChildren++;
    }

    //if there are no children, set the root to be the empty string, which will be removed later
    if (terminalChildren == 0 && nonTerminalChildren == 0) {
        root->character="e";
    }
    //if there are 3 terminal children, evaluate the node and set the root to have that value
    if (terminalChildren == 3) {
        root->character = evaluateNode(left, center, right);
        root->terminal=1; //whenever we set the value of a node to be a number, we have to set it to terminal
        root->leftChild=NULL;

    }
    //if there are 2 nonterminals, then we need to get the four values contained within the two children
    //(there can't be more than 4) and evaluate the three rightmost values (this accounts for order of operations)
    //then set the left node to its former left child
    if (nonTerminalChildren == 2) {
        PNODE leftMost = left->leftChild;
        PNODE leftCenter = left->leftChild->rightSibling;
        PNODE centerLeft = center->leftChild;
        PNODE rightMost = center->leftChild->rightSibling;

        center->character = evaluateNode(leftCenter, centerLeft, rightMost); //this is going to be a problem... need to store more than one character in a node
        left->character = leftMost->character;

        left->terminal = 1;
        center->terminal = 1;
        // free(leftMost);
        // free(leftCenter);
        // free(centerLeft);
        // free(rightMost);
    }
    //This can occur with a statement like x+y in order to fix this, we evaluate an expression of either the
    //the three leftmost values or the three rightmost, depending on which node is null
    if (terminalChildren == 1 && nonTerminalChildren == 1) {
        if (left->terminal == 1) {
            PNODE centerLeft = center->leftChild;
            PNODE centerRight = center->leftChild->rightSibling;
            root->character = evaluateNode(left, centerLeft, centerRight); //evaluate right most
            root->terminal=1;
            terminalChildren=0;
            nonTerminalChildren=0;
        }
        else if (center->terminal == 1) {
            PNODE leftMost = left->leftChild;
            PNODE leftCenter = leftMost->rightSibling;
            root->character = evaluateNode(leftMost, leftCenter, center); //evaluate left most
            root->terminal=1;
        }
        /*free(leftMost);
        free(leftCenter);
        free(centerLeft);
        free(centerRight);*/
    }
    //if there is only one non terminal child, we split the values it contains into the left and center nodes
    if (terminalChildren == 0 && nonTerminalChildren == 1) {
        PNODE child1, child2;
        if (left != NULL) {
            child1 = left->leftChild; 
            child2 = left->leftChild->rightSibling;

            left->character =child1->character; //move left child to left
            center=createNewNode(child2->character, child1->terminal); //move other left child to center
        }
        //repeat the same process for other two cases
        else if (center != NULL) {
            child1 = center->leftChild;
            child2 = center->leftChild->rightSibling;

            left=createNewNode(child1->character, child1->terminal); //might need to flip order
            root->leftChild=left;
            center->character=child2->character;
        }
        else {
            child1 = right->leftChild;
            child2 = right->leftChild->rightSibling;

            left=createNewNode(child1->character, child1->terminal);
            root->leftChild=left;
            center=createNewNode(child2->character, child1->terminal);
            root->leftChild->rightSibling=center;
            root->leftChild->rightSibling->rightSibling=NULL;
        }
        left->terminal = 1;
        center->terminal = 1;
    }
    //move the one terminal child up the tree, effectively bubbling it up
    else if (terminalChildren == 1) {
        root->character = left->character;
        root->terminal = 1;
        root->leftChild=NULL;
    }    
    //evaluate with the two values in the non terminal, and the value in the center node
    //this accounts for the x+x+x... case
    else if (terminalChildren==2 && nonTerminalChildren==1) {
        center->character=evaluateNode(center, right->leftChild, right->leftChild->rightSibling);
        center->terminal=1;
        center->rightSibling=NULL;
    }
    //if there are two terminals and its a number, concatenate the digits together
    else if (terminalChildren == 2 && (strcmp(root->character, "N")==0 /*|| strcmp(root->character, "t")==0)*/)) {
       if (left != NULL) {
        root->character = strcat(left->character, center->character);
        root->terminal=1;
       }
    }
}

/*
 * Evaluates a specific Node if it is deemed necessary by evaluate_tree.
 * This function takes the left center and right node and returns the result of the operation. 
*/
char* evaluateNode(PNODE leftnode, PNODE centernode, PNODE rightnode) {
    //printf("%s\n", "EVALUATING NODE");
    //get all the characters to be evaluated
    char * right = rightnode->character;
    char * center = centernode->character;
    char * left = leftnode->character;

    //execute the expression and return the result
    char* buffer = malloc(100*sizeof(char));
    if (strcmp(center, "+")==0) {
        snprintf(buffer, 100, "%f", (atof(left)+atof(right)));
        return buffer;
    }
    else if (strcmp(center, "-")==0) {
        snprintf(buffer, 100, "%f", (atof(left)-atof(right)));
        return buffer;
    }
    else if (strcmp(center, "*")==0) {
        snprintf(buffer, 100, "%f", (atof(left)*atof(right)));
        return buffer;
    }
    else if (strcmp(center, "/")==0) {
        snprintf(buffer, 100, "%f", (atof(left)/atof(right)));
        return buffer;
    }
    else if(strcmp(left, "(")==0) {
        return center;
    }
    return""; // if there somehow is no result, return empty string
}





/*
 * This is the main function of the program that takes in the arguements.
 * ARGUEMENTS:
 * There are always 3 arguements passed in by user:
 * 1: -t for table-driven parser and -r for recursively-driven parser
 * 2: -f for input from file and -c for input from command-line
 * 3: If you used -c for command line input, input an expression- '(3+3)'
 * 3: If you used -f for file input, type the name of the file- expressions.txt
 * Examples:
 * ./main -r -f expressions.txt
 * ./main -t -c 1+3+4+5
*/
int main(int argc, char *argv[])
{
    //Check and evaluate given arguements.
    int parserToUse=0;
    if (argc<4) {
        printf("Not enough arguments given, can't run program\n");
        return 0;
    }
    else if (argc>4) {
        printf("Too many arguments, can't run programs\n");
        return 0;
    }
    else if (strcmp(argv[1], "-t")==0) {
        parserToUse = 1; //table driven parser
    } else if (strcmp(argv[1], "-r")==0) {
        parserToUse = 0; //recursive parse
    } else {
        printf("There was a problem with arguement 1, use lowercase 't' or 'r' for this arguement.");
        return 0;
    }
    //For file input
    if (strcmp(argv[2], "-f")==0) {
        FILE *f;
        f = fopen(argv[3], "r");
        if (f == NULL) {
            printf("%s\n", "File not found");
        }
        else {
            char * linebuffer=(char*)malloc(sizeof(char)*200);
            int length;

            while (fgets(linebuffer, 200, f)) {
                int len = strlen(linebuffer);
                char line[len];
                strcpy(line, linebuffer);
                if (line[length-1] != '\0') {
                    line[length-1] = '\0';
                }
                terminal=(char*)malloc(len*sizeof(char));
                strcpy(terminal, line);
                printf("\n*************************************\nThe input given is: %s\n*************************************\n", terminal);

                if (parserToUse == 0) {
                    rootTree2 = E();
                    if (rootTree2 != NULL) {
                        printf("\n-------- Print ParseTree created: --------\n");
                        printTree(rootTree2, 0);
                        evaluate_tree(rootTree2);
                        printf("\n-------- Print Result: --------\n");
                        printf("%s\n", rootTree2->character);
                    }
                    else {
                        printf("Parse failed, no tree\n");
                    }
                }

                else {
                    tableDrivenParse(terminal);
                }
            }
            fclose(f);
        }
    }
    //For command line execution
    else if (strcmp(argv[2], "-c")==0) {
        printf("In command line execution\n");
        terminal = argv[3];
        printf("\n*************************************\nThe input given is: %s\n*************************************\n", terminal);


        if (parserToUse == 0) {
            rootTree2 = E();
            if (rootTree2 != NULL) {
                printf("\n--------Print ParseTree created: --------\n");
                printTree(rootTree2, 0);
                evaluate_tree(rootTree2);
                printf("\n-------- Print Result: --------\n");
                printf("%s\n", rootTree2->character);
            }
            else {
             printf("Parse failed, no tree\n");
            }
        }

        else {
            tableDrivenParse(terminal);
        }
    }
    return 0;
}
