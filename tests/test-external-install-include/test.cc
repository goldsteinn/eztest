#include "eztest/eztest.h"

#include <malloc.h>

TEST(success, run_okay) {
    void * p = malloc(1);
    ASSERT_NE(p, nullptr);
    free(p);
}
