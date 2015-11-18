#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    ssize_t nr;
    size_t n = 0;
    char *buf;
    buf = NULL;
    printf("melisp > ");
    nr = getline(&buf, &n, stdin);
    while (nr > 0) {
        printf("you\'re %s", buf);
        free(buf);
        buf = NULL;
        printf("melisp > ");
        nr = getline(&buf, &n, stdin);
    }
    printf("\n");
    return 0;
}
