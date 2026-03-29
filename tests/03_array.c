#include "shared.h"

static int compare_ints(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int main() {
    int result = 0;
    Aids_Array array;
    aids_array_init(&array, sizeof(int));

    // Test append
    int value1 = 5;
    int value2 = 3;
    int value3 = 8;
    int value4 = 1;
    AIDS_ASSERT(aids_array_append(&array, &value1) == AIDS_OK, "Failed to append value1");
    AIDS_ASSERT(aids_array_append(&array, &value2) == AIDS_OK, "Failed to append value2");
    AIDS_ASSERT(aids_array_append(&array, &value3) == AIDS_OK, "Failed to append value3");
    AIDS_ASSERT(aids_array_append(&array, &value4) == AIDS_OK, "Failed to append value4");
    AIDS_ASSERT(array.count == 4, "Expected count 4, got %lu", array.count);

    // Test append_many
    int values[] = {7, 2, 9};
    AIDS_ASSERT(aids_array_append_many(&array, values, 3) == AIDS_OK, "Failed to append_many");
    AIDS_ASSERT(array.count == 7, "Expected count 7, got %lu", array.count);

    // Test get
    int *item;
    AIDS_ASSERT(aids_array_get(&array, 0, (void **)&item) == AIDS_OK, "Failed to get item at index 0");
    AIDS_ASSERT(*item == 5, "Expected 5, got %d", *item);

    AIDS_ASSERT(aids_array_get(&array, 4, (void **)&item) == AIDS_OK, "Failed to get item at index 4");
    AIDS_ASSERT(*item == 7, "Expected 7, got %d", *item);

    // Test contains
    int search = 8;
    AIDS_ASSERT(aids_array_contains(&array, &search, compare_ints) == true, "Array should contain 8");
    search = 100;
    AIDS_ASSERT(aids_array_contains(&array, &search, compare_ints) == false, "Array should not contain 100");

    // Test swap
    AIDS_ASSERT(aids_array_swap(&array, 0, 3) == AIDS_OK, "Failed to swap indices 0 and 3");
    AIDS_ASSERT(aids_array_get(&array, 0, (void **)&item) == AIDS_OK, "Failed to get item at index 0");
    AIDS_ASSERT(*item == 1, "Expected 1 at index 0, got %d", *item);
    AIDS_ASSERT(aids_array_get(&array, 3, (void **)&item) == AIDS_OK, "Failed to get item at index 3");
    AIDS_ASSERT(*item == 5, "Expected 5 at index 3, got %d", *item);

    // Test sort
    aids_array_sort(&array, compare_ints);
    AIDS_ASSERT(aids_array_get(&array, 0, (void **)&item) == AIDS_OK, "Failed to get item at index 0");
    AIDS_ASSERT(*item == 1, "Expected 1 at sorted index 0, got %d", *item);
    AIDS_ASSERT(aids_array_get(&array, 6, (void **)&item) == AIDS_OK, "Failed to get item at index 6");
    AIDS_ASSERT(*item == 9, "Expected 9 at sorted index 6, got %d", *item);

    // Test pop
    int popped;
    AIDS_ASSERT(aids_array_pop(&array, 3, &popped) == AIDS_OK, "Failed to pop at index 3");
    AIDS_ASSERT(popped == 5, "Expected 5, got %d", popped);
    AIDS_ASSERT(array.count == 6, "Expected count 6, got %lu", array.count);

    // Test out of bounds
    AIDS_ASSERT(aids_array_get(&array, 100, (void **)&item) == AIDS_ERR, "Should fail for out of bounds");
    AIDS_ASSERT(aids_array_pop(&array, 100, &popped) == AIDS_ERR, "Should fail for out of bounds");

    // Clean up
    aids_array_free(&array);

    return_defer(0);

defer:
    return result;
}
