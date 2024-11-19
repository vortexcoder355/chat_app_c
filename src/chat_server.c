#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for memset
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5147
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);  // Zero out the buffer
        
        // Receive message from client
        n = read(client_socket, buffer, sizeof(buffer)-1);
        if (n <= 0) {
            printf("Client disconnected or error occurred\n");
            break;
        }
        
        printf("Client: %s", buffer);
        
        // Send response to client
        memset(buffer, 0, BUFFER_SIZE);  // Zero out the buffer
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(client_socket, buffer, strlen(buffer));
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));  // Zero out the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    
    client_len = sizeof(client_addr);
    
    // Accept client connections
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0) {
        perror("Server accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");
    
    // Handle client communication
    handle_client(client_socket);
    
    // Close sockets
    close(client_socket);
    close(server_socket);
    return 0;
}
