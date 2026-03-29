#include "shared.h"

static int compare_ints(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int main() {
    int result = 0;
    Aids_Priority_Queue pq;
    aids_priority_queue_init(&pq, sizeof(int), compare_ints);

    // Test insert
    int value1 = 5;
    int value2 = 3;
    int value3 = 8;
    int value4 = 1;
    int value5 = 10;
    AIDS_ASSERT(aids_priority_queue_insert(&pq, &value1) == AIDS_OK, "Failed to insert value1");
    AIDS_ASSERT(aids_priority_queue_insert(&pq, &value2) == AIDS_OK, "Failed to insert value2");
    AIDS_ASSERT(aids_priority_queue_insert(&pq, &value3) == AIDS_OK, "Failed to insert value3");
    AIDS_ASSERT(aids_priority_queue_insert(&pq, &value4) == AIDS_OK, "Failed to insert value4");
    AIDS_ASSERT(aids_priority_queue_insert(&pq, &value5) == AIDS_OK, "Failed to insert value5");

    // Test peek (should be minimum element)
    int *peeked = NULL;
    AIDS_ASSERT(aids_priority_queue_peek(&pq, (void *)&peeked) == AIDS_OK, "Failed to peek");
    AIDS_ASSERT(*(int *)peeked == 1, "Expected 1 at top, got %d", *(int *)peeked);

    // Test pull (should return elements in ascending order)
    int pulled;
    AIDS_ASSERT(aids_priority_queue_pull(&pq, &pulled) == AIDS_OK, "Failed to pull");
    AIDS_ASSERT(pulled == 1, "Expected 1, got %d", pulled);

    AIDS_ASSERT(aids_priority_queue_pull(&pq, &pulled) == AIDS_OK, "Failed to pull");
    AIDS_ASSERT(pulled == 3, "Expected 3, got %d", pulled);

    AIDS_ASSERT(aids_priority_queue_pull(&pq, &pulled) == AIDS_OK, "Failed to pull");
    AIDS_ASSERT(pulled == 5, "Expected 5, got %d", pulled);

    AIDS_ASSERT(aids_priority_queue_pull(&pq, &pulled) == AIDS_OK, "Failed to pull");
    AIDS_ASSERT(pulled == 8, "Expected 8, got %d", pulled);

    AIDS_ASSERT(aids_priority_queue_pull(&pq, &pulled) == AIDS_OK, "Failed to pull");
    AIDS_ASSERT(pulled == 10, "Expected 10, got %d", pulled);

    // Test pull from empty queue
    AIDS_ASSERT(aids_priority_queue_pull(&pq, &pulled) == AIDS_ERR, "Should fail to pull from empty queue");

    // Clean up
    aids_priority_queue_free(&pq);

    return_defer(0);

defer:
    return result;
}
