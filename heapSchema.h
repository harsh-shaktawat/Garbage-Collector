#include<stdio.h>
#include<stdlib.h>

typedef struct node_tag{
    int data;
    int count;//for reference count
    int bit;//for mark-sweep
    struct node_tag* ptr1;
    struct node_tag* ptr2;
    struct node_tag* ptr3;
}Node;
typedef struct root_tag{
    Node* ptr;
}Root;

Node* adj[11];
Root root1;
Root root2;
/* HEAP SCHEMA GIVEN IN PROBLEM
root1->5  7  3
       | /| /|
       |/ |/ |
root2->1  8  | 
       |\ |  |
       | \|  |
       |\ |\ |
       | \| \|
       2  9 10
*/
Node* createNode(int val);
void print_node(Node* node);
void print_heap();
void print_root();
void createSchema();