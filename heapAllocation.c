#include<stdio.h>
#include<stdlib.h>

#define TOTAL_MEMORY 1024

typedef enum{FALSE,TRUE} bool; 

typedef struct node_tag{
    int start;
    int end;
    int size;
    bool isFree;
    bool isAllocated;
    struct node_tag* prev;
    struct node_tag* next;
}Node;
 
typedef struct heap_tag{
    Node* head;
}HeapMemory;

Node* create_Node(int start,int size){
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->size=size;
    temp->start=start;
    temp->end=start+size-1;
    temp->isAllocated=FALSE;
    temp->isFree=FALSE;
    temp->prev=NULL;
    temp->next=NULL;
    return temp;
}

void Assign_initial_memory(HeapMemory* ptr){
    Node* temp=(Node*)malloc(sizeof(Node));
    if(temp!=NULL){
        temp=create_Node(0,TOTAL_MEMORY);
        temp->isFree=TRUE;
        ptr->head=temp;
    }
    else{
        printf("Failed to assign initial memory");
    }
}

void print_freeList(HeapMemory* ptr){
    Node* temp=ptr->head;
    bool spaceFree=FALSE;
    printf("\n");
    while(temp!=NULL){
        if(temp->isFree==TRUE){
            spaceFree=TRUE;
            printf("memory block free from %d to %d\n", temp->start,temp->end);
        }
        temp=temp->next;
    }
    if(spaceFree==FALSE){
        printf("Heap is full.No free space available\n");
    }
}

void print_allocatedList(HeapMemory* ptr){
    Node* temp=ptr->head;
    bool spaceAllocated=FALSE;
    printf("\n");
    while(temp!=NULL){
        if(temp->isAllocated==TRUE){
            spaceAllocated=TRUE;
            printf("memory allocated from %d to %d\n", temp->start,temp->end);
        }
        temp=temp->next;
    }
    if(spaceAllocated==FALSE){
        printf("No space is allocated\n");
    }
}

void allocate(HeapMemory* ptr){
    
    int size;
    printf("\nenter the size of memory required for allocation\n");
    scanf("%d", &size);
    Node* temp=ptr->head;
    if(temp==NULL){
        printf("initial heap is empty\n");
        return;
    }
    else{
        Node* nptr=temp,*foundptr=NULL;
        bool found=FALSE;
        while(found==FALSE && nptr!=NULL){
            int curr_size=nptr->size;
            bool isAvailable=nptr->isFree;
            if(curr_size>=size && isAvailable==TRUE){
                found=TRUE;
                foundptr=nptr;
            }
            else{
                nptr=nptr->next;
            }
        }
        if(foundptr==NULL){
            printf("required space cannot be allocated\n");
        }
        else{
            Node* new_node=create_Node(foundptr->start,size);
            printf("\nMemory block of size %d allocated from %d to %d\n", new_node->size,new_node->start,new_node->end);
            if(foundptr->size==size && foundptr->next==NULL){
                foundptr->isFree=FALSE;
                foundptr->isAllocated=TRUE;
                free(new_node);
            }
            else{
                foundptr->start=new_node->start+new_node->size;
                foundptr->size=foundptr->size-new_node->size;
                if(foundptr->prev!=NULL){
                    foundptr->prev->next=new_node;
                    new_node->prev=foundptr->prev;
                }
                new_node->next=foundptr;
                foundptr->prev=new_node;
                new_node->isAllocated=TRUE;
            }
            
        }
        
        while(temp->prev!=NULL){
                temp=temp->prev;
            }
        ptr->head=temp;
    }
}

void deallocate(HeapMemory* ptr){
    int size,start_point;
    printf("\nEnter the size and starting address of block to deallocate\n");
    scanf("%d%d", &size, &start_point);
    Node* temp=ptr->head;
    if(temp==NULL){
        printf("Initial heap is empty\n");
    }
    else{
        Node* nptr=temp;
        Node* foundptr=NULL;
        bool found=FALSE;
        while(nptr!=NULL && found==FALSE){
            if(nptr->start==start_point && nptr->size==size && nptr->isAllocated==TRUE){
                found=TRUE;
                foundptr=nptr;
            }
            else{
                nptr=nptr->next;
            }
        } 
        if(foundptr==NULL){
            printf("No such block was allocated\n");
        }
        else{
            Node* prev_ptr;
            if(foundptr->prev!=NULL){
                if(foundptr->prev->isFree==TRUE){
                    prev_ptr=foundptr->prev;
                    foundptr->size=foundptr->size+prev_ptr->size;
                    foundptr->start=prev_ptr->start;
                    if(prev_ptr->prev!=NULL) prev_ptr->prev->next=foundptr;
                    foundptr->prev=prev_ptr->prev;
                    free(prev_ptr);
                }
            }
            Node* next_ptr;
            if(foundptr->next!=NULL){
                if(foundptr->next->isFree==TRUE){
                    next_ptr=foundptr->next;
                    foundptr->size=foundptr->size+next_ptr->size;
                    foundptr->end=next_ptr->end;
                    if(next_ptr->next!=NULL) next_ptr->next->prev=foundptr;
                    foundptr->next=next_ptr->next;
                    free(next_ptr);
                }
            }
            foundptr->isAllocated=FALSE;
            foundptr->isFree=TRUE;
            temp=foundptr;
            while(temp->prev!=NULL){
                temp=temp->prev;
            }
            ptr->head=temp;
        }
       
    }
}

int main(){
    HeapMemory heap;
    HeapMemory *ptr=&heap;
    
    Assign_initial_memory(ptr);
    
    char choice='y';
    while(choice=='y'){
        int option;
        printf("\nEnter the operation to perform\n");
        printf("Press\n1 to allocate memory\n2 to deallocate memory\n3 to print free list\n");
        printf("4 to print allocated list\n5 to stop\n");
        scanf("%d", &option);
        if(option==1){
            allocate(ptr);
        }
        else if(option==2){
            deallocate(ptr);
        }
        else if(option==3){
            print_freeList(ptr);
        }
        else if(option==4){
            print_allocatedList(ptr);
        }
        else{
            printf("Process stopped\n");
            choice='n';
        }
    }
    return 0;
}
