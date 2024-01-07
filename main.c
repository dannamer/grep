#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "e:")) != -1) {
        switch (opt) {
            case 'e':
                printf("Option -e with value: %s\n", optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-e value]\n", argv[0]);
                return 1;
        }
    }
    return 0;
}