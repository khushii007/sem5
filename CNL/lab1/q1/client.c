#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

void encrypt(char *message) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        // Encrypt by adding 4 to the ASCII value of each character
        message[i] = message[i] + 4;
    }
}

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char message[1024];

    // Create TCP socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter the message to be encrypted: ");
    fgets(message, 1024, stdin);

    // Remove the newline character from the input
    message[strcspn(message, "\n")] = 0;

    // Encrypt the message
    encrypt(message);
    printf("Encrypted Message: %s\n", message);

    // Send the encrypted message to the server
    send(client_fd, message, strlen(message), 0);
    printf("Message sent to server.\n");

    return 0;
}
