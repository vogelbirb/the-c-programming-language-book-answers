#include "syscalls.h"

int main(const int argc, const char **argv) {
    if (argc < 1) {
        return 1;
    }
    // Does not handle errors or idk
    unlink(argv[1]);
    return 0;
}