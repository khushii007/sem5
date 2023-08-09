#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

// Function to list all files in a directory and its subdirectories
void list_files_recursive(const char *dir_name) {
    // Open the directory
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir"); // Print an error message if directory cannot be opened
        return;
    }

    struct dirent *entry;
    // Loop through each entry (file or subdirectory) in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip these special entries
        }

        // Construct the full path of the current entry
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        struct stat stat_buf;
        // Retrieve file attributes using "stat" system call
        if (stat(path, &stat_buf) == -1) {
            perror("stat"); // Print an error message if file attributes cannot be retrieved
            continue;
        }

        // Check if the entry is a directory
        if (S_ISDIR(stat_buf.st_mode)) {
            // Recursively list files in the subdirectory
            list_files_recursive(path);
        } else {
            // Print the file path if it's not a directory
            printf("%s\n", path);
        }
    }

    // Close the directory
    closedir(dir);
}

// Main function
int main() {
    // Call the list_files_recursive function to start listing files from the current directory
    list_files_recursive(".");
    return 0;
}
