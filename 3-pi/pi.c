// Some googling to find the right way to handle this and here we are
// usage: compile the source, then call it like so `./pi <number>`
// e.g.: ./pi 42 <- will give you 3.(...42 digits)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[argc + 1]) {
    char* p;  // necessary for strtol -> RTFM
    // Converting the received argument (`string`) to `long` then casting it
    int const n = (int)strtol(argv[1], &p, 10);

    if (n > 49) {
        puts("Only the first 49 digits can be displayed.");
    }

    // For the example, let's say the user entered `14`

    // `sprintf` is basically like `printf`
    // except that it stores the resulting string in the first argument

    // Storing "%.14g"
    char foo[7];
    sprintf(foo, "%%.%dg", n + 1);

    // The `%.14g` is now replaced by 3.(...14 digits)
    // It's like doing `printf("%.14g", M_PI);` except that it works
    char bar[51];
    sprintf(bar, foo, M_PI);

    printf("%s", bar);

    return EXIT_SUCCESS;
}
