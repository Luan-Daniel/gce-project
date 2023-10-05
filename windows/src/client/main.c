#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        printf("socket failed: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set the broadcast option to true
    BOOL broadcast = TRUE;
    iResult = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast));
    if (iResult == SOCKET_ERROR) {
        printf("setsockopt failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send a broadcast message to all devices on the local network
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    iResult = sendto(sock, "Server Discovery Request", strlen("Server Discovery Request"), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR) {
        printf("sendto failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Wait for a response from the server
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    iResult = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (iResult == SOCKET_ERROR) {
        printf("recvfrom failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Extract the IP address and port number of the server from the response
    char* ip = inet_ntoa(clientAddr.sin_addr);
    int port = ntohs(clientAddr.sin_port);

    printf("Server IP address: %s\n", ip);
    printf("Server port number: %d\n", port);

    // Cleanup
    closesocket(sock);
    WSACleanup();

    return 0;
}