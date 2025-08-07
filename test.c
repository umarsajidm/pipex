#include <stdio.h>

int main() {
    int x = -1;

    if (x < 0) {
        fprintf(2, "Error: x cannot be negative!\n");
    }

    return 0;
}
