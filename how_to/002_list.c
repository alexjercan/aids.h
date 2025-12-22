// This is an example of using Aids to create and manipulate a linked list.
// The example demonstrates how to initialize a list, add items to it, and
// remove items from it while handling potential errors.
#define AIDS_IMPLEMENTATION
#include "../aids.h"

#include <stdlib.h>

static void list_example() {
    // Initialize an Aids_List structure. We do this by calling
    // `aids_list_init`, which takes a pointer to the Aids_List and the size of
    // the items we want to store in the list.
    Aids_List list = {0};
    aids_list_init(&list, sizeof(int));

    // Add items to the list using `aids_list_push_back`. This function will
    // allocate memory if needed and add the item to the end of the list.
    for (int i = 0; i < 10; i++) {
        if (aids_list_push_back(&list, (unsigned char *)&i) != AIDS_OK) {
            aids_log(AIDS_ERROR, "Failed to append item %d to list: %s", i, aids_failure_reason());
            exit(EXIT_FAILURE);
        }
    }

    // Remove items from the list using `aids_list_pop_back`. This function
    // will remove the last item from the list and copy its value into the
    // provided pointer.
    int num = 0;
    while (aids_list_pop_back(&list, (unsigned char *)&num) == AIDS_OK) {
        aids_log(AIDS_INFO, "Popped item: %d", num);
    }

    // Free the list to release allocated memory.
    aids_list_free(&list);
}

int main() {
    list_example();

    return 0;
}
