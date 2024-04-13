#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define SERVER_ADDRESS "127.0.0.1" // Change this to the server's IP address
#define SERVER_PORT 55410
#define BUFFER_SIZE 8192

int main(void) {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE] = "Hello, server!"; // Message to send

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error initializing Winsock.\n");
        return 1;
    }

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error creating socket.\n");
        WSACleanup();
        return 1;
    }

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    // Send data to server
    if (sendto(clientSocket, buffer, strlen(buffer), 0,
               (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Error sending data.\n");
    } else {
        printf("Data sent successfully!\n");
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
