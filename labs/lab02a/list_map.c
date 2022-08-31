#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
};

typedef struct node* List;


List create_default_list();
void print_list(List head);
void print_newline();
void map(List head, int (*f)(int));
int square(int value);
int decrement(int value);

int main() {
    List head;
    head = create_default_list();
    print_list(head);
    print_newline();
    map(head, square);
    print_list(head);
    print_newline();
    map(head, decrement);
    print_list(head);
    print_newline();

}

List create_default_list() {
    int i;
    List last = NULL;
    for (i = 0; i != 10; ++i) {
        List node = malloc(sizeof(struct node));
        node->value = i;
        node->next = last;
        last = node;
    }
    return last;
}

void print_list(List head) {
    if (!head) return;
    printf("%d ", head->value);
    print_list(head->next);
}

void print_newline() {
    printf("\n");
}

void map(List head, int (*f)(int)) {
    if (!head) return;
    head->value = f(head->value);
    map(head->next, f);
}

int square(int value) {
    return value * value;
}

int decrement(int value) {
    return value - 1;
}