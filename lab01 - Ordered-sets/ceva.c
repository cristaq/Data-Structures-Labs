#include <stdio.h>

struct test {struct test inner; };

int main() {
    struct test t;
    t.inner.i = 3;
}