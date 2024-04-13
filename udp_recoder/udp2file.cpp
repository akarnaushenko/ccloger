#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define PORT 55410
#define BUFFER_SIZE 8192

int main(void) {
    WSADATA wsaData;
    SOCKET ListenSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    int receivedDataLen;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error initializing Winsock.\n");
        return 1;
    }

    // Create UDP socket
    ListenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ListenSocket == INVALID_SOCKET) {
        printf("Error creating socket.\n");
        WSACleanup();
        return 1;
    }

    // Bind the socket to the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(ListenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Error binding socket.\n");
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("UDP server listening on port %d...\n", PORT);

    while (1) {
        receivedDataLen = recvfrom(ListenSocket, buffer, BUFFER_SIZE, 0,
            (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (receivedDataLen > 0) {
            printf("Received %d bytes from %s:%d\n", receivedDataLen,
                inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
            // Process the received data as needed
            // ...
        }
    }

    closesocket(ListenSocket);
    WSACleanup();
    return 0;
}
