
#include "libmath.h"
int main() {
    long long res;
    Status status = addition(5, 4, res);
    (void)status; // Suppress unused variable warning
    (void)res;    // Suppress unused variable warning
    return 0;
}
