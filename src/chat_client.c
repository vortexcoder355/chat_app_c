#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For memset
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5147
#define BUFFER_SIZE 1024

// Custom secure memory clear function (similar to memset_s)
int secure_memset(void *ptr, size_t size, int value) {
    if (ptr == NULL || size == 0) {
        return -1;  // Return an error if invalid parameters
    }
    memset(ptr, value, size);  // Use memset to clear memory
    return 0;  // Success
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set up server address
    secure_memset(&server_addr, sizeof(server_addr), 0);  // Securely zero the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server address (localhost)
    
    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Connected to server. You can start chatting!\n");
    
    while (1) {
        secure_memset(buffer, BUFFER_SIZE, 0);  // Securely zero out the buffer
        
        // Read input from user
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        // Send message to server
        write(sockfd, buffer, strlen(buffer));
        
        // Receive message from server
        secure_memset(buffer, BUFFER_SIZE, 0);  // Securely zero out the buffer
        read(sockfd, buffer, sizeof(buffer)-1);
        printf("Server: %s", buffer);
        
        // Exit the loop if the client types 'exit'
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Exiting chat...\n");
            break;
        }
    }
    
    // Close the socket
    close(sockfd);
    return 0;
}
