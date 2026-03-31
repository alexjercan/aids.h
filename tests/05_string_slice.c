#include "shared.h"

int main() {
    int result = 0;

    // Test from_cstr
    Aids_String_Slice ss = aids_string_slice_from_cstr("Hello World");
    AIDS_ASSERT(ss.len == 11, "Expected length 11, got %lu", ss.len);

    // Test to_cstr
    char *cstr = NULL;
    AIDS_ASSERT(aids_string_slice_to_cstr(&ss, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "Hello World") == 0, "Expected 'Hello World', got '%s'", cstr);
    AIDS_FREE(cstr);

    // Test tokenize
    Aids_String_Slice input = aids_string_slice_from_cstr("apple,banana,cherry");
    Aids_String_Slice token;
    
    AIDS_ASSERT(aids_string_slice_tokenize(&input, ',', &token) == true, "Failed to tokenize");
    AIDS_ASSERT(aids_string_slice_to_cstr(&token, &cstr) == AIDS_OK, "Failed to convert token to cstr");
    AIDS_ASSERT(strcmp(cstr, "apple") == 0, "Expected 'apple', got '%s'", cstr);
    AIDS_FREE(cstr);

    AIDS_ASSERT(aids_string_slice_tokenize(&input, ',', &token) == true, "Failed to tokenize");
    AIDS_ASSERT(aids_string_slice_to_cstr(&token, &cstr) == AIDS_OK, "Failed to convert token to cstr");
    AIDS_ASSERT(strcmp(cstr, "banana") == 0, "Expected 'banana', got '%s'", cstr);
    AIDS_FREE(cstr);

    AIDS_ASSERT(aids_string_slice_tokenize(&input, ',', &token) == true, "Failed to tokenize");
    AIDS_ASSERT(aids_string_slice_to_cstr(&token, &cstr) == AIDS_OK, "Failed to convert token to cstr");
    AIDS_ASSERT(strcmp(cstr, "cherry") == 0, "Expected 'cherry', got '%s'", cstr);
    AIDS_FREE(cstr);

    AIDS_ASSERT(aids_string_slice_tokenize(&input, ',', &token) == false, "Should return false when empty");

    // Test trim
    Aids_String_Slice whitespace = aids_string_slice_from_cstr("  hello  ");
    aids_string_slice_trim(&whitespace);
    AIDS_ASSERT(aids_string_slice_to_cstr(&whitespace, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "hello") == 0, "Expected 'hello', got '%s'", cstr);
    AIDS_FREE(cstr);

    // Test starts_with
    Aids_String_Slice text = aids_string_slice_from_cstr("Hello World");
    Aids_String_Slice prefix = aids_string_slice_from_cstr("Hello");
    AIDS_ASSERT(aids_string_slice_starts_with(&text, prefix) == true, "Should start with 'Hello'");
    
    prefix = aids_string_slice_from_cstr("World");
    AIDS_ASSERT(aids_string_slice_starts_with(&text, prefix) == false, "Should not start with 'World'");

    // Test ends_with
    Aids_String_Slice suffix = aids_string_slice_from_cstr("World");
    AIDS_ASSERT(aids_string_slice_ends_with(&text, suffix) == true, "Should end with 'World'");
    
    suffix = aids_string_slice_from_cstr("Hello");
    AIDS_ASSERT(aids_string_slice_ends_with(&text, suffix) == false, "Should not end with 'Hello'");

    // Test skip
    Aids_String_Slice skip_test = aids_string_slice_from_cstr("abcdef");
    aids_string_slice_skip(&skip_test, 3);
    AIDS_ASSERT(aids_string_slice_to_cstr(&skip_test, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "def") == 0, "Expected 'def', got '%s'", cstr);
    AIDS_FREE(cstr);

    // Test atol
    Aids_String_Slice number = aids_string_slice_from_cstr("12345");
    long value;
    AIDS_ASSERT(aids_string_slice_atol(&number, &value, 10) == true, "Failed to convert to long");
    AIDS_ASSERT(value == 12345, "Expected 12345, got %ld", value);

    // Test compare
    Aids_String_Slice s1 = aids_string_slice_from_cstr("apple");
    Aids_String_Slice s2 = aids_string_slice_from_cstr("banana");
    AIDS_ASSERT(aids_string_slice_compare(&s1, &s2) < 0, "apple should be < banana");
    AIDS_ASSERT(aids_string_slice_compare(&s2, &s1) > 0, "banana should be > apple");
    AIDS_ASSERT(aids_string_slice_compare(&s1, &s1) == 0, "apple should be == apple");

    // Test skip_while
    Aids_String_Slice skip_while_test = aids_string_slice_from_cstr("   hello");
    aids_string_slice_skip_while(&skip_while_test, isspace);
    AIDS_ASSERT(aids_string_slice_to_cstr(&skip_while_test, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "hello") == 0, "Expected 'hello', got '%s'", cstr);
    AIDS_FREE(cstr);

    skip_while_test = aids_string_slice_from_cstr("123abc");
    aids_string_slice_skip_while(&skip_while_test, isdigit);
    AIDS_ASSERT(aids_string_slice_to_cstr(&skip_while_test, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "abc") == 0, "Expected 'abc', got '%s'", cstr);
    AIDS_FREE(cstr);

    skip_while_test = aids_string_slice_from_cstr("abcABC123");
    aids_string_slice_skip_while(&skip_while_test, islower);
    AIDS_ASSERT(aids_string_slice_to_cstr(&skip_while_test, &cstr) == AIDS_OK, "Failed to convert to cstr");
    AIDS_ASSERT(strcmp(cstr, "ABC123") == 0, "Expected 'ABC123', got '%s'", cstr);
    AIDS_FREE(cstr);

    return_defer(0);

defer:
    return result;
}
