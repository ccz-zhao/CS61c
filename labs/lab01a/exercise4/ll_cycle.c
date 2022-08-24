#include <stddef.h>
#include "ll_cycle.h"

bool ll_has_cycle(node *head) {
    /* TODO: Implement ll_has_cycle */
    if (head == NULL)
        return false;
    node *fast_ptr = head;
    node *slow_ptr = head;
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
        if (fast_ptr == slow_ptr)
            return true;
    }
    return false;
}
