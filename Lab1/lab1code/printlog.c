#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;  // reset errno before conversion
    double x = strtod(argv[1], &endptr);

    // Check for conversion errors
    if (errno != 0) {
        perror("Error converting input to number");
        return 1;
    }

    // Check for invalid input (no digits found or leftover characters)
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: '%s' is not a valid number\n", argv[1]);
        return 1;
    }

    // Check domain for log (x > 0)
    if (x <= 0.0) {
        fprintf(stderr, "Math error: log(x) is undefined for x <= 0 (you entered %f)\n", x);
        return 1;
    }

    double result = log(x);
    printf("log(%g) = %.10f\n", x, result);

    return 0;
}
