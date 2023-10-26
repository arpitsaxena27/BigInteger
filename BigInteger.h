#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} node;

struct BigInteger
{
    node *head;
    int length;
};

struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
void insertend(node **, int);
void display(struct BigInteger a);
int count(struct BigInteger a);
int compare(struct BigInteger a, struct BigInteger b);
struct BigInteger copy(struct BigInteger a);

#endif // BIGINTEGER_H
