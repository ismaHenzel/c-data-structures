#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node * last_node; // pointing to the last_node
    int number; // current_value 
}node;

void insert_value(node **list, int value){
    // creating the new node
    node * new_node = malloc(sizeof(node));

    if(new_node){

        // filling the value and the malloc node ref
        new_node->number = value;
        new_node->last_node = *list; // storing the last node ref
        *list=new_node; // changing the current node to this
    }else{ 
        printf("Error in memory allocation \n");
    }
}

node* remove_value(node **list, int value){ 
    node *last_node, *temp_node;

    if(*list){
        if((*list)->number == value){
            last_node = *list;
            *list = last_node->last_node; //pointing to another struct
        }else{
            temp_node = *list;
            while(temp_node->last_node && temp_node->last_node->number != value)
                temp_node = temp_node->last_node;
            if(temp_node->last_node){
                last_node = temp_node->last_node; // get the node ref that the deleted value have
                temp_node->last_node = last_node->last_node;  // setting the last_node to itself
            }
        }
    }
    return last_node;
}
void print_list(node *list){
    while (list)
    {
        printf("%d\n", list->number);
        list = list->last_node;
    }
}
void main(){
    int  value, option;
    node *list =  NULL;
    value = 1;
    do{
      printf(" Exit - 0 | Insert Value - 1 | Remove value - 2 | Print List - 3 : ");
      scanf("%d", &option);
      if(option == 2){
        printf("Digit the value to remove: ");
        scanf("%d", &value);
        remove_value(&list, value);
      }
      else if(option == 1){
        printf("Digit the value to insert: ");
        scanf("%d", &value);
        insert_value(&list,value);
      }
      else if(option == 3){
        print_list(list);
      }
     else if(option == 0){
        break;
      }
    else{
      printf("Invalid Option \n");
    }

    }while (option != 0);
}

