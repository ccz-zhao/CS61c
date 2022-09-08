#include <stdio.h>
#include <stdlib.h>

int arrays[] = {5, 6, 7, 8, 9,
                1, 2, 3, 4, 7,
                5, 2, 7, 4, 3,
                1, 6, 3, 8, 4,
                5, 2, 7, 8, 1};

const char *start_msg = "Lists before: \n";
const char *end_msg = "Lists after: \n";

struct node {
    int *arr;
    int size;
    struct node *next;
};

typedef struct node* List;

List create_default_list();
void print_list(List lst);
void print_newline();
int mystery(int a);
void map(List curr_node, int (*f)(int));


int main() {
    List lst;
    lst = create_default_list();
    printf("%s", start_msg);
    print_list(lst);
    print_newline();
    map(lst, mystery);
    printf("%s", end_msg);
    print_list(lst);
}

void fillArray(int *dest, int *src) {
    int i = 0;
    while (i != 5) {
        *dest++ = *src++;
        i++;
    }
}

List create_default_list() {
    List last = NULL;
    int i = 0;
    int size = 5;
    int *arr = arrays;
    do {
        List node = malloc(sizeof(struct node));
        int *narr = malloc(5*sizeof(int));
        node->arr = narr;
        fillArray(narr, arr);
        node->size = 5;
        node->next = last;
        last = node;
        i++;
        arr += 5;
    } while(i != 5);
}

void print_list(List lst) {
    if (!lst) return;
    int *arr = lst->arr;
    int i = 0;
    do {
        printf("%d ", arr[i]);
        i++;
    } while (i != 5);
    printf("\n");
    print_list(lst->next);
}

void print_newline() {
    printf("\n");
}

int mystery(int a) {
    return a * a + a;
}

void map(List curr_node, int (*f)(int)) {
    if (!curr_node) return;
    for (int i = 0; i < curr_node->size; i++) {
        curr_node->arr[i] = f(curr_node->arr[i]);
    }
    map(curr_node->next, f);
}