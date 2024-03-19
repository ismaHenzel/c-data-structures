#include <stdio.h>
#include <stdlib.h>
#define size 100

struct node {
    char data;
    int left;
    int right;
    int parent;
};

struct node tree[size];
int index = 0;

int find_data_index(char data) {
    if (index != 0) {
        for (int i = 0; i < size; i++) {
            if (tree[i].data == data) {
                return i;
            }
        }
    } else {
        return 0;
    }
}

void insert_data(char data, char side) {
    if (index == 0) {
        printf("First value of the tree, setting the value as Root\n");
        tree[index].data = data;
        tree[index].parent = -1;
        tree[index].left = -1;
        tree[index].right = -1;
        index += 1;
    } else {
        switch (side) {
            case 'L':
                tree[index].data = data;
                tree[index].parent = index - 1;
                tree[index].left = index;
                tree[index].right = -1;
                index += 1;
                break;
            case 'R':
                tree[index].data = data;
                tree[index].parent = index - 1;
                tree[index].left = -1;
                tree[index].right = index;
                index += 1;
                break;
        }
    }
}

int main(void) {
    insert_data('A', 'L');
    insert_data('B', 'R');
    insert_data('C', 'L');
    insert_data('C', 'L');
    insert_data('C', 'L');
    insert_data('D', 'R');

    int curr_index = 0;
    while (curr_index < index) {
        printf("%c\n", tree[curr_index].data);
        curr_index++;
    }
    return 0;
}

