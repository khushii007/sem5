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

    // Create a new hard link
    if (link(oldPath, newLinkPath) == -1) {
        perror("link");
        return 1;
    }

    printf("Created a new hard link: %s -> %s\n", newLinkPath, oldPath);

    // Unlink the new hard link
    if (unlink(newLinkPath) == -1) {
        perror("unlink");
        return 1;
    }

    printf("Unlinked the new hard link: %s\n", newLinkPath);

    return 0;
}
