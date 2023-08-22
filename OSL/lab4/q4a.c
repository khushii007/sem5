#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *oldPath = argv[1];
    char newLinkPath[256]; // Modify this size accordingly.

    // Create a symbolic (soft) link
    if (symlink(oldPath, newLinkPath) == -1) {
        perror("symlink");
        return 1;
    }

    printf("Created a new symbolic link: %s -> %s\n", newLinkPath, oldPath);

    // Unlink (remove) the symbolic link
    if (unlink(newLinkPath) == -1) {
        perror("unlink");
        return 1;
    }

    printf("Unlinked the new symbolic link: %s\n", newLinkPath);

    return 0;
}
