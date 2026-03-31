#include "shared.h"

int main() {
    int result = 0;

    // Test aids_io_getcwd
    Aids_String_Slice cwd = {0};
    AIDS_ASSERT(aids_io_getcwd(&cwd) == AIDS_OK, "Failed to get current working directory");
    AIDS_ASSERT(cwd.len > 0, "Current working directory should not be empty");
    char *cwd_cstr = NULL;
    AIDS_ASSERT(aids_string_slice_to_cstr(&cwd, &cwd_cstr) == AIDS_OK, "Failed to convert cwd to cstr");
    aids_log(AIDS_INFO, "Current working directory: %s", cwd_cstr);
    AIDS_FREE(cwd_cstr);

    // Test aids_io_mkdir (non-recursive)
    Aids_String_Slice test_dir = aids_string_slice_from_cstr("build/test_dir");
    AIDS_ASSERT(aids_io_mkdir(&test_dir, false) == AIDS_OK, "Failed to create test directory");
    AIDS_ASSERT(aids_io_isdir(&test_dir) == true, "Test directory should exist");

    // Test aids_io_mkdir (non-recursive for existing dir - should succeed with EEXIST)
    AIDS_ASSERT(aids_io_mkdir(&test_dir, false) == AIDS_OK, "Failed to handle existing directory");

    // Test aids_io_mkdir recursive with a path that makes sense
    // Create a unique test directory path
    Aids_String_Slice test_nested_dir = aids_string_slice_from_cstr("build/test_dir/nested");
    AIDS_ASSERT(aids_io_mkdir(&test_nested_dir, false) == AIDS_OK, "Failed to create nested directory");
    AIDS_ASSERT(aids_io_isdir(&test_nested_dir) == true, "Nested directory should exist");
    
    // Create another level
    Aids_String_Slice deeper_dir = aids_string_slice_from_cstr("build/test_dir/nested/deep");
    AIDS_ASSERT(aids_io_mkdir(&deeper_dir, false) == AIDS_OK, "Failed to create deeper nested directory");
    AIDS_ASSERT(aids_io_isdir(&deeper_dir) == true, "Deeper directory should exist");

    // Test aids_io_isdir with non-directory
    Aids_String_Slice not_a_dir = aids_string_slice_from_cstr("aids.h");
    AIDS_ASSERT(aids_io_isdir(&not_a_dir) == false, "File should not be detected as directory");

    // Test aids_io_listdir
    Aids_String_Slice tests_dir = aids_string_slice_from_cstr("tests");
    Aids_Array files = {0};
    aids_array_init(&files, sizeof(Aids_String_Slice));
    AIDS_ASSERT(aids_io_listdir(&tests_dir, &files) == AIDS_OK, "Failed to list directory");
    AIDS_ASSERT(files.count > 0, "Tests directory should contain files");

    // Check that we found some expected files
    boolean found_shared_h = false;
    boolean found_this_test = false;
    for (unsigned long i = 0; i < files.count; i++) {
        Aids_String_Slice *name = NULL;
        AIDS_ASSERT(aids_array_get(&files, i, (void **)&name) == AIDS_OK, "Failed to get file name");
        
        char *name_cstr = NULL;
        AIDS_ASSERT(aids_string_slice_to_cstr(name, &name_cstr) == AIDS_OK, "Failed to convert name to cstr");
        
        if (strcmp(name_cstr, "shared.h") == 0) {
            found_shared_h = true;
        }
        if (strcmp(name_cstr, "09_io.c") == 0) {
            found_this_test = true;
        }
        
        AIDS_FREE(name_cstr);
    }

    AIDS_ASSERT(found_shared_h == true, "Should find shared.h in tests directory");
    AIDS_ASSERT(found_this_test == true, "Should find 09_io.c in tests directory");

    // Clean up the array (note: the string slices inside are managed by aids_io_listdir)
    for (unsigned long i = 0; i < files.count; i++) {
        Aids_String_Slice *name = NULL;
        AIDS_ASSERT(aids_array_get(&files, i, (void **)&name) == AIDS_OK, "Failed to get file name");
        aids_string_builder_free((Aids_String_Builder *)&name->str);
    }
    aids_array_free(&files);

    // Test aids_io_isdir with nested directory
    Aids_String_Slice nested_check = aids_string_slice_from_cstr("build/test_dir/nested");
    AIDS_ASSERT(aids_io_isdir(&nested_check) == true, "Nested directory should exist");

    return_defer(0);

defer:
    return result;
}
