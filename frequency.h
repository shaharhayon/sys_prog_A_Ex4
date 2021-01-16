#define LETTERS 26
#define DIFF 'a' - 'A'
#define TOINDEX 'a'

struct Node;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;

typedef struct Node
{
    char letter;
    long unsigned int count;
    long unsigned int depth;
    boolean isEnd;
    struct Node *children[LETTERS];
} Node;

char lowerCase(char c);
Node *newNode(char letter);
unsigned int readText(Node *root);
void toPrint(Node *root, char *buffer, boolean reversed);
void print(Node *currentNode, Node *root, char *buffer, char *orgBuffer);
void printReversed(Node *currentNode, Node *root, char *buffer, char *orgBuffer);
void freeMemory(Node* root);
