#include "shared.h"

int main() {
    int result = 0;

    return_defer(1);
    result = 2;

defer:
    AIDS_ASSERT(result == 1, "Expected result to be 1, but got %d", result);
    return 0;
}
