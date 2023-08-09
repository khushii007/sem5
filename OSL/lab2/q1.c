#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// Function to print access permissions in "ls -l" format
void print_permissions(mode_t mode) {
    // Determine and print file type and permissions for user, group, and others
    putchar((S_ISDIR(mode)) ? 'd' : '-');
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

// Function to emulate "ls -l" for a given directory
void ls_l(const char *dir_name) {
    // Open the directory
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    // Loop through each entry (file or subdirectory) in the directory
    while ((entry = readdir(dir)) != NULL) {
        struct stat stat_buf;
        char path[512];
        // Construct the full path of the current entry
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        // Retrieve file attributes using "stat" system call
        if (stat(path, &stat_buf) == -1) {
            perror("stat");
            continue;
        }

        // Print access permissions
        print_permissions(stat_buf.st_mode);
        // Print number of hard links to the file
        printf(" %ld ", (long) stat_buf.st_nlink);

        // Retrieve user and group names using "getpwuid" and "getgrgid"
        struct passwd *pw = getpwuid(stat_buf.st_uid);
        struct group *gr = getgrgid(stat_buf.st_gid);

        // Print user and group names
        printf("%s %s ", pw->pw_name, gr->gr_name);
        // Print file size
        printf("%5lld ", (long long) stat_buf.st_size);

        // Format and print modification time
        char time_str[80];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&stat_buf.st_mtime));
        printf("%s ", time_str);

        // Print file or directory name
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);
}

// Main function
int main() {
    // Call the ls_l function for the current directory
    ls_l(".");
    return 0;
}
