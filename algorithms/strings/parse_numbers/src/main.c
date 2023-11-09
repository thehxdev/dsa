#include <stdio.h>
#include <assert.h>
#include "parseInt.h"

int main(void) {
    assert(1234 == parseInt("abc1234de"));
    assert(1234 == parseInt("1234de"));
    assert(1234 == parseInt("abc1234"));
    assert(1234 == parseInt("1234"));
    assert(84 == parseInt("foo84BAR32"));
    assert(2 == parseInt("2"));
    assert(0 == parseInt("foobar"));

    printf("[OK] All tests are PASSED!\n");
    return 0;
}
