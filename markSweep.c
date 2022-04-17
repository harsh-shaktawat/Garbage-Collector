#include<stdio.h>
#include"heapSchema.h"
void mark(Node* node){
    if(node==NULL) return;
    else{
        if(node->bit==0){
            node->bit=1;
            printf("Node(memory) with data %d marked\n",node->data);
            if(node->ptr1) mark(node->ptr1);
            if(node->ptr2) mark(node->ptr2);
            if(node->ptr3) mark(node->ptr3);
        }
    }
}
void sweep(){
    for(int i=0;i<11;i++){
        if(adj[i]!=NULL){
            if(adj[i]->bit==0) {
                printf("Node(memory) with data %d sweeped\n",adj[i]->data);
                adj[i]->ptr1=NULL;
                adj[i]->ptr2=NULL;
                adj[i]->ptr3=NULL;
                free(adj[i]);
                adj[i]=NULL;
            }
            else{
                adj[i]->bit=0;
            }
        }
    }
}
void garbageCollector(){
    printf("Mark Phase started\n");
    mark(root1.ptr);  
    mark(root2.ptr);  
    printf("\nSweep Phase Started\n");
    sweep();
}
int main(){
    createSchema();
    printf("\nUSEFUL HEAP\n");
    print_root();
    printf("\nTOTAL HEAP\n");
    print_heap();
    printf("\nGarbage collector(mark-sweep) is called\n");
    garbageCollector();
    printf("\nTOTAL HEAP AFTER GARBAGE COLLECTION(mark-sweep method)\n");
    print_heap();
    return 0;
}
//gcc heapSchema.c markSweep.c heapSchema.h