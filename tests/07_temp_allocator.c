#include "shared.h"

int main() {
    int result = 0;

    // Test basic allocation
    int *ptr1 = (int *)aids_temp_alloc(sizeof(int));
    AIDS_ASSERT(ptr1 != NULL, "Failed to allocate temp memory");
    *ptr1 = 42;
    AIDS_ASSERT(*ptr1 == 42, "Expected 42, got %d", *ptr1);

    // Test multiple allocations
    int *ptr2 = (int *)aids_temp_alloc(sizeof(int) * 10);
    AIDS_ASSERT(ptr2 != NULL, "Failed to allocate temp array");
    for (int i = 0; i < 10; i++) {
        ptr2[i] = i;
    }
    AIDS_ASSERT(ptr2[5] == 5, "Expected 5, got %d", ptr2[5]);

    // Test save/load
    size_t saved = aids_temp_save();
    int *ptr3 = (int *)aids_temp_alloc(sizeof(int));
    AIDS_ASSERT(ptr3 != NULL, "Failed to allocate temp memory");
    *ptr3 = 100;
    
    aids_temp_load(saved);
    
    // After load, the next allocation should be at the same position as ptr3 was
    int *ptr4 = (int *)aids_temp_alloc(sizeof(int));
    AIDS_ASSERT(ptr4 == ptr3, "Expected same pointer after load");

    // Test temp_sprintf
    char *str = aids_temp_sprintf("Number: %d, String: %s", 123, "test");
    AIDS_ASSERT(str != NULL, "Failed to create temp sprintf");
    AIDS_ASSERT(strcmp(str, "Number: 123, String: test") == 0, "Expected 'Number: 123, String: test', got '%s'", str);

    // Test reset
    aids_temp_reset();
    size_t size_after_reset = aids_temp_save();
    AIDS_ASSERT(size_after_reset == 0, "Expected size 0 after reset, got %lu", size_after_reset);

    return_defer(0);

defer:
    return result;
}
