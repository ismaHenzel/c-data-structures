/*
Description:
My code implements a dynamic array that grows and shrinks based on the maximum size.
The implemented functions can behave as both a list and a stack.
Therefore, I didn't create specific codes for one or the other; it may have been confusing to understand.

Author: Ismael Henzel

Compiler: gcc version 12.2.1 20230201 (GCC)
OS: Arch Linux (on the Windows Subsystem for Linux)
Kernel: x86_64 Linux 5.15.90.1-microsoft-standard-WSL2
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Dynamic_array{
    int max_arr_size;
    int current_index;
    int * array;
} Dynamic_array;

void array_print_chars(Dynamic_array *array){
    // print the array
    for(int i = 0; i<array->max_arr_size; i++){
        printf("%c ", (array->array)[i]);
    }
    printf("\n");
}

void array_grow(Dynamic_array *array){
    // Copies the data from the array to a larger array.
    
    int new_size = array->max_arr_size * 2;
    int * new_array = malloc(sizeof(int)*new_size);

    for(int i=0; i < array->max_arr_size; i++){
        new_array[i]  = (array->array)[i];
    }

    // Frees the previous array from memory
    free(array->array);

    array->array = new_array;
    array->max_arr_size = new_size;
}

void array_shrink(Dynamic_array *array) {
    int new_size = (array->max_arr_size)/2;

    int * new_array = malloc(sizeof(int)*new_size);

    // Copy elements from the original array to the new array
    for (int i = 0; i < new_size; i++) {
        new_array[i] = array->array[i];
    }

    free(array->array);  // Free the memory occupied by the original array

    array->array = new_array;
    array->max_arr_size = new_size;
}

void array_insert(Dynamic_array *array,int index, char value){
    // Inserts a value at a specific index of the array.
  
    if(array->current_index == array->max_arr_size){
        array_grow(array);
    }
    else if(array->max_arr_size/3 > array->current_index){
        array_shrink(array);
    }

    for(int i = array->max_arr_size; i > index ; i--){
        (array->array)[i] = (array->array)[i-1];
    }
    (array->array)[index] = value;
}

void array_push(Dynamic_array *array,char value){
    // inserts a new value inse the array 
    
    if(array->current_index == array->max_arr_size){
        array_grow(array);
    }
    else if(array->max_arr_size/3 > array->current_index){
        array_shrink(array);
    }

    (array->array)[array->current_index] = value;
    array->current_index+=1;
}

char array_remove(Dynamic_array *array, int index) {

    if ((index < 0) || (index > array->current_index)) {
        return '\0';
    }

    char temp_char = (array->array)[index];
    
    for (int i = 0; i <  (array->max_arr_size - index -1); i++){
        (array->array)[i+index] = (array->array)[i+index+1];    
    }

    (array->array)[array->current_index-1] = '\0';
    array->current_index -= 1;

    return temp_char;
}

void clear_buffer() {
    // clear input buffer  
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char convert_nucleotide_sequence(char value) {
    switch (value) {
        case 'A':
        case 'a':
            return 'T';
        case 'T':
        case 't':
            return 'A';
        case 'C':
        case 'c':
            return 'G';
        case 'G':
        case 'g':
            return 'C';
    }
}
int main() {
    char console_message[1000] = "Options:\n"
                                 "\t- 0 = Exit the program\n"
                                 "\t- 1 = Add nucleotide\n"
                                 "\t- 2 = Remove last nucleotide\n"
                                 "\t- 3 = Print the entered sequence \n"
                                 "\t- 4 = Finish Insertion and print\n";

    int max_arr_size = 5; // define initial size of the array

    // ALLOCATING MEMORY FOR THE QUEUE
    Dynamic_array *dynamic_queue = malloc(sizeof(Dynamic_array));
    dynamic_queue->max_arr_size = max_arr_size;
    dynamic_queue->current_index = 0;
    dynamic_queue->array = malloc(sizeof(char) * max_arr_size);

    // ALLOCATING MEMORY FOR THE STACK
    Dynamic_array *dynamic_stack = malloc(sizeof(Dynamic_array));
    dynamic_stack->max_arr_size = max_arr_size;
    dynamic_stack->current_index = 0;
    dynamic_stack->array = malloc(sizeof(char) * max_arr_size);

    int option = -1;
    char nucleotide;
    while (option != 0) {

        printf("%s\n", console_message);
        scanf("%d", &option);
        clear_buffer();

        switch (option) {
            case 1:
                printf("Nucleotide: (Type 0 to stop typing)  ");
                while (1) {
                    scanf(" %c", &nucleotide);
                    if (nucleotide == '0') {
                        break;
                    }
                    if (nucleotide == 'T' || nucleotide == 'C' || nucleotide == 'G' ||
                        nucleotide == 'A' || nucleotide == 't' || nucleotide == 'c' ||
                        nucleotide == 'g' || nucleotide == 'a') {
                        array_push(dynamic_queue, nucleotide);
                    } else {
                        printf("Only the values T G A C are available\n");
                    }
                    printf("Nucleotide (Type 0 to stop): ");
                }
                break;
            case 2:
                array_remove(dynamic_queue, dynamic_queue->current_index - 1);
                break;
            case 3:
                array_print_chars(dynamic_queue);
                printf("\n");
                break;
            case 4:
                printf("Queue: ");
                array_print_chars(dynamic_queue);

                // Always removing index 0 to simulate the behavior of the queue (pop)
                char removed_value;

                while ((removed_value = array_remove(dynamic_queue, 0)) != '\0') {
                    // Converting nucleotide sequence and appending to a "stack"
                    array_push(dynamic_stack, convert_nucleotide_sequence(removed_value));
                }

                // Emptying the stack and printing the return to have the requested inputs
                printf("Stack: ");
                while ((removed_value = array_remove(dynamic_stack, dynamic_stack->current_index - 1)) != '\0') {
                    // Removing and returning the value from the stack (getting the last index) (pop)
                    printf("%c ", removed_value);
                }
                printf("\n Stack and Queue cleared! \n");
                break;
            case 0:
                break;
            default:
                printf("Invalid option\n");
                printf("%s\n", console_message);
                scanf("%d", &option);
        }
    }

    free(dynamic_queue->array);
    free(dynamic_queue);
    free(dynamic_stack->array);
    free(dynamic_stack);

    return 0;
}
