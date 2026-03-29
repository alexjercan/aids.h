#include "shared.h"

static int compare_strings(const void *a, const void *b) {
    const Aids_String_Slice *ss_a = (const Aids_String_Slice *)a;
    const Aids_String_Slice *ss_b = (const Aids_String_Slice *)b;

    size_t min_len = (ss_a->len < ss_b->len) ? ss_a->len : ss_b->len;
    int cmp = memcmp(ss_a->str, ss_b->str, min_len);
    if (cmp != 0) {
        return cmp;
    }

    if (ss_a->len < ss_b->len) {
        return -1;
    } else if (ss_a->len > ss_b->len) {
        return 1;
    } else {
        return 0;
    }
}

static unsigned long hash_string(const void *key) {
    const Aids_String_Slice *ss = (const Aids_String_Slice *)key;
    unsigned long hash = 5381;
    for (unsigned long i = 0; i < ss->len; i++) {
        hash = ((hash << 5) + hash) + ss->str[i];
    }
    return (hash % 1024);
}

int main() {
    int result = 0;
    Aids_Hash_Map hm = {0};
    aids_hash_map_init(&hm, hash_string, compare_strings);

    // Test insert
    Aids_String_Slice key1 = aids_string_slice_from_cstr("key1");
    Aids_String_Slice value1 = aids_string_slice_from_cstr("value1");
    Aids_String_Slice key2 = aids_string_slice_from_cstr("key2");
    Aids_String_Slice value2 = aids_string_slice_from_cstr("value2");
    Aids_String_Slice key3 = aids_string_slice_from_cstr("key3");
    Aids_String_Slice value3 = aids_string_slice_from_cstr("value3");
    AIDS_ASSERT(aids_hash_map_insert(&hm, &key1, &value1) == AIDS_OK, "Failed to insert key1");
    AIDS_ASSERT(aids_hash_map_insert(&hm, &key2, &value2) == AIDS_OK, "Failed to insert key2");
    AIDS_ASSERT(aids_hash_map_insert(&hm, &key3, &value3) == AIDS_OK, "Failed to insert key3");

    // Test get
    void *retrieved_value = NULL;
    AIDS_ASSERT(aids_hash_map_get(&hm, &key1, &retrieved_value) == AIDS_OK, "Failed to get value for key1");
    Aids_String_Slice *retrieved_value_ss = (Aids_String_Slice *)retrieved_value;
    AIDS_ASSERT(aids_string_slice_compare(retrieved_value_ss, &value1) == 0, "Expected value1 for key1, got " SS_Fmt, SS_Arg(*retrieved_value_ss));

    AIDS_ASSERT(aids_hash_map_get(&hm, &key2, &retrieved_value) == AIDS_OK, "Failed to get value for key2");
    retrieved_value_ss = (Aids_String_Slice *)retrieved_value;
    AIDS_ASSERT(aids_string_slice_compare(retrieved_value_ss, &value2) == 0, "Expected value2 for key2, got " SS_Fmt, SS_Arg(*retrieved_value_ss));

    AIDS_ASSERT(aids_hash_map_get(&hm, &key3, &retrieved_value) == AIDS_OK, "Failed to get value for key3");
    retrieved_value_ss = (Aids_String_Slice *)retrieved_value;
    AIDS_ASSERT(aids_string_slice_compare(retrieved_value_ss, &value3) == 0, "Expected value3 for key3, got " SS_Fmt, SS_Arg(*retrieved_value_ss));

    // Test get for non-existent key
    Aids_String_Slice key4 = aids_string_slice_from_cstr("key4");
    AIDS_ASSERT(aids_hash_map_get(&hm, &key4, &retrieved_value) == AIDS_ERR, "Should fail to get value for non-existent key4");

    // Test remove
    AIDS_ASSERT(aids_hash_map_remove(&hm, &key1) == AIDS_OK, "Failed to remove key1");
    AIDS_ASSERT(aids_hash_map_get(&hm, &key1, &retrieved_value) == AIDS_ERR, "Should fail to get value for removed key1");

    // Test iterator
    Aids_Hash_Map_Iterator it;
    aids_hash_map_iterator_init(&it, &hm);
    void *key, *value;
    int found_key2 = 0;
    int found_key3 = 0;
    while (aids_hash_map_iterator_next(&it, &key, &value)) {
        Aids_String_Slice *key_ss = (Aids_String_Slice *)key;
        Aids_String_Slice *value_ss = (Aids_String_Slice *)value;

        if (aids_string_slice_compare(key_ss, &key2) == 0) {
            AIDS_ASSERT(aids_string_slice_compare(value_ss, &value2) == 0, "Expected value2 for key2, got " SS_Fmt, SS_Arg(*value_ss));
            found_key2 = 1;
        } else if (aids_string_slice_compare(key_ss, &key3) == 0) {
            AIDS_ASSERT(aids_string_slice_compare(value_ss, &value3) == 0, "Expected value3 for key3, got " SS_Fmt, SS_Arg(*value_ss));
            found_key3 = 1;
        } else {
            AIDS_ASSERT(false, "Unexpected key in hash map: " SS_Fmt, SS_Arg(*key_ss));
        }
    }
    AIDS_ASSERT(found_key2, "Did not find key2 in hash map iterator");
    AIDS_ASSERT(found_key3, "Did not find key3 in hash map iterator");

    return_defer(0);

defer:
    aids_hash_map_free(&hm);

    return result;
}
