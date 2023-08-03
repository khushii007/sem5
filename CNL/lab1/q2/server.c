#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void removeDuplicates(char *sentence) {
    char words[100][100];
    int count[100] = {0};
    int numWords = 0;

    // Tokenize the sentence into words
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < numWords; i++) {
            if (strcmp(words[i], token) == 0) {
                count[i]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(words[numWords], token);
            count[numWords] = 1;
            numWords++;
        }

        token = strtok(NULL, " ");
    }

    // Create the resultant sentence by retaining only one occurrence of each word
    char result[1000] = "";
    for (int i = 0; i < numWords; i++) {
        if (count[i] == 1) {
            strcat(result, words[i]);
            strcat(result, " ");
        }
    }

    strcpy(sentence, result);
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to a specific address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive the sentence from the client
        valread = read(new_socket, buffer, 1024);
        buffer[valread] = '\0';

        // Check if the client wants to stop
        if (strcmp(buffer, "Stop") == 0) {
            printf("Client has terminated the session. Server is exiting.\n");
            break;
        }

        // Remove duplicate words and send the result back to the client
        removeDuplicates(buffer);
        send(new_socket, buffer, strlen(buffer), 0);
    }

    return 0;
}
