// This is a basic example of using the All In one DS (AIDS) library. The next
// generation ds.h library for C. It provides some basic utitlities like data
// strructures, string manipulation, and logging.
//
// Aids is a single header library that can be used in any C project. To start
// using aids, you need to define `AIDS_IMPLEMENTATION` before including the
// header file. You can also define `AIDS_STRIP_PREFIX` to avoid prefixing the
// functions and types with `aids_`. This is useful if you want to use the
// library in a project that already has similar names.
#define AIDS_STRIP_PREFIX
#define AIDS_IMPLEMENTATION
#include "../aids.h"

#include <stdlib.h>

// Now that we have aids included, we can use its features. For example,
// we can log messages using the `aids_log` function. This function takes a
// log level, a format string, and optional arguments.

static void say_hello(const char *name) {
    aids_log(AIDS_INFO, "Hello, %s!\n", name);
}

// Aids also provides a dynamic array implementation. You can use it to
// store and manipulate collections of data. Here is an example of how to
// use the dynamic array to store integers:

static void dynamic_array_example() {
    // We first need to initialize an Aids_Array structure.
    // We do this by calling `aids_array_init`, which takes a pointer to the
    // Aids_Array and the size of the items we want to store in the array.
    Aids_Array array = {0};
    aids_array_init(&array, sizeof(int));

    for (int i = 0; i < 10; i++) {
        // We can append items to the array using `aids_array_append`.
        // This function will allocate memory if needed and add the item to the end of the array.
        if (aids_array_append(&array, (unsigned char *)&i) != AIDS_OK) {

            // Aids provides a failure reason function that returns a string
            // describing the last error that occurred. We can use this to log errors.
            aids_log(AIDS_ERROR, "Failed to append item %d to array: %s", i, aids_failure_reason());
            exit(EXIT_FAILURE);
        }
    }

    for (unsigned long i = 0; i < array.count; i++) {
        int *item = NULL;

        // We can retrieve items from the array using `aids_array_get`.
        // This function will get the reference to the item at the specified index.
        if (aids_array_get(&array, i, (unsigned char **)&item) != AIDS_OK) {
            aids_log(AIDS_ERROR, "Failed to get item at index %lu: %s", i, aids_failure_reason());
            exit(EXIT_FAILURE);
        }
        aids_log(AIDS_INFO, "Item %lu: %d", i, *item);
    }

    aids_array_free(&array);
}

// Aids provides a simple way to handle strings using `Aids_String_Slice` and `Aids_String_Builder`.
// `Aids_String_Slice` is a structure that holds a pointer to a string and its length.
// `Aids_String_Builder` is a dynamic string builder that allows you to append formatted strings and slices.

static void string_example() {
    Aids_String_Builder sb = {0};
    aids_string_builder_init(&sb);

    // Append a formatted string to the string builder.
    if (aids_string_builder_append(&sb, "Hello, %s!", "Aids") != AIDS_OK) {
        aids_log(AIDS_ERROR, "Failed to append to string builder: %s", aids_failure_reason());
        exit(EXIT_FAILURE);
    }

    // Convert the string builder to a string slice.
    // This will not allocate memory, it will just point to the internal buffer.
    Aids_String_Slice slice = {0};
    aids_string_builder_to_slice(&sb, &slice);

    // Log the resulting string slice using the `%.*s` format specifier.
    aids_log(AIDS_INFO, "String Builder Result: %.*s", (int)slice.len, slice.str);

    // Free the string builder.
    aids_string_builder_free(&sb);
}

int main() {

    say_hello("World");
    dynamic_array_example();
    string_example();

    return 0;
}
