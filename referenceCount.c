#include<stdio.h>
#include"heapSchema.h"
void garbageCollector(){
    int yes=0;
    for(int i=0;i<11;i++)
    {
        if(adj[i]!=NULL)
        {   
           // printf("%d-%d\n", adj[i]->data,adj[i]->count);
            if(adj[i]->count==0)
            {
                if(adj[i]->ptr1)
                {
                    adj[i]->ptr1->count--;
                    adj[i]->ptr1=NULL;//delete node's links
                }
                if(adj[i]->ptr2)
                {
                    adj[i]->ptr2->count--;
                    adj[i]->ptr2=NULL;//delete node's links
                }
                if(adj[i]->ptr3)
                {
                    adj[i]->ptr3->count--;
                    adj[i]->ptr3=NULL;//delete node's links
                }
                printf("Node(memory) containing data %d is freed\n", adj[i]->data);
                free(adj[i]) ;
                adj[i]=NULL;
                yes=1;
            }
        }
    }
    if(yes) //if reference counts were updated, call function again
    {
        garbageCollector();
    }
}
int main(){
    createSchema();
    printf("\nUSEFUL HEAP\n");
    print_root();
    printf("\nTOTAL HEAP\n");
    print_heap();
    printf("\nGarbage collector(reference count) is called\n");
    garbageCollector();
    printf("\nTOTAL HEAP AFTER GARBAGE COLLECTION(reference count menthod)\n");
    print_heap();
    return 0;
}
