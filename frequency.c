#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency.h"

int main(int argc, char *argv[])
{
    Node *root = newNode('\n');
    unsigned int depth = readText(root);
    boolean reversed = FALSE;
    char *buffer = (char *)malloc(depth * sizeof(char) + 1);
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "r") == 0)
            reversed = TRUE;
    }

    toPrint(root, buffer, reversed);
    free(buffer);
    freeMemory(root);
    return 0;
}

void freeMemory(Node *root)
{
    for (int i = 0; i < LETTERS; i++)
    {
        if (root->children[i] != NULL)
            freeMemory(root->children[i]);
    }
    free(root);
}

void toPrint(Node *root, char *buffer, boolean reversed)
{
    root->isEnd = FALSE;
    if (reversed == FALSE)
        print(root, root, buffer, buffer);
    else
    {
        printReversed(root, root, buffer, buffer);
    }
}

void printReversed(Node *currentNode, Node *root, char *buffer, char *orgBuffer)
{
    if (currentNode->letter != '\n')
    {
        *buffer = currentNode->letter;
        *(buffer + 1) = '\0';
    }

    if (currentNode->isEnd == TRUE)
    {
        printf("%s %ld\n", orgBuffer, currentNode->count);
        return;
    }
    else
    {
        for (int i = LETTERS; i >= 0; i--)
        {
            if (currentNode->children[i] != NULL)
            {
                if (currentNode->letter == '\n')
                {
                    printReversed(currentNode->children[i], root, buffer, orgBuffer);
                }
                else
                {
                    printReversed(currentNode->children[i], root, buffer + 1, orgBuffer);
                }
            }
        }
    }
}

void print(Node *currentNode, Node *root, char *buffer, char *orgBuffer)
{
    if (currentNode->letter != '\n')
    {
        *buffer = currentNode->letter;
        *(buffer + 1) = '\0';
    }

    if (currentNode->isEnd == TRUE)
    {
        printf("%s %ld\n", orgBuffer, currentNode->count);
        return;
    }
    else
    {
        for (int i = 0; i < LETTERS; i++)
        {
            if (currentNode->children[i] != NULL)
            {
                if (currentNode->letter == '\n')
                {
                    print(currentNode->children[i], root, buffer, orgBuffer);
                }
                else
                {
                    print(currentNode->children[i], root, buffer + 1, orgBuffer);
                }
            }
        }
    }
}

unsigned int readText(Node *root) // reads text to trie, and returns the trie's depth;
{
    Node *currentNode = root;
    char c = 0;
    unsigned int depth = 0, maxDepth = 0;
    while (c != EOF)
    {
        c = lowerCase(getchar());
        if (c == 0)
        {
            continue;
        }
        else if ((c == ' ') || (c == '\n') || (c == EOF))
        {
            currentNode->isEnd = TRUE;
            currentNode->count++;
            currentNode = root;
            if (depth > maxDepth)
            {
                maxDepth = depth;
            }
            depth = 0;
            continue;
        }

        if (currentNode->children[c - TOINDEX] == NULL)
        {
            currentNode->children[c - TOINDEX] = newNode(c);
        }
        currentNode = currentNode->children[c - TOINDEX];
        depth++;
    }
    return maxDepth;
}

Node *newNode(char letter) // Dinamically allocates memory for a new node, and returns pointer to it.
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->letter = letter;
    new->count = 0;
    new->isEnd = FALSE;
    for (int i = 0; i < LETTERS; i++)
    {
        new->children[i] = NULL;
    }
    return new;
}

char lowerCase(char c) // if char c is legal input, returns c as lower case. else returns NULL.
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        return c + DIFF;
    }
    else if ((c >= 'a') && (c <= 'z'))
    {
        return c;
    }
    else if ((c == ' ') || (c == '\n') || (c == EOF))
    {
        return c;
    }
    else
    {
        return 0;
    }
}
