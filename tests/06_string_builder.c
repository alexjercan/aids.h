#include "shared.h"

int main() {
    int result = 0;
    Aids_String_Builder sb;
    aids_string_builder_init(&sb);

    // Test append
    AIDS_ASSERT(aids_string_builder_append(&sb, "Hello") == AIDS_OK, "Failed to append 'Hello'");
    AIDS_ASSERT(aids_string_builder_append(&sb, " %s", "World") == AIDS_OK, "Failed to append ' World'");
    AIDS_ASSERT(aids_string_builder_append(&sb, "! Number: %d", 42) == AIDS_OK, "Failed to append number");

    // Test to_cstr
    char *cstr = NULL;
    AIDS_ASSERT(aids_string_builder_to_cstr(&sb, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "Hello World! Number: 42") == 0, "Expected 'Hello World! Number: 42', got '%s'", cstr);
    AIDS_FREE(cstr);

    // Test to_slice
    Aids_String_Slice slice;
    aids_string_builder_to_slice(&sb, &slice);
    AIDS_ASSERT(slice.len == 23, "Expected length 23, got %lu", slice.len);

    // Clean up
    aids_string_builder_free(&sb);

    // Test append_slice
    aids_string_builder_init(&sb);
    Aids_String_Slice input = aids_string_slice_from_cstr("Test");
    AIDS_ASSERT(aids_string_builder_append_slice(&sb, input) == AIDS_OK, "Failed to append_slice");
    AIDS_ASSERT(aids_string_builder_to_cstr(&sb, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "Test") == 0, "Expected 'Test', got '%s'", cstr);
    AIDS_FREE(cstr);

    // Test appendc
    AIDS_ASSERT(aids_string_builder_appendc(&sb, '!') == AIDS_OK, "Failed to appendc");
    AIDS_ASSERT(aids_string_builder_to_cstr(&sb, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "Test!") == 0, "Expected 'Test!', got '%s'", cstr);
    AIDS_FREE(cstr);

    // Clean up
    aids_string_builder_free(&sb);

    return_defer(0);

defer:
    return result;
}
