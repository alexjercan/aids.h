#include "shared.h"

int main() {
    int result = 0;
    Aids_List list;
    aids_list_init(&list, sizeof(int));

    // Test push_back
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    AIDS_ASSERT(aids_list_push_back(&list, &value1) == AIDS_OK, "Failed to push_back value1");
    AIDS_ASSERT(aids_list_push_back(&list, &value2) == AIDS_OK, "Failed to push_back value2");
    AIDS_ASSERT(aids_list_push_back(&list, &value3) == AIDS_OK, "Failed to push_back value3");

    // Test pop_back
    int popped;
    AIDS_ASSERT(aids_list_pop_back(&list, &popped) == AIDS_OK, "Failed to pop_back");
    AIDS_ASSERT(popped == 30, "Expected 30, got %d", popped);

    // Test pop_front
    AIDS_ASSERT(aids_list_pop_front(&list, &popped) == AIDS_OK, "Failed to pop_front");
    AIDS_ASSERT(popped == 10, "Expected 10, got %d", popped);

    // Test push_front
    int value4 = 40;
    AIDS_ASSERT(aids_list_push_front(&list, &value4) == AIDS_OK, "Failed to push_front value4");

    // Test peek_front
    int *peeked;
    AIDS_ASSERT(aids_list_peek_front(&list, (void **)&peeked) == AIDS_OK, "Failed to peek_front");
    AIDS_ASSERT(*peeked == 40, "Expected 40, got %d", *peeked);

    // Test peek_back
    AIDS_ASSERT(aids_list_peek_back(&list, (void **)&peeked) == AIDS_OK, "Failed to peek_back");
    AIDS_ASSERT(*peeked == 20, "Expected 20, got %d", *peeked);

    // Test reverse
    aids_list_reverse(&list);
    AIDS_ASSERT(aids_list_pop_front(&list, &popped) == AIDS_OK, "Failed to pop_front after reverse");
    AIDS_ASSERT(popped == 20, "Expected 20 after reverse, got %d", popped);

    // Clean up
    aids_list_free(&list);

    return_defer(0);

defer:
    return result;
}
