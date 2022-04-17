#include"heapSchema.h"
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
Node* createNode(int val){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=val;
    newNode->count=0;
    newNode->bit=0;
    newNode->ptr1=NULL;
    newNode->ptr2=NULL;
    newNode->ptr3=NULL;
    return newNode;
}

void print_node(Node* node)
{
    printf(" %d",node->data);
    if (node->ptr1!=NULL || node->ptr2!=NULL || node->ptr3!=NULL)
    {
        printf("->(");
        if(node->ptr1) print_node(node->ptr1);
        if(node->ptr2) print_node(node->ptr2);
        if(node->ptr3) print_node(node->ptr3);
        printf(")");
    }
}
void print_heap(){
    for(int i=0;i<11;i++){
        if(adj[i]!=NULL){
            print_node(adj[i]);
            printf("\n");
        }
    }
}
void print_root()
{
    printf("Root1->");
    print_node(root1.ptr);
    printf("\nRoot2->");
    print_node(root2.ptr);
    printf("\n");
}
void createSchema(){
    //creating nodes of value mentioned in HEAP SCHEMA 
    for(int i=0;i<11;i++){
        if(i==0 || i==4 || i==6){
            adj[i]=NULL;
        }
        else{
            Node* newNode=createNode(i);
            adj[i]=newNode;
        }
    }
    //creating links and incrementing count variable
    root1.ptr=adj[5];     adj[5]->count++;  //root1------>5
    root2.ptr=adj[1];     adj[1]->count++;  //root2------>1
    adj[5]->ptr1=adj[1];  adj[1]->count++;  //5---------->1
    adj[7]->ptr1=adj[1];  adj[1]->count++;  //7---------->1
    adj[7]->ptr2=adj[8];  adj[8]->count++;  //7---------->8
    adj[3]->ptr1=adj[8];  adj[8]->count++;  //3---------->8
    adj[3]->ptr2=adj[10]; adj[10]->count++; //3---------->10
    adj[1]->ptr1=adj[2];  adj[2]->count++;  //1---------->2
    adj[1]->ptr2=adj[9];  adj[9]->count++;  //1---------->9
    adj[1]->ptr3=adj[10]; adj[10]->count++; //1---------->10
    adj[8]->ptr1=adj[9];  adj[9]->count++;  //8---------->9

}